#include <iostream>
#include <gst/gst.h>

int main(int argc, char *argv[])
{
	GstElement *pipeline = nullptr;
	GstBus *bus = nullptr;
	GstMessage *msg = nullptr;
	GMainLoop *loop = nullptr;
	GstStateChangeReturn ret;
	
	
	gst_init(&argc, &argv);

	
	/* Create empty pipeline */
	pipeline 	= gst_pipeline_new ("pipeline");

	/* Create the elements */
	GstElement *source, *decoder, *scaler, *encoder, *payloadencoder, *sink, *filter;
	
	source	 	= gst_element_factory_make ("v4l2src", "source");
	decoder 	= gst_element_factory_make ("decodebin", "decoder");
	scaler		= gst_element_factory_make ("videoscale", "scaler");
	encoder 	= gst_element_factory_make ("jpegenc", "encoder");
	payloadencoder 	= gst_element_factory_make ("rtpjpegpay", "payloadencoder");
	sink		= gst_element_factory_make ("udpsink", "sink");
	
	filter 		= gst_element_factory_make ("capsfilter", "filter");

	if (!source || !decoder || !scaler || !encoder || !payloadencoder || !sink || !filter)
	{	
		g_printerr("Not all elements could be created");

		std::cout << "\n" << "source[" << !source << "] " 
				<< "decoder[" << !decoder << "] "
				<< "scaler[" << !scaler << "] "
				<< "encoder[" << !encoder << "] "
				<< "payloadencoder[" << !payloadencoder << "] "
				<< "sink[" << !sink << "] " << std::endl;
		return -1;
	}

	/* Create caps */
	GstCaps *filtercaps	= gst_caps_new_simple ("video/x-raw", 
					"format", G_TYPE_STRING, "I420",
					"width", G_TYPE_INT, 800,
					"height", G_TYPE_INT, 600,
					"framerate", GST_TYPE_FRACTION, 25, 1,
					NULL);

	g_object_set (G_OBJECT (source), "device", "/dev/video0", NULL);
	g_object_set (G_OBJECT (filter), "caps", filtercaps, NULL);
	g_object_set (G_OBJECT (sink), "host", "192.168.178.100", "port", 5000, "sync", false, NULL);

	gst_bin_add_many (GST_BIN (pipeline), source, decoder, scaler, filter, encoder, payloadencoder, sink, NULL);
	if (gst_element_link (source, sink) != TRUE)
	{
		g_printerr("Not all elements could be linked");
		return -1;
	}
	std::cout << "Succesfully linked elements" << std::endl;
	
	ret = gst_element_set_state (pipeline, GST_STATE_PLAYING);
	if (ret == GST_STATE_CHANGE_FAILURE)
	{
		std::cout << "Pipeline was not able to play" << std::endl;
		return -1;
	}
	std::cout << "Running?" << std::endl;

	bus = gst_element_get_bus (pipeline);
	loop = g_main_loop_new(NULL, FALSE);

	g_main_loop_run(loop);

	g_main_loop_unref (loop);
	gst_object_unref (bus);
	gst_element_set_state (pipeline, GST_STATE_NULL);
	gst_object_unref (pipeline);

	return 0;
}
