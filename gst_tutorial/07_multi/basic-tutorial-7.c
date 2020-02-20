#include <gst/gst.h>


int main(int argc, char *argv[])
{
	GstElement *pipeline;
	GstElement *audio_source;
	GstElement *tee;
	GstElement *audio_queue;
	GstElement *audio_convert;
	GstElement *audio_resample;
	GstElement *audio_sink;
	GstElement *video_queue;
	GstElement *visual;
	GstElement *video_convert;
	GstElement *video_sink;
	GstBus *bus;
	GstMessage *msg;
	GstPad *tee_audio_pad;
	GstPad *tee_video_pad;
	GstPad *queue_audio_pad;
	GstPad *queue_video_pad;

	GstStateChangeReturn ret;
	gboolean terminate = FALSE;

	gst_init(&argc, &argv);

	audio_source = gst_element_factory_make("audiotestsrc", "audio_source");
	tee = gst_element_factory_make("tee", "tee");
	audio_queue = gst_element_factory_make("queue", "audio_queue");
	audio_convert = gst_element_factory_make("audioconvert", "audio_convert");
	audio_resample = gst_element_factory_make("audioresample", "audio_resample");
	audio_sink = gst_element_factory_make("autoaudiosink", "audio_sink");
	video_queue = gst_element_factory_make("queue", "video_queue");
	visual = gst_element_factory_make("wavescope", "visual");
	video_convert = gst_element_factory_make("videoconvert", "csp");
	video_sink = gst_element_factory_make("autovideosink", "video_sink");

	pipeline = gst_pipeline_new("test-pipeline");

	if ( !pipeline || !audio_source || !tee || !audio_queue || !audio_convert || !audio_resample || !audio_sink || !video_queue || !visual || !video_convert || !video_sink) {
		g_printerr("Not all elements could be created.\n");
		return -1;
	}

	g_object_set(audio_source, "freq", 215.0f, NULL);
	g_object_set(visual, "shader", 1, "style", 2, NULL);

	gst_bin_add_many(GST_BIN(pipeline), audio_source, tee, audio_queue, audio_convert, audio_resample, audio_sink, video_queue, visual, video_convert, video_sink, NULL);

	if ( gst_element_link_many(audio_source, tee, NULL) != TRUE || 
			gst_element_link_many(audio_queue, audio_convert, audio_resample, audio_sink, NULL) != TRUE || 
			gst_element_link_many(video_queue, visual, video_convert, video_sink, NULL) != TRUE ) {
		g_printerr("Elements could not be linked.\n");
		gst_object_unref(pipeline);
		return -1;
	}


	tee_audio_pad = gst_element_get_request_pad(tee, "src_%u");
	g_print("Obtained request pad %s for audio branch.\n", gst_pad_get_name(tee_audio_pad));
	queue_audio_pad = gst_element_get_static_pad(audio_queue, "sink");

	tee_video_pad = gst_element_get_request_pad(tee, "src_%u");
	g_print("Obtained request pad %s for video branch.\n", gst_pad_get_name(tee_video_pad));
	queue_video_pad = gst_element_get_static_pad(video_queue, "sink");

	if ( gst_pad_link(tee_audio_pad, queue_audio_pad) != GST_PAD_LINK_OK  ||
			gst_pad_link(tee_video_pad, queue_video_pad) != GST_PAD_LINK_OK ) {
		g_printerr("Tee could not be linked.\n");
		gst_object_unref(pipeline);
		return -1;
	}

	gst_object_unref(queue_audio_pad);
	gst_object_unref(queue_video_pad);

	ret = gst_element_set_state(pipeline, GST_STATE_PLAYING);
	if ( ret == GST_STATE_CHANGE_FAILURE ) {
		g_printerr("Unable to set the pipeline to the playing state.\n");
		gst_object_unref(pipeline);
		return -1;
	}

	bus = gst_element_get_bus(pipeline);
	do {
		msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE, GST_MESSAGE_STATE_CHANGED | GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

		if ( msg != NULL ) {
			GError * err;
			gchar *debug_info;

			switch (GST_MESSAGE_TYPE(msg)) {
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
					if ( GST_MESSAGE_SRC(msg) == GST_OBJECT(pipeline)) {
						GstState old_state, new_state, pending_state;
						gst_message_parse_state_changed(msg, &old_state, &new_state, &pending_state);
						g_print("Pipeline state changed from %s to %s:\n", gst_element_state_get_name(old_state), gst_element_state_get_name(new_state));
					}
					break;

				default:
					g_printerr("Unexpected message received.\n");
					break;
			}
			gst_message_unref(msg);
		}

	} while(!terminate);

	gst_element_release_request_pad(tee, tee_audio_pad);
	gst_element_release_request_pad(tee, tee_video_pad);
	gst_object_unref(tee_audio_pad);
	gst_object_unref(tee_video_pad);

	gst_object_unref(bus);
	gst_element_set_state(pipeline, GST_STATE_NULL);
	gst_object_unref(pipeline);
	return 0;
}
