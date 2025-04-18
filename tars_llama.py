import ollama
import serial
import re

def extract_single_word(response):
    """
    Extract a single meaningful word from the response, avoiding trivial words.
    Args:
        response (str): The full response from LLaMA.
    Returns:
        str: A single word, or 'Error' if none found.
    """
    words = re.findall(r'\b\w+\b', response.lower())
    stopwords = {'a', 'an', 'the', 'is', 'are', 'was', 'were', 'to', 'and', 'or', 'in', 'on', 'at'}
    for word in words:
        if word not in stopwords and len(word) > 2:
            return word
    return "Error"

def generate_response(user_input):
    """
    Generate a response and extract a single word.
    Args:
        user_input (str): User's input prompt.
    Returns:
        str: A single word from the response.
    """
    try:
        response = ollama.generate(
            model="llama3",
            prompt=user_input,
            options={"temperature": 0.7, "max_tokens": 50}
        )
        return extract_single_word(response["response"])
    except Exception as e:
        return "Error"

def main():
    arduino = serial.Serial('/dev/cu.usbserial-10', 9600, timeout=1)  # Adjust to your port
    print("TARS with Ollama LLaMA is online! Type a prompt (type 'exit' to stop).")

    while True:
        user_input = input("You: ")
        if user_input.lower() == "exit":
            print("TARS: Shutting down.")
            arduino.write(b"exit\n")
            break
        word = generate_response(user_input)
        print(f"TARS LCD Output: {word}")
        arduino.write(word.encode() + b"\n")

if __name__ == "__main__":
    main()