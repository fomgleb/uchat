#include "../server.h"

t_authentication_data recieve_authentication_data(int client_socket) {
    char *login = recieve_string(client_socket, MAX_LOGIN_LENGTH);
    send_unsigned_char(client_socket, SUCCESSFULLY_READ);

    char *password = recieve_string(client_socket, MAX_PASSWORD_LENGTH);
    send_unsigned_char(client_socket, SUCCESSFULLY_READ);

    t_authentication_data authentication_data = {login, password};
    return authentication_data;
}

t_chat_creation_data recieve_chat_creation_data(int client_socket) {
    char *chat_name = recieve_string(client_socket, MAX_CHAT_NAME_LENGTH);
    send_unsigned_char(client_socket, SUCCESSFULLY_READ);

    char *owner_login = recieve_string(client_socket, MAX_LOGIN_LENGTH);
    send_unsigned_char(client_socket, SUCCESSFULLY_READ);

    t_chat_creation_data chat_cration_data = {chat_name, owner_login};
    return chat_cration_data;
}

