#include <gtk-4.0/gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/gui.h"

GtkWidget *app_stack;

void on_start_button_click(GtkWidget *widget, gpointer user_data){
    gtk_stack_set_visible_child_name(GTK_STACK(app_stack), "game-panel");
}

void on_end_button_click(GtkWidget *widget, gpointer user_data){
    gtk_stack_set_visible_child_name(GTK_STACK(app_stack), "main-menu");
}
GtkWidget *create_main_menu(){
    GtkWidget *container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *overlay = gtk_overlay_new();
    GtkWidget *background = gtk_picture_new();
    GtkWidget *start_button_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *middle_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    GtkWidget *start_button = gtk_button_new_with_label("Start Game");
    GtkWidget *header_label = gtk_label_new("MC Wordle");

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

GtkWidget *create_game_panel(){
    GtkWidget *container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *end_button = gtk_button_new_with_label("End Game");
    
    gtk_box_append(GTK_BOX(container), end_button);
    g_signal_connect(end_button, "clicked", G_CALLBACK(on_end_button_click), NULL);

    g_print("DEBUG: created game panel\n");
    return container;
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

    /*GtkCssProvider *provider = gtk_css_provider_new();

    gtk_css_provider_load_from_path(GTK_CSS_PROVIDER(provider), "");
    g_object_unref(provider);
    */

    gtk_window_set_child(GTK_WINDOW(window), app_stack);
    gtk_window_present(GTK_WINDOW(window));
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
