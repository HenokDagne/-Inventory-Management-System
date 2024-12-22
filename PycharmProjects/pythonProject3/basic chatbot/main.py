from workChatbot import worK_chatbot
def get_chat(user_input):
    respond = {
        "hello": "Hi there! How can I help you today?",
        "how are you": "I am great and how are you?",
        "bye": "goodbye  you",
        "default": "I am sorry,I don't understand please rephrase here "
    }

    answer = worK_chatbot(respond, user_input)
    print(answer)

