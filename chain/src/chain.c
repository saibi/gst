#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <gst/gst.h>

#include "gstmyfilter.h"


// for file i/o
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/* chain function
 * this function does the actual processing
 */
GstFlowReturn gst_my_filter_chain(GstPad * pad, GstObject * parent, GstBuffer * buf)
{
	GstMyFilter *filter;
	static gssize cnt = 0;
	static int fd = -1;

	if ( fd < 0 )
	{
		fd = creat("/tmp/dump", S_IRWXU); 
		g_print("create /tmp/dump, fd = %d\n", fd);
	}

	filter = GST_MYFILTER(parent);

	if (filter->silent == FALSE)
	{
		GstMemory *mem = gst_buffer_get_all_memory(buf);
		guint f = GST_MEMORY_FLAGS(mem);

		g_print("#%" G_GSIZE_FORMAT "  Have data of size %" G_GSIZE_FORMAT " bytes! n=%d, offset=%" G_GSIZE_FORMAT ", pts=%" G_GSIZE_FORMAT ", mem flag %d, %s %s %s %s %s %s\n",
				cnt++, gst_buffer_get_size(buf), gst_buffer_n_memory(buf), GST_BUFFER_OFFSET(buf), GST_BUFFER_TIMESTAMP(buf),
				f, 
				f& GST_MEMORY_FLAG_READONLY ? "rdonly" : "", 
				f& GST_MEMORY_FLAG_NO_SHARE ? "noshare" : "", 
				f& GST_MEMORY_FLAG_ZERO_PREFIXED ? "zpf" : "", 
				f& GST_MEMORY_FLAG_ZERO_PADDED ? "zpd" : "", 
				f& GST_MEMORY_FLAG_PHYSICALLY_CONTIGUOUS ? "pc" : "", 
				f& GST_MEMORY_FLAG_NOT_MAPPABLE ? "notmap" : "" 
				);

		if ( fd > 0 ) 
		{
			GstMapInfo info;

			if ( gst_memory_map(mem, &info, GST_MAP_READ | GST_MAP_WRITE) ) 
			{

				memset(&info.data[512*288], 128, info.size - 512*288);

				g_print("write /tmp/dump , size %" G_GSIZE_FORMAT "\n", info.size);
				
				
				write(fd, info.data, info.size);

				gst_memory_unmap(mem, &info);
			}
		}

		gst_memory_unref(mem);

	}

	if ( cnt == 300 )
	{
		if ( fd > 0 ) 
		{
			close(fd);
			fd = 0;
			g_print("close fd\n");
		}
	}

	/* just push out the incoming buffer without touching it */
	return gst_pad_push(filter->srcpad, buf);
}
