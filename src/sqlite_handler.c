#include <sqlite3.h>
#include "../include/sqlite_handler.h"
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include "../include/get_files_path.h"
#include <stdio.h>
#include <ctype.h>

struct MobQueryData *init_pointer;
struct MobQueryData *current_struct;
struct MobQueryData *random_mob;
const char *search;
int is_init_pointer_set = 0;

// Helper function to safely copy strings
static char* strdup_safe(const char* str) {
    if (!str) return NULL;
    return strdup(str);
}

// Callback-Funktion für das Ergebnis der SQL-Abfrage
int zufallCallback(void *data, int argc, char **argv, char **azColName) {
    printf("DEBUG Zufällig ausgewähltes Tier: %s\n", argv[0]);
    printf("werte einfüllen");
    random_mob->name = strdup_safe(argv[0]);
    random_mob->version = strdup_safe(argv[1]);
    random_mob->health = strdup_safe(argv[2]);
    random_mob->height = strdup_safe(argv[3]);
    random_mob->behavior = strdup_safe(argv[4]);
    random_mob->spawn = strdup_safe(argv[5]);
    random_mob->class = strdup_safe(argv[6]);
    random_mob->picture_path = strdup_safe(argv[7]);
    printf("DEBUG: struct beschrieben\n");
    return 0;
}

struct MobQueryData* select_random_Mob() {
    sqlite3 *db;
    char *errMsg = 0;

    char *base_path = return_folders_path();
    char database_path[strlen(base_path) + strlen("/Minecraft_Projekt_Minecraft.db") + 1];
    strcpy(database_path, base_path);
    strcat(database_path, "/Minecraft_Projekt_Minecraft.db");

    // Öffne die SQLite-Datenbank (erstellt sie, wenn sie nicht existiert)
    if (sqlite3_open(database_path, &db)) {
        fprintf(stderr, "Kann Datenbank nicht öffnen: %s\n", sqlite3_errmsg(db));
        return NULL;
    }

    // SQL-Abfrage, um ein zufälliges Tier auszuwählen
    const char *sql = "SELECT Name, Version, HP, Height, Behavior, Spawn, Class, Picture FROM Mops ORDER BY RANDOM() LIMIT 1;";

    random_mob = NULL;
    random_mob = (struct MobQueryData *)malloc(sizeof(struct MobQueryData));
    if (random_mob == NULL){
        printf("memory allocation failed!\n");
        return NULL;
    }

    // Führe die SQL-Abfrage aus
    if (sqlite3_exec(db, sql, zufallCallback, 0, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "SQL-Fehler: %s\n", errMsg);
        sqlite3_free(errMsg);
    }



    // Schließe die Datenbank
    sqlite3_close(db);
    printf("returning value\n");
    return random_mob;
}

// Flexible, case-insensitive matching function
int flexible_match_case_insensitive(const char *haystack, const char *needle) {
    while (*needle) {
        // Skip spaces in needle
        while (isspace((unsigned char)*needle)) needle++;

        // Skip spaces in haystack
        while (isspace((unsigned char)*haystack)) haystack++;

        // If the end of either string is reached prematurely, it's not a match
        if (*needle == '\0' || *haystack == '\0') {
            return *needle == '\0'; // Match only if the needle is fully processed
        }

        // Check if characters match, ignoring case
        if (tolower((unsigned char)*needle) != tolower((unsigned char)*haystack)) {
            return 0; // Mismatch
        }

        // Move to the next character in both strings
        needle++;
        haystack++;
    }

    return 1; // All characters in needle matched
}

int clear_search_result_data(struct MobQueryData* mob_query_data) {
    struct MobQueryData *temp = mob_query_data->next;
    while (temp != NULL) {
        // Free all allocated strings
        free((char*)mob_query_data->name);
        free((char*)mob_query_data->version);
        free((char*)mob_query_data->health);
        free((char*)mob_query_data->height);
        free((char*)mob_query_data->behavior);
        free((char*)mob_query_data->spawn);
        free((char*)mob_query_data->class);
        free((char*)mob_query_data->picture_path);

        free(mob_query_data);
        mob_query_data = temp;
        temp = temp->next;
    }

    // Free the last node
    if (mob_query_data) {
        free((char*)mob_query_data->name);
        free((char*)mob_query_data->version);
        free((char*)mob_query_data->health);
        free((char*)mob_query_data->height);
        free((char*)mob_query_data->behavior);
        free((char*)mob_query_data->spawn);
        free((char*)mob_query_data->class);
        free((char*)mob_query_data->picture_path);
        free(mob_query_data);
    }

    return 0;
}

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    if (flexible_match_case_insensitive(argv[0], search)) {
        if (!is_init_pointer_set) {
            current_struct = (struct MobQueryData *)malloc(sizeof(struct MobQueryData));
            if (!current_struct) return 1;
        } else {
            current_struct->next = (struct MobQueryData *)malloc(sizeof(struct MobQueryData));
            if (!current_struct->next) return 1;
            current_struct = current_struct->next;
        }

        if (!is_init_pointer_set) {
            init_pointer = current_struct;
            is_init_pointer_set = 1;
        }

        // Make copies of all strings
        current_struct->name = strdup_safe(argv[0]);
        current_struct->version = strdup_safe(argv[1]);
        current_struct->health = strdup_safe(argv[2]);
        current_struct->height = strdup_safe(argv[3]);
        current_struct->behavior = strdup_safe(argv[4]);
        current_struct->spawn = strdup_safe(argv[5]);
        current_struct->class = strdup_safe(argv[6]);
        current_struct->picture_path = strdup_safe(argv[7]);
        current_struct->next = NULL;

        // Print the values for debugging
        printf("Name: %s\n", current_struct->name);
        printf("Version: %s\n", current_struct->version);
        printf("Health: %s\n", current_struct->health);
        printf("Height: %s\n", current_struct->height);
        printf("Class: %s\n", current_struct->class);
    }
    return 0;
}

struct MobQueryData* get_search_results(const char *text) {
    search = text;
    is_init_pointer_set = 0;
    init_pointer = NULL;
    current_struct = NULL;

    sqlite3 *db;
    char *errMsg = 0;
    int rc;

    char *base_path = return_folders_path();
    char database_path[strlen(base_path) + strlen("/Minecraft_Projekt_Minecraft.db") + 1];
    strcpy(database_path, base_path);
    strcat(database_path, "/Minecraft_Projekt_Minecraft.db");
    printf("Database path: %s\n", database_path);

    rc = sqlite3_open(database_path, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return NULL;
    }
    fprintf(stderr, "Database opened\n");

    // Set UTF-8 encoding
    sqlite3_exec(db, "PRAGMA encoding = 'UTF-8';", NULL, NULL, NULL);

    const char *sql_query = "SELECT * FROM Mops;";
    rc = sqlite3_exec(db, sql_query, callback, 0, &errMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        fprintf(stdout, "Operation Successful\n");
    }

    sqlite3_close(db);
    return init_pointer;
}
