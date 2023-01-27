#include "../client.h"

void handle_user_commands(t_address server_address) {
    printf("\nEnter a command (newchat): ");
    char user_command[100];
    scanf("%s", user_command);

    if (strcmp(user_command, "newchat") == 0) {
        t_chat_data chat_data = get_chat_data();
        t_state_code creating_chat_result = create_chat(chat_data, server_address);
        if (creating_chat_result == CHAT_CREATED_SUCCESSFULLY) {
            printf("Chat \"%s\" created successfully.", chat_data.name);
        }
        free_chat_data(chat_data);
    }
}

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("usage: ./uchat [ip] [port]");
        return 0;
    }

    t_address server_address = {argv[1], atoi(argv[2])};

    while (true)
    {
        printf("\nEnter a command (login, register, exit): ");
        char user_command_str[1024];
        scanf("%s", user_command_str);

        if (strcmp(user_command_str, "login") == 0) {
            t_authentication_data authentication_data = get_authentication_data();
            t_state_code login_result = authenticate_user(authentication_data, LOGIN_MODE, server_address);
            if (login_result == SUCCESSFUL_LOGIN) {
                printf("Successful login.\n");
            } else if (login_result == SUCH_LOGIN_DOES_NOT_EXIST) {
                printf("Such login does not exist.\n");
            } else if (login_result == WRONG_PASSWORD) {
                printf("Wrong password.\n");
            }
            free_authentication_data(authentication_data);
        } else if (strcmp(user_command_str, "register") == 0) {
            t_authentication_data authentication_data = get_authentication_data();
            t_state_code registration_result = authenticate_user(authentication_data, REGISTER_MODE, server_address);
            if (registration_result == SUCCESSFUL_REGISTRATION) {
                printf("Successful registration.\n");
            } else if (registration_result == SUCH_LOGIN_ALREADY_EXISTS) {
                printf("Such login already exists.\n");
            }
            free_authentication_data(authentication_data);
        } else if (strcmp(user_command_str, "exit") == 0) {
            return 0;
        }
    }

    return 0;
}

