#include <stdio.h>
#include "foo.h"

int main(int argc, char *argv[])
{
	printf("Hello world V%d\n", VER);

	foo();

#ifdef HELLO
	printf("hello\n");
#endif

#ifdef WORLD 
	printf("world\n");
#endif


	return 0;

}
