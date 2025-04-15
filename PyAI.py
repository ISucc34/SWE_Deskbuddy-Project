from langchain_ollama import OllamaLLM
from langchain.prompts import ChatPromptTemplate



template = """



Answer the question below.

Here is the conversation history:
{history}
Question:
{question}
Answer:

"""

def handle_conversation():
    context = ""
    print()
    while True:
        User_input = input("You: ")
        if User_input.lower() in ["exit", "quit"]:
            break

        result = chain.invoke({"history":context, "question":User_input})
        print("Bot: ", result)
        context += f"\nYou: {User_input}\nBot: {result}\n"

model = OllamaLLM(model="llama3.1")
prompt = ChatPromptTemplate.from_template(template)
chain = prompt | model

if __name__ == "__main__":
    handle_conversation()





