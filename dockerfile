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

RUN cmake .. && make
CMD ./cpp-gstreamer-stream_to_localhost /dev/video0


