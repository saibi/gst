#ifndef _MY_CLOCK_H_
#define _MY_CLOCK_H_

#include <glib-object.h>

G_BEGIN_DECLS

#define MY_TYPE_CLOCK (my_clock_get_type())
#define MY_CLOCK(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), MY_TYPE_CLOCK, MyClock))
#define MY_CLOCK_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST((klass), MY_TYPE_CLOCK, MyClockClass))
#define MY_IS_CLOCK(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), MY_TYPE_CLOCK))
#define MY_IS_CLOCK_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass), MY_TYPE_CLOCK))
#define MY_GET_CLOCK_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS((obj), MY_TYPE_CLOCK, MyClockClass))

typedef struct _MyClock MyClock;
typedef struct _MyClockClass MyClockClass;
typedef struct _MyClockPrivate MyClockPrivate;

struct _MyClock 
{
	GObject parent;

	MyClockPrivate *priv;
};

struct _MyClockClass
{
	GObjectClass parent_class;

	void (*changed)(MyClock *cl, GDateTime *datetime);
};

GType my_clock_get_type(void) G_GNUC_CONST;
MyClock * my_clock_new(void);
GDateTime * my_clock_get_date_time(MyClock *cl);
const gchar * my_clock_get_text(MyClock *cl);

G_END_DECLS


#endif 
