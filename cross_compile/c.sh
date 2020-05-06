#!/bin/bash

SRC=basic-tutorial-1.c
CC=/opt/gcc-linaro-7.3.1-2018.05-i686_aarch64-linux-gnu/bin/aarch64-linux-gnu-gcc 
SYSROOT=/opt/rootfs-rk3399pc-ubuntu18.04 

$CC --sysroot=$SYSROOT -pthread -I$SYSROOT/usr/include/gstreamer-1.0 -I$SYSROOT/usr/include/glib-2.0 -I$SYSROOT/usr/lib/aarch64-linux-gnu/glib-2.0/include -Wl,-rpath-link,$SYSROOT/usr/lib/aarch64-linux-gnu -Wl,-rpath-link,$SYSROOT/lib/aarch64-linux-gnu -lgstreamer-1.0 -lgobject-2.0 -lglib-2.0 $SRC
