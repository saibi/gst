#include <gtk/gtk.h>

void common_dialog(GtkWidget *widget, gpointer window, GtkMessageType type, GtkButtonsType btn, const gchar *title, const gchar *msg)
{
	GtkWidget *dialog;

	dialog = gtk_message_dialog_new(GTK_WINDOW(window), GTK_DIALOG_DESTROY_WITH_PARENT, type, btn, "%s", msg);

	gtk_window_set_title(GTK_WINDOW(dialog), title);
	g_print("%d - before\n", type);
	gtk_dialog_run(GTK_DIALOG(dialog));
	g_print("after\n");
	gtk_widget_destroy(dialog);
}

void show_info(GtkWidget *widget, gpointer window)
{
	common_dialog(widget, window, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Information", "Download Completed");
}

void show_error(GtkWidget *widget, gpointer window)
{
	common_dialog(widget, window, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Error", "Error loading file");
}

void show_question(GtkWidget *widget, gpointer window)
{
	common_dialog(widget, window, GTK_MESSAGE_QUESTION, GTK_BUTTONS_YES_NO, "Question", "Are you sure to quit?");
}

void show_warning(GtkWidget *widget, gpointer window)
{
	common_dialog(widget, window, GTK_MESSAGE_WARNING, GTK_BUTTONS_OK, "Warning", "Unallowed operation");
}


int main(int argc, char *argv[])
{
	GtkWidget *window;
	GtkWidget *table;

	GtkWidget *info;
	GtkWidget *warn;
	GtkWidget *que;
	GtkWidget *err;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
	gtk_window_set_title(GTK_WINDOW(window), "Message dialogs");
	gtk_container_set_border_width(GTK_CONTAINER(window), 5);

	table = gtk_table_new(2, 2, TRUE);
	gtk_table_set_row_spacings(GTK_TABLE(table), 2);
	gtk_table_set_col_spacings(GTK_TABLE(table), 2);

	info = gtk_button_new_with_label("Info");
	warn = gtk_button_new_with_label("Warning");
	que = gtk_button_new_with_label("Question");
	err = gtk_button_new_with_label("Error");

	gtk_table_attach(GTK_TABLE(table), info, 0, 1, 0, 1, GTK_FILL, GTK_FILL, 3, 3);
	gtk_table_attach(GTK_TABLE(table), warn, 1, 2, 0, 1, GTK_FILL, GTK_FILL, 3, 3);
	gtk_table_attach(GTK_TABLE(table), que, 0, 1, 1, 2, GTK_FILL, GTK_FILL, 3, 3);
	gtk_table_attach(GTK_TABLE(table), err, 1, 2, 1, 2, GTK_FILL, GTK_FILL, 3, 3);


	gtk_container_add(GTK_CONTAINER(window), table);
	gtk_container_set_border_width(GTK_CONTAINER(window), 15);

	g_signal_connect(G_OBJECT(info), "clicked", G_CALLBACK(show_info), (gpointer)window);
	g_signal_connect(G_OBJECT(warn), "clicked", G_CALLBACK(show_warning), (gpointer)window);
	g_signal_connect(G_OBJECT(que), "clicked", G_CALLBACK(show_question), (gpointer)window);
	g_signal_connect(G_OBJECT(err), "clicked", G_CALLBACK(show_error), (gpointer)window);

	g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	gtk_widget_show_all(window);

	gtk_main();

	return 0;
}
