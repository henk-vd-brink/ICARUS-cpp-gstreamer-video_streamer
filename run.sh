#!/bin/bash

docker kill gst
docker rm gst --force

docker build -t test .
docker run --name gst -d --device /dev/video0 test
