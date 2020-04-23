#include <gtk/gtk.h>

void select_color(GtkWidget *widget, gpointer label)
{
	GtkResponseType result;
	GtkColorSelection *colorsel;

	GtkWidget *dialog = gtk_color_selection_dialog_new("Font color");

	result = gtk_dialog_run(GTK_DIALOG(dialog));

	if ( result == GTK_RESPONSE_OK || result == GTK_RESPONSE_APPLY )
	{
		GdkColor color;

		colorsel = GTK_COLOR_SELECTION( GTK_COLOR_SELECTION_DIALOG(dialog)->colorsel);
		gtk_color_selection_get_current_color(colorsel, &color);

		gtk_widget_modify_fg(GTK_WIDGET(label), GTK_STATE_NORMAL, &color);
	}

	gtk_widget_destroy(dialog);
}

int main(int argc, char *argv[])
{
	GtkWidget *window;
	GtkWidget *label;
	GtkWidget *vbox;

	GtkWidget *toolbar;
	GtkToolItem *col;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
	gtk_window_set_title(GTK_WINDOW(window), "Color selection dialog");
	gtk_container_set_border_width(GTK_CONTAINER(window), 15);

	vbox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(window), vbox);

	toolbar = gtk_toolbar_new();
	gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);

	gtk_container_set_border_width(GTK_CONTAINER(toolbar), 2);


	col = gtk_tool_button_new_from_stock(GTK_STOCK_SELECT_COLOR);
	gtk_toolbar_insert(GTK_TOOLBAR(toolbar), col, -1);
	gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 5);

	label = gtk_label_new("* 012345 ZetCode ! ? #");
	gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
	gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 5);

	g_signal_connect(G_OBJECT(col), "clicked", G_CALLBACK(select_color), (gpointer)label);
	g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	gtk_widget_show_all(window);

	gtk_main();

	return 0;
}



