SRCS=$(wildcard *.c)
OBJS=$(SRCS:%.c=%.o)
APPS=$(SRCS:%.c=%.app)


all: $(APPS)

.c.o:
	gcc -Wall -c $< -o $@ `pkg-config --cflags gtk+-2.0`

.SUFFIXES: .o .app
.o.app:
	gcc -Wall -o $@ $< `pkg-config --cflags --libs gtk+-2.0`

clean:
	rm -rf *.app *.o

