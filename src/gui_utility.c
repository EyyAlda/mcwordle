#include <gtk-4.0/gtk/gtk.h>
#include <string.h>
#include "../include/game.h"
#include "../include/gui_utility.h"
#include "../include/get_files_path.h"
#include "../include/sqlite_handler.h"
#include "glibconfig.h"
/*
typedef struct {
    const char *name;
    const char *version;
    const char *height;
    const char *health;
    const char *spawn;
    const char *class;
    const char *behavior;
    const char *icon_path;
} MobDataItem;

static GtkListItemFactory* create_factory();
GListStore *list_store = NULL;

G_DECLARE_FINAL_TYPE(ListItem, list_item, LIST, ITEM, GObject)

struct _ListItem {
    GObject parent_instance;
    MobDataItem data;
};

G_DEFINE_TYPE(ListItem, list_item, G_TYPE_OBJECT)

static void list_item_init(ListItem *self) {
}

static void list_item_class_init(ListItemClass *self) {
}

ListItem* mob_data_item_new(const char *name, const char *version, const char *height, const char *health, const char *spawn, const char *class, const char *behavior, const char *icon_path) {
    ListItem *item = g_object_new(list_item_get_type(), NULL);
    item->data.name = name;
    item->data.version = version;
    item->data.height = height;
    item->data.health = health;
    item->data.spawn = spawn;
    item->data.class = class;
    item->data.behavior = behavior;
    item->data.icon_path = icon_path;

    return item;
}
*/

/** Erstellt eine Reihe mit den 5 Mob-Daten für die Anzeige im Spiel
 * @param char **mob_data
 */
//static void setup_mob_element(GtkListItemFactory *factory, GtkListItem *item){

    /** Container Element
     * Beinhaltet mehrere weitere Elemente
     *
    GtkWidget *container = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);

    GtkWidget *mob_name = gtk_button_new();
    GtkWidget *mob_icon = gtk_button_new();
    GtkWidget *health = gtk_button_new();
    GtkWidget *height = gtk_button_new();
    GtkWidget *version = gtk_button_new();
    GtkWidget *spawn = gtk_button_new();
    GtkWidget *class = gtk_button_new();
    GtkWidget *behavior = gtk_button_new();

    GtkWidget *mob_name_label = gtk_label_new(NULL);
    GtkWidget *mob_health_label = gtk_label_new(NULL);
    GtkWidget *mob_height_label = gtk_label_new(NULL);
    GtkWidget *mob_version_label = gtk_label_new(NULL);
    GtkWidget *mob_spawn_text = gtk_text_view_new();
    GtkWidget *mob_class_text = gtk_text_view_new();
    GtkWidget *mob_behavior_text = gtk_text_view_new();

    gtk_text_view_set_editable(GTK_TEXT_VIEW(mob_spawn_text), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(mob_spawn_text), FALSE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(mob_spawn_text), GTK_WRAP_WORD);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(mob_class_text), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(mob_class_text), FALSE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(mob_class_text), GTK_WRAP_WORD);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(mob_behavior_text), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(mob_behavior_text), FALSE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(mob_behavior_text), GTK_WRAP_WORD);


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

    gtk_box_set_homogeneous(GTK_BOX(container), TRUE);

    // füge alles zum Container hinzu
    gtk_box_append(GTK_BOX(container), mob_name);
    gtk_box_append(GTK_BOX(container), mob_icon);
    gtk_box_append(GTK_BOX(container), version);
    gtk_box_append(GTK_BOX(container), health);
    gtk_box_append(GTK_BOX(container), height);
    gtk_box_append(GTK_BOX(container), behavior);
    gtk_box_append(GTK_BOX(container), spawn);
    gtk_box_append(GTK_BOX(container), class);

    gtk_button_set_child(GTK_BUTTON(mob_name), mob_name_label);
    gtk_button_set_child(GTK_BUTTON(version), mob_version_label);
    gtk_button_set_child(GTK_BUTTON(health), mob_health_label);
    gtk_button_set_child(GTK_BUTTON(height), mob_height_label);
    gtk_button_set_child(GTK_BUTTON(behavior), mob_behavior_text);
    gtk_button_set_child(GTK_BUTTON(spawn), mob_spawn_text);
    gtk_button_set_child(GTK_BUTTON(class), mob_class_text);

    // gib allen Elementen die gleiche Größe
    //gtk_widget_set_size_request(GTK_WIDGET(container), 110, 110);
    //gtk_box_set_homogeneous(GTK_BOX(container), TRUE);
    gtk_widget_set_halign(GTK_WIDGET(container), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(container), GTK_ALIGN_START);
*/
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
    //gtk_button_set_child(GTK_BUTTON(container_container), container);
    //gtk_list_item_set_child(item, container);
//}

/*static void bind_mob_element(GtkListItemFactory *factory, GtkListItem *item){


    GtkWidget *container = gtk_list_item_get_child(item);
    GtkWidget *mob_name = gtk_widget_get_first_child(container);
    GtkWidget *mob_icon = gtk_widget_get_next_sibling(mob_name);
    GtkWidget *version = gtk_widget_get_next_sibling(mob_icon);
    GtkWidget *health = gtk_widget_get_next_sibling(version);
    GtkWidget *height = gtk_widget_get_next_sibling(health);
    GtkWidget *behavior = gtk_widget_get_next_sibling(height);
    GtkWidget *spawn = gtk_widget_get_next_sibling(behavior);
    GtkWidget *class = gtk_widget_get_next_sibling(spawn);

    ListItem *list_item = gtk_list_item_get_item(item);
    MobDataItem *data = &list_item->data;

    GtkWidget *mob_name_label = gtk_widget_get_first_child(mob_name);
    gtk_label_set_text(GTK_LABEL(mob_name_label), data->name);

    GtkWidget *version_label = gtk_widget_get_first_child(version);
    gtk_label_set_text(GTK_LABEL(version_label), data->version);

    GtkWidget *health_label = gtk_widget_get_first_child(health);
    gtk_label_set_text(GTK_LABEL(health_label), data->health);

    GtkWidget *height_label = gtk_widget_get_first_child(height);
    gtk_label_set_text(GTK_LABEL(height_label), data->height);

    GtkWidget *behavior_text = gtk_widget_get_first_child(behavior);
    GtkTextBuffer *behavior_text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(behavior_text));
    gtk_text_buffer_set_text(behavior_text_buffer, data->behavior, -1);

    GtkWidget *spawn_text = gtk_widget_get_first_child(spawn);
    GtkTextBuffer *spawn_text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(spawn_text));
    gtk_text_buffer_set_text(spawn_text_buffer, data->behavior, -1);

    GtkWidget *class_text = gtk_widget_get_first_child(class);
    GtkTextBuffer *class_text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(class_text));
    gtk_text_buffer_set_text(class_text_buffer, data->behavior, -1);

    char *base_path = return_folders_path();
    char picture_path[strlen(base_path) + strlen(data->icon_path) + 1];
    fprintf(stdout, "DEBUG: loading image\n");
    strcpy(picture_path, base_path);
    strcat(picture_path, data->icon_path);
    // lade das Bild für das Mob
    fprintf(stdout, "DEBUG: Image Path: %s\n", picture_path);
    GtkWidget *icon_texture = gtk_image_new_from_file(picture_path);
    gtk_button_set_child(GTK_BUTTON(mob_icon), icon_texture);
    fprintf(stdout, "DEBUG: freeing base_path\n");
    free(base_path);

}

*/
/**Zählt die Menge an Elementen, die zu einer Box hinzugefügt wurden
 * Wird genutzt, um einen leeren bildschirm zu verhindern falls kein mob mit einem spezifischem Namen gefunden wurde
 * @param GtkWidget *widget
 */
/*int count_found_mobs(GtkStringList *widget){
    int count = 0;
    while (gtk_string_list_get_string(widget, count) != NULL){
        count++;
    }
    return count;
}
*/
/**Gibt eine vertikale Box mit Mob-Ergebnissen zurück
 * Wird genutzt, wenn ein neues Mob gesucht wird
 * @param GtkWidget *container
 * @param const char *mob_name
 */
/*GtkWidget* create_mob_search_result_list(const char *mob_name){
    int mob_count = get_mob_counter();


    fprintf(stdout, "DEBUG: getting Data\n");
    char ***mob_data = get_mob_data();

    list_store = g_list_store_new(list_item_get_type());

    fprintf(stdout, "DEBUG: checking pointer\n");
    if (mob_data != NULL){
        for (int i = 0; i < mob_count; i++){

            // vergleiche eingegebenen Namen und vorhandene Daten
            if (g_strstr_len(mob_data[i][0], -1, mob_name)){

                g_print("DEBUG: counting results\n");
                //bei jedem treffer wird ein neues Element zur Liste hinzugefügt
                g_list_store_append(list_store, mob_data_item_new(
                            mob_data[i][0], // name
                            mob_data[i][1], // version
                            mob_data[i][3], // height
                            mob_data[i][2], // health
                            mob_data[i][5], // spawn
                            mob_data[i][6], // class
                            mob_data[i][4], // behavior
                            mob_data[i][7]  // icon Path
                            ));
            }
        }

    }

    GtkWidget *list_view = gtk_list_view_new(GTK_SELECTION_MODEL(gtk_single_selection_new(G_LIST_MODEL(list_store))), create_factory());

    //falls die Suche keine treffer ergab, zeige es an
    //if (!count_found_mobs(container)){
        //GtkWidget *empty_label = gtk_label_new("No result found");
    //}

    return list_view;
}

static GtkListItemFactory* create_factory(){
    GtkListItemFactory *factory = gtk_signal_list_item_factory_new();
    g_signal_connect(factory, "setup", G_CALLBACK(setup_mob_element), NULL);
    g_signal_connect(factory, "bind", G_CALLBACK(bind_mob_element), NULL);
    return factory;
}
*/
/**removes the listed search results
 */
 /*
void destroy_search_results(GtkWidget *list_view){
    g_object_unref(list_store);
    gtk_widget_unparent(list_view);
}
*/



typedef struct {
    GtkWidget *scrolled_window;
    GtkWidget *list_box;
} MobListView;

static MobListView *global_mob_list_view = NULL;

static void setup_mob_row(GtkListBoxRow *row, struct MobQueryData *mob_data) {
    // Create a vertical box for the content
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_widget_set_margin_start(hbox, 10);
    gtk_widget_set_margin_end(hbox, 10);
    gtk_widget_set_margin_top(hbox, 5);
    gtk_widget_set_margin_bottom(hbox, 5);

    GtkWidget *name_button = gtk_button_new();
    GtkWidget *icon_button = gtk_button_new();
    GtkWidget *health_button = gtk_button_new();
    GtkWidget *height_button = gtk_button_new();
    GtkWidget *class_button = gtk_button_new();
    GtkWidget *behavior_button = gtk_button_new();

    // Create labels for mob information
    GtkWidget *name_label = gtk_label_new(mob_data->name);
    printf("%s\n", mob_data->name);
    gtk_widget_set_halign(name_label, GTK_ALIGN_CENTER);
    //gtk_label_set_markup(GTK_LABEL(name_label), g_markup_printf_escaped("<b>%s</b>", mob_data->name));

    GtkWidget *health_label = gtk_label_new(mob_data->health);
    printf("%s\n", mob_data->name);
    gtk_widget_set_halign(name_label, GTK_ALIGN_CENTER);

    GtkWidget *height_label = gtk_label_new(mob_data->height);
    printf("%s\n", mob_data->name);
    gtk_widget_set_halign(name_label, GTK_ALIGN_CENTER);

    GtkWidget *class_label = gtk_label_new(mob_data->class);
    printf("%s\n", mob_data->name);
    gtk_widget_set_halign(name_label, GTK_ALIGN_CENTER);

    GtkWidget *behavior_label = gtk_label_new(mob_data->behavior);
    printf("%s\n", mob_data->name);
    gtk_widget_set_halign(name_label, GTK_ALIGN_CENTER);

    gtk_button_set_child(GTK_BUTTON(name_button), name_label);
    gtk_button_set_child(GTK_BUTTON(health_button), health_label);
    gtk_button_set_child(GTK_BUTTON(height_button), height_label);
    gtk_button_set_child(GTK_BUTTON(behavior_button), behavior_label);
    gtk_button_set_child(GTK_BUTTON(class_button), class_label);
    /*GtkWidget *details_label = gtk_label_new(NULL);
    gtk_widget_set_halign(details_label, GTK_ALIGN_CENTER);
    char *details = g_strdup_printf("Version: \tHealth: \tHeight: \tClass: \n %s \t %s \t %s \t %s", mob_data->version, mob_data->health, mob_data->height, mob_data->class);
    gtk_label_set_text(GTK_LABEL(details_label), details);
    g_free(details);
    */

    printf("Version: \tHealth: \tHeight: \tClass: \n %s \t %s \t %s \t %s", mob_data->version, mob_data->health, mob_data->height, mob_data->class);

    // Add labels to the vertical box
    gtk_box_append(GTK_BOX(hbox), icon_button);
    gtk_box_append(GTK_BOX(hbox), name_button);
    gtk_box_append(GTK_BOX(hbox), health_button);
    gtk_box_append(GTK_BOX(hbox), height_button);
    gtk_box_append(GTK_BOX(hbox), behavior_button);
    gtk_box_append(GTK_BOX(hbox), class_button);

    // Set the vertical box as the child of the row
    gtk_list_box_row_set_child(row, hbox);

    // Make sure the row and its contents are visible
    gtk_widget_set_visible(GTK_WIDGET(row), TRUE);
    gtk_widget_set_visible(hbox, TRUE);
    gtk_widget_set_visible(name_label, TRUE);
    //gtk_widget_set_visible(details_label, TRUE);
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
    const char *css = "list { background-color: rgba(255, 255, 255, 0.0); }"
                     "row { background-color: rgba(255, 255, 255, 0.9); margin: 2px; border-radius: 5px; }"
                     "label { color: rgb(0, 0, 0); }"; // Make sure text is visible
    gtk_css_provider_load_from_string(provider, css);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(provider);

    // Add the list box to the scrolled window
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(view->scrolled_window), view->list_box);

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
    update_mob_list("");

    return global_mob_list_view->scrolled_window;
}
