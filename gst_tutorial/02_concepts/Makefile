Q=@
ifdef V
	ifneq ($(V),0)
		Q =
		SOPTION =
	endif
endif


INC = -I/usr/include/gstreamer-1.0 -I/usr/lib/x86_64-linux-gnu/gstreamer-1.0/include -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include

ifdef C
	ifneq ($(C),0)
		CROSS_COMPILE=/opt/gcc-linaro-7.3.1-2018.05-i686_aarch64-linux-gnu/bin/aarch64-linux-gnu-
		SYSROOT=/opt/rootfs-rk3399pc-ubuntu18.04

		CFLAGS += --sysroot=$(SYSROOT) 
		LFLAGS += --sysroot=$(SYSROOT) -Wl,-rpath-link,$(SYSROOT)/usr/lib/aarch64-linux-gnu -Wl,-rpath-link,$(SYSROOT)/lib/aarch64-linux-gnu 
		

		INC=-I$(SYSROOT)/usr/include/gstreamer-1.0 -I$(SYSROOT)/usr/include/glib-2.0 -I$(SYSROOT)/usr/lib/aarch64-linux-gnu/glib-2.0/include
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
	-I. \
	$(INC)

LFLAGS += 
LIBS = -lgstreamer-1.0 -lgobject-2.0 -lglib-2.0


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
