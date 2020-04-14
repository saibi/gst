#include "edc-host.h"
#include "myclock.h"

#include <stdio.h>

static void print_properties(GObject *object)
{
	GObjectClass *oclass;
	GParamSpec **specs;
	guint n;
	guint i;

	oclass = G_OBJECT_GET_CLASS(object);
	specs = g_object_class_list_properties(oclass, &n);
	for ( i = 0; i < n ; i++ )
	{
		GParamSpec *spec;
		GValue value = { 0 };
		gchar *str;

		spec = specs[i];

		g_value_init(&value, spec->value_type);
		g_object_get_property(G_OBJECT(object), spec->name, &value);
		str = g_strdup_value_contents(&value);

		g_print("property '%s' is '%s'\n", spec->name, str);

		g_value_unset(&value);
		g_free(str);
	}
}

static void property_notified(GObject *object, GParamSpec *pspec, gpointer data)
{
	GValue value = { 0 };
	gchar *str;

	g_value_init(&value, pspec->value_type);
	g_object_get_property(object, pspec->name, &value);

	str = g_strdup_value_contents(&value);

	g_print("property '%s' is set to '%s'\n", pspec->name, str);
	g_value_unset(&value);
	g_free(str);
}

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


int main(void)
{
	EdcHost *host = edc_host_new();

	printf("hello gobject\n");

	{
		GValue val = G_VALUE_INIT;
		printf("hello gvalue\n");

		g_value_init(&val, G_TYPE_STRING);
		g_value_set_static_string(&val, "my name");
		g_print("%s\n", g_value_get_string(&val));
		g_value_unset(&val);

	}

	g_object_set(host, "address", "127.0.0.1", "port", 8080, NULL);

	{
		gchar * address;
		gint port;

		printf("hello propery\n");

		address = edc_host_get_address(host);

		g_print("address = [%s]\n", address);
		g_free(address);

		g_object_get(host, "port", &port, "address", &address, NULL);
		g_print("port=%d, address=[%s]\n", port, address);
		g_free(address);
	}

	{
		GValue val = G_VALUE_INIT;
		g_value_init(&val, G_TYPE_INT);

		printf("hello get_property, port\n");

		g_object_get_property(G_OBJECT(host), "port", &val);

		g_print("port=%d\n", g_value_get_int(&val));

		g_value_unset(&val);

		g_value_init(&val, G_TYPE_STRING);

		printf("hello get_property, addr\n");

		g_object_get_property(G_OBJECT(host), "address", &val);

		g_print("address=[%s]\n", g_value_get_string(&val));

		g_value_unset(&val);


	}

	g_object_unref(host);


	{
		gchar *addr;
		gint port;

		host = g_object_new(EDC_TYPE_HOST, "address", "world.com", "port", 1818, NULL);

		g_object_get(host, "address", &addr, "port", &port, NULL);
		g_print("port=%d, address=[%s]\n", port, addr);

		g_free(addr);


		print_properties(G_OBJECT(host));

		g_object_unref(host);
	}

	{
		g_print("property signal\n");

		host = g_object_new(EDC_TYPE_HOST, NULL);

		g_signal_connect(host, "notify::address", G_CALLBACK(property_notified), NULL);
		g_signal_connect(host, "notify::port", G_CALLBACK(property_notified), NULL);

		g_object_set(host, "name", "your name", "address", "seoul", "port", 18, NULL);
		edc_host_set_address(host, "pusan");
		g_object_unref(host);
	}

	{
		GMainLoop *loop;


		MyClock *clock;

		clock = my_clock_new();

		g_signal_connect(clock, "notify::datetime", G_CALLBACK(clock_datetime_changed), "hohoho" );

		g_print("loop_run\n");
		loop = g_main_loop_new(NULL, FALSE);
		g_main_loop_run(loop);

		g_print("loop_unref\n");
		g_main_loop_unref(loop);
	}

	return 0;
}
