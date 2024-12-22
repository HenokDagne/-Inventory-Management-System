def worK_chatbot(response, user_input):

    user_input = user_input.lower()
    for key in response:
        if key in user_input:
            return response[key]
        else:
            return response["default"]
    return response["default"]







