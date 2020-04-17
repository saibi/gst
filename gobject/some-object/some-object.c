#include "some-object.h"


static void some_object_method1_impl (SomeObject *self, gint a)
{
	self->m_a = a;
	g_print("(v)method1: %i\n", self->m_a);
}

static void some_object_method2_impl(SomeObject *self, gchar *b)
{
	self->m_b = b;
	g_print("(v)method2: %s\n", self->m_b);
}

void some_object_method1(SomeObject *self, gint a)
{
	SOME_OBJECT_GET_CLASS(self)->method1(self, a); 
}

void some_object_method2(SomeObject *self, gchar* b)
{
	SOME_OBJECT_GET_CLASS(self)->method2(self, b);
}

void some_object_method3(SomeObject *self, gfloat c)
{
	self->m_c = c;
	g_print("method3: %f\n", self->m_c);
}

void some_object_class_init(gpointer g_class, gpointer class_data)
{
	SomeObjectClass *this_class = SOME_OBJECT_CLASS(g_class);

	this_class->method1 = &some_object_method1_impl;
	this_class->method2 = &some_object_method2_impl;
}

void some_object_class_final(gpointer g_class, gpointer class_data)
{

}

void some_object_instance_init(GTypeInstance *instance, gpointer g_class)
{
	SomeObject *this_object = SOME_OBJECT(instance);

	this_object->m_a = 0;
	this_object->m_b = "empty";
	this_object->m_c = 0.0;
}

GType some_object_get_type(void)
{
	static GType type = 0;

	if ( type == 0 )
	{
		static const GTypeInfo type_info = 
		{
			sizeof(SomeObjectClass),
			NULL,
			NULL,
			some_object_class_init,
			some_object_class_final,
			NULL,
			sizeof(SomeObject),
			0,
			some_object_instance_init
		};

		static const GTypeFundamentalInfo fundamental_info = 
		{
			G_TYPE_FLAG_CLASSED | G_TYPE_FLAG_INSTANTIATABLE
		};

		type = g_type_register_fundamental( g_type_fundamental_next(), "SomeObjectType", &type_info, &fundamental_info, 0);

	}

	return type;
}

