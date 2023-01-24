#include "../inc/main.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("usage: ./uchat_server [port]\n");
        return 0;
    }

    sqlite3 *database = open_database();
    create_users_table(database);
    close_database(database);

    int listening_socket = create_socket();
    bind_socket(listening_socket, atoi(argv[1]));
    listen_socket(listening_socket, 5);

    create_default_thread(accept_requests_thread, &listening_socket);

    printf("Server is listening for user requests.\n");

    while (true)
    {
        printf("\nEnter a command (exit): ");
        char user_command[1024];
        scanf("%s", user_command);

        if (strcmp(user_command, "exit") == 0) {
            sqlite3_close(database);
            close(listening_socket);
            exit(EXIT_FAILURE);
        }
    }
    
    return 0;
}

