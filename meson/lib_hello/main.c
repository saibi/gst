#include <stdio.h>
#include "foo.h"

extern void bar(void);

int main(int argc, char *argv[])
{
	printf("Hello world\n");

	foo();
	bar();

	return 0;

}
