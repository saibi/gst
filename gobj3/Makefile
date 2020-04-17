main: main.c hello-app.c hello-app.h
	gcc -Wall -o main main.c hello-app.c `pkg-config --cflags --libs gobject-2.0`

clean:
	rm -f main *.o
