#include <gst/gst.h>
#include "helper.h"


/* structure to contain all our information, so we can pass it to callbacks */

typedef struct _CustomData {
	GstElement *pipeline;
	GstElement *source;
	GstElement *filter;
	GstElement *convert;
	GstElement *sink;
} CustomData;


// prototypes
int use_factory_make(CustomData *data);

int use_factory_make(CustomData *data)
{
	GstCaps *caps;

	/* create the elements */
	data->source = gst_element_factory_make("rkisp", "source");
	data->filter = gst_element_factory_make("capsfilter", "filter");
	data->convert = gst_element_factory_make("videoconvert", "convert");
	data->sink = gst_element_factory_make("kmssink", "sink");

	/* create the empty pipeline */
	data->pipeline = gst_pipeline_new("test-pipeline");

	if ( !data->pipeline || !data->source || !data->filter || !data->convert || !data->sink ) {
		g_printerr("Not all elements could be created.\n");
		return -1;
	}

	/* build the pipeline. Note that we are Not linking the source at this point. We will do it later. */
	gst_bin_add_many(GST_BIN(data->pipeline), data->source, data->filter, data->convert, data->sink, NULL);
	if ( !gst_element_link_many( data->source, data->filter, data->convert, data->sink, NULL) ) 
	{
		g_printerr("Elements could be linked.\n");
		gst_object_unref(data->pipeline);
		return -1;
	}

	/* set the properties */
	g_object_set(data->source, "device", "/dev/video0", NULL);
	g_object_set(data->source, "analyzer", "1", NULL);


	caps = gst_caps_from_string("video/x-raw,format=NV12,width=320,height=240,framerate=30/1");
	g_object_set(data->filter, "caps", caps, NULL);

	//g_object_set(data->sink, "can-scale", "false", NULL); // not working
	//g_object_set(data->sink, "render-rectangle", "<100,100,320,240>", NULL); // GstValueArray error
	

	// dump pad caps
	if ( dump_src_caps(data->source) < 0 )
	{
		gst_object_unref(data->pipeline);
		return -1;
	}

	return 0;
}



int main(int argc, char *argv[])
{
	CustomData data;
	GstBus *bus;
	GstMessage *msg;
	GstStateChangeReturn ret;
	gboolean terminate = FALSE;

	/* initialize gstreamer */
	gst_init(&argc, &argv);

	if (use_factory_make(&data) < 0 )
		return -1;


	/* Start playing */
	ret = gst_element_set_state(data.pipeline, GST_STATE_PLAYING);
	if ( ret == GST_STATE_CHANGE_FAILURE ) {
		g_printerr("Unable to set the pipeline to the playing state.\n");
		gst_object_unref(data.pipeline);
		return -1;
	}

	/* Listen to the bus */
	bus = gst_element_get_bus(data.pipeline);

	do {
		msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE, GST_MESSAGE_STATE_CHANGED | GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

		/* parse message */
		if ( msg != NULL) {
			GError *err;
			gchar *debug_info;

			switch(GST_MESSAGE_TYPE(msg) ) {
				case GST_MESSAGE_ERROR:
					gst_message_parse_error(msg, &err, &debug_info);
					g_printerr("Error received from element %s: %s\n", GST_OBJECT_NAME(msg->src), err->message);
					g_printerr("Debugging information: %s\n", debug_info ? debug_info : "none");
					g_clear_error(&err);
					g_free(debug_info);
					terminate = TRUE;
					break;

				case GST_MESSAGE_EOS:
					g_print("End-Of-Stream reached.\n");
					terminate = TRUE;
					break;

				case GST_MESSAGE_STATE_CHANGED:

					/* we are only interested in state-changed messages from the pipeline */
					if ( GST_MESSAGE_SRC(msg) == GST_OBJECT(data.pipeline) ) {
						GstState old_state, new_state, pending_state;
						gst_message_parse_state_changed(msg, &old_state, &new_state, &pending_state);
						g_print("Pipeline state changed from %s to %s:\n", gst_element_state_get_name(old_state), gst_element_state_get_name(new_state));
					}
					break;

				default:
					/* we should not reach here */
					g_printerr("Unexpected message received.\n");
					break;
			}

			gst_message_unref(msg);
		}
	} while (!terminate);


	/* free resources */
	gst_object_unref(bus);
	gst_element_set_state(data.pipeline, GST_STATE_NULL);
	gst_object_unref(data.pipeline);

	return 0;
}

/********** end of file **********/
