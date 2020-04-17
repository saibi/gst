#ifndef _SOME_OBJECT_H_
#define _SOME_OBJECT_H_

#include <glib-object.h>


G_BEGIN_DECLS


typedef struct _SomeObject SomeObject;
struct _SomeObject
{
	GTypeInstance gtype;

	gint m_a;
	gchar * m_b;
	gfloat m_c;
};

typedef struct _SomeObjectClass SomeObjectClass;
struct _SomeObjectClass
{
	GTypeClass gtypeclass;

	void (*method1)(SomeObject *self, gint);
	void (*method2)(SomeObject *self, gchar *);
};

GType some_object_get_type(void);

void some_object_class_init(gpointer g_class, gpointer class_data);
void some_object_class_final(gpointer g_class, gpointer class_data);
void some_object_instance_init(GTypeInstance *instance, gpointer g_class);


void some_object_method1(SomeObject *self, gint); // virtual
void some_object_method2(SomeObject *self, gchar*); // virtual
void some_object_method3(SomeObject *self, gfloat); // non-virtual


#define SOME_OBJECT_TYPE		(some_object_get_type ())
#define SOME_OBJECT(obj)		(G_TYPE_CHECK_INSTANCE_CAST ((obj), SOME_OBJECT_TYPE, SomeObject))
#define SOME_OBJECT_CLASS(c)		(G_TYPE_CHECK_CLASS_CAST ((c), SOME_OBJECT_TYPE, SomeObjectClass))
#define SOME_IS_OBJECT(obj)		(G_TYPE_CHECK_TYPE ((obj), SOME_OBJECT_TYPE))
#define SOME_IS_OBJECT_CLASS(c)		(G_TYPE_CHECK_CLASS_TYPE ((c), SOME_OBJECT_TYPE))
#define SOME_OBJECT_GET_CLASS(obj)	(G_TYPE_INSTANCE_GET_CLASS ((obj), SOME_OBJECT_TYPE, SomeObjectClass))


G_END_DECLS

#endif //_SOME_OBJECT_H_
