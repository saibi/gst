#include <glib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	GSList* list = NULL;

	list = g_slist_append(list, "first");
	list = g_slist_append(list, "second");
	list = g_slist_append(list, "third");

	printf("The list is now %d items long, %p\n", g_slist_length(list), list);

	printf("The last item is '%s'\n", (gchar*)g_slist_last(list)->data);
	printf("The item at index '1' is '%s'\n", (gchar*)g_slist_nth(list, 1)->data);
	printf("Now the item at index '1' the easy way: '%s'\n", (gchar*)g_slist_nth_data(list, 1));
	printf("And the 'next' item after first item is '%s'\n", (gchar*)g_slist_next(list)->data);
	
	g_slist_free(list);

	return 0;
}




