#include "db.h"

int main (int argc, char **argv) {

    sqlite3 *DB;
    if (sqlite3_open(":memory:", &DB) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database, %s\n", sqlite3_errmsg(DB));
        return 1;
    }

    int rv;
    rv = DBCreate(DB);
    if (rv != 0) {
        sqlite3_close(DB);
        return 1;
    }
    rv = DBAddTask(DB, "My description");
    if (rv != 0) {
        sqlite3_close(DB);
        return 1;
    }
    rv = DBListTasks(DB);
    if (rv != 0) {
        sqlite3_close(DB);
        return 1;
    }
    rv = DBUpdateTask(DB, 1, "My deleted description", 1);
    if (rv != 0) {
        sqlite3_close(DB);
        return 1;
    }
    rv = DBListTasks(DB);
    if (rv != 0) {
        sqlite3_close(DB);
        return 1;
    }

    printf("All done.");
    sqlite3_close(DB);
    return 0;
}
