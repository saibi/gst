Q=@
ifdef V
	ifneq ($(V),0)
		Q =
		SOPTION =
	endif
endif

INC_GSTREAMER = -I/usr/include/gstreamer-1.0 -I/usr/lib/x86_64-linux-gnu/gstreamer-1.0/include -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include

INC_GTK = -I/usr/include/gtk-3.0 -I/usr/include/at-spi2-atk/2.0 -I/usr/include/at-spi-2.0 -I/usr/include/dbus-1.0 -I/usr/lib/x86_64-linux-gnu/dbus-1.0/include -I/usr/include/gtk-3.0 -I/usr/include/gio-unix-2.0/ -I/usr/include/mirclient -I/usr/include/mircore -I/usr/include/mircookie -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/harfbuzz -I/usr/include/pango-1.0 -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng12 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/libpng12 

INC = $(INC_GTK) $(INC_GSTREAMER) -I.

ifdef C
	ifneq ($(C),0)
		CROSS_COMPILE=/opt/gcc-linaro-7.3.1-2018.05-i686_aarch64-linux-gnu/bin/aarch64-linux-gnu-
		SYSROOT=/opt/rootfs-rk3399pc-ubuntu18.04

		CFLAGS += --sysroot=$(SYSROOT) 
		LFLAGS += --sysroot=$(SYSROOT) -Wl,-rpath-link,$(SYSROOT)/usr/lib/aarch64-linux-gnu -Wl,-rpath-link,$(SYSROOT)/lib/aarch64-linux-gnu 
		

		INC_CROSS_GSTREAMER=-I$(SYSROOT)/usr/include/gstreamer-1.0 -I$(SYSROOT)/usr/include/glib-2.0 -I$(SYSROOT)/usr/lib/aarch64-linux-gnu/glib-2.0/include

		INC_RK3399_GTK= -I/usr/include/orc-0.4 -I/usr/include/gtk-3.0 -I/usr/include/at-spi2-atk/2.0 -I/usr/include/at-spi-2.0 -I/usr/include/dbus-1.0 -I/usr/lib/aarch64-linux-gnu/dbus-1.0/include -I/usr/include/gio-unix-2.0/ -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/harfbuzz -I/usr/include/pango-1.0 -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/libpng16 
		INC_CROSS_GTK = $(INC_RK3399_GTK:-I%=-I$(SYSROOT)%)


		INC = $(INC_CROSS_GTK) $(INC_CROSS_GSTREAMER) -I.
	endif
endif



OS=$(shell uname -o)

CC=$(CROSS_COMPILE)gcc
LD=$(CROSS_COMPILE)ld
AR=$(CROSS_COMPILE)ar


CFLAGS += -Wall -Wstrict-prototypes -Wmissing-declarations  \
	-Winline -Wshadow -Wreturn-type -Wsign-compare -Wundef \
	-Wpointer-arith -Wcast-align -Wbad-function-cast \
	-pthread \
	$(INC)

LFLAGS += 


LIB_GSTREAMER = -lgstreamer-1.0 -lgobject-2.0 -lglib-2.0
LIB_GSTREAMER_VIDEO = -lgstvideo-1.0 -lgstbase-1.0 
LIB_GTK = -lgtk-3 -lgdk-3 -lpangocairo-1.0 -lpango-1.0 -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 


LIBS = $(LIB_GTK) $(LIB_GSTREAMER_VIDEO) $(LIB_GSTREAMER)

	# normal `pkg-config --cflags gstreamer-1.0`
	# for gtk-player `pkg-config --cflags gstreamer-video-1.0 gtk+-3.0  gstreamer-1.0` 
	#`pkg-config --cflags gstreamer-video-1.0 gstreamer-1.0` 
#`pkg-config --cflags gstreamer-audio-1.0 gstreamer-video-1.0 gtk+-3.0 gstreamer-1.0 gstreamer-pbutils-1.0` 


	#`pkg-config --libs gstreamer-video-1.0 gstreamer-1.0` 
	#`pkg-config --libs gstreamer-audio-1.0 gstreamer-video-1.0 gtk+-3.0  gstreamer-1.0 gstreamer-pbutils-1.0` 
	#-D_GCC_  
	#-Wimplicit-prototypes # -ansi-pedantic

ALL_SRC=$(wildcard *.c)
ALL_OBJ=$(ALL_SRC:%.c=%.o)
ALL_BIN=$(ALL_SRC:%.c=%)

all: $(ALL_OBJ)

%.o : %.c
	$(Q)$(CC) $(CFLAGS) -c $< 
	$(Q)$(CC) $(LFLAGS) -o $(basename $@) $@ $(LIBS)


clean:
	$(Q)rm -f *.o test $(ALL_BIN)


#	$(Q)$(CC) $(LFLAGS) -o test $(ALL_OBJ) $(LIBS)
