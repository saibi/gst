#!/bin/bash 
gst-launch-1.0 --gst-plugin-path=/tmp/gstreamer-1.0 videotestsrc ! video/x-raw,width=200,height=200,format=NV12 ! myfilter int=128 ! videoconvert ! autovideosink

