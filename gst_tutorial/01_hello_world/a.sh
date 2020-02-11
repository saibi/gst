#!/bin/bash

sysroot=/opt/rootfs-rk3399pc-ubuntu18.04 
/opt/gcc-linaro-7.3.1-2018.05-i686_aarch64-linux-gnu/bin/aarch64-linux-gnu-gcc basic-tutorial-1.c --sysroot=$sysroot -pthread -I$sysroot/usr/include -I$sysroot/usr/include/gstreamer-1.0 -I$sysroot/usr/include/glib-2.0 -I$sysroot/usr/lib/aarch64-linux-gnu/glib-2.0/include -Wl,-rpath-link,$sysroot/usr/lib/aarch64-linux-gnu -Wl,-rpath-link,$sysroot/lib/aarch64-linux-gnu -lgstreamer-1.0 -lgobject-2.0 -lglib-2.0 
