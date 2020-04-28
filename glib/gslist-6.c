#include <glib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	GSList* list1 = NULL;

	list1 = g_slist_append(list1, "first");
	list1 = g_slist_append(list1, "second");


	GSList* list2 = NULL;
	list2 = g_slist_append(list2, "third");
	list2 = g_slist_append(list2, "fourth");

	GSList* both = g_slist_concat(list1, list2);

	printf("The third item in the concatenated list is '%s'\n", (const char*)g_slist_nth_data(both, 2));

	GSList* reversed = g_slist_reverse(both);
	printf("The first item in the reversed list is '%s'\n", (const char*)reversed->data);


	printf("list1 %p, list2 %p, both %p, reversed %p\n", list1, list2, both, reversed);

	g_slist_free(reversed);

	return 0;
}

