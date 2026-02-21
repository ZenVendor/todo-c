#include "todo.h"

int DBCreate(sqlite3 *DB) {

    char *query = "CREATE TABLE IF NOT EXISTS Tasks ("
                  "Id INTEGER PRIMARY KEY,"
                  "Description NCHAR(100) NOT NULL,"
                  "IsDeleted INTEGER NOT NULL DEFAULT 0,"
                  "CreatedAt INTEGER NOT NULL DEFAULT CURRENT_TIMESTAMP,"
                  "UpdatedAt INTEGER NOT NULL DEFAULT CURRENT_TIMESTAMP,"
                  "DeletedAt INTEGER NULL);";
 
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

int DBUpdateTask(sqlite3 *DB, int id, char *description) {
    
    char *query = "UPDATE Tasks SET Description = ?, UpdatedAt = CURRENT_TIMESTAMP WHERE Id = ?;";
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
    ok = sqlite3_bind_int(stmt, 2, id);
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

int DBDeleteTask(sqlite3 *DB, int id) {
    
    char *query = "UPDATE Tasks SET IsDeleted = 1, UpdatedAt = CURRENT_TIMESTAMP, DeletedAt = CURRENT_TIMESTAMP WHERE Id = ?;";
    sqlite3_stmt *stmt;
    int ok;

    ok = sqlite3_prepare_v2(DB, query, -1, &stmt, 0);
    if (ok != SQLITE_OK) {
        fprintf(stderr, "Cannot delete task: %s\n", sqlite3_errmsg(DB));
        sqlite3_finalize(stmt);
        return 1;
    }
    ok = sqlite3_bind_int(stmt, 1, id);
    if (ok != SQLITE_OK) {
        fprintf(stderr, "Cannot delete task: %s\n", sqlite3_errmsg(DB));
        sqlite3_clear_bindings(stmt);
        sqlite3_finalize(stmt);
        return 1;
    }
    ok = sqlite3_step(stmt);
    if (ok != SQLITE_DONE) {
        fprintf(stderr, "Cannot delete task: %s\n", sqlite3_errmsg(DB));
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
    char *query = "SELECT Id, Description, IsDeleted, unixepoch(CreatedAt), unixepoch(UpdatedAt), unixepoch(DeletedAt) FROM Tasks;";
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
