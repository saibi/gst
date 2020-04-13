#include "edc-host.h"

G_DEFINE_TYPE(EdcHost, edc_host, G_TYPE_OBJECT);


EdcHost * edc_host_new(void)
{
	return EDC_HOST(g_object_new(EDC_TYPE_HOST, NULL));
}

static void edc_host_init(EdcHost *host)
{
	g_print("edc_host_init\n");
	host->name = NULL;
	host->address = NULL;
	host->port = 0;
	host->user = NULL;
	host->password = NULL;
}

static void edc_host_finalize(GObject *self)
{
	EdcHost *host = EDC_HOST(self);

	g_print("edc_host_finalize\n");
	g_free(host->name);
	g_free(host->address);
	g_free(host->user);
	g_free(host->password);

	G_OBJECT_CLASS(edc_host_parent_class)->finalize(self);
}

static void edc_host_class_init(EdcHostClass *klass)
{
	GObjectClass *object_class;

	object_class = G_OBJECT_CLASS(klass);
	object_class->finalize = edc_host_finalize;
}

