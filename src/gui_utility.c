#include <gtk-4.0/gtk/gtk.h>
#include <gtk/gtk.h>
#include <string.h>
#include "../include/game.h"
#include "../include/gui_utility.h"
#include "../include/get_files_path.h"

GtkWidget *mcwordle_create_game_mob_row_view(char **mob_data){
    if (mob_data == NULL) return NULL;

    GtkWidget *container_container = gtk_button_new();

    /** Container Element
     * Beinhaltet mehrere weitere Elemente
     */
    GtkWidget *container = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10); 
    
    GtkWidget *mob_name = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *mob_icon = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *health = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *height = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *version = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *spawn = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *class = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *behavior = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    GtkWidget *mob_name_label = gtk_label_new(mob_data[0]);
    GtkWidget *mob_health_label = gtk_label_new(mob_data[2]);
    GtkWidget *mob_height_label = gtk_label_new(mob_data[3]);
    GtkWidget *mob_version_label = gtk_label_new(mob_data[1]);
    GtkWidget *mob_spawn_label = gtk_label_new(mob_data[5]);
    GtkWidget *mob_class_label = gtk_label_new(mob_data[6]);
    GtkWidget *mob_behavior_label = gtk_label_new(mob_data[4]);

    gtk_widget_set_size_request(mob_icon, 110, 110);
    gtk_widget_set_size_request(mob_name, 110, 110);
    gtk_widget_set_size_request(health, 110, 110);
    gtk_widget_set_size_request(height, 110, 110);
    gtk_widget_set_size_request(version, 110, 110);
    gtk_widget_set_size_request(spawn, 110, 110);
    gtk_widget_set_size_request(class, 110, 110);
    gtk_widget_set_size_request(behavior, 110, 110);

    gtk_widget_set_hexpand(mob_name, FALSE);
    gtk_widget_set_hexpand(mob_icon, FALSE);
    gtk_widget_set_hexpand(health, FALSE);
    gtk_widget_set_hexpand(height, FALSE);
    gtk_widget_set_hexpand(version, FALSE);
    gtk_widget_set_hexpand(spawn, FALSE);
    gtk_widget_set_hexpand(class, FALSE);
    gtk_widget_set_hexpand(behavior, FALSE);

    char *base_path = return_folders_path();
    char picture_path[strlen(base_path) + strlen(mob_data[7]) + 1];
    fprintf(stdout, "DEBUG: loading image\n");
    strcpy(picture_path, base_path);
    strcat(picture_path, mob_data[7]);
    // lade das Bild für das Mob
    fprintf(stdout, "DEBUG: Image Path: %s\n", picture_path);
    GtkWidget *icon_texture = gtk_image_new_from_file(picture_path);
    gtk_box_append(GTK_BOX(mob_icon), icon_texture);
    fprintf(stdout, "DEBUG: freeing base_path\n");
    free(base_path);
    
    
    // füge alles zum Container hinzu
    gtk_box_append(GTK_BOX(container), mob_name);
    gtk_box_append(GTK_BOX(container), mob_icon);
    gtk_box_append(GTK_BOX(container), version);
    gtk_box_append(GTK_BOX(container), health);
    gtk_box_append(GTK_BOX(container), height);
    gtk_box_append(GTK_BOX(container), behavior);
    gtk_box_append(GTK_BOX(container), spawn);
    gtk_box_append(GTK_BOX(container), class);

    gtk_box_append(GTK_BOX(mob_name), mob_name_label);
    gtk_box_append(GTK_BOX(version), mob_version_label);
    gtk_box_append(GTK_BOX(health), mob_health_label);
    gtk_box_append(GTK_BOX(height), mob_height_label);
    gtk_box_append(GTK_BOX(behavior), mob_behavior_label);
    gtk_box_append(GTK_BOX(spawn), mob_spawn_label);
    gtk_box_append(GTK_BOX(class), mob_class_label);

    // gib allen Elementen die gleiche Größe
    //gtk_widget_set_size_request(GTK_WIDGET(container), 110, 110);
    //gtk_box_set_homogeneous(GTK_BOX(container), TRUE);
    gtk_widget_set_halign(GTK_WIDGET(container), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(container), GTK_ALIGN_START);

    // jedes Button Element soll später mit einer CSS-Klasse bearbeitet werden können
    /*gtk_widget_add_css_class(GTK_WIDGET(mob_icon), "wordle-field");
    gtk_widget_add_css_class(GTK_WIDGET(health), "wordle-field");
    gtk_widget_add_css_class(GTK_WIDGET(height), "wordle-field");
    gtk_widget_add_css_class(GTK_WIDGET(version), "wordle-field");
    gtk_widget_add_css_class(GTK_WIDGET(spawn), "wordle-field");
    gtk_widget_add_css_class(GTK_WIDGET(class), "wordle-field");
    gtk_widget_add_css_class(GTK_WIDGET(behavior), "wordle-field");
    */


    // Zeige die nötigen Werte in den Feldern an
    
    /*fprintf(stdout, "DEBUG: filling in data\n");
    fprintf(stdout, "DEBUG: health\n");
    gtk_button_set_label(GTK_BUTTON(health), mob_data[2]);

    fprintf(stdout, "DEBUG: height\n");
    gtk_button_set_label(GTK_BUTTON(height), mob_data[3]);

    fprintf(stdout, "DEBUG: version\n");
    gtk_button_set_label(GTK_BUTTON(version), mob_data[1]);
    fprintf(stdout, "DEBUG: spawn\n");
    gtk_button_set_label(GTK_BUTTON(spawn), mob_data[5]);

    fprintf(stdout, "DEBUG: class\n");
    gtk_button_set_label(GTK_BUTTON(class), mob_data[6]);
    
    fprintf(stdout, "DEBUG: behavior\n");
    gtk_button_set_label(GTK_BUTTON(behavior), mob_data[4]);

    fprintf(stdout, "DEBUG: name\n");
    gtk_button_set_label(GTK_BUTTON(mob_name), mob_data[0]);
    */
    gtk_button_set_child(GTK_BUTTON(container_container), container);
    return container_container;
}

/**Zählt die Menge an Elementen, die zu einer Box hinzugefügt wurden
 * Wird genutzt, um einen leeren bildschirm zu verhindern falls kein mob mit einem spezifischem Namen gefunden wurde
 * @param GtkWidget *widget
 */
int count_found_mobs(GtkWidget *widget){
    int count = 0;
    GtkWidget *child = gtk_widget_get_first_child(widget);
    while (child != NULL){
        count++;
        child = gtk_widget_get_next_sibling(child);
    }
    return count;
}

/**Gibt eine vertikale Box mit Mob-Ergebnissen zurück
 * Wird genutzt, wenn ein neues Mob gesucht wird
 * @param GtkWidget *container
 * @param const char *mob_name
 */
int create_mob_search_result_list(GtkWidget *container, const char *mob_name){
    int mob_count = get_mob_counter();


    fprintf(stdout, "DEBUG: getting Data\n");
    char ***mob_data = get_mob_data();
    
    fprintf(stdout, "DEBUG: checking pointer\n");
    if (mob_data != NULL){
        for (int i = 0; i < mob_count; i++){

            if (g_strstr_len(mob_data[i][0], -1, mob_name)){

                g_print("DEBUG: creating results\n");
                //bei jedem treffer wird ein neues Element zur Liste hinzugefügt
                gtk_box_append(GTK_BOX(container), mcwordle_create_game_mob_row_view(mob_data[i]));
            }
        }
    }

    //falls die Suche keine treffer ergab, zeige es an
    if (!count_found_mobs(container)){
        GtkWidget *empty_label = gtk_label_new("No result found");
        gtk_box_append(GTK_BOX(container), empty_label);
    }

    return 0;
}

/**removes the listed search results
 */
int destroy_search_results(GtkWidget *parent){
    GtkWidget *child;

    while ((child = gtk_widget_get_first_child(parent)) != NULL) {
        gtk_widget_unparent(child);
    }
    return 0;
}
