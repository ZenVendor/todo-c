#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

/* Commanad mask bits */
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

void PrintHelp();
Command ParseCommand(char *cmd);
unsigned int ParseId(char *str_id);
char * ParseDescription(char *description);

#endif
