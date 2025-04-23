import ollama
import serial
import re
import time

def generate_response(user_input):
    """
    Prompt LLaMA to generate a condensed response (max 160 chars) and split into chunks of max 16 chars.
    Args:
        user_input (str): User's input prompt.
    Returns:
        list: List of chunks (each ≤16 chars, breaking at word boundaries).
    """
    try:
        # Craft a prompt that instructs LLaMA to condense the response
        prompt = (
            f"{user_input}\n\n"
            "Respond in a concise, meaningful way. Your response must be a complete thought, "
            "no longer than 160 characters (including spaces), and should be easily split into "
            "chunks of up to 16 characters each, breaking at word boundaries. Avoid filler phrases "
            "like 'what an interesting question' and ensure clarity. For example, if the prompt is "
            "'Tell me about the Ming Dynasty', respond with something like 'Ming: 1368-1644, Great Wall built, art flourished, trade grew.'"
        )
        response = ollama.generate(
            model="llama3",
            prompt=prompt,
            options={"temperature": 0.7, "max_tokens": 100}  # Increased to allow longer response
        )
        full_response = response["response"].strip()

        # Ensure the response is ≤160 chars (in case LLaMA doesn't fully comply)
        if len(full_response) > 160:
            words = full_response.split()
            trimmed = ""
            for word in words:
                if len(trimmed) + len(word) + 1 <= 160:
                    trimmed += (word + " ") if trimmed else word
                else:
                    break
            full_response = trimmed.strip()

        # Split into chunks of ≤16 chars, breaking at word boundaries
        chunks = []
        current_chunk = ""
        words = full_response.split()
        for word in words:
            space_to_add = 1 if current_chunk else 0
            if len(current_chunk) + len(word) + space_to_add <= 16:
                if current_chunk:
                    current_chunk += " " + word
                else:
                    current_chunk = word
            else:
                if current_chunk:
                    chunks.append(current_chunk)
                    current_chunk = word
                if len(chunks) == 10:  # Max 10 refreshes
                    break
        if current_chunk and len(chunks) < 10:
            chunks.append(current_chunk)

        return chunks if chunks else ["Error"]
    except Exception as e:
        return ["Error"]

def main():
    arduino = serial.Serial('/dev/cu.usbserial-10', 9600, timeout=1)  # Adjust to your port
    print("TARS with Ollama LLaMA is online! Type a prompt (type 'exit' to stop).")

    while True:
        user_input = input("You: ")
        if user_input.lower() == "exit":
            print("TARS: Shutting down.")
            arduino.write(b"exit\n")
            break
        chunks = generate_response(user_input)
        print("TARS LCD Output (sequential):", " | ".join(chunks))
        for chunk in chunks:
            arduino.write(chunk.encode() + b"\n")
            time.sleep(2)  # Delay to allow LCD to display each chunk

if __name__ == "__main__":
    main()