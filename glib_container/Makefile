SRCS=$(wildcard *.c)
OBJS=$(SRCS:%.c=%.o)
APPS=$(SRCS:%.c=%.app)

all: $(APPS)



clean:
	rm -rf *.app *.o

.SUFFIXES: .o .app
.o.app:
	gcc -Wall -o $@ $< `pkg-config --libs glib-2.0`

.c.o:
	gcc -Wall -c $< -o $@ `pkg-config --cflags glib-2.0`
