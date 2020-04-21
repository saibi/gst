all: version.c
	gcc -Wall -o version version.c `pkg-config --cflags --libs gtk+-2.0`

clean:
	rm -rf version *.o

