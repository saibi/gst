#include "viewer_file.h"

typedef struct {
	gchar *filename;
} ViewerFilePrivate;


/* final class */

struct _ViewerFile
{
	GObject parent_instance;

};

//G_DEFINE_TYPE(ViewerFile, viewer_file, G_TYPE_OBJECT)

G_DEFINE_TYPE_WITH_PRIVATE(ViewerFile, viewer_file, G_TYPE_OBJECT)

static void viewer_file_class_init(ViewerFileClass *klass)
{
}


static void viewer_file_init(ViewerFile *self)
{
	ViewerFilePrivate *priv = viewer_file_get_instance_private(self);

}
