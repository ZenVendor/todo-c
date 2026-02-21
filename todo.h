#ifndef TODO_H
#define TODO_H

#define VERSION 0.1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <sqlite3.h>

typedef enum { 
    CMD_NONE,
    CMD_LIST,
    CMD_ADD,     
    CMD_UPDATE,  
    CMD_DELETE
} Command;

/* Parameter mask bits */
#define SW_ID   (1<<0)
#define SW_DESC (1<<1)

typedef struct {
    unsigned int id;
    char *description;
    int is_deleted;
    unsigned long created;
    unsigned long updated;
    unsigned long deleted;
} Task;

/* Parser functions */
void PrintHelp();
Command ParseCommand(char *cmd);
unsigned int ParseId(char *str_id);
char * ParseDescription(char *description);

/* DB functions */
int DBCreate(sqlite3 *DB);
int DBAddTask(sqlite3 *DB, char *description);
int DBUpdateTask(sqlite3 *DB, int id, char *description);
int DBDeleteTask(sqlite3 *DB, int id);
int DBListTasks(sqlite3 *DB);

#endif
