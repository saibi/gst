main: main.c some-object.c some-object.h
	gcc -Wall -o main main.c some-object.c `pkg-config --cflags --libs gobject-2.0`



clean:
	rm -f main *.o
