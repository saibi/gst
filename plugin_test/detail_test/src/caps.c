#include "gstrkcamcalib.h"


// print caps

static gboolean print_field(GQuark field, const GValue * value, gpointer pfx)
{
	gchar *str = gst_value_serialize(value);

	g_print("%s  %15s: %s\n", (gchar *)pfx, g_quark_to_string(field), str);
	g_free(str);
	return TRUE;
}


void print_caps(const GstCaps * caps, const gchar * pfx)
{
	guint i;

	g_return_if_fail(caps != NULL);

	if ( gst_caps_is_any(caps) ) {
		g_print("%sANY\n", pfx);
		return;
	}

	if ( gst_caps_is_empty(caps) ) {
		g_print("%sEMPTY\n", pfx);
		return;
	}

	g_print("gst_caps_get_size = %d\n", gst_caps_get_size(caps));
	for ( i = 0; i < gst_caps_get_size(caps); i++) {
		GstStructure * structure = gst_caps_get_structure(caps, i);

		g_print("%s%s\n", pfx, gst_structure_get_name(structure));
		gst_structure_foreach(structure, print_field, (gpointer) pfx);
	}
}

gboolean cam_format_ok = FALSE;
gint cam_width = 0;
gint cam_height = 0;

void parse_cam_data_caps(const GstCaps * caps)
{
	int i;

	cam_format_ok = FALSE;

	g_return_if_fail(caps != NULL);

	for ( i = 0; i < gst_caps_get_size(caps); i++) 
	{
		GstStructure * structure = gst_caps_get_structure(caps, i);
		const gchar *name = gst_structure_get_name(structure);;
		if ( g_strcmp0(name, "video/x-raw") == 0 )
		{
			const GValue *val = gst_structure_get_value(structure, "format");
			const gchar *format = NULL;
			if ( G_VALUE_HOLDS_STRING(val) )
				format = g_value_get_string(val);

			if ( g_strcmp0(format, "NV12") == 0 )
			{
				cam_width = 0;
				val = gst_structure_get_value(structure, "width");
				if ( G_VALUE_HOLDS_INT(val) )
					cam_width = g_value_get_int(val);

				cam_height = 0;
				val = gst_structure_get_value(structure, "height");
				if ( G_VALUE_HOLDS_INT(val) )
					cam_height = g_value_get_int(val);

				g_print("video/x-raw NV12 %dx%d\n", cam_width, cam_height);
				cam_format_ok = TRUE;
				return;
			}
		}
	}
}
