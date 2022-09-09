#!/bin/bash

while getopts w:h:c: flag
do
    case "${flag}" in
        w) caps_width=${OPTARG};;
        h) caps_height=${OPTARG};;
        c) clients=${OPTARG};;
    esac
done

echo "caps_width: $caps_width";
echo "caps_height: $caps_height";
echo "clients: $clients";


gst-launch-1.0 v4l2src device=/dev/video0 \
	! videoconvert \
	! video/x-raw,height=$caps_height,width=$caps_width \
	! videoconvert \
	! x264enc tune=zerolatency \
	! rtph264pay \
	! multiudpsink clients="$clients" sync=false