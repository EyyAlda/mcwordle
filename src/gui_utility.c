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

static void setup_mob_row(GtkListBoxRow *row, struct MobQueryData *mob_data) {
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
    gtk_picture_set_keep_aspect_ratio(GTK_PICTURE(picture), TRUE);
    
    printf("DEBUG: Icon_path: %s\n", full_path);
    free(base_path);

    // Create labels for mob information
    GtkWidget *name_label = gtk_label_new(mob_data->name);
    gtk_widget_set_halign(name_label, GTK_ALIGN_CENTER);

    GtkWidget *health_label = gtk_label_new(mob_data->health);
    gtk_widget_set_halign(health_label, GTK_ALIGN_CENTER);

    GtkWidget *height_label = gtk_label_new(mob_data->height);
    gtk_widget_set_halign(height_label, GTK_ALIGN_CENTER);

    GtkWidget *class_label = gtk_label_new(mob_data->class);
    gtk_widget_set_halign(class_label, GTK_ALIGN_CENTER);

    GtkWidget *spawn_label = gtk_label_new(mob_data->spawn);
    gtk_widget_set_halign(spawn_label, GTK_ALIGN_CENTER);

    GtkWidget *behavior_label = gtk_label_new(mob_data->behavior);
    gtk_widget_set_halign(behavior_label, GTK_ALIGN_CENTER);

    // Add labels and picture to boxes
    gtk_box_append(GTK_BOX(name_box), name_label);
    gtk_box_append(GTK_BOX(health_box), health_label);
    gtk_box_append(GTK_BOX(height_box), height_label);
    gtk_box_append(GTK_BOX(behavior_box), behavior_label);
    gtk_box_append(GTK_BOX(class_box), class_label);
    gtk_box_append(GTK_BOX(spawn_box), spawn_label);
    gtk_box_append(GTK_BOX(icon_box), picture);

    // Add boxes to the horizontal box
    gtk_box_append(GTK_BOX(hbox), icon_box);
    gtk_box_append(GTK_BOX(hbox), name_box);
    gtk_box_append(GTK_BOX(hbox), health_box);
    gtk_box_append(GTK_BOX(hbox), height_box);
    gtk_box_append(GTK_BOX(hbox), behavior_box);
    gtk_box_append(GTK_BOX(hbox), class_box);
    gtk_box_append(GTK_BOX(hbox), spawn_box);

    // Set the horizontal box as the child of the row
    gtk_list_box_row_set_child(row, hbox);

    // Make sure the row and its contents are visible
    gtk_widget_set_visible(GTK_WIDGET(row), TRUE);
    gtk_widget_set_visible(hbox, TRUE);
    gtk_widget_set_visible(name_label, TRUE);

    // Cleanup
    g_object_unref(file);
}

// Add this row click handler function
static void on_row_clicked(GtkListBox *box, GtkListBoxRow *row, gpointer user_data) {
    if (!row || !row_click_callback) return;

    // Get the mob data associated with this row
    struct MobQueryData *mob_data = g_object_get_data(G_OBJECT(row), "mob-data");
    if (!mob_data) return;

    // Call the user's callback with the mob data
    row_click_callback(mob_data, row_click_user_data);
}

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
        setup_mob_row(GTK_LIST_BOX_ROW(row), current);
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

    // Style the list box
    GtkStyleContext *context = gtk_widget_get_style_context(view->list_box);
    GtkCssProvider *provider = gtk_css_provider_new();
    const char *css = 
        "list { background-color: rgba(255, 255, 255, 0.0); }"
        "row { background-color: rgba(255, 255, 255, 0.9); margin: 2px; border-radius: 5px; }"
        ".icon-box { background-color: rgb(220, 220, 220); padding: 3px; }";

    gtk_css_provider_load_from_string(provider, css);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(provider);

    // Add the list box to the scrolled window
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(view->scrolled_window), view->list_box);

    g_signal_connect(view->list_box, "row-activated", G_CALLBACK(on_row_clicked), NULL);
    return view;
}

void cleanup_mob_list_view(void) {
    if (global_mob_list_view) {
        g_free(global_mob_list_view);
        global_mob_list_view = NULL;
    }
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