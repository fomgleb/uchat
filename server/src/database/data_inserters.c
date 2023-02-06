#include "../../server.h"

int db_create_user(char *login, char *password) {
    if (db_users_table_has_login(login)) {
        return -1;
    }

    sqlite3 *database = db_open();

    char *sql_command;
    asprintf(&sql_command, "INSERT INTO "USERS_TABLE" ("USERS_LOGIN", "USERS_PASSWORD") \
                            VALUES ('%s', '%s');", login, password
    );
    db_execute_sql(database, sql_command);
    free(sql_command);

    sqlite3_int64 last_insert_rowid = sqlite3_last_insert_rowid(database);
    asprintf(&sql_command, "SELECT "USERS_ID" FROM "USERS_TABLE" \
                            WHERE rowid = %llu;", last_insert_rowid
    );
    sqlite3_stmt *statement = db_open_statement(database, sql_command);
    sqlite3_step(statement);
    int created_user_id = sqlite3_column_int(statement, 0);

    free(sql_command);
    db_close_statement_and_database(statement, database);

    return created_user_id;
}

int db_create_chat(char *chat_name, int owner_id) {
    char *sql_command = NULL;
    asprintf(&sql_command, "INSERT INTO "CHATS_TABLE" ("CHATS_NAME", "CHATS_USER_ID") \
                            VALUES ('%s', '%d');", chat_name, owner_id
    );

    sqlite3 *database = db_open();

    db_execute_sql(database, sql_command);
    free(sql_command);

    sqlite3_int64 last_insert_rowid = sqlite3_last_insert_rowid(database);
    asprintf(&sql_command, "SELECT "CHATS_ID" FROM "CHATS_TABLE" \
                            WHERE rowid = %llu;", last_insert_rowid
    );
    sqlite3_stmt *statement = db_open_statement(database, sql_command);
    sqlite3_step(statement);
    int created_chat_id = sqlite3_column_int(statement, 0);
    
    free(sql_command);
    db_close_statement_and_database(statement, database);

    return created_chat_id;
}

bool db_add_new_member_to_chat(int user_id, int chat_id) {
    if (db_user_is_in_chat(user_id, chat_id)) {
        return false;
    }

    char *sql_command = NULL;
    asprintf(&sql_command, "INSERT INTO "MEMBERS_TABLE" ("MEMBERS_CHAT_ID", "MEMBERS_USER_ID") \
                            VALUES (%d, %d)", chat_id, user_id
    );

    db_open_and_execute_sql(sql_command);

    free(sql_command);

    return true;
}

void db_add_text_message(uint32_t chat_id, uint32_t user_id, char *text_message) {
    char *sql_command = NULL;
    asprintf(&sql_command, "INSERT INTO "MESSAGES_TABLE" ("MESSAGES_CHAT_ID", "MESSAGES_USER_ID", "MESSAGES_CONTENT", "MESSAGES_CREATION_DATE") \
                            VALUES (%d, %d, '%s', 'implement later')", chat_id, user_id, text_message);
    db_open_and_execute_sql(sql_command);
    free(sql_command);
}

