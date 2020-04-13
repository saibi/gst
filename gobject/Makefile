main: main.c edc-host.c edc-host.h edc-object.h
	gcc -Wall -o main main.c edc-host.c `pkg-config --cflags --libs gobject-2.0`

clean:
	rm -f main *.o
