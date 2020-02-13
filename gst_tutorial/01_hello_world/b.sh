#!/bin/bash
# host compile
gcc basic-tutorial-1.c -Wall `pkg-config --cflags --libs gstreamer-1.0`
