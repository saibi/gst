SRCS=$(wildcard *.c)
OBJS=$(SRCS:%.c=%.o)
APPS=$(SRCS:%.c=%)


all: $(OBJS)
	gcc -Wall -o simple simple.o `pkg-config --libs gtk+-2.0`
	gcc -Wall -o center center.o `pkg-config --cflags --libs gtk+-2.0`


.c.o:
	gcc -Wall -c $< -o $@ `pkg-config --cflags gtk+-2.0`

clean:
	rm -rf app center *.o

