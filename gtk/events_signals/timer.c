#include <gtk/gtk.h>
#include <cairo.h>
#include <glib/gprintf.h> // g_sprintf


gchar buf[256];

gboolean on_expose_event(GtkWidget * widget, GdkEventExpose *event, gpointer data)
{
	cairo_t *cr;

	cr = gdk_cairo_create(widget->window);

	cairo_move_to(cr, 30, 30);
	cairo_set_font_size(cr, 15);
	cairo_show_text(cr, buf);

	cairo_destroy(cr);

	return FALSE;
}

gboolean time_handler(GtkWidget *widget)
{
	if ( widget->window == NULL)
		return FALSE;

	GDateTime *now = g_date_time_new_now_local();
	gchar *my_time = g_date_time_format(now, "%H:%M:%S");

	g_sprintf(buf, "%s", my_time);

	g_free(my_time);
	g_date_time_unref(now);

	gtk_widget_queue_draw(widget);

	return TRUE;
}


int main(int argc, char *argv[])
{
	GtkWidget *window;
	GtkWidget *darea;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
	gtk_container_set_border_width(GTK_CONTAINER(window), 5);
	gtk_window_set_title(GTK_WINDOW(window), "timer");

	darea = gtk_drawing_area_new();
	gtk_container_add(GTK_CONTAINER(window), darea);

	g_signal_connect(darea, "expose-event", G_CALLBACK(on_expose_event), NULL);

	g_timeout_add(1000, (GSourceFunc)time_handler, (gpointer)window);

	g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	gtk_widget_show_all(window);
	time_handler(window);

	gtk_main();

	return 0;
}





