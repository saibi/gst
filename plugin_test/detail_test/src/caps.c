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

		const GValue *val = gst_structure_get_value(structure, "format");
		g_print("format typename %s\n", G_VALUE_TYPE_NAME(val));

		gchar *str = gst_value_serialize(val);
		g_print("serialize format = [%s]\n", str);
		g_free(str);
		if ( G_VALUE_HOLDS_STRING(val) )
			g_print("extract format str = [%s]\n", g_value_get_string(val));


		val = gst_structure_get_value(structure, "width");
		g_print("width typename %s\n", G_VALUE_TYPE_NAME(val));
		if ( G_VALUE_HOLDS_STRING(val) )
			g_print("extract width str = [%s]\n", g_value_get_string(val));
		else if ( G_VALUE_HOLDS_INT(val) )
			g_print("extract width int = [%d]\n", g_value_get_int(val));

		val = gst_structure_get_value(structure, "height");
		g_print("height typename %s\n", G_VALUE_TYPE_NAME(val));
		if ( G_VALUE_HOLDS_INT(val) )
			g_print("extract height int = [%d]\n", g_value_get_int(val));

	}
}


#if 0

gboolean extract_resolution_from_cap(const GstCaps * caps, int *pwidth, int *pheight)
{
	GstStructure *structure;
	int i;

	g_return_val_if_fail(caps != NULL, FALSE);

	for ( i = 0; i < gst_caps_get_size(caps); i++) 
	{
		GstStructure * structure = gst_caps_get_structure(caps, i);
		const gchar *name = gst_structure_get_name(structure);;
		if ( g_strcmp0(name, "video/x-raw") == 0 )
		{
			const GValue *val = gst_structure_get_value(structure, "format");


			const GValue *val = gst_structure_get_value(structure, "width");
			if ( G_VALUE_HOLDS_INT(val) )
				if ( pwidth )
					*pwidth = g_value_get_int(val);


				g_print("extract height int = [%d]\n", g_value_get_int(val));

		}

	}
	if ( gst_caps_get_size(caps) < 1 ) 
		return FALSE;
	

	GstStructure * structure = gst_caps_get_structure(caps, i);
	; i++) {
	for ( i = 0; i < 

	name = gst_structure_get_name(structure));
		g_print("%s%s\n", pfx, 
	if ( 

}
#endif 


