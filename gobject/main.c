#include "edc-host.h"

#include <stdio.h>

int main(void)
{
	EdcHost *host = edc_host_new();

	printf("hello\n");

	edc_object_unref(host);

	return 0;
}
