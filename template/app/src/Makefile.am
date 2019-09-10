# name of your binary
bin_PROGRAMS = gst-app tester

# list of source files
# the prefix is the name of the binary
gst_app_SOURCES = main.c play.c

# list of headers we're not going to install
noinst_HEADERS = gst-app.h play.h

# our CFLAGS and LDFLAGS used for compiling and linking
# make sure you prefix these with the name of your binary
gst_app_CFLAGS = $(GST_CFLAGS)
gst_app_LDFLAGS = $(GST_LIBS)



tester_SOURCES = tester.c

tester_CFLAGS = $(GST_CFLAGS)
tester_LDFLAGS = $(GST_LIBS)
