main: main.c viewer_file.c viewer_file.h 
	gcc -Wall -o main main.c viewer_file.c `pkg-config --cflags --libs gobject-2.0`



clean:
	rm -f main *.o
