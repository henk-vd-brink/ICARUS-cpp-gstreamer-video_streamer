#!/bin/bash

gst-launch-1.0 -e udpsrc port=3100 \
    ! application/x-rtp,payload=96 \
    ! rtph264depay \
    ! avdec_h264 \
    ! jpegenc \
    ! avimux \
    ! filesink location=mjpeg.avi