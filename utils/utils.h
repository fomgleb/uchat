#pragma once 

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <netdb.h>
#include <fcntl.h>  
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include "../resources/libraries/libmx/inc/libmx.h"

#define MAX_LOGIN_LENGTH 40
#define MAX_PASSWORD_LENGTH 50
#define MAX_CHAT_NAME_LENGTH 30

typedef struct s_address {
    char *ip;
    int port;
} t_address;

typedef struct s_authentication_data {
    char *login;
    char *password;
} t_authentication_data;

typedef struct s_chat_creation_data {
    char *chat_name;
    char *owner_login;
} t_chat_creation_data;

typedef enum e_request {
    LOGIN, // -> login -> password
    REGISTER, // -> login -> password
    CREATE_CHAT, // -> chat_name -> owner_login
    ADD_MEMBER_TO_CHAT // -> chat_id -> member_login
} t_request;

typedef enum e_state_code {
    NONE,

    SUCCESSFULLY_READ,
    SUCCESSFUL_REGISTRATION,
    SUCCESSFUL_LOGIN,
    CHAT_CREATED_SUCCESSFULLY,
    
    SUCH_LOGIN_ALREADY_EXISTS,
    SUCH_LOGIN_DOES_NOT_EXIST,
    WRONG_PASSWORD
} t_state_code;

unsigned char recieve_unsigned_char(int socket);
uint16_t recieve_unsigned_short(int socket);
uint32_t recieve_unsigned_int(int socket);
char *recieve_string(int socket, int max_string_length);

void send_unsigned_char(int socket, unsigned char character);
void send_unsigned_short(int socket, uint16_t number);
void send_unsigned_int(int socket, uint32_t number);
void send_string(int socket, char *string);

pthread_t create_default_thread(void *(*func)(void *), void *arg);
void create_detached_thread(void *(*func)(void *), void *arg);
void join_thread(pthread_t thread, void **thread_return);
void cancel_thread(pthread_t thread);

int create_socket();
void bind_socket(int socket, unsigned int port);
void listen_socket(int socket, int queue_len);
int accept_socket(int this_socket);
void *read_socket(int socket, unsigned int max_read_bytes, int *read_bytes_count);
void connect_socket(int socket, char *ip, unsigned int port);

void free_authentication_data(t_authentication_data authentication_data);
void free_chat_creation_data(t_chat_creation_data chat_data);
