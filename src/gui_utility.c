#include <gtk-4.0/gtk/gtk.h>
#include <string.h>
#include <game.h>
#include "../include/gui_utility.h"
#include "../include/get_files_path.h"

GtkWidget *mcwordle_create_game_mob_row_view(MinecraftMob *mob_struct){

    /** Container Element
     * Beinhaltet mehrere weitere Elemente
     */
    GtkWidget *container = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10); 
    
    GtkWidget *mob_icon = gtk_button_new();
    GtkWidget *health = gtk_button_new();
    GtkWidget *height = gtk_button_new();
    GtkWidget *version = gtk_button_new();
    GtkWidget *spawn = gtk_button_new();
    GtkWidget *class = gtk_button_new();
    GtkWidget *behavior = gtk_button_new();

    char *base_path = return_folders_path();
    char *picture_path = NULL;
    strcpy(picture_path, base_path);
    strcat(picture_path, mob_struct->picture_path);
    // lade das Bild für das Mob
    GtkWidget *icon_texture = gtk_image_new_from_file(picture_path);
    gtk_button_set_child(GTK_BUTTON(mob_icon), icon_texture);
    free(base_path);
    
    // füge alles zum Container hinzu
    gtk_box_append(GTK_BOX(container), mob_icon);
    gtk_box_append(GTK_BOX(container), version);
    gtk_box_append(GTK_BOX(container), health);
    gtk_box_append(GTK_BOX(container), height);
    gtk_box_append(GTK_BOX(container), behavior);
    gtk_box_append(GTK_BOX(container), spawn);
    gtk_box_append(GTK_BOX(container), class);

    // gib allen Elementen die gleiche Größe
    gtk_widget_set_size_request(GTK_WIDGET(container), 110, 110);
    gtk_box_set_homogeneous(GTK_BOX(container), TRUE);

    // jedes Button Element soll später mit einer CSS-Klasse bearbeitet werden können
    gtk_widget_add_css_class(GTK_WIDGET(mob_icon), "wordle-field");
    gtk_widget_add_css_class(GTK_WIDGET(health), "wordle-field");
    gtk_widget_add_css_class(GTK_WIDGET(height), "wordle-field");
    gtk_widget_add_css_class(GTK_WIDGET(version), "wordle-field");
    gtk_widget_add_css_class(GTK_WIDGET(spawn), "wordle-field");
    gtk_widget_add_css_class(GTK_WIDGET(class), "wordle-field");
    gtk_widget_add_css_class(GTK_WIDGET(behavior), "wordle-field");


    // Zeige die nötigen Werte in den Feldern an

    char *health_value = NULL;
    sprintf(health_value, "%d", mob_struct->health);
    gtk_button_set_label(GTK_BUTTON(health), health_value);

    char *height_value = NULL;
    sprintf(height_value, "%f", mob_struct->height);
    gtk_button_set_label(GTK_BUTTON(height), height_value);

    gtk_button_set_label(GTK_BUTTON(version), mob_struct->version);
    gtk_button_set_label(GTK_BUTTON(spawn), mob_struct->spawn);

    char *class_value = NULL;
    sprintf(class_value, "%d", mob_struct->class);
    gtk_button_set_label(GTK_BUTTON(class), class_value);
    
    char *behavior_value = NULL;
    sprintf(behavior_value, "%d", mob_struct->behavior);
    gtk_button_set_label(GTK_BUTTON(behavior), behavior_value);

    return container;
}
