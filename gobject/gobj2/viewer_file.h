#ifndef __VIEWER_FILE_H__
#define __VIEWER_FILE_H__

#include <glib-object.h>

G_BEGIN_DECLS


/* final class */

#define VIEWER_TYPE_FILE viewer_file_get_type()

G_DECLARE_FINAL_TYPE (ViewerFile, viewer_file, VIEWER, FILE, GObject)

ViewerFile *viewer_file_new(void);




#if 0
/* derivable class */

#define VIEWER_TYPE_FILE viewer_file_get_type()

G_DECLARE_DERIVABLE_TYPE (ViewerFile, viewer_file, VIEWER, FILE, GObject)

struct _ViewerFileClass
{
	GObjectClass parent_class;

	void (* open)(ViewerFile *file, GError **error);

	gpointer padding[12];
};

ViewerFile *viewer_file_new(void);
#endif 




G_END_DECLS

#endif // __VIEWER_FILE_H__
