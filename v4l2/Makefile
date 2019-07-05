OS=$(shell uname -o)
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
	-pthread -I$(SYSROOT)/usr/include/gstreamer-1.0 -I$(SYSROOT)/usr/include/glib-2.0 -I$(SYSROOT)/usr/lib/aarch64-linux-gnu/glib-2.0/include
	#`pkg-config --cflags gstreamer-audio-1.0 gstreamer-video-1.0 gtk+-3.0 gstreamer-1.0 gstreamer-pbutils-1.0` 

LFLAGS = -Wl,-rpath-link,$(SYSROOT)/usr/lib/aarch64-linux-gnu -Wl,-rpath-link,$(SYSROOT)/lib/aarch64-linux-gnu --sysroot=$(SYSROOT)

LIBS= -lgstvideo-1.0 -lgstreamer-1.0 -lgobject-2.0 -lglib-2.0
	#`pkg-config --libs gstreamer-audio-1.0 gstreamer-video-1.0 gtk+-3.0  gstreamer-1.0 gstreamer-pbutils-1.0` 


ALL_SRC=$(wildcard *.c)
ALL_OBJ=$(ALL_SRC:%.c=%.o)

TARGET=v4l2

all: $(ALL_OBJ)
	$(CC) $(LFLAGS) -o $(TARGET) $(ALL_OBJ) $(LIBS)

%.o : %.c
	$(CC) $(CFLAGS) -c $< 


clean:
	rm -f *.o $(ALL_OBJ) $(TARGET)
