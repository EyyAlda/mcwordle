#include <gtk-4.0/gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/sqlite_handler.h"
#include "../include/gui.h"
#include "../include/gui_utility.h"
#include "../include/get_files_path.h"

GtkWidget *app_stack;
GtkWidget *search_results;
GtkWidget *item_container;
GtkWidget *search_entry;
GtkWidget *list_container;
struct MobQueryData *random_Mob;
GArray *chosen_mobs;

int is_initialized = 0;

void on_start_Mop_button_click(GtkWidget *widget, gpointer user_data){
    chosen_mobs = g_array_new(FALSE, FALSE, sizeof(char*));
    random_Mob = select_random_Mob();
    gtk_widget_set_visible(search_entry, TRUE);
    gtk_stack_set_visible_child_name(GTK_STACK(app_stack), "game-panel");
}
void on_start_Block_button_click(GtkWidget *widget, gpointer user_data){

}

void free_string_array(GArray *array) {
    for(guint i = 0; i < array->len; i++) {
        g_free(g_array_index(array, char *, i));
    }
    g_array_free(array, TRUE);
}

void on_end_button_click(GtkWidget *widget, gpointer user_data){
    gtk_stack_set_visible_child_name(GTK_STACK(app_stack), "main-menu");
    free(random_Mob);
    random_Mob = NULL;
    free_string_array(chosen_mobs);
    chosen_mobs = NULL;
    clear_list();
}

GtkWidget *create_main_menu(){
    fprintf(stdout, "0\n");
    char *path = return_folders_path();


    char background_path[strlen(path) + strlen("/Background/download.webp") + 1];
    fprintf(stdout, "1\n");
    strcpy(background_path, path);
    fprintf(stdout, "2\n");
    strcat(background_path, "/Background/download.webp");

    if (does_file_exist(background_path)) g_print("DEBUG: Main Menu background found\n");

    free(path);
    fprintf(stdout, "DEBUG: Background: %s\n", background_path);

    GtkWidget *container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *overlay = gtk_overlay_new();
    GtkWidget *background = gtk_picture_new_for_filename(background_path);
    GtkWidget *start_button_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *middle_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    GtkWidget *start_button_Mop = gtk_button_new_with_label("Mop Wordel");
    GtkWidget *start_button_Block = gtk_button_new_with_label("Block Wordle");
    GtkWidget *header_label = gtk_label_new("MC Wordle");

    gtk_picture_set_can_shrink(GTK_PICTURE(background), TRUE);
    gtk_widget_set_vexpand(background, TRUE);
    gtk_picture_set_content_fit(GTK_PICTURE(background), GTK_CONTENT_FIT_COVER);

    gtk_overlay_set_child(GTK_OVERLAY(overlay), background);
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay), middle_container);

    gtk_widget_set_halign(GTK_WIDGET(overlay), GTK_ALIGN_FILL);
    gtk_widget_set_valign(GTK_WIDGET(overlay), GTK_ALIGN_FILL);
    gtk_widget_set_hexpand(GTK_WIDGET(overlay), TRUE);
    gtk_widget_set_vexpand(GTK_WIDGET(overlay), TRUE);

    gtk_widget_set_halign(GTK_WIDGET(start_button_container), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(start_button_container), GTK_ALIGN_CENTER);
    gtk_widget_set_vexpand(GTK_WIDGET(start_button_container), TRUE);
    gtk_widget_set_hexpand(GTK_WIDGET(start_button_container), TRUE);

    gtk_widget_set_halign(GTK_WIDGET(middle_container), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(middle_container), GTK_ALIGN_CENTER);
    gtk_widget_set_hexpand(GTK_WIDGET(middle_container), TRUE);
    gtk_widget_set_vexpand(GTK_WIDGET(middle_container), TRUE);

    gtk_box_append(GTK_BOX(start_button_container), start_button_Mop);
    gtk_box_append(GTK_BOX(start_button_container), start_button_Block);
    gtk_box_append(GTK_BOX(middle_container), header_label);
    gtk_box_append(GTK_BOX(middle_container), start_button_container);

    gtk_box_append(GTK_BOX(container), overlay);

    gtk_widget_add_css_class(GTK_WIDGET(start_button_Mop), "start-button");
    gtk_widget_add_css_class(GTK_WIDGET(start_button_Block), "start-button");
    gtk_widget_add_css_class(GTK_WIDGET(header_label), "header-main-menu");

    g_signal_connect(start_button_Mop, "clicked", G_CALLBACK(on_start_Mop_button_click), NULL);
    g_signal_connect(start_button_Block, "clicked", G_CALLBACK(on_start_Block_button_click), NULL);
    g_print("DEBUG: created main menu\n");
    return container;
}

void check_if_won(struct MobQueryData *mob_data){
    if (!strcmp(mob_data->name, random_Mob->name)) {
        g_print("Congrats! You've won!");
        gtk_widget_set_visible(search_entry, FALSE);
    }

}

void search_row_click_handler(struct MobQueryData *mob_data, void *user_data){
    int already_exists = 0;
    if (!mob_data) return;
    printf("row_clicked %s\n", mob_data->name);


    // check if a mob is already added to the list
    for (guint i = 0; i < chosen_mobs->len; i++) {
        char *mob = g_array_index(chosen_mobs, char*, i);
        g_print("Mob at index %d: %s\n", i, mob);
        already_exists = strcmp(mob_data->name, mob);
        already_exists = !already_exists;
        g_print("Already exists: %d\n", already_exists);
        // if we found a match, there is no need to search for more
        if (already_exists) break;
    }

    if (!already_exists){
        gtk_editable_set_text(GTK_EDITABLE(search_entry), "");
        char *mob = strdup(mob_data->name);
        g_array_append_val(chosen_mobs, mob);
        add_to_list(mob_data);
        check_if_won(mob_data);
    } else {
        g_print("Mob already added to the list\n");
    }
}

/*GtkWidget *create_mob_container(){
    GtkWidget *mop_container = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    GdkPaintable *test_icon = GDK_PAINTABLE(gdk_texture_new_from_filename( "../../Bilder/allay.gif",NULL));
    GtkWidget *button_icon = gtk_image_new_from_paintable(test_icon);
    GtkWidget *picture_button = gtk_button_new();
    GtkWidget *version2_button = gtk_button_new_with_label("Version");
    GtkWidget *hp2_button = gtk_button_new_with_label("HP");
    GtkWidget *height2_button = gtk_button_new_with_label("Height");
    GtkWidget *behavior2_button = gtk_button_new_with_label("Behavior");
    GtkWidget *spawn2_button = gtk_button_new_with_label("Spawn");
    GtkWidget *class2_button = gtk_button_new_with_label("Class");

    gtk_box_append(GTK_BOX(mop_container),picture_button);
    gtk_box_append(GTK_BOX(mop_container),version2_button);
    gtk_box_append(GTK_BOX(mop_container),hp2_button);
    gtk_box_append(GTK_BOX(mop_container),height2_button);
    gtk_box_append(GTK_BOX(mop_container),behavior2_button);
    gtk_box_append(GTK_BOX(mop_container),spawn2_button);
    gtk_box_append(GTK_BOX(mop_container),class2_button);

    gtk_widget_set_size_request(picture_button, 110, 110);
    gtk_widget_set_size_request(version2_button, 110, 110);
    gtk_widget_set_size_request(hp2_button, 110, 110);
    gtk_widget_set_size_request(height2_button, 110, 110);
    gtk_widget_set_size_request(behavior2_button, 110, 110);
    gtk_widget_set_size_request(spawn2_button, 110, 110);
    gtk_widget_set_size_request(class2_button, 110, 110);

    gtk_button_set_child(GTK_BUTTON(picture_button), button_icon);

    return mop_container;
}
*/

static void on_search(GtkEditable *editable, gpointer user_data) {
  const char *text = gtk_editable_get_text(editable);
  if (strlen(text) > 0) {
      update_mob_list(text);
      g_print("DEBUG: loaded search results\n");
      gtk_widget_set_visible(item_container, FALSE);
      gtk_widget_set_visible(list_container, FALSE);
  } else {
      update_mob_list("adsfladskjfghaldsfkjghls");
      gtk_widget_set_visible(item_container, TRUE);
      gtk_widget_set_visible(list_container, TRUE);
  }
  g_print("text changed: %s\n", text);
}

GtkWidget *create_game_panel(){
    fprintf(stdout, "0\n");
    char *path = return_folders_path();


    char background_path[strlen(path) + strlen("/Background/background2.webp") + 1];
    fprintf(stdout, "1\n");
    strcpy(background_path, path);
    fprintf(stdout, "2\n");
    strcat(background_path, "/Background/background2.webp");

    if (does_file_exist(background_path)) g_print("DEBUG: Game Panel background found\n");

    free(path);
    fprintf(stdout, "DEBUG: Background: %s\n", background_path);

    GtkWidget *overlay = gtk_overlay_new();
    GtkWidget *background = gtk_picture_new_for_filename(background_path);
    GtkWidget *container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    item_container = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    //GtkWidget *mop_container = create_mob_container();
    GtkWidget *end_button = gtk_button_new_with_label("End Game");
    GtkWidget *mop_button = gtk_button_new_with_label("Mop");
    GtkWidget *version_button = gtk_button_new_with_label("Version");
    GtkWidget *hp_button = gtk_button_new_with_label("HP");
    GtkWidget *height_button = gtk_button_new_with_label("Height");
    GtkWidget *behavior_button = gtk_button_new_with_label("Behavior");
    GtkWidget *spawn_button = gtk_button_new_with_label("Spawn");
    GtkWidget *class_button = gtk_button_new_with_label("Class");
    GtkWidget *button_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    //GtkWidget *search_bar = gtk_search_bar_new();
    GtkWidget *search_bar_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    list_container = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    search_entry = gtk_search_entry_new();

    gtk_overlay_set_child(GTK_OVERLAY(overlay), background);
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay), item_container);
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay), list_container);
    add_list_to_overlay(GTK_OVERLAY(overlay));
    add_list_to_box(GTK_BOX(list_container));
    
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay), search_bar_container);
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay), button_container);

    set_row_click_handler(search_row_click_handler, NULL);

    gtk_box_append(GTK_BOX(item_container), mop_button);
    gtk_box_append(GTK_BOX(item_container), version_button);
    gtk_box_append(GTK_BOX(item_container), hp_button);
    gtk_box_append(GTK_BOX(item_container), height_button);
    gtk_box_append(GTK_BOX(item_container), behavior_button);
    gtk_box_append(GTK_BOX(item_container), spawn_button);
    gtk_box_append(GTK_BOX(item_container), class_button);

    gtk_widget_set_halign(GTK_WIDGET(search_results), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(search_results), GTK_ALIGN_START);
    gtk_widget_set_margin_top(search_results, 200);

    gtk_box_append(GTK_BOX(search_bar_container), search_entry);

    gtk_box_append(GTK_BOX(button_container),end_button);

    gtk_picture_set_can_shrink(GTK_PICTURE(background), TRUE);
    gtk_widget_set_vexpand(background, TRUE);
    gtk_picture_set_content_fit(GTK_PICTURE(background), GTK_CONTENT_FIT_COVER);

    gtk_widget_set_halign(GTK_WIDGET(button_container), GTK_ALIGN_END);
    gtk_widget_set_valign(GTK_WIDGET(button_container), GTK_ALIGN_END);
    gtk_widget_set_hexpand(GTK_WIDGET(button_container), TRUE);
    gtk_widget_set_vexpand(GTK_WIDGET(button_container), TRUE);

    gtk_widget_set_size_request(mop_button, 110, 20);
    gtk_widget_set_size_request(version_button, 110, 20);
    gtk_widget_set_size_request(hp_button, 110, 20);
    gtk_widget_set_size_request(height_button, 110, 20);
    gtk_widget_set_size_request(behavior_button, 110, 20);
    gtk_widget_set_size_request(spawn_button, 110, 20);
    gtk_widget_set_size_request(class_button, 110, 20);


    gtk_box_set_homogeneous(GTK_BOX(item_container), TRUE);
    gtk_widget_set_halign(GTK_WIDGET(item_container), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(item_container), GTK_ALIGN_START);
    gtk_widget_set_margin_top(GTK_WIDGET(item_container), 200);
    gtk_widget_set_hexpand(GTK_WIDGET(item_container), TRUE);
    gtk_widget_set_vexpand(GTK_WIDGET(item_container), TRUE);

    guint search_delay = 200;
    gtk_widget_set_halign(GTK_WIDGET(search_bar_container), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(search_bar_container), GTK_ALIGN_START);
    gtk_widget_set_margin_top(GTK_WIDGET(search_bar_container), 20);
    gtk_search_entry_set_placeholder_text(GTK_SEARCH_ENTRY(search_entry), "Search for a Mob");
    gtk_search_entry_set_search_delay(GTK_SEARCH_ENTRY(search_entry), search_delay);
    g_signal_connect(search_entry, "search-changed", G_CALLBACK(on_search), NULL);

    /*gtk_box_set_homogeneous(GTK_BOX(mop_container), TRUE);
    gtk_widget_set_halign(GTK_WIDGET(mop_container), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(mop_container), GTK_ALIGN_START);
    gtk_widget_set_margin_top(GTK_WIDGET(mop_container), 260);
    gtk_widget_set_hexpand(GTK_WIDGET(mop_container), TRUE);
    gtk_widget_set_vexpand(GTK_WIDGET(mop_container), TRUE);
   */


    gtk_box_append(GTK_BOX(container), overlay);

    g_signal_connect(end_button, "clicked", G_CALLBACK(on_end_button_click), overlay);

    g_print("DEBUG: created game panel\n");
    return container;
}

void on_destroy(GtkWidget *window, gpointer user_data){
    //unref_mob_data();
    g_print("DEBUG: running on_destroy\n");

    g_print("DEBUG: clearing the list if necessary\n");
    clear_list();

    g_print("DEBUG: removing the data of the lists\n");
    cleanup_mob_list_view();
    if (random_Mob) free(random_Mob);
    if (chosen_mobs) free_string_array(chosen_mobs);
    g_print("DEBUG: ran on_destroy\n");
}

void on_activate(GtkApplication *app, gpointer user_data){

    // Check if we already have a window
    GList *windows = gtk_application_get_windows(app);
    if (windows) {
        // If window exists, present it and focus it
        gtk_window_present(GTK_WINDOW(windows->data));
        return;
    }
    GtkWidget *window = gtk_application_window_new(app);
    app_stack = gtk_stack_new();
    GtkWidget *main_menu = create_main_menu();
    GtkWidget *game_panel = create_game_panel();

    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    gtk_stack_set_transition_type(GTK_STACK(app_stack), GTK_STACK_TRANSITION_TYPE_CROSSFADE);
    gtk_stack_set_transition_duration(GTK_STACK(app_stack), 100);
    gtk_widget_set_hexpand(GTK_WIDGET(app_stack), TRUE);
    gtk_widget_set_vexpand(GTK_WIDGET(app_stack), TRUE);
    gtk_widget_set_size_request(GTK_WIDGET(app_stack), 600, 400);
    gtk_stack_add_named(GTK_STACK(app_stack), main_menu, "main-menu");
    gtk_stack_add_named(GTK_STACK(app_stack), game_panel, "game-panel");
    gtk_stack_set_visible_child_name(GTK_STACK(app_stack), "main-menu");





    GtkCssProvider *provider = gtk_css_provider_new();


    char *css_path;

#ifdef FLATPAK_BUILD

    const char *datadir = g_get_user_data_dir();
    css_path = g_build_filename(datadir, "share", "mcwordle", "styles", "styles.css", NULL);

#else
    
    css_path = g_build_filename(".", "resources", "styles", "styles.css", NULL);

#endif

    gtk_css_provider_load_from_path(GTK_CSS_PROVIDER(provider), css_path);

    gtk_style_context_add_provider_for_display(gdk_display_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    g_free(css_path);
    g_object_unref(provider);

    gtk_window_set_child(GTK_WINDOW(window), app_stack);
    gtk_window_present(GTK_WINDOW(window));

    g_signal_connect(window, "destroy", G_CALLBACK(on_destroy), NULL);
    g_print("DEBUG: ran activate\n");
}




int create_user_interface(int argc, char *argv[]){
    int status;
    GtkApplication *app = gtk_application_new("net.mcwordle.game", G_APPLICATION_DEFAULT_FLAGS);

    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
