#include <glib.h>
#include <stdio.h>

gint my_comparator(gconstpointer item1, gconstpointer item2)
{
	return g_ascii_strcasecmp(item1, item2);
}


int main(int argc, char *argv[])
{
	GSList* list = g_slist_append(NULL, g_strdup("Chicago"));

	list = g_slist_append(list, g_strdup("Boston"));
	list = g_slist_append(list, g_strdup("Albany"));

	printf("The first item is now '%s'\n", (char*)list->data);
	printf("The last item is now '%s'\n", (char*)g_slist_last(list)->data);

	printf("after g_slist_sort()\n");
	list = g_slist_sort(list, (GCompareFunc)my_comparator);

	printf("The first item is now '%s'\n", (char*)list->data);
	printf("The last item is now '%s'\n", (char*)g_slist_last(list)->data);


	printf("Now freeing each item\n");
	g_slist_foreach(list, (GFunc)g_free, NULL);
	g_slist_free(list);
	return 0;
}

