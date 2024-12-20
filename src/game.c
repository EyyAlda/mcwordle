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

#define MAX_ROWS 82
#define MAX_COLUMNS 8
#define MAX_LENGTH 256

// Globale Array-Deklaration
char resultArray[MAX_ROWS][MAX_COLUMNS][MAX_LENGTH];

int rowCounter = 0;

// Callback-Funktion, um die Ergebnisse zu verarbeiten
int callback(void *data, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        if (rowCounter < MAX_ROWS && i < MAX_COLUMNS) {
            snprintf(resultArray[rowCounter][i], MAX_LENGTH, "%s", argv[i] ? argv[i] : "NULL");
        }
    }
    rowCounter++;
    return 0;
}

int array() {
    sqlite3 *db;
    char *errMsg = 0;
    const char *sql = "SELECT * FROM Mops;"; // SQL-Abfrage
    int rc;

    // Datenbank öffnen
    rc = sqlite3_open("../../Minecraft Projekt Minecraft.db", &db);
    if (rc) {
        fprintf(stderr, "Datenbank kann nicht geöffnet werden: %s\n", sqlite3_errmsg(db));
        return 1;
    } else {
        printf("Datenbank erfolgreich geöffnet.\n");
    }

    // SQL-Abfrage ausführen
    rc = sqlite3_exec(db, sql, callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL-Fehler: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        printf("Abfrage erfolgreich ausgeführt.\n");
    }

    // Ergebnisse anzeigen
    printf("Ergebnisse:\n");
    for (int i = 0; i < rowCounter; i++) {
        for (int j = 0; j < MAX_COLUMNS && resultArray[i][j][0] != '\0'; j++) {
            printf("%s ", resultArray[i][j]);
        }
        printf("\n");
    }

    // Datenbank schließen
    sqlite3_close(db);
    return 0;
}