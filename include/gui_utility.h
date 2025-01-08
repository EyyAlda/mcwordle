#ifndef GUI_UTILITY_H
#define GUI_UTILITY_H


#include <gtk-4.0/gtk/gtk.h>

GtkWidget* add_list_to_overlay(GtkOverlay *overlay);

void update_mob_list(const char *search_text);

GtkWidget* add_list_to_overlay(GtkOverlay *overlay);

void cleanup_mob_list_view(void);
//#include "game.h"

//GtkWidget *mcwordle_create_mob_element(char **mob_data);

//GtkWidget* create_mob_search_result_list(const char *mob_name);

//void destroy_search_results(GtkWidget *list_view);
#endif
