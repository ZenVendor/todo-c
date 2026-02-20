#include "db.h"

int DBCreate(sqlite3 *DB) {

    char *query = "CREATE TABLE IF NOT EXISTS Tasks ("
                  "Id INTEGER PRIMARY KEY,"
                  "Description NCHAR(100) NOT NULL,"
                  "IsDeleted INTEGER NOT NULL DEFAULT 0,"
                  "CreatedAt INTEGER NOT NULL DEFAULT CURRENT_DATE,"
                  "UpdatedAt INTEGER NOT NULL DEFAULT CURRENT_DATE,"
                  "DeletedAt INTEGER NOT NULL DEFAULT CURRENT_DATE);";
 
    char *err_msg;
    if (sqlite3_exec(DB, query, 0, 0, &err_msg) != SQLITE_OK) {
        fprintf(stderr, "Cannot create database: %s\n", err_msg);
        return 1;
    }
    fprintf(stdout, "Database 'Tasks' created\n");
    return 0;   
}

int DBAddTask(sqlite3 *DB, char *description) {

    char *query = "INSERT INTO Tasks (Description) VALUES (?);";
    sqlite3_stmt *stmt;
    int ok;

    ok = sqlite3_prepare_v2(DB, query, -1, &stmt, 0);
    if (ok != SQLITE_OK) {
        fprintf(stderr, "Cannot add task: %s\n", sqlite3_errmsg(DB));
        sqlite3_finalize(stmt);
        return 1;
    }
    ok = sqlite3_bind_text(stmt, 1, description, 100, SQLITE_TRANSIENT);
    if (ok != SQLITE_OK) {
        fprintf(stderr, "Cannot add task: %s\n", sqlite3_errmsg(DB));
        sqlite3_finalize(stmt);
        return 1;
    }
    ok = sqlite3_step(stmt);
    if (ok != SQLITE_DONE) {
        fprintf(stderr, "Cannot add task: %s\n", sqlite3_errmsg(DB));
        sqlite3_clear_bindings(stmt);
        sqlite3_finalize(stmt);
        return 1;
    }
    // Cleanup 
    sqlite3_clear_bindings(stmt);
    sqlite3_finalize(stmt);
    return 0;
}   

int DBUpdateTask(sqlite3 *DB, int id, char *description, int is_deleted) {
    
    char *query = "UPDATE Tasks SET Description = ?, IsDeleted = ? WHERE Id = ?;";
    sqlite3_stmt *stmt;
    int ok;

    ok = sqlite3_prepare_v2(DB, query, -1, &stmt, 0);
    if (ok != SQLITE_OK) {
        fprintf(stderr, "Cannot update task: %s\n", sqlite3_errmsg(DB));
        sqlite3_finalize(stmt);
        return 1;
    }
    ok = sqlite3_bind_text(stmt, 1, description, 100, SQLITE_TRANSIENT);
    if (ok != SQLITE_OK) {
        fprintf(stderr, "Cannot update task: %s\n", sqlite3_errmsg(DB));
        sqlite3_finalize(stmt);
        return 1;
    }
    ok = sqlite3_bind_int(stmt, 2, is_deleted);
    if (ok != SQLITE_OK) {
        fprintf(stderr, "Cannot update task: %s\n", sqlite3_errmsg(DB));
        sqlite3_clear_bindings(stmt);
        sqlite3_finalize(stmt);
        return 1;
    }
    ok = sqlite3_bind_int(stmt, 3, id);
    if (ok != SQLITE_OK) {
        fprintf(stderr, "Cannot update task: %s\n", sqlite3_errmsg(DB));
        sqlite3_clear_bindings(stmt);
        sqlite3_finalize(stmt);
        return 1;
    }
    ok = sqlite3_step(stmt);
    if (ok != SQLITE_DONE) {
        fprintf(stderr, "Cannot update task: %s\n", sqlite3_errmsg(DB));
        sqlite3_clear_bindings(stmt);
        sqlite3_finalize(stmt);
        return 1;
    }
    // Cleanup 
    sqlite3_clear_bindings(stmt);
    sqlite3_finalize(stmt);
    return 0;
}   

int DBListTasks(sqlite3 *DB) {
    char *query = "SELECT * FROM Tasks;";
    sqlite3_stmt *stmt;
    int ok;

    ok = sqlite3_prepare_v2(DB, query, -1, &stmt, 0);
    if (ok != SQLITE_OK) {
        fprintf(stderr, "Cannot list tasks: %s\n", sqlite3_errmsg(DB));
        sqlite3_finalize(stmt);
        return 1;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        printf("%d\t%s\t%d\t%d\t%d\t%d\n", 
                sqlite3_column_int(stmt, 0),
                sqlite3_column_text(stmt, 1),
                sqlite3_column_int(stmt, 2),
                sqlite3_column_int(stmt, 3),
                sqlite3_column_int(stmt, 4),
                sqlite3_column_int(stmt, 5));
    }
    // Cleanup 
    sqlite3_finalize(stmt);
    return 0;

}
