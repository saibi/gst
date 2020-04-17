#include "myclock.h"

G_DEFINE_TYPE(MyClock, my_clock, G_TYPE_OBJECT);

enum
{
	PROP_0,
	PROP_DATE_TIME,
	PROP_TEXT,
	PROP_LAST
};

struct _MyClockPrivate
{
	GDateTime *datetime;
	guint timeout;
	gchar *text;
};



static GParamSpec *props[PROP_LAST];

enum
{
	SIGNAL_CHANGED,
	SIGNAL_LAST
};

static guint signals[SIGNAL_LAST];



GDateTime * my_clock_get_date_time(MyClock *cl)
{
	g_return_val_if_fail(MY_IS_CLOCK(cl), NULL);

	return g_date_time_ref(cl->priv->datetime);
}

const gchar * my_clock_get_text(MyClock *cl)
{
	g_return_val_if_fail(MY_IS_CLOCK(cl), NULL);

	return cl->priv->text;
}

static void my_clock_set_date_time(MyClock *cl, GDateTime *datetime)
{
	g_date_time_unref(cl->priv->datetime);
	cl->priv->datetime = g_date_time_ref(datetime);
	g_object_notify_by_pspec(G_OBJECT(cl), props[PROP_DATE_TIME]);

	g_free(cl->priv->text);
	cl->priv->text = g_date_time_format(datetime, "%xT%H:%M:%S");
	g_object_notify_by_pspec(G_OBJECT(cl), props[PROP_TEXT]);
}

static void my_clock_real_changed(MyClock *cl, GDateTime *datetime)
{
	g_print("real_changed\n");
	my_clock_set_date_time(cl, datetime);
}

static gboolean my_clock_update(gpointer data)
{
	MyClock *cl = data;
	GTimeVal now;
	GDateTime *datetime;
	guint interval;

	g_print("my_clock_update\n");

	g_get_current_time(&now);

	datetime = g_date_time_new_from_timeval_local(&now);
	g_signal_emit(cl, signals[SIGNAL_CHANGED], 0, datetime);
	g_date_time_unref(datetime);

	interval = (1000000L - now.tv_usec) / 1000L;
	cl->priv->timeout = g_timeout_add_full(G_PRIORITY_HIGH_IDLE, interval, my_clock_update, g_object_ref(cl), g_object_unref);

	return FALSE;
}

static void my_clock_set_property(GObject *object, guint param_id, const GValue *value, GParamSpec *pspec)
{
	switch( param_id )
	{
		G_OBJECT_WARN_INVALID_PROPERTY_ID(object, param_id, pspec);
		break;
	}
}

static void my_clock_get_property(GObject * object, guint param_id, GValue *value, GParamSpec *pspec)
{
	MyClock *cl = MY_CLOCK(object);

	switch ( param_id )
	{
		case PROP_DATE_TIME:
			g_value_set_boxed(value, cl->priv->datetime);
			break;

		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID(object, param_id, pspec);
			break;
	}
}


static void my_clock_finalize(GObject *object)
{
	MyClockPrivate *priv = MY_CLOCK(object)->priv;

	g_print("my_clock_finalize\n");

	g_date_time_unref(priv->datetime);
	g_source_remove(priv->timeout);
	g_free(priv->text);
	G_OBJECT_CLASS(my_clock_parent_class)->finalize(object);
}

static void my_clock_class_init(MyClockClass *klass)
{
	GObjectClass *obj_class = G_OBJECT_CLASS(klass);
	GParamSpec *pspec;

	g_print("my_clock_class_init\n");

	obj_class->set_property = my_clock_set_property;
	obj_class->get_property = my_clock_get_property;
	obj_class->finalize = my_clock_finalize;
	klass->changed = my_clock_real_changed;

	g_type_class_add_private(klass, sizeof(MyClockPrivate));

	pspec = g_param_spec_boxed("datetime", "Date and Time", "The date and time to show in the clock", G_TYPE_DATE_TIME, G_PARAM_READABLE | G_PARAM_STATIC_STRINGS);
	props[PROP_DATE_TIME] = pspec;
	g_object_class_install_property(obj_class, PROP_DATE_TIME, pspec);

	pspec = g_param_spec_string("text", "Text", "The text of the date and time", NULL, G_PARAM_READABLE | G_PARAM_STATIC_STRINGS);
	props[PROP_TEXT] = pspec;
	g_object_class_install_property(obj_class, PROP_TEXT, pspec);


	signals[SIGNAL_CHANGED] = g_signal_new("changed", G_TYPE_FROM_CLASS(klass), G_SIGNAL_RUN_LAST, G_STRUCT_OFFSET(MyClockClass, changed), NULL, NULL, g_cclosure_marshal_VOID__POINTER, G_TYPE_NONE, 1, G_TYPE_POINTER);

}

MyClock * my_clock_new(void)
{
	return g_object_new(MY_TYPE_CLOCK, NULL);
}

static void my_clock_init(MyClock *cl)
{
	MyClockPrivate *priv;

	g_print("my_clock_init\n");
	priv = cl->priv = G_TYPE_INSTANCE_GET_PRIVATE(cl, MY_TYPE_CLOCK, MyClockPrivate);

	priv->datetime = g_date_time_new_now_local();
	priv->timeout = 0;
	priv->text = NULL;

	my_clock_update(cl);
}

