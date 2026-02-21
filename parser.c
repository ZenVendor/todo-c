#include "todo.h"

void PrintHelp() {
    printf("Version: %.1f\n", VERSION);
    printf("todo <action> [id] [arguments]\n");
}

Command ParseCommand(char *cmd) {
    if (strcmp("list", cmd) == 0) {
        return CMD_LIST;
    }
    if (strcmp("add", cmd) == 0) {
        return CMD_ADD;
    }
    if (strcmp("update", cmd) == 0) {
        return CMD_UPDATE;
    }
    if (strcmp("delete", cmd) == 0) {
        return CMD_DELETE;
    }
    return CMD_NONE;
}

unsigned int ParseId(char *str_id) {
    char *endptr;
    unsigned int id = strtol(str_id, &endptr, 10);
    if (strlen(endptr) > 0 || id == 0) {
        fprintf(stderr, "ID must me a number.\n");
        return 0;
    }
    if (id < 0) {
        fprintf(stderr, "ID number cannot be negative.\n");
        return 0;
    }
    if (id > UINT_MAX) {
        fprintf(stderr, "ID number is outside of range.\n");
        return 0;
    }
    return id;
}

char * ParseDescription(char *description) {
    if (strlen(description) > 100) {
        fprintf(stderr, "Description cut to 100 characters.\n");
        description[100] = '\0';
    }
    return description;
}

