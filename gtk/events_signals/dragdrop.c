#include <gtk/gtk.h>

gboolean on_button_press(GtkWidget *widget, GdkEventButton *event, GdkWindowEdge edge) 
{
	if ( event->type == GDK_BUTTON_PRESS)
	{
		if ( event->button == 1 ) 
		{
			gtk_window_begin_move_drag(GTK_WINDOW(gtk_widget_get_toplevel(widget)), event->button, event->x_root, event->y_root, event->time);
		}
	}

	return TRUE;
}

int main(int argc, char *argv[])
{
	GtkWidget *window;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
	gtk_container_set_border_width(GTK_CONTAINER(window), 5);
	gtk_window_set_title(GTK_WINDOW(window), "drag & drop");
	gtk_window_set_decorated(GTK_WINDOW(window), FALSE);
	gtk_widget_add_events(window, GDK_BUTTON_PRESS_MASK);

	g_signal_connect(G_OBJECT(window), "button-press-event", G_CALLBACK(on_button_press), NULL);

	g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	gtk_widget_show_all(window);

	gtk_main();

	return 0;
}




