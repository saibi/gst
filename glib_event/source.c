#include <glib.h>

gboolean callback(gpointer data)
{
	static int i = 0;

	i++;

	g_print("callback called %d times\n", i);

	if ( 10 == i )
	{
		g_main_loop_quit((GMainLoop*)data);
		return FALSE;
	}
	return TRUE;
}


gboolean prepare(GSource *source, gint *timeout_)
{
	g_print("prepare\n");
	*timeout_ = -1;
	return TRUE;
}

gboolean check(GSource *source)
{
	g_print("check\n");
	return TRUE;
}

gboolean dispatch(GSource *source, GSourceFunc callback, gpointer user_data)
{
	g_print("dispatch\n");
	if ( callback(user_data))
		return TRUE;
	else
		return FALSE;
}


int main(int argc, char *argv[])
{
	GMainLoop * loop = NULL;
	GMainContext *context;
	GSource *source;
	int id;

	// create a variable of type GSourceFuncs
	GSourceFuncs SourceFuncs = 
	{
		prepare,
		check,
		dispatch,
		NULL
	};

	// create a new source 
	source = g_source_new(&SourceFuncs, sizeof(GSource));

	// create a context
	context = g_main_context_new();

	// attach source to context 
	id = g_source_attach(source, context);
	
	// create a main loop with context
	loop = g_main_loop_new(context, FALSE);

	// set the callback for this source 
	g_source_set_callback(source, callback, loop, NULL);

	g_print("start main loop\n");
	g_main_loop_run(loop);
	g_print("end\n");

	g_main_loop_unref(loop);

	return 0;
}
