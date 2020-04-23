#include <gtk/gtk.h>

int main(int argc, char *argv[])
{
	GtkWidget *window;
	GtkWidget *label;
	
	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
	gtk_window_set_title(GTK_WINDOW(window), "No sleep");
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);

	label = gtk_label_new("I've always been to lame\n\
To see what's before me\nAnd I know nothing sweeter than\nChampaign from last New Years\nSweet music in ears\nAnd a night full of no fears\n\nBut If I had one wish fulfilled tonight\nI'd ask for the sun to never rise\nIf God passed a mic to me to speak\nI'd say \"Stay in bed, world,\nSleep in peace");

	gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
	gtk_container_add(GTK_CONTAINER(window), label);

	g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	gtk_widget_show_all(window);

	gtk_main();

	return 0;
}




