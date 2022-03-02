#include <iostream>
#include <gst/gst.h>

int main(int argc, char *argv[])
{
	GstElement *pipeline;
	GstBus *bus;
	GstMessage *msg;
	GMainLoop *loop;
	GstStateChangeReturn ret;
	
	gst_init(&argc, &argv);

	/* Create empty pipeline */
	pipeline 	= gst_pipeline_new("pipeline");
	bus		= gst_element_get_bus (pipeline);

	/* Create the elements */
	GstElement *source, *decoder, *converter, *videoscaler, *encoder, *payloadencoder, *sink;
	
	source	 	= gst_element_factory_make ("v4l2src", "source");
	decoder 	= gst_element_factory_make ("decodebin", "decoder");
	converter	= gst_element_factory_make ("videoconvert", "converter");
	videoscaler	= gst_element_factory_make ("videoscale", "videoscaler");
	encoder 	= gst_element_factory_make ("x264enc", "encoder");
	payloadencoder 	= gst_element_factory_make ("rtph264pay", "payloadencoder");
	sink		= gst_element_factory_make ("udpsink", "sink");
	
	/* Test if elements are created succesfully */
	if (!source || !decoder || !converter || !videoscaler || !encoder || !payloadencoder || !sink)
	{	
		g_printerr("Not all elements could be created");

		std::cout << "\n" << "source[" << !source << "] " 
				<< "decoder[" << !decoder << "] "
				<< "converter[" << !converter << "] "
				<< "videoscaler[" << !videoscaler << "] "
				<< "encoder[" << !encoder << "] "
				<< "payloadencoder[" << !payloadencoder << "] "
				<< "sink[" << !sink << "] " << std::endl;
		return -1;
	}

	/* Set objects with settings */
	g_object_set (G_OBJECT (source), "device", "/dev/video0", NULL);
	g_object_set (G_OBJECT (encoder), "speed-preset", 2, NULL);
	g_object_set (G_OBJECT (sink), "host", "192.168.178.34", "port", 5000, NULL);

	/* Link elements */
	gst_bin_add_many (GST_BIN (pipeline), source, converter, encoder, payloadencoder, sink, NULL);
	if (gst_element_link (source, sink) != TRUE)
	{
		std::cout << "Not all elements could be linked" << std::endl;
		return -1;
	}
	
	/* Set state */	
	ret = gst_element_set_state (pipeline, GST_STATE_PLAYING);
	if (ret == GST_STATE_CHANGE_FAILURE)
	{
		std::cout << "Pipeline was not able to play" << std::endl;
		return -1;
	}
	
	/* Start pipeline */
	std::cout << "Starting pipeline." << std::endl;
	loop = g_main_loop_new(NULL, FALSE);
	g_main_loop_run(loop);

	/* Clean up */
	g_main_loop_unref (loop);
	gst_object_unref (bus);
	gst_element_set_state (pipeline, GST_STATE_NULL);
	gst_object_unref (pipeline);

	return 0;
}
