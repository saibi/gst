#!/bin/bash 
gst-launch-1.0 udpsrc port=5000 ! "application/x-rtp, media=(string)video, clock-rate=(int)90000, encoding-name=(string)JPEG, a-framerate=(string)30.000000, payload=(int)26, ssrc=(uint)4041571713, timestamp-offset=(uint)3564984763, seqnum-offset=(uint)18037" ! rtpjpegdepay ! jpegdec ! autovideosink
