#include <glib.h>
#include <stdio.h>

gint my_finder(gconstpointer item)
{
	return g_ascii_strcasecmp(item, "second");
}

int main(int argc, char *argv[])
{
	GSList* list = g_slist_append(NULL, g_strdup("first"));

	printf("dbg0\n");
	gchar *str = g_strdup("second");

	list = g_slist_append(list, str);
	list = g_slist_append(list, g_strdup("third"));

	printf("dbg1\n");

	GSList* item = g_slist_find(list, str);
	printf("dbg2\n");
	printf("This should be the 'second' item: '%s'\n", item ? (const char*)item->data : "(null)");

	item = g_slist_find_custom(list, NULL, (GCompareFunc)my_finder);
	printf("Again, this should be the 'second' item: '%s'\n", (const char*)item->data);

	item = g_slist_find(list, "delta");
	printf("'delta' is not in the list, so we get: '%s'\n", item ? (const char*)item->data : "(null)");


	g_slist_foreach(list, (GFunc)g_free, NULL);

	g_slist_free(list);
	return 0;
}
