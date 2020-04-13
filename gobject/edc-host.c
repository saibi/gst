#include "edc-host.h"


typedef struct _EdcHostPrivate EdcHostPrivate;
struct _EdcHostPrivate
{
	gchar *name;
	gchar *address;
	gint port;
	gchar *user;
	gchar *password;
};

#define EDC_HOST_GET_PRIVATE(host) G_TYPE_INSTANCE_GET_PRIVATE(host, EDC_TYPE_HOST, EdcHostPrivate)

G_DEFINE_TYPE(EdcHost, edc_host, G_TYPE_OBJECT);

EdcHost * edc_host_new(void)
{
	return EDC_HOST(g_object_new(EDC_TYPE_HOST, NULL));
}

static void edc_host_init(EdcHost *host)
{
	EdcHostPrivate *priv;

	priv = EDC_HOST_GET_PRIVATE(host);

	g_print("edc_host_init\n");

	priv->name = g_strdup("");
	priv->address = g_strdup("");
	priv->port = 0;
	priv->user = g_strdup("");
	priv->password = g_strdup("");
}

static void edc_host_finalize(GObject *self)
{
	EdcHost *host = EDC_HOST(self);
	EdcHostPrivate *priv;

	priv = EDC_HOST_GET_PRIVATE(host);

	g_print("edc_host_finalize\n");

	g_free(priv->name);
	g_free(priv->address);
	g_free(priv->user);
	g_free(priv->password);

	G_OBJECT_CLASS(edc_host_parent_class)->finalize(self);
}

static void edc_host_class_init(EdcHostClass *klass)
{
	GObjectClass *object_class;

	object_class = G_OBJECT_CLASS(klass);
	object_class->finalize = edc_host_finalize;

	g_type_class_add_private(object_class, sizeof(EdcHostPrivate));
}

gchar * edc_host_get_name(EdcHost *host)
{
	EdcHostPrivate *priv;

	g_return_val_if_fail(EDC_IS_HOST(host), NULL);

	priv = EDC_HOST_GET_PRIVATE(host);
	return g_strdup(priv->name);
}

void edc_host_set_name(EdcHost *host, const gchar *name)
{
	EdcHostPrivate *priv;

	g_return_if_fail(EDC_IS_HOST(host));
	g_return_if_fail(name != NULL);

	priv = EDC_HOST_GET_PRIVATE(host);

	g_free(priv->name);
	priv->name = g_strdup(name);
}

gchar *edc_host_get_address(EdcHost *host)
{
	EdcHostPrivate *priv;

	g_return_val_if_fail(EDC_IS_HOST(host), NULL);

	priv = EDC_HOST_GET_PRIVATE(host);
	return g_strdup(priv->address);
}

void edc_host_set_address(EdcHost *host, const gchar *address)
{
	EdcHostPrivate *priv;

	g_return_if_fail(EDC_IS_HOST(host));
	g_return_if_fail(address != NULL);

	priv = EDC_HOST_GET_PRIVATE(host);

	g_free(priv->address);
	priv->address = g_strdup(address);
}

gint edc_host_get_port(EdcHost *host)
{
	EdcHostPrivate *priv;

	g_return_val_if_fail(EDC_IS_HOST(host), 0);

	priv = EDC_HOST_GET_PRIVATE(host);
	return priv->port;
}

void edc_host_set_port(EdcHost *host, gint port)
{
	EdcHostPrivate *priv;

	g_return_if_fail(EDC_IS_HOST(host));

	priv = EDC_HOST_GET_PRIVATE(host);

	priv->port = port;
}

gchar *edc_host_get_user(EdcHost *host)
{
	EdcHostPrivate *priv;

	g_return_val_if_fail(EDC_IS_HOST(host), NULL);

	priv = EDC_HOST_GET_PRIVATE(host);
	return g_strdup(priv->user);
}

void edc_host_set_user(EdcHost *host, const gchar *user)
{
	EdcHostPrivate *priv;

	g_return_if_fail(EDC_IS_HOST(host));
	g_return_if_fail(user != NULL);

	priv = EDC_HOST_GET_PRIVATE(host);

	g_free(priv->user);
	priv->user = g_strdup(user);
}

gchar *edc_host_get_password(EdcHost *host)
{
	EdcHostPrivate *priv;

	g_return_val_if_fail(EDC_IS_HOST(host), NULL);

	priv = EDC_HOST_GET_PRIVATE(host);
	return g_strdup(priv->password);
}

void edc_host_set_password(EdcHost *host, const gchar *password)
{
	EdcHostPrivate *priv;

	g_return_if_fail(EDC_IS_HOST(host));
	g_return_if_fail(password != NULL);

	priv = EDC_HOST_GET_PRIVATE(host);

	g_free(priv->password);
	priv->password= g_strdup(password);
}

