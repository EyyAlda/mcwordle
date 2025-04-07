#include <gtk-4.0/gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/path_handler.h"


/**Returns a malloc'ed char * containing the path to the specified location
 * @param enum Pathype type
 */
char *get_program_path(enum PathType type) {
    char *data_dir = g_build_filename(g_get_user_data_dir(), "com.mcwordle.game", NULL);
    switch (type) {
        case ROOT:
            return data_dir;
            break;
        case STYLESHEET: 
            {
                printf("DEBUG: returning stylesheet path");
                char *stylesheet_path = (char *)malloc(strlen(data_dir) + strlen("/resources/styles/styles.css") + 1);
                strcpy(stylesheet_path, data_dir);
                strcat(stylesheet_path, "/resources/styles/styles.css");
                g_free(data_dir);
                return stylesheet_path;
            }
        case FONTS:
            return NULL;
        case MOB_PICTURES:
        case BLOCK_PICTURES: 
            {
                printf("DEBUG: returning picture paths");
                char *pictures_path = (char *)malloc(strlen(data_dir) + strlen("/resources") + 1);
                strcpy(pictures_path, data_dir);
                strcat(pictures_path, "/resources");
                g_free(data_dir);
                return pictures_path;
            }
        case DATABASE:
            {
                printf("DEBUG: returning db path");
                char *db_path = (char *)malloc(strlen(data_dir) + strlen("/resources/Minecraft_Projekt_Minecraft.db") + 1);
                strcpy(db_path, data_dir);
                strcat(db_path, "/resources/Minecraft_Projekt_Minecraft.db");
                g_free(data_dir);
                return db_path;
            }
        case HOME_BACKGROUND:
            {
                printf("DEBUG: returning home background path");
                char *bg_path = (char *)malloc(strlen(data_dir) + strlen("/resources/backgrounds/home_background.webp") + 1);
                strcpy(bg_path, data_dir);
                strcat(bg_path, "/resources/backgrounds/home_background.webp");
                g_free(data_dir);
                return bg_path;
            }
        case GAME_BACKGROUND:
            {
                printf("DEBUG: returning game background path");
                char *bg_path = (char *)malloc(strlen(data_dir) + strlen("/resources/backgrounds/game_background.webp") + 1);
                strcpy(bg_path, data_dir);
                strcat(bg_path, "/resources/backgrounds/game_background.webp");
                g_free(data_dir);
                return bg_path;
            }
        default:
            return NULL;
    }
}
