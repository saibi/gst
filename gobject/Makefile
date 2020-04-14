main: main.c edc-host.c edc-host.h edc-object.h myclock.c myclock.h
	gcc -Wall -o main main.c edc-host.c myclock.c `pkg-config --cflags --libs gobject-2.0`



clean:
	rm -f main *.o
