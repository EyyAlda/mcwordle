#ifndef GUI_UTILITY_H
#define GUI_UTILITY_H

#include <gtk-4.0/gtk/gtk.h>
#include "game.h"

GtkWidget *mcwordle_create_mob_element(char **mob_data);

GtkWidget* create_mob_search_result_list(const char *mob_name);

void destroy_search_results(GtkWidget *list_view);
#endif
