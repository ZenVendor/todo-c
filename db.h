#ifndef DB_H
#define DB_H 

#include <stdio.h>
#include <sqlite3.h>

int DBCreate(sqlite3 *DB);
int DBAddTask(sqlite3 *DB, char *description);
int DBUpdateTask(sqlite3 *DB, int id, char *description, int is_deleted);
int DBListTasks(sqlite3 *DB);

#endif
