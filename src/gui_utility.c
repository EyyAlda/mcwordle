#include <gtk-4.0/gtk/gtk.h>
#include <string.h>
#include <game.h>
#include "../include/gui_utility.h"

GtkWidget *mcwordle_create_game_mob_row_view(MinecraftMob *mob_struct){
    GtkWidget *container = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    
    GtkWidget *mob_icon = gtk_button_new();
    GtkWidget *health = gtk_button_new_with_label((char *)mob_struct->health);
    GtkWidget *height = gtk_button_new();
    GtkWidget *version = gtk_button_new();
    GtkWidget *spawn = gtk_button_new();
    GtkWidget *class = gtk_button_new();
    GtkWidget *behavior = gtk_button_new();

    gtk_box_append(GTK_BOX(container), mob_icon);
    gtk_box_append(GTK_BOX(container), version);
    gtk_box_append(GTK_BOX(container), health);
    gtk_box_append(GTK_BOX(container), height);
    gtk_box_append(GTK_BOX(container), behavior);
    gtk_box_append(GTK_BOX(container), spawn);
    gtk_box_append(GTK_BOX(container), class);
    return container;
}
