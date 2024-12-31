#include <sqlite3.h>
#include "../include/sqlite_handler.h"
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include "../include/get_files_path.h"
#include <stdio.h>

/**Pointer auf den Anfang der linked List mit den Mob Daten
*/
struct MobQueryData *init_pointer;

/**Pointer auf den aktuellen struct in der linked List
*/
struct MobQueryData *current_struct;

/**beinhaltet den Text, der in die Suche eingegeben wurde
*/
const char *search;

int is_init_pointer_set = 0;

int clear_search_result_data(struct MobQueryData* mob_query_data) {
    struct MobQueryData *temp = mob_query_data->next;
    while (temp != NULL){
        free(mob_query_data);
        mob_query_data = temp;
        temp = temp->next;
    }
    return 0;
}

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    if (strcasecmp(search, argv[0]) == 0) {
        if (!is_init_pointer_set){
            current_struct = (struct MobQueryData *)malloc(sizeof(struct MobQueryData));
        } else {
            current_struct->next = (struct MobQueryData *)malloc(sizeof(struct MobQueryData));
            current_struct = current_struct->next;
        }

        if (current_struct == NULL) {
            clear_search_result_data(init_pointer);
            return NULL;
        }

        if (!is_init_pointer_set) {
            init_pointer = current_struct;
            is_init_pointer_set = 1;
        }

        current_struct->name = argv[0];
        current_struct->version = argv[1];
        current_struct->health = argv[2];
        current_struct->height = argv[3];
        current_struct->behavior = argv[4];
        current_struct->spawn = argv[5];
        current_struct->class = argv[6];
        current_struct->picture_path = argv[7];
        current_struct->next = NULL;
    }
    printf("%s", argv[0]);
    printf("\n");
    return 0;
}


struct MobQueryData* get_search_results(const char *text) {
    search = text;

    sqlite3 *db;
    char *errMsg = 0;
    int rc;

    // Zustammenstellen des Pfads zur Datenbank
    char *base_path = return_folders_path();
    char database_path[strlen(base_path) + strlen("Minecraft Projekt Minecraft.db") + 1];
    strcpy(database_path, base_path);
    strcat(database_path, "Minecraft Projekt Minecraft.db");

    //öffnen der Datenbank
    rc = sqlite3_open(database_path, &db);
    if (rc) {
        fprintf(stderr, "Konnte Datenbank nicht öffnen: %s\n", sqlite3_errmsg(db));
        return NULL;
    } else {
        fprintf(stderr, "Datenbank geöffnet\n");
    }

    const char *sql_query = "SELECT * FROM Mops;";

    //Ausführen der SQL Query
    rc = sqlite3_exec(db, sql_query, callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        fprintf(stdout, "Operation Erfolgreich\n");
    }

    sqlite3_close(db);
    return init_pointer;
}
