#include <glib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	GList * list = NULL;

	list = g_list_append(list, "Hello world!");

	printf("The first item is '%s'\n", (char*)g_list_first(list)->data);

	return 0;
}
