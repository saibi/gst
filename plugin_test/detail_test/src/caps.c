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



