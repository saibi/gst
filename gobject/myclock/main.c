#include "myclock.h"

#include <stdio.h>


static void clock_datetime_changed(GObject *object, GParamSpec *pspec, gpointer data)
{
	MyClock *clock = MY_CLOCK(object);
	GDateTime *datetime;
	gchar *str;
	gchar *msg = data;

	datetime = my_clock_get_date_time(clock);
	str = g_date_time_format(datetime, "%x\n%H:%M:%S");

	g_print("%s, %s\n", msg, str);
	g_free(str);
	g_date_time_unref(datetime);
}

static void clock_changed(MyClock *cl, GDateTime *datetime, gpointer user_data)
{
	g_print("clock_changed : %s\n", my_clock_get_text(cl));
}


int main(void)
{
	GMainLoop *loop;


	MyClock *clock;

	clock = my_clock_new();

	g_signal_connect(clock, "notify::datetime", G_CALLBACK(clock_datetime_changed), "hohoho" );
	g_signal_connect(clock, "changed", G_CALLBACK(clock_changed), 0 );

	g_print("loop_run\n");
	loop = g_main_loop_new(NULL, FALSE);
	g_main_loop_run(loop);

	g_print("loop_unref\n");
	g_main_loop_unref(loop);

	return 0;
}
