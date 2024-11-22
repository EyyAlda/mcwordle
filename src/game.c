#include <stdio.h>
#include <stdlib.h>
#include "../include/game.h"
#include <sqlite3.h>
#include <string.h>

static int sql_callback(void *minecraft_mob_ptr, int argc, char **argv, char **colNames){


}
/**Creates a struct containing all the data for a single minecraft mob
 * @param const char *mob_name
 * @param sqlite3 *db
 */
MinecraftMob *mcwordle_create_minecraft_mob_item(const char *mob_name, sqlite3 *db, int rc){
    MinecraftMob *mob_item_ptr = (MinecraftMob *)malloc(sizeof(MinecraftMob));

    if (mob_item_ptr == NULL) {
        fprintf(stdout, "Couldn't allocate Memory\n");
        return NULL;
    }

    //prepare the sql query
    char *errMsg = 0;
    char *base_query  = "SELECT Name, Version, HP, Height, Behavior, Spawn, Class, Picture FROM Mops WHERE Name = ";
    char mob_query[strlen(base_query) + strlen(mob_name) + 1];
    strcpy(mob_query, base_query);
    strcat(mob_query, mob_name);

    rc = sqlite3_exec(db, mob_query, sql_callback, mob_item_ptr, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    }



    return mob_item_ptr;
}

