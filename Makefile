all: container-build run

container-build:
	sudo docker build -t icarus-cpp-streamer-image .

run:
	sudo docker run --name icarus-cpp-streamer --device /dev/video0 -d --privileged icarus-cpp-streamer-image
