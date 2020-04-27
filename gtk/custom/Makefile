all: main.c mycpu.c mycpu.h
	gcc -Wall -o main main.c mycpu.c `pkg-config --cflags --libs gtk+-2.0`

clean:
	rm -rf main *.o

