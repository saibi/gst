#ifndef __HLW_HELLO_APP_H__
#define __HLW_HELLO_APP_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define HLW_TYPE_HELLO_APP (hlw_hello_app_get_type())
G_DECLARE_FINAL_TYPE (HlwHelloApp, hlw_hello_app, HLW, HELLO_APP, Gobject)

HlwHelloApp *hlw_hello_app_new(void);
gint hlw_hello_app_hello(HlwHelloApp *self, const gchar *msg, gchar *hello_msg);


G_END_DECLS


#endif // __HLW_HELLO_APP_H__
