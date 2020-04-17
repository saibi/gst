#include "hello-app.h"

struct _HlwHelloApp {
	GObject parent;

	gchar *name;
};

G_DEFINE_TYPE(HlwHelloApp, hlw_hello_app, G_TYPE_OBJECT)

HlwHelloApp * hlw_hello_app_new(void)
{
	return g_object_new(HLW_TYPE_HELLO_APP, NULL);
}

gint hlw_hello_app_hello(HlwHelloApp *self, const gchar *msg, gchar *hello_msg)
{
	return g_sprintf(hello_msg, "%s!, %s", slef->name, msg);
}


static void hlw_hello_app_init(HlwHelloApp *self)
{
}

static void hlw_hello_app_dispose(GObject *object)
{
	HlwHelloApp *self = HLW_HELLO_APP(object);

	g_clear_pointer(&self->name, g_free);

	G_OBJECT_CLASS(hlw_app_parent_class)->dispose(object);
}

static void hlw_hello_app_class_init(HlwHelloAppClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS(klass);

	object_class->dispose = hlw_hello_app_dispose;
}

