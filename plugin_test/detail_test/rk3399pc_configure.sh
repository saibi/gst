#!/bin/bash 
export CROSS_COMPILE="/opt/gcc-linaro-7.3.1-2018.05-i686_aarch64-linux-gnu/bin/aarch64-linux-gnu"
export AR=${CROSS_COMPILE}-ar
export AS=${CROSS_COMPILE}-as
export LD=${CROSS_COMPILE}-ld
export CC=${CROSS_COMPILE}-gcc
export NM=${CROSS_COMPILE}-nm
export RANLIB=${CROSS_COMPILE}-ranlib
 

# 컴파일 플래그 설정

export CFLAGS=""                                   
export CPPFLAGS=""

# 링크 플래그 설정
export LDFLAGS=""

# 추가 라이브러리
export LIBS=""


export CROSS=aarch64-linux-gnu
 
export SYSROOT=/opt/rootfs-rk3399pc-ubuntu18.04

export GST_CFLAGS="--sysroot=${SYSROOT} -pthread -I${SYSROOT}/usr/include -I${SYSROOT}/usr/include/gstreamer-1.0 -I${SYSROOT}/usr/include/glib-2.0 -I${SYSROOT}/usr/lib/aarch64-linux-gnu/glib-2.0/include -Wall"

export GST_LIBS="-Wl,-rpath-link,${SYSROOT}/usr/lib/aarch64-linux-gnu -Wl,-rpath-link,${SYSROOT}/lib/aarch64-linux-gnu -lgstreamer-1.0 -lgobject-2.0 -lglib-2.0"

./configure --prefix=/tmp/build --target=${CROSS} --host=${CROSS} --build=i686-pc-linux-gnu --with-sysroot=${SYSROOT}
