#include <gst/gst.h>

int main(int argc, char *argv[])
{
	GstElement *pipeline;
	GstBus *bus;
	GstMessage *msg;
	GstStateChangeReturn ret;

	gst_init(&argc, &argv);

	pipeline = gst_parse_launch("playbin uri=https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm", NULL);

	ret = gst_element_set_state(pipeline, GST_STATE_PLAYING);
	if ( ret == GST_STATE_CHANGE_FAILURE ) {
		g_printerr("Unable to set the pipeline to the playing state.\n");
		gst_object_unref(pipeline);
		return -1;
	}

	bus = gst_element_get_bus(pipeline);
	msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE, GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

	if ( msg != NULL ) {
		GError *err;
		gchar *debug_info;

		switch(GST_MESSAGE_TYPE(msg)) {
			case GST_MESSAGE_ERROR:
				gst_message_parse_error(msg, &err, &debug_info);
				g_printerr("Error received from element %s: %s\n", GST_OBJECT_NAME(msg->src), err->message);
				g_printerr("Debugging information: %s\n", debug_info ? debug_info : "none");
				g_clear_error(&err);
				g_free(debug_info);

				break;

			case GST_MESSAGE_EOS:
				g_print("End-Of-Stream reached.\n");
				break;

			default:
				g_printerr("Unexpected message received.\n");
				break;
		}
		gst_message_unref(msg);
	}

	gst_object_unref(bus);
	gst_element_set_state(pipeline, GST_STATE_NULL);
	gst_object_unref(pipeline);

	return 0;
}

