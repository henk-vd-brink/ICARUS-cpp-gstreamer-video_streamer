## About the Project
This repository contains an out-of-the box application to set up a streaming service.

## Getting Started

### Prerequisites
- Linux device
- Docker
- USB camera

### Installation
```
git clone https://github.com/henk-vd-brink/ICARUS-docker-gstreamer.git
cd ICARUS-docker-gstreamer
```

### Build
```
docker build -t icarus-gstreamer-image .
```

### Run
```
docker run --name icarus-vs --device /dev/video0 -d --rm icarus-gstreamer-image
```

## Additional Information

Source to h264 stream:
```
 gst-launch-1.0 v4l2src device=/dev/video0 ! decodebin ! videoconvert ! x264enc tune=zerolatency ! rtph264pay ! udpsink host=192.168.178.34 port=5000
```
 
h264 stream to file:
```
 gst-launch-1.0 -e udpsrc port=5000 ! application/x-rtp,media=video,clock-rate=90000,encoding-name=H264,payload=96 ! rtph264depay ! avdec_h264 ! jpegenc ! avimux ! filesink location=mjpeg.avi
```

h264 stream to screen (Linux)
```
gst-launch-1.0 -vv udpsrc port=6502 ! application/x-rtp,payload=96 ! rtph264depay ! avdec_h264 ! videoconvert ! xvimagesink sync=false
```

h264 stream to screen (Windows)
```
gst-launch-1.0 -vv udpsrc port=6502 ! application/x-rtp,payload=96 ! rtph264depay ! avdec_h264 ! videoconvert ! autovideosink sync=false
```

VLC test.sdp
```
v=0
c=IN IP4 127.0.0.1
m=video 3100 RTP/AVP 96 
a=rtpmap:96 H264/90000
```

### Inspect Camera

Possible caps
```
v4l2-ctl -d /dev/video0 --list-formats-ext
```
