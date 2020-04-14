#include "edc-host.h"

#include <stdio.h>

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

		g_object_unref(host);
	}

	return 0;
}
