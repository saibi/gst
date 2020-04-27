#include "mycpu.h"

void cb_changed(GtkRange *range, GtkWidget *cpu)
{
	my_cpu_set_percent(MY_CPU(cpu), gtk_range_get_value(range));
}

int main(int argc, char *argv[])
{
	GtkWidget * window;
	GtkWidget *hbox;
	GtkWidget *cpu;
	GtkWidget *scale;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 150, 100);
	gtk_window_set_title(GTK_WINDOW(window), "MyCpu");
	gtk_container_set_border_width(GTK_CONTAINER(window), 5);

	hbox = gtk_hbox_new(FALSE, 25);
	gtk_container_add(GTK_CONTAINER(window), hbox);


	cpu = my_cpu_new();
	gtk_box_pack_start(GTK_BOX(hbox), cpu, FALSE, FALSE, 0);

	scale = gtk_vscale_new_with_range(0, 100, 1);
	gtk_scale_set_draw_value(GTK_SCALE(scale), FALSE);
	gtk_range_set_inverted(GTK_RANGE(scale), TRUE);
	gtk_box_pack_start(GTK_BOX(hbox), scale, FALSE, FALSE, 0);

	g_signal_connect(scale, "value-changed", G_CALLBACK(cb_changed), G_OBJECT(cpu));

	g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	gtk_widget_show_all(window);

	gtk_main();

	return 0;
}
