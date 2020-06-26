#if 0
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <gst/gst.h>
#endif 

#include "gstmyfilter.h"


/* chain function
 * this function does the actual processing
 */
GstFlowReturn gst_my_filter_chain(GstPad * pad, GstObject * parent, GstBuffer * buf)
{
	static gssize cnt = 0;
	GstMyFilter *filter;
	GstMemory *mem;

	filter = GST_MYFILTER(parent);

	mem = gst_buffer_get_all_memory(buf);

	if (filter->silent == FALSE)
	{
		g_print("I'm plugged, therefore I'm in. (%s) %d\n", filter->str ? filter->str : "NULL", filter->int_val);

		if ( mem ) 
		{
			guint f;

			f = GST_MEMORY_FLAGS(mem);
			g_print("#%" G_GSIZE_FORMAT " Have data of size %" G_GSIZE_FORMAT " bytes! n=%d, offset=%" G_GSIZE_FORMAT ", pts=%" G_GSIZE_FORMAT ", mem flag %d, %s %s %s %s %s %s\n",
				cnt++, gst_buffer_get_size(buf), gst_buffer_n_memory(buf), GST_BUFFER_OFFSET(buf), GST_BUFFER_TIMESTAMP(buf),
				f,
				f & GST_MEMORY_FLAG_READONLY ? "rdonly" : "",
				f & GST_MEMORY_FLAG_NO_SHARE ? "noshare" : "",
				f & GST_MEMORY_FLAG_ZERO_PREFIXED ? "zpf" : "", f & GST_MEMORY_FLAG_ZERO_PADDED ? "zpd" : "", f & GST_MEMORY_FLAG_PHYSICALLY_CONTIGUOUS ? "pc" : "", f & GST_MEMORY_FLAG_NOT_MAPPABLE ? "notmap" : "");
		}

	}

	if ( mem && filter->format_ok )
	{
		GstMapInfo info;

		if ( gst_memory_map(mem, &info, GST_MAP_READ | GST_MAP_WRITE) )
		{
			gsize y_size = filter->width * filter->height;
			memset(&info.data[y_size], filter->int_val, info.size - y_size); 

			gst_memory_unmap(mem, &info);
		}
		gst_memory_unref(mem);
	}

	/* just push out the incoming buffer without touching it */
	return gst_pad_push(filter->srcpad, buf);
}
