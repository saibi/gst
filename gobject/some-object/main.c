#include "some-object.h"

int main(void)
{
	SomeObject *testobj = NULL;

	testobj = SOME_OBJECT( g_type_create_instance(some_object_get_type()) );

	if ( testobj )
	{
		g_print("%d\n", testobj->m_a);
		some_object_method1(testobj, 32);

		g_print("%s\n", testobj->m_b);
		some_object_method2(testobj, "New string");

		g_print("%f\n", testobj->m_c);
		some_object_method3(testobj, 6.9);
	}

	return 0;
}
