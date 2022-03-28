## About the Project
This repository contains a containerized Gstreamer pipeline implementation.

## Getting Started

### Preqrequisites
- Docker
- Linux device
- USB camera

### Installation
```
git clone https://github.com/henk-vd-brink/ICARUS-cpp-video_streamer.git
cd ICARUS-cpp-video_streamer
```

### Build
```
make build-container
```

### Run
```
make run
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

### Inspect Camera

Possible caps
```
v4l2-ctl -d /dev/video0 --list-formats-ext
```





