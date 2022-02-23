# gstreamer-stream_to_browser

 gst-launch-1.0 v4l2src device=/dev/video0 ! decodebin ! videoconvert ! x264enc tune=zerolatency ! rtph264pay ! udpsink host=192.168.178.34 port=5000
 
 gst-launch-1.0 -e udpsrc port=5000 ! application/x-rtp,media=video,clock-rate=90000,encoding-name=H264,payload=96 ! rtph264depay ! avdec_h264 ! jpegenc ! avimux ! filesink location=mjpeg.avi

