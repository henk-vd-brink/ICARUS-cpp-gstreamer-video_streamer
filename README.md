## About the Project
This repository contains a dockerized Gstreamer pipeline implemented in C++. The pipeline can be adjusted to send to a arbitrary ip.

## Getting Started

### Preqrequisites
- Docker
- Linux device (e.g. Raspberry Pi)
- USB camera

### Installation
```
git clone https://github.com/henk-vd-brink/ICARUS-cpp-video_stream.git
cd ICARUS-cpp-video_stream
```

### Build
```
docker build -t video_streamer_image .
```

### Run
```
docker run --name video_streamer --device /dev/video0 -d --privileged video_streamer_image
```

## Additional information

Stream:
```
 gst-launch-1.0 v4l2src device=/dev/video0 ! decodebin ! videoconvert ! x264enc tune=zerolatency ! rtph264pay ! udpsink host=192.168.178.34 port=5000
```
 
Receive:
```
 gst-launch-1.0 -e udpsrc port=5000 ! application/x-rtp,media=video,clock-rate=90000,encoding-name=H264,payload=96 ! rtph264depay ! avdec_h264 ! jpegenc ! avimux ! filesink location=mjpeg.avi
```

### 
Inspect camera

Possible caps
```
v4l2-ctl -d /dev/video0 --list-formats-ext
```





