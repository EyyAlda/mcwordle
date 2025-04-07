#include <gtk-4.0/gtk/gtk.h>
#include <string.h>
#include "../include/game.h"
#include "../include/gui_utility.h"
#include "../include/get_files_path.h"
#include "../include/sqlite_handler.h"
#include "glibconfig.h"

typedef struct {
    GtkWidget *scrolled_window;
    GtkWidget *list_box;
} MobListView;

static MobListView *global_mob_list_view = NULL;
static MobRowClickCallback row_click_callback = NULL;
static void *row_click_user_data = NULL;
static MobListView *global_list = NULL;

// Function to set the click handler
void set_row_click_handler(MobRowClickCallback callback, void *user_data) {
    row_click_callback = callback;
    row_click_user_data = user_data;
}

// Helper function to create a copy of mob data
static struct MobQueryData* copy_mob_data(const struct MobQueryData *src) {
    struct MobQueryData *copy = malloc(sizeof(struct MobQueryData));
    if (!copy) return NULL;

    copy->name = src->name ? strdup(src->name) : NULL;
    copy->version = src->version ? strdup(src->version) : NULL;
    copy->height = src->height ? strdup(src->height) : NULL;
    copy->health = src->health ? strdup(src->health) : NULL;
    copy->class = src->class ? strdup(src->class) : NULL;
    copy->behavior = src->behavior ? strdup(src->behavior) : NULL;
    copy->spawn = src->spawn ? strdup(src->spawn) : NULL;
    copy->picture_path = src->picture_path ? strdup(src->picture_path) : NULL;
    copy->next = NULL;

    return copy;
}

void check_match(GtkWidget *element, char *first, char *second) {
    if (!strcmp(first, second)) {
        gtk_widget_add_css_class(element, "match");
    } else if (flexible_match_case_insensitive(first, second)) {
        gtk_widget_add_css_class(element, "partly");
    } else {
        gtk_widget_add_css_class(element, "no-match");
    }
}

static void setup_mob_row(GtkListBoxRow *row, struct MobQueryData *mob_data, struct MobQueryData *target) {
    GtkWidget *picture;
    
    // Store a copy of the mob data in the row
    struct MobQueryData *row_data = copy_mob_data(mob_data);
    g_object_set_data_full(G_OBJECT(row), "mob-data", row_data,
                          (GDestroyNotify)clear_search_result_data);

    // Create a horizontal box for the content
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_widget_set_margin_start(hbox, 10);
    gtk_widget_set_margin_end(hbox, 10);
    gtk_widget_set_margin_top(hbox, 5);
    gtk_widget_set_margin_bottom(hbox, 5);

    // Erstellen der Boxen mit fester Breite
    GtkWidget *name_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget *icon_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget *health_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget *height_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget *class_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget *behavior_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget *spawn_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

    // Setzen fester Breiten für die Boxen
    gtk_widget_set_size_request(name_box, 100, -1);
    gtk_widget_set_size_request(icon_box, 70, 70);
    gtk_widget_set_size_request(health_box, 80, -1);
    gtk_widget_set_size_request(height_box, 80, -1);
    gtk_widget_set_size_request(class_box, 100, -1);
    gtk_widget_set_size_request(behavior_box, 120, -1);
    gtk_widget_set_size_request(spawn_box, 100, -1);

    // CSS-Klassen hinzufügen
    gtk_widget_add_css_class(name_box, "data-box");
    gtk_widget_add_css_class(icon_box, "data-box");
    gtk_widget_add_css_class(health_box, "data-box");
    gtk_widget_add_css_class(height_box, "data-box");
    gtk_widget_add_css_class(class_box, "data-box");
    gtk_widget_add_css_class(behavior_box, "data-box");
    gtk_widget_add_css_class(spawn_box, "data-box");

    // Set up icon
    char *base_path = return_folders_path();
    char full_path[strlen(base_path) + strlen(mob_data->picture_path) + 1];
    strcpy(full_path, base_path);
    strcat(full_path, mob_data->picture_path);
    
    // Erstellen Sie das GFile mit dem vollständigen Pfad
    GFile *file = g_file_new_for_path(full_path);
    GError *error = NULL;
    
    if (error != NULL) {
        g_printerr("Error loading image: %s\n", error->message);
        g_error_free(error);
        g_object_unref(file);
        free(base_path);
        return;
    }
    picture = gtk_picture_new_for_file(file);
    gtk_widget_set_size_request(picture, 15, 15);
    gtk_picture_set_content_fit(GTK_PICTURE(picture), GTK_CONTENT_FIT_CONTAIN);
    
    printf("DEBUG: Icon_path: %s\n", full_path);
    free(base_path);


    // Create labels for mob information
    GtkWidget *name_field = gtk_text_view_new();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(name_field), GTK_WRAP_WORD_CHAR);
    GtkTextBuffer *name_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(name_field));
    gtk_text_buffer_set_text(name_buffer, mob_data->name, -1);
    gtk_widget_set_hexpand(name_field, TRUE);
    gtk_widget_set_vexpand(name_field, TRUE);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(name_field), FALSE);
    gtk_text_view_set_justification(GTK_TEXT_VIEW(name_field), GTK_JUSTIFY_CENTER);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(name_field), TRUE);

    GtkWidget *version_field = gtk_text_view_new();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(version_field), GTK_WRAP_WORD_CHAR);
    GtkTextBuffer *version_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(version_field));
    gtk_text_buffer_set_text(version_buffer, mob_data->version, -1);
    gtk_widget_set_hexpand(version_field, TRUE);
    gtk_widget_set_vexpand(version_field, TRUE);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(version_field), FALSE);


    GtkWidget *health_field = gtk_text_view_new();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(health_field), GTK_WRAP_WORD_CHAR);
    GtkTextBuffer *health_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(health_field));
    gtk_text_buffer_set_text(health_buffer, mob_data->health, -1);
    gtk_widget_set_hexpand(health_field, TRUE);
    gtk_widget_set_vexpand(health_field, TRUE);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(health_field), FALSE);

    GtkWidget *height_field = gtk_text_view_new();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(height_field), GTK_WRAP_WORD_CHAR);
    GtkTextBuffer *height_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(height_field));
    gtk_text_buffer_set_text(height_buffer, mob_data->height, -1);
    gtk_widget_set_hexpand(height_field, TRUE);
    gtk_widget_set_vexpand(height_field, TRUE);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(height_field), FALSE);

    GtkWidget *class_field = gtk_text_view_new();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(class_field), GTK_WRAP_WORD_CHAR);
    GtkTextBuffer *class_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(class_field));
    gtk_text_buffer_set_text(class_buffer, mob_data->class, -1);
    gtk_widget_set_hexpand(class_field, TRUE);
    gtk_widget_set_vexpand(class_field, TRUE);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(class_field), FALSE);

    GtkWidget *behavior_field = gtk_text_view_new();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(behavior_field), GTK_WRAP_WORD_CHAR);
    GtkTextBuffer *behavior_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(behavior_field));
    gtk_text_buffer_set_text(behavior_buffer, mob_data->behavior, -1);
    gtk_widget_set_hexpand(behavior_field, TRUE);
    gtk_widget_set_vexpand(behavior_field, TRUE);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(behavior_field), FALSE);

    printf("Version: \tHealth: \tHeight: \tClass: \n %s \t\t %s \t\t %s \t\t %s\n", mob_data->version, mob_data->health, mob_data->height, mob_data->class);
  
    GtkWidget *spawn_field = gtk_text_view_new();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(spawn_field), GTK_WRAP_WORD_CHAR);
    GtkTextBuffer *spawn_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(spawn_field));
    gtk_text_buffer_set_text(spawn_buffer, mob_data->spawn, -1);
    gtk_widget_set_hexpand(spawn_field, TRUE);
    gtk_widget_set_vexpand(spawn_field, TRUE);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(spawn_field), FALSE);

    gtk_box_append(GTK_BOX(icon_box), picture);
    
    if (target != NULL) {
        check_match(name_field, mob_data->name, target->name);
        check_match(health_field, mob_data->health, target->health);
        check_match(height_field, mob_data->height, target->height);
        check_match(class_field, mob_data->class, target->class);
        check_match(behavior_field, mob_data->behavior, target->behavior);
        check_match(spawn_field, mob_data->spawn, target->spawn);
        check_match(version_field, mob_data->version, target->version);
    } else {
        gtk_widget_add_css_class(name_field, "list_text_field");
        gtk_widget_add_css_class(health_field, "list_text_field");
        gtk_widget_add_css_class(height_field, "list_text_field");
        gtk_widget_add_css_class(class_field, "list_text_field");
        gtk_widget_add_css_class(behavior_field, "list_text_field");
        gtk_widget_add_css_class(spawn_field, "list_text_field");
        gtk_widget_add_css_class(version_field, "list_text_field");
    }

    // Add boxes to the horizontal box
    gtk_box_append(GTK_BOX(hbox), icon_box);
    gtk_box_append(GTK_BOX(hbox), name_field);
    gtk_box_append(GTK_BOX(hbox), version_field);
    gtk_box_append(GTK_BOX(hbox), health_field);
    gtk_box_append(GTK_BOX(hbox), height_field);
    gtk_box_append(GTK_BOX(hbox), behavior_field);
    gtk_box_append(GTK_BOX(hbox), spawn_field);
    gtk_box_append(GTK_BOX(hbox), class_field);

    // Set the horizontal box as the child of the row
    gtk_list_box_row_set_child(row, hbox);
    

    // Make sure the row and its contents are visible
    gtk_widget_set_visible(GTK_WIDGET(row), TRUE);
    gtk_widget_set_visible(hbox, TRUE);
    gtk_widget_set_visible(name_field, TRUE);

    // Cleanup
    g_object_unref(file);
}

// Add this row click handler function
static void on_row_clicked(GtkListBox *box, GtkListBoxRow *row, gpointer user_data) {
    if (!row || !row_click_callback) return;
    g_print("DEBUG: on_row_clicked\n");

    // Get the mob data associated with this row
    struct MobQueryData *mob_data = g_object_get_data(G_OBJECT(row), "mob-data");
    if (!mob_data) return;

    // Call the user's callback with the mob data
    row_click_callback(mob_data, row_click_user_data);
}

/**fügt ausgewählte mobs zur Wordle-Liste hinzu
 */
void add_to_list(struct MobQueryData *data, struct MobQueryData *target) {
    g_print("DEBUG: adding entry: %s\n", data->name);

    if (!global_list || !global_list->list_box) {
        g_print("Error: List view not initialized\n");
        return;
    }

    g_print("DEBUG: creating row\n");
    GtkWidget *row = gtk_list_box_row_new();
    g_print("DEBUG: setting up row\n");
    setup_mob_row(GTK_LIST_BOX_ROW(row), data, target);
    g_print("DEBUG: appending row to list\n");
    gtk_list_box_append(GTK_LIST_BOX(global_list->list_box), row);
    
    
    g_print("DEBUG: redrawing list\n");
    // Queue a redraw
    gtk_widget_queue_draw(global_list->scrolled_window);
}

/**läd Suchergebnisse in eine Liste
 */
void update_mob_list(const char *search_text) {
    g_print("Updating mob list with search text: %s\n", search_text);

    if (!global_mob_list_view || !global_mob_list_view->list_box) {
        g_print("Error: List view not initialized\n");
        return;
    }

    // Clear existing rows
    GtkWidget *child;
    while ((child = gtk_widget_get_first_child(GTK_WIDGET(global_mob_list_view->list_box))) != NULL) {
        gtk_list_box_remove(GTK_LIST_BOX(global_mob_list_view->list_box), child);
    }

    // Get search results
    struct MobQueryData *results = get_search_results(search_text);
    struct MobQueryData *current = results;

    int row_count = 0;
    // Add new rows
    while (current != NULL) {
        GtkWidget *row = gtk_list_box_row_new();
        setup_mob_row(GTK_LIST_BOX_ROW(row), current, NULL);
        gtk_list_box_append(GTK_LIST_BOX(global_mob_list_view->list_box), row);
        current = current->next;
        row_count++;
    }

    g_print("Added %d rows to the list\n", row_count);

    // Make sure the list box and scrolled window are visible
    gtk_widget_set_visible(global_mob_list_view->list_box, TRUE);
    gtk_widget_set_visible(global_mob_list_view->scrolled_window, TRUE);

    // Queue a redraw
    gtk_widget_queue_draw(global_mob_list_view->scrolled_window);

    // Clear the search results
    if (results != NULL) {
        clear_search_result_data(results);
    }
}

GtkWidget* get_mob_list_box(void) {
    return global_mob_list_view ? global_mob_list_view->list_box : NULL;
}

static MobListView* create_mob_list_view(void) { 
    MobListView *view = g_new0(MobListView, 1);

    // Create a scrolled window
    view->scrolled_window = gtk_scrolled_window_new();
    gtk_scrolled_window_set_min_content_height(GTK_SCROLLED_WINDOW(view->scrolled_window), 400);
    gtk_widget_set_hexpand(view->scrolled_window, TRUE);
    gtk_widget_set_vexpand(view->scrolled_window, TRUE);

    // Create the list box
    view->list_box = gtk_list_box_new();
    gtk_list_box_set_selection_mode(GTK_LIST_BOX(view->list_box), GTK_SELECTION_SINGLE);

    // Make sure widgets are visible
    gtk_widget_set_visible(view->list_box, TRUE);
    gtk_widget_set_visible(view->scrolled_window, TRUE);

    // Add the list box to the scrolled window
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(view->scrolled_window), view->list_box);

    g_signal_connect(view->list_box, "row-activated", G_CALLBACK(on_row_clicked), NULL);
    return view;
}

void cleanup_mob_list_view(void) {
    if (global_mob_list_view) {
        g_print("DEBUG: (utility) freeing global_mob_list_view\n");
        g_free(global_mob_list_view);
        global_mob_list_view = NULL;
    }
    if (global_list) {
        g_print("DEBUG: (utility) freeing global_list\n");
        g_free(global_list);
        global_list = NULL;
    }
}

static MobListView* create_list(void) {
    MobListView *view = g_new0(MobListView, 1);

    // Create a scrolled window
    view->scrolled_window = gtk_scrolled_window_new();
    gtk_scrolled_window_set_min_content_height(GTK_SCROLLED_WINDOW(view->scrolled_window), 400);
    gtk_widget_set_hexpand(view->scrolled_window, TRUE);
    gtk_widget_set_vexpand(view->scrolled_window, TRUE);

    // Create the list box
    view->list_box = gtk_list_box_new();
    gtk_list_box_set_selection_mode(GTK_LIST_BOX(view->list_box), GTK_SELECTION_SINGLE);

    // Make sure widgets are visible
    gtk_widget_set_visible(view->list_box, TRUE);
    gtk_widget_set_visible(view->scrolled_window, TRUE);

    // Add the list box to the scrolled window
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(view->scrolled_window), view->list_box);

    return view;
}

GtkWidget* add_list_to_overlay(GtkOverlay *overlay) {
    g_print("Adding list to overlay\n");

    if (!global_mob_list_view) {
        global_mob_list_view = create_mob_list_view();
    }

    gtk_overlay_add_overlay(overlay, global_mob_list_view->scrolled_window);

    // Set size and position in the overlay
    gtk_widget_set_size_request(global_mob_list_view->scrolled_window, 300, 400); // Set minimum size

    // Make sure everything is visible
    gtk_widget_set_visible(global_mob_list_view->scrolled_window, TRUE);
    gtk_widget_set_visible(global_mob_list_view->list_box, TRUE);

    // Initial population
    update_mob_list("aösdlkfjalkdjf");

    return global_mob_list_view->scrolled_window;

}

void clear_list(){
    if (global_list) {
        GtkWidget *child;
        while ((child = gtk_widget_get_first_child(GTK_WIDGET(global_list->list_box))) != NULL) {
            gtk_list_box_remove(GTK_LIST_BOX(global_list->list_box), child);
        }
    }
}

GtkWidget* add_list_to_box(GtkBox *box){
    if (!global_list){
        global_list = create_list();
    }

    gtk_box_append(box, global_list->scrolled_window);

    gtk_widget_set_size_request(global_list->scrolled_window, 300, 400);

    gtk_widget_set_visible(global_list->scrolled_window, TRUE);
    gtk_widget_set_visible(global_list->list_box, TRUE);

    return global_list->scrolled_window;
}

