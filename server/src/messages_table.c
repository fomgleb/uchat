#include "../inc/database.h"

char *get_current_date(sqlite3 *database) {
    char *get_time_command = "SELECT date() AS date";
    sqlite3_stmt *statement;

    if (sqlite3_prepare_v2(database, get_time_command, -1, &statement, 0) != SQLITE_OK) {
        printf("sqlite3_prepare_v2 error: %s\n", sqlite3_errmsg(database));
        sqlite3_close(database);
        exit(EXIT_FAILURE);
    }

    sqlite3_step(statement);

    return (char *)sqlite3_column_text(statement, 0);
}

void create_messages_table(sqlite3 *database) {
    char sql_command[SQLITE_COMMAND_SIZE];

    sprintf(sql_command, "CREATE TABLE IF NOT EXISTS %s ( \
        %s INTEGER PRIMARY KEY AUTOINCREMENT, \
        %s INTEGER, \
        %s INTEGER, \
        %s BLOB NOT NULL DEFAULT ' ', \
        %s TEXT NOT NULL, \
        FOREIGN KEY (%s) REFERENCES %s (%s), \
        FOREIGN KEY (%s) REFERENCES %s (%s), \
        FOREIGN KEY (%s) REFERENCES %s (%s), \
        FOREIGN KEY (%s) REFERENCES %s (%s));",
        
        MESSAGES_TABLE_NAME,

        MESSAGES_ID_NAME,
        MESSAGES_CHAT_ID_NAME,
        MESSAGES_USER_ID_NAME,
        MESSAGES_CONTEXT_NAME,
        MESSAGES_DATE_NAME,

        MESSAGES_CHAT_ID_NAME, 
        PARTY_TABLE_NAME,
        PARTY_CHAT_ID_NAME,

        MESSAGES_USER_ID_NAME,
        PARTY_TABLE_NAME,
        PARTY_USER_ID_NAME,

        MESSAGES_ID_NAME,
        MESSAGES_STATUSES_TABLE_NAME,
        MESSAGES_STATUSES_MESSAGES_ID_NAME,

        MESSAGES_USER_ID_NAME,
        MESSAGES_STATUSES_TABLE_NAME,
        MESSAGES_STATUSES_USER_ID_NAME
    );
    
    if (sqlite3_exec(database, sql_command, NULL, NULL, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to create/open messages table.\n");
        sqlite3_close(database);
        exit(EXIT_FAILURE);
    } 
}