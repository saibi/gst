CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT("gstreamer tutorial - rk3399")

SET(CMAKE_VERBOSE_MAKEFILE true)
SET(CROSS_COMPILE /opt/gcc-linaro-7.3.1-2018.05-i686_aarch64-linux-gnu/bin/aarch64-linux-gnu-)
SET(CC ${CROSS_COMPILE}gcc)
SET(LD ${CROSS_COMPILE}ld)
SET(AR ${CROSS_COMPILE}ar)

SET(CMAKE_C_COMPILER ${CC})
SET(ROOTFS /opt/rootfs-rk3399pc-ubuntu18.04)
SET(COMMON_FLAGS "--sysroot=${ROOTFS} -g -Wall -W -pthread -pipe -march=armv8-a -mtune=cortex-a57.cortex-a53")

SET(RPATH_FLAGS "-Wl,-rpath-link,${ROOTFS}/usr/lib/aarch64-linux-gnu:${ROOTFS}/lib/aarch64-linux-gnu")

SET(CMAKE_C_FLAGS ${COMMON_FLAGS})
SET(CMAKE_EXE_LINKER_FLAGS "${COMMON_FLAGS} ${RPATH_FLAGS}")


INCLUDE_DIRECTORIES(${ROOTFS}/usr/include/gstreamer-1.0 ${ROOTFS}/usr/include/glib-2.0 ${ROOTFS}/usr/lib/aarch64-linux-gnu/glib-2.0/include)

LINK_LIBRARIES(gstreamer-1.0 gobject-2.0 glib-2.0)

SET(src basic-tutorial-1.c)
ADD_EXECUTABLE(tutorial01 ${src} )
