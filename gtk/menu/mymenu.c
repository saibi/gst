#include <gtk/gtk.h>
#include <glib/gprintf.h>

int main(int argc, char *argv[])
{
	GtkWidget *window;
	GtkWidget *vbox;

	GtkWidget *menubar;
	GtkWidget *menubar_file;
	GtkWidget *submenu_file;
	GtkWidget *file_newWindow;
	GtkWidget *file_newTab;
	GtkWidget *file_sep1;
	GtkWidget *file_newDoc;
	GtkWidget *submenu_newDoc;
	GtkWidget *newDoc_empty;
	GtkWidget *file_sep2;
	GtkWidget *file_quit;

	GtkWidget *menubar_edit;
	GtkWidget *submenu_edit;
	GtkWidget *edit_copy;
	GtkWidget *edit_cut;
	GtkWidget *edit_paste;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
	gtk_container_set_border_width(GTK_CONTAINER(window), 15);
	gtk_window_set_title(GTK_WINDOW(window), "my menu");

	vbox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(window), vbox);

	menubar = gtk_menu_bar_new();
	menubar_file = gtk_menu_item_new_with_label("File");

	submenu_file = gtk_menu_new();

	file_newWindow = gtk_menu_item_new_with_label("New Window");
	file_newTab = gtk_menu_item_new_with_label("New Tab");
	file_sep1 = gtk_separator_menu_item_new();
	file_newDoc = gtk_menu_item_new_with_label("New Document");
	submenu_newDoc = gtk_menu_new();
	newDoc_empty = gtk_menu_item_new_with_label("Empty document");

	file_sep2 = gtk_separator_menu_item_new();
	file_quit = gtk_menu_item_new_with_label("Quit");

	gtk_menu_shell_append(GTK_MENU_SHELL(submenu_file), file_newWindow);
	gtk_menu_shell_append(GTK_MENU_SHELL(submenu_file), file_newTab);
	gtk_menu_shell_append(GTK_MENU_SHELL(submenu_file), file_sep1);

	gtk_menu_shell_append(GTK_MENU_SHELL(submenu_newDoc), newDoc_empty);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_newDoc), submenu_newDoc);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menubar_file), submenu_file);

	gtk_menu_shell_append(GTK_MENU_SHELL(submenu_file), file_newDoc);
	gtk_menu_shell_append(GTK_MENU_SHELL(submenu_file), file_sep2);
	gtk_menu_shell_append(GTK_MENU_SHELL(submenu_file), file_quit);

	edit_copy = gtk_menu_item_new_with_label("Copy");
	edit_cut = gtk_menu_item_new_with_label("Cut");
	edit_paste = gtk_menu_item_new_with_label("Paste");

	submenu_edit = gtk_menu_new();
	gtk_menu_shell_append(GTK_MENU_SHELL(submenu_edit), edit_copy);
	gtk_menu_shell_append(GTK_MENU_SHELL(submenu_edit), edit_cut);
	gtk_menu_shell_append(GTK_MENU_SHELL(submenu_edit), edit_paste);

	menubar_edit = gtk_menu_item_new_with_label("Edit");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menubar_edit), submenu_edit);



	gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), menubar_file);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), menubar_edit);


	g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	g_signal_connect(G_OBJECT(file_quit), "activate", G_CALLBACK(gtk_main_quit), NULL);

	gtk_widget_show_all(window);

	gtk_main();

	return 0;
}
