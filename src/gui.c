#include <gtk-4.0/gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>


GtkWidget *create_main_menu(){



}

GtkWidget *create_game_panel(){


}

void on_activate(GtkApplication *app, gpointer user_data){



}


int create_user_interface(int argc, char *argv[]){
    int status;
    GtkApplication *app = gtk_application_new("net.mcwordle", G_APPLICATION_DEFAULT_FLAGS);

    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);

    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
