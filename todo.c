#include "db.h"
#include "parser.h"

int main (int argc, char **argv) {
    
    sqlite3 *DB;
    if (sqlite3_open("todo.db", &DB) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database, %s\n", sqlite3_errmsg(DB));
        return 1;
    }
    int rv;
    rv = DBCreate(DB);
    if (rv != 0) {
        sqlite3_close(DB);
        return 1;
    }

    if (argc == 2) {
        Command cmd = ParseCommand(argv[1]);
        switch (cmd) {
            case CMD_LIST:
            {
                if (DBListTasks(DB) != 0) {
                    sqlite3_close(DB);
                    return 1;
                }
            } break;
            default:
            {
                PrintHelp();
                return 0;
            }
        }
    }
    if (argc == 3) {
        Command cmd = ParseCommand(argv[1]);
        switch (cmd) {
            case CMD_ADD:
            {
                char *desc = ParseDescription(argv[2]);
                if (DBAddTask(DB, desc) != 0) {
                    sqlite3_close(DB);
                    return 1;
                }
                printf("Task added: %s\n", desc);
            } break;
            case CMD_DELETE:
            {
                unsigned int id = ParseId(argv[2]);
                if (DBDeleteTask(DB, id) != 0) {
                    sqlite3_close(DB);
                    return 1;
                }
                printf("Task %d deleted.\n", id);
            } break;
            default:
            {
                PrintHelp();
                return 0;
            }
        }
    }

    printf("All done.\n");
    sqlite3_close(DB);
    return 0;
}
