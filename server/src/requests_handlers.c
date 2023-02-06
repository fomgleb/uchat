#include "../server.h"

void handle_registration(int client_socket) {
    t_authentication_data authentication_data = receive_authentication_data(client_socket);
    int user_id = db_create_user(authentication_data.login, authentication_data.password);

    if (user_id != -1) {
        send_unsigned_char(client_socket, SUCCESSFUL_REGISTRATION);
        send_unsigned_int(client_socket, user_id);
    } else {
        send_unsigned_char(client_socket, SUCH_LOGIN_ALREADY_EXISTS);
    }

    free_authentication_data(authentication_data);
}

void handle_login(int client_socket) {
    t_authentication_data authentication_data = receive_authentication_data(client_socket);
    int user_id = db_get_user_id_by_login(authentication_data.login);
    char *found_password = db_get_password_by_id(user_id);
    if (found_password != NULL) {
        if (strcmp(authentication_data.password, found_password) == 0) {
            send_unsigned_char(client_socket, SUCCESSFUL_LOGIN);
            send_unsigned_int(client_socket, user_id);
        } else {
            send_unsigned_char(client_socket, WRONG_PASSWORD);
        }
    } else {
        send_unsigned_char(client_socket, SUCH_LOGIN_DOES_NOT_EXIST);
    }

    free(found_password);
    free_authentication_data(authentication_data);
}

void handle_chat_creation(int client_socket) {
    t_chat_creation_data chat_creation_data = receive_chat_creation_data(client_socket);
    int created_chat_id = db_create_chat(chat_creation_data.chat_name, chat_creation_data.owner_id);
    db_add_new_member_to_chat(chat_creation_data.owner_id, created_chat_id);

    send_unsigned_char(client_socket, CHAT_CREATED_SUCCESSFULLY);

    free_chat_creation_data(chat_creation_data);
}

void handle_getting_chats(int client_socket) {
    int user_id = receive_unsigned_int(client_socket);

    size_t number_of_chats = 0;
    t_chat *chats = db_get_chats_user_is_in(user_id, &number_of_chats);

    if (number_of_chats > 0) {
        send_unsigned_char(client_socket, START_OF_CHATS_ARRAY);
    } else {
        send_unsigned_char(client_socket, END_OF_CHATS_ARRAY);
    }
    for (size_t i = 0; i < number_of_chats; i++) {
        send_chat(client_socket, chats[i]);
        if (i + 1 == number_of_chats) {
            send_unsigned_char(client_socket, END_OF_CHATS_ARRAY);
        } else {
            send_unsigned_char(client_socket, CONTINUATION_OF_CHATS_ARRAY);
        }
    }

    send_unsigned_char(client_socket, CHATS_ARRAY_TRENSFERRED_SUCCESSFULLY);

    free_chats(chats, number_of_chats);
}

void handle_adding_new_member_to_chat(int client_socket) {
    t_new_chat_member_data new_chat_memeber_data = receive_new_chat_memeber_data(client_socket);
    int user_id = db_get_user_id_by_login(new_chat_memeber_data.member_login);

    if (db_add_new_member_to_chat(user_id, new_chat_memeber_data.chat_id)) {
        send_unsigned_char(client_socket, USER_SUCCESSFULLY_ADDED_TO_CHAT);
    } else {
        send_unsigned_char(client_socket, SUCH_USER_IS_ALREADY_IN_CHAT);
    }

    free_new_chat_member_data(new_chat_memeber_data);
}

void handle_text_message_sending(int client_socket) {
    uint32_t user_id = receive_unsigned_int(client_socket);
    uint32_t chat_id = receive_unsigned_int(client_socket);
    char *text_message = receive_string(client_socket);
    db_add_text_message(chat_id, user_id, text_message);
    send_unsigned_char(client_socket, TEXT_MESSAGE_SENT_SUCCESSFULLY);
}

void handle_last_messages_getting(int client_socket) {
    uint16_t messages_count = receive_unsigned_short(client_socket);
    uint32_t chat_id = receive_unsigned_int(client_socket);

    size_t number_of_found = 0;
    t_message *last_messages = db_get_last_messages(chat_id, messages_count, &number_of_found);

    send_unsigned_short(client_socket, number_of_found);
    for (size_t i = 0; i < number_of_found; i++) {
        send_unsigned_int(client_socket, last_messages[i].user_id);
        send_string(client_socket, last_messages[i].bytes);
    }

    free_messages_array(last_messages, number_of_found);
}

