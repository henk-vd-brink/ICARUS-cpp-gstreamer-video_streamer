FROM ubuntu:18.04

ARG DEBIAN_FRONTEND=noninteractive

ENV TZ=Europe

RUN apt-get update
 

RUN apt-get install -y libgstreamer1.0-dev \
	libgstreamer-plugins-base1.0-dev \
	libgstreamer-plugins-bad1.0-dev \
	gstreamer1.0-plugins-base \
	gstreamer1.0-plugins-good \
	gstreamer1.0-plugins-bad \
	gstreamer1.0-plugins-ugly \
	gstreamer1.0-libav \
	gstreamer1.0-doc \
	gstreamer1.0-tools \
	gstreamer1.0-x \
	gstreamer1.0-alsa \
	gstreamer1.0-gl \
	gstreamer1.0-gtk3 \
	gstreamer1.0-qt5 \ 
	gstreamer1.0-pulseaudio

RUN apt-get install cmake -y

WORKDIR /code

ADD CMakeLists.txt .
COPY src /code/src 


WORKDIR /code/build

ENV GST_DEBUG=4

RUN cmake .. && make

#CMD ./cpp-gstreamer-stream_to_localhost /dev/video0
CMD gst-launch-1.0 v4l2src device=/dev/video0 ! video/x-raw,height=1080,width=1920,framframerate=30/1 ! decodebin ! videoconvert ! x264enc tune=zerolatency ! rtph264pay ! udpsink host=192.168.178.34 port=5000



