#!/bin/bash

gst-launch-1.0 v4l2src device=/dev/video0 \
	! videoconvert \
	! video/x-raw,height=1080,width=1920 \
	! videoscale \
	! video/x-raw,height=270,width=480 \
	! videoconvert \
	! x264enc tune=zerolatency \
	! rtph264pay \
	! multiudpsink clients="127.0.0.1:3100" sync=false