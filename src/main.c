#include <gtk/gtk.h>
#include <string.h>

#include "types.h"

StringArray get_profiles();

static void
run_profile(GtkWidget* widget, gpointer profile)
{
    FFParams* params = profile;

    char* result = malloc((26 + strlen((*params).profile) + strlen((*params).url)) * sizeof(char));
    strcpy(result, "firefox -p \"");
    strcat(result, (*params).profile);
    strcat(result, "\" \"");
    strcat(result, (*params).url);
    strcat(result, "\" & disown");

    printf("Command: %s\n", result);
    system(result);
}

static void
activate(GtkApplication* app, gpointer profiles)
{
    GtkWidget* window;
    GtkWidget* box;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Firefox Profile");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(box, GTK_ALIGN_CENTER);

    gtk_window_set_child(GTK_WINDOW(window), box);

    FFParamsAll* paramsAll = profiles;
    for (int i = 0; i < (*paramsAll).profiles.length; i++) {
        GtkWidget* button;
        button = gtk_button_new_with_label((*paramsAll).profiles.data[i]);

        FFParams* params = malloc(sizeof(FFParams));
        (*params).profile = (*paramsAll).profiles.data[i];
        (*params).url = (*paramsAll).url;

        g_signal_connect(button, "clicked", G_CALLBACK(run_profile), params);
        g_signal_connect_swapped(
            button, "clicked", G_CALLBACK(gtk_window_destroy), window);

        gtk_box_append(GTK_BOX(box), button);
    }

    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char* argv[])
{
    StringArray profiles = get_profiles();
    FFParamsAll paramsAll;
    paramsAll.profiles = profiles;

    if (argc >= 2) {
        paramsAll.url = argv[1];
    } else {
        // TODO: get from config
        paramsAll.url = malloc(23 * sizeof(char));
        strcpy(paramsAll.url, "https://www.google.com");
    }

    GtkApplication* app;
    int status;

    app = gtk_application_new("org.gtk.ff_profiles", G_APPLICATION_DEFAULT_FLAGS);

    g_signal_connect(app, "activate", G_CALLBACK(activate), &paramsAll);
    status = g_application_run(G_APPLICATION(app), 0, NULL);
    g_object_unref(app);

    return status;
}
