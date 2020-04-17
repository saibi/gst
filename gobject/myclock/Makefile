main: main.c myclock.c myclock.h
	gcc -Wall -o main main.c myclock.c `pkg-config --cflags --libs gobject-2.0`



clean:
	rm -f main *.o
