#include <gtk/gtk.h>

void toggle_title(GtkWidget * widget, gpointer window)
{
	if ( gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))) 
	{
		gtk_window_set_title(window, "GtkCheckButton");
	}
	else
	{
		gtk_window_set_title(window, "");
	}
}

int main(int argc, char *argv[])
{
	GtkWidget *window;
	GtkWidget *halign;
	GtkWidget *btn;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
	gtk_window_set_title(GTK_WINDOW(window), "GtkCheckButton");
	gtk_container_set_border_width(GTK_CONTAINER(window), 5);

	halign = gtk_alignment_new(0, 0, 0, 0);
	gtk_container_add(GTK_CONTAINER(window), halign);

	btn = gtk_check_button_new_with_label("Show title");
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(btn), TRUE);

	GTK_WIDGET_UNSET_FLAGS(btn, GTK_CAN_FOCUS);
	gtk_container_add(GTK_CONTAINER(halign), btn);
	
	g_signal_connect(G_OBJECT(btn), "clicked", G_CALLBACK(toggle_title), G_OBJECT(window));

	g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	gtk_widget_show_all(window);

	gtk_main();

	return 0;
}

