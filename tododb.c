#include <stdio.h>
#include <sqlite3.h>



int DBCreate(sqlite3 *DB) {

    query = "CREATE DATABASE IF NOT EXISTS Tasks ("
            "Id INTEGER PRIMARY KEY,"
            "Description NCHAR(100) NOT NULL,"
            "IsDeleted INTEGER NOT NULL DEFAULT 0,"
            "CreatedAt INTEGER NOT NULL DEFAULT CURRENT_DATE,"
            "UpdatedAt INTEGER NOT NULL DEFAULT CURRENT_DATE,"
            "DeletedAt INTEGER NOT NULL DEFAULT CURRENT_DATE);";
 
    char *err_msg;
    if (sqlite3_exec(DB, query, 0, 0, &err_msg) != SQLITE_OK) {
        fprintf(stderr, "Cannot create database: %s\n", *err_msg);
        return 1;
    }
    fprintf(stdout, "Database 'Tasks' created\n")
    return 0;   
}

int DBAddTask(sqlite3 *DB, char *description) {

    query = "INSERT INTO Tasks (Description) VALUES ('?');";
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
    if (ok != SQLITE_OK) {
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
    
    query = "UPDATE Tasks SET Description = '?', IsDeleted = ? WHERE Id = ?;";
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
    ok = sqlite3_bind_text(stmt, 2, is_deleted);
    if (ok != SQLITE_OK) {
        fprintf(stderr, "Cannot add task: %s\n", sqlite3_errmsg(DB));
        sqlite3_finalize(stmt);
        return 1;
    }
    ok = sqlite3_bind_text(stmt, 3, id);
    if (ok != SQLITE_OK) {
        fprintf(stderr, "Cannot add task: %s\n", sqlite3_errmsg(DB));
        sqlite3_finalize(stmt);
        return 1;
    }
    ok = sqlite3_step(stmt);
    if (ok != SQLITE_OK) {
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
