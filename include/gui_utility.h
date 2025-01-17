#ifndef GUI_UTILITY_H
#define GUI_UTILITY_H


#include <gtk-4.0/gtk/gtk.h>
#include "sqlite_handler.h"


void update_mob_list(const char *search_text);

GtkWidget* add_list_to_overlay(GtkOverlay *overlay);

GtkWidget* add_list_to_box(GtkBox *box);

void add_to_list(struct MobQueryData *data);

void clear_list();

void cleanup_mob_list_view(void);

// Function type for click callbacks
typedef void (*MobRowClickCallback)(struct MobQueryData *mob_data, void *user_data);

// Functions to manage click handling
void set_row_click_handler(MobRowClickCallback callback, void *user_data);

#endif
