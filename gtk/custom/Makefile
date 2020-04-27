all: main.c mycpu.c mycpu.h
	gcc -Wall -o main main.c mycpu.c `pkg-config --cflags --libs gtk+-2.0`



# for rk3399pc cross compile - not working

CROSS_COMPILE=/opt/gcc-linaro-7.3.1-2018.05-i686_aarch64-linux-gnu/bin/aarch64-linux-gnu-

CC=$(CROSS_COMPILE)gcc
LD=$(CROSS_COMPILE)ld
AR=$(CROSS_COMPILE)ar


SYSROOT=/opt/rootfs-rk3399pc-ubuntu18.04

CFLAGS=	--sysroot=$(SYSROOT) \
	-Wall -Wstrict-prototypes -Wmissing-declarations  \
	-Winline -Wshadow -Wreturn-type -Wsign-compare -Wundef \
	-Wpointer-arith -Wcast-align -Wbad-function-cast \
	-I. \
	-pthread -I$(SYSROOT)/usr/include/gtk-3.0 -I$(SYSROOT)/usr/include/at-spi2-atk/2.0 -I$(SYSROOT)/usr/include/at-spi-2.0 -I$(SYSROOT)/usr/include/dbus-1.0 -I$(SYSROOT)/usr/lib/aarch64-linux-gnu/dbus-1.0/include -I$(SYSROOT)/usr/include/gtk-3.0 -I$(SYSROOT)/usr/include/gio-unix-2.0/ -I$(SYSROOT)/usr/include/cairo -I$(SYSROOT)/usr/include/pango-1.0 -I$(SYSROOT)/usr/include/harfbuzz -I$(SYSROOT)/usr/include/pango-1.0 -I$(SYSROOT)/usr/include/atk-1.0 -I$(SYSROOT)/usr/include/cairo -I$(SYSROOT)/usr/include/pixman-1 -I$(SYSROOT)/usr/include/freetype2 -I$(SYSROOT)/usr/include/libpng16 -I$(SYSROOT)/usr/include/freetype2 -I$(SYSROOT)/usr/include/libpng16 -I$(SYSROOT)/usr/include/gdk-pixbuf-2.0 -I$(SYSROOT)/usr/include/libpng16 -I$(SYSROOT)/usr/include/glib-2.0 -I$(SYSROOT)/usr/lib/aarch64-linux-gnu/glib-2.0/include



LFLAGS = -Wl,-rpath-link,$(SYSROOT)/usr/lib/aarch64-linux-gnu -Wl,-rpath-link,$(SYSROOT)/lib/aarch64-linux-gnu --sysroot=$(SYSROOT)

LIBS= \
	-lgtk-3 -lgdk-3 -lpangocairo-1.0 -lpango-1.0 -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0


rk3399pc: main.c mycpu.c mycpu.h
	$(CC) $(CFLAGS) -o main main.c mycpu.c $(LFLAGS) $(LIBS)



clean:
	rm -rf main *.o


