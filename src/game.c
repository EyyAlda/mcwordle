#include <stdio.h>
#include <stdlib.h>
#include "../include/game.h"
#include <sqlite3.h>
#include <string.h>
#include "../include/get_files_path.h"

char ***mob_data;
/*static int sql_callback(void *minecraft_mob_ptr, int argc, char **argv, char **colNames){


}
**Creates a struct containing all the data for a single minecraft mob
 * @param const char *mob_name
 * @param sqlite3 *db
 *
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
*/

#define MAX_ROWS 82
#define MAX_COLUMNS 8
#define MAX_LENGTH 256

// Globale Array-Deklaration
char resultArray[MAX_ROWS][MAX_COLUMNS][MAX_LENGTH];

int rowCounter = 0;
int mob_counter = 0;


/**Gibt die Anzahl der jetzt verfügbaren Mobs zurück
 */
int get_mob_counter(){
    return mob_counter;
}

/**Gibt einen Pointer array zu den jetzt verfügbaren mobs zurück
 */
char ***get_mob_data(){
    return mob_data;
}


// Callback-Funktion, um die Ergebnisse zu verarbeiten
int callback(void *data, int argc, char **argv, char **azColName) {
    mob_counter += 1;

    for (int i = 0; i < argc; i++) {
        if (rowCounter < MAX_ROWS && i < MAX_COLUMNS) {
            snprintf(resultArray[rowCounter][i], MAX_LENGTH, "%s", argv[i] ? argv[i] : "NULL");
        }
    }
    rowCounter++;
    return 0;
}

/**Löscht alle gespeicherten Mob daten aus dem Speicher
*/
int unref_mob_data(){
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLUMNS; j++) {
            free(mob_data[i][j]);
        }
        free(mob_data[i]);
    }
    free(mob_data);
    return 0;
}

/**Liest die Mobdaten aus der Datenbank und speichert sie
 */
int array() {
    char *base_path = return_folders_path();

    char database_path[strlen(base_path) + strlen("/Minecraft Projekt Minecraft.db") + 1];

    strcpy(database_path, base_path);
    strcat(database_path, "/Minecraft Projekt Minecraft.db");

    free(base_path);

    sqlite3 *db;
    char *errMsg = 0;
    const char *sql = "SELECT * FROM Mops;"; // SQL-Abfrage
    int rc;
    rowCounter = 0;

    // Datenbank öffnen
    rc = sqlite3_open(database_path, &db);
    if (rc) {
        fprintf(stderr, "Datenbank kann nicht geöffnet werden: %s\n", sqlite3_errmsg(db));
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

    mob_data = (char ***)malloc(rowCounter * sizeof(char **));
    if (mob_data == NULL) {
        // Handle memory allocation failure
        return 1;
    }

    for (int i = 0; i < rowCounter; i++) {
        mob_data[i] = (char **)malloc(rowCounter * sizeof(char *));
        if (mob_data[i] == NULL) {
            // Handle memory allocation failure
            // Free previously allocated memory
            for (int j = 0; j < i; j++) {
                free(mob_data[j]);
            }
            free(mob_data);
            return 1;
        }

        for (int j = 0; j < rowCounter; j++) {
            mob_data[i][j] = (char *)malloc(rowCounter * sizeof(char));
            if (mob_data[i][j] == NULL) {
                // Handle memory allocation failure
                // Free previously allocated memory
                for (int k = 0; k < j; k++) {
                    free(mob_data[i][k]);
                }
                for (int k = 0; k < i; k++) {
                    for (int l = 0; l < rowCounter; l++) {
                        free(mob_data[k][l]);
                    }
                    free(mob_data[k]);
                }
                free(mob_data);
                return 1;
            }
        }
    }

    for (int i = 0; i < rowCounter; i++){
        for (int j = 0; j < MAX_COLUMNS; j++){
            mob_data[i][j]  = strdup(resultArray[i][j]);
        }
    }

    for (int i = 0; i < rowCounter; i++) {
        for (int j = 0; j < MAX_COLUMNS && mob_data[i][j][0] != '\0'; j++) {
            printf("%s ", mob_data[i][j]);
        }
        printf("\n");
    }


    return 0;
}
    
