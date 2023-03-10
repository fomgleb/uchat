#include "../../client.h"

char *get_entry_text(GtkBuilder *builder, char *entry_name)
{
    GtkWidget *entry = GTK_WIDGET(gtk_builder_get_object(builder, entry_name));

    return (char *)gtk_entry_get_text(GTK_ENTRY(entry));
}

void write_label_text(GtkBuilder *builder, char *label_name, char *text)
{
    GtkWidget *label = GTK_WIDGET(gtk_builder_get_object(builder, label_name));

    gtk_label_set_text(GTK_LABEL(label), text);
}

void add_to_box(GtkBuilder *builder, GtkWidget *new_element, char *box_name)
{
    GtkWidget *box = GTK_WIDGET(gtk_builder_get_object(builder, box_name));

    gtk_box_pack_start(GTK_BOX(box), new_element, false, false, 0);
    gtk_widget_show(new_element);
}

void open_window(GtkBuilder *builder, char *window_name)
{
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, window_name));

    gtk_widget_show_all(window);
}

void close_window(GtkBuilder *builder, char *window_name)
{
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, window_name));

    gtk_widget_hide(window);
}

void exit_app()
{
    gtk_main_quit();
}

