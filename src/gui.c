#include <gtk-4.0/gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/gui.h"
#include "../include/gui_utility.h"
#include "../include/get_files_path.h"

GtkWidget *app_stack;
GtkWidget *search_results;

int is_initialized = 0;

void on_start_button_click(GtkWidget *widget, gpointer user_data){
    gtk_stack_set_visible_child_name(GTK_STACK(app_stack), "game-panel");
}

void on_end_button_click(GtkWidget *widget, gpointer user_data){
    gtk_stack_set_visible_child_name(GTK_STACK(app_stack), "main-menu");
}
GtkWidget *create_main_menu(){
    fprintf(stdout, "0\n");
    char *path = return_folders_path();


    char background_path[strlen(path) + strlen("/Background/download.webp") + 1];
    fprintf(stdout, "1\n");
    strcpy(background_path, path);
    fprintf(stdout, "2\n");
    strcat(background_path, "/Background/download.webp");

    free(path);
    fprintf(stdout, "DEBUG: Background: %s", background_path);

    GtkWidget *container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *overlay = gtk_overlay_new();
    GtkWidget *background = gtk_picture_new_for_filename(background_path);
    GtkWidget *start_button_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *middle_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    GtkWidget *start_button = gtk_button_new_with_label("Start Game");
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

    gtk_box_append(GTK_BOX(start_button_container), start_button);
    gtk_box_append(GTK_BOX(middle_container), header_label);
    gtk_box_append(GTK_BOX(middle_container), start_button_container);

    gtk_box_append(GTK_BOX(container), overlay);

    gtk_widget_add_css_class(GTK_WIDGET(start_button), "start-button");
    gtk_widget_add_css_class(GTK_WIDGET(header_label), "header-main-menu");

    g_signal_connect(start_button, "clicked", G_CALLBACK(on_start_button_click), NULL);
    g_print("DEBUG: created main menu\n");
    return container;
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
  } else {
      update_mob_list("adsfladskjfghldsfkjghls");
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

    free(path);
    fprintf(stdout, "DEBUG: Background: %s", background_path);

    GtkWidget *overlay = gtk_overlay_new();
    GtkWidget *background = gtk_picture_new_for_filename(background_path);
    GtkWidget *container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *item_container = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
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
    GtkWidget *search_entry = gtk_search_entry_new();

    gtk_overlay_set_child(GTK_OVERLAY(overlay), background);
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay), item_container);
    add_list_to_overlay(GTK_OVERLAY(overlay));
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay), search_bar_container);
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay), button_container);


    gtk_box_append(GTK_BOX(item_container),mop_button);
    gtk_box_append(GTK_BOX(item_container),version_button);
    gtk_box_append(GTK_BOX(item_container),hp_button);
    gtk_box_append(GTK_BOX(item_container),height_button);
    gtk_box_append(GTK_BOX(item_container),behavior_button);
    gtk_box_append(GTK_BOX(item_container),spawn_button);
    gtk_box_append(GTK_BOX(item_container),class_button);

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
    cleanup_mob_list_view();
    g_print("DEBUG: ran on_destroy\n");
}

void on_activate(GtkApplication *app, gpointer user_data){
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

    char *base_path = return_folders_path();

    char css_path[strlen(base_path) + strlen("/styles.css") + 1];

    strcpy(css_path, base_path);
    strcat(css_path, "/styles.css");

    free(base_path);

    GtkCssProvider *provider = gtk_css_provider_new();

    gtk_css_provider_load_from_path(GTK_CSS_PROVIDER(provider), css_path);

    g_object_unref(provider);

    gtk_window_set_child(GTK_WINDOW(window), app_stack);
    gtk_window_present(GTK_WINDOW(window));

    g_signal_connect(window, "destroy", G_CALLBACK(on_destroy), NULL);
    g_print("DEBUG: ran activate\n");
}




int create_user_interface(int argc, char *argv[]){
    int status;
    GtkApplication *app = gtk_application_new("net.mcwordle", G_APPLICATION_DEFAULT_FLAGS);

    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
