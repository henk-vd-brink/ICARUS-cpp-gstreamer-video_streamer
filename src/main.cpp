#include <iostream>
#include <gst/gst.h>

int main(int argc, char *argv[])
{
	GstElement *pipeline = nullptr;
	GstBus *bus = nullptr;
	GstMessage *msg = nullptr;
	GstStateChangeReturn ret;
	
	
	gst_init(&argc, &argv);

	
	/* Create empty pipeline */
	pipeline 	= gst_pipeline_new ("pipeline");

	/* Create the elements */
	GstElement *source, *decoder, *scaler, *encoder, *payloadencoder, *sink;
	
	source	 	= gst_element_factory_make ("autovideosrc", "source");
	decoder 	= gst_element_factory_make ("decodebin", "decoder");
	scaler		= gst_element_factory_make ("videoscale", "scaler");
	encoder 	= gst_element_factory_make ("jpegenc", "encoder");
	payloadencoder 	= gst_element_factory_make ("rtpjpegpay", "payloadencoder");
	sink		= gst_element_factory_make ("autovideosink", "sink");
	
	if (!source || !decoder || !scaler || !encoder || !payloadencoder || !sink);
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
	GstCaps *caps 	= gst_caps_new_simple ("video/x-raw", 
					"format", G_TYPE_STRING, "I420",
					"width", G_TYPE_INT, 800,
					"height", G_TYPE_INT, 600,
					"framerate", GST_TYPE_FRACTION, 25, 1,
					NULL);

	g_object_set(G_OBJECT (source), "location", argv[1], NULL);
	g_object_set(G_OBJECT (sink), "host", "192.168.178.100", "port", 5000, "sync", false, NULL);

	gst_bin_add_many (GST_BIN (pipeline), source, decoder, scaler, sink, NULL);
	
	if (gst_element_link (source, sink) != TRUE)
	{
		g_printerr("Not all elements could be linked");
		return -1;
	}
	

	ret = gst_element_set_state (pipeline, GST_STATE_PLAYING);
	if (ret == GST_STATE_CHANGE_FAILURE)
	{
		std::cout << "Pipeline was not able to play" << std::endl;
		return -1;
	}





	return 0;
}
