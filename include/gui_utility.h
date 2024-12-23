#ifndef GUI_UTILITY_H
#define GUI_UTILITY_H

#include <gtk-4.0/gtk/gtk.h>
#include "game.h"

GtkWidget *mcwordle_create_game_mob_row_view(char **mob_data);

int create_mob_search_result_list(GtkStringList *container, const char *mob_name);

int destroy_search_results(GtkStringList *parent);
#endif
