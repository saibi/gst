#include <glib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	GSList* list = NULL;
	GSList* iterator = NULL;

	list = g_slist_append(list, "first");
	list = g_slist_append(list, "second");
	list = g_slist_append(list, "third");

	for (iterator = list; iterator; iterator = iterator->next)
	{
		printf("Current item is '%s'\n", (const char*)iterator->data);
	}
	g_slist_free(list);
	return 0;
}


