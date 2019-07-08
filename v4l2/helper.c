#include "helper.h"

static gboolean print_field(GQuark field, const GValue * value, gpointer pfx)
{
	gchar *str = gst_value_serialize(value);

	g_print("%s  %15s: %s\n", (gchar *)pfx, g_quark_to_string(field), str);
	g_free(str);

	return TRUE;
}


void print_caps(const GstCaps * caps, const gchar *pfx)
{
	guint i;

	g_return_if_fail(caps != NULL);

	if ( gst_caps_is_any(caps) ) 
	{
		g_print("%sANY\n", pfx);
		return;
	}

	if ( gst_caps_is_empty(caps) )
	{
		g_print("%sEMPTY\n", pfx);
		return;
	}

	for ( i = 0 ; i < gst_caps_get_size(caps); i++ )
	{
		GstStructure * structure = gst_caps_get_structure(caps, i);

		g_print("%s%s\n", pfx, gst_structure_get_name(structure));
		gst_structure_foreach(structure, print_field, (gpointer)pfx);
	}
}

int dump_src_caps(GstElement *source)
{
	GstPad * video_pad = NULL;
	GstCaps *video_caps = NULL;

	video_pad = gst_element_get_static_pad(source, "src");
	if ( !video_pad )
	{
		g_printerr("Could not retrieve pad\n");
		return -1;
	}

	video_caps = gst_pad_get_current_caps(video_pad);
	if ( !video_caps ) 
		video_caps = gst_pad_query_caps(video_pad, NULL);

	g_print("caps for the src pad:\n");
	print_caps(video_caps, "    ");
	gst_caps_unref(video_caps);

	gst_caps_unref(video_caps);
	gst_object_unref(video_pad);

	return 0;
}
/********** end of file **********/
