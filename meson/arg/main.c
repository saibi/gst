#include <stdio.h>
#include "foo.h"

int main(int argc, char *argv[])
{
	printf("Hello world V%d\n", VER);

	foo();

	return 0;

}
