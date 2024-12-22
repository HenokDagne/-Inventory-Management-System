from main import get_chat

def main():
    while True:
        try:
            user_input = input("What do you want to do: ")
        except KeyboardInterrupt:
            print("\nExiting...")
            break
        else:
            chat = get_chat(user_input)
            print(chat)
            choice = input("Do you want to continue chatting with the bot [y/n]: ")
            if choice.lower() != "y":
                break

if __name__ == "__main__":
    main()
