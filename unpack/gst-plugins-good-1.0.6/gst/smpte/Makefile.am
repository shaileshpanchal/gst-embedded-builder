plugin_LTLIBRARIES = libgstsmpte.la

libgstsmpte_la_SOURCES = gstsmpte.c gstmask.c barboxwipes.c paint.c gstsmptealpha.c plugin.c

noinst_HEADERS = gstsmpte.h gstmask.h paint.h gstsmptealpha.h

libgstsmpte_la_CFLAGS = $(GST_PLUGINS_BASE_CFLAGS) $(GST_CFLAGS)
libgstsmpte_la_LIBADD = $(GST_PLUGINS_BASE_LIBS) $(GST_BASE_LIBS) $(LIBM) \
			-lgstvideo-$(GST_API_VERSION) 
libgstsmpte_la_LDFLAGS = $(GST_PLUGIN_LDFLAGS)
libgstsmpte_la_LIBTOOLFLAGS = --tag=disable-static

Android.mk: Makefile.am $(BUILT_SOURCES)
	androgenizer \
	-:PROJECT libgstsmpte -:SHARED libgstsmpte \
	 -:TAGS eng debug \
         -:REL_TOP $(top_srcdir) -:ABS_TOP $(abs_top_srcdir) \
	 -:SOURCES $(libgstsmpte_la_SOURCES) \
	 -:CFLAGS $(DEFS) $(DEFAULT_INCLUDES) $(libgstsmpte_la_CFLAGS) \
	 -:LDFLAGS $(libgstsmpte_la_LDFLAGS) \
	           $(libgstsmpte_la_LIBADD) \
	           -ldl \
	 -:PASSTHROUGH LOCAL_ARM_MODE:=arm \
		       LOCAL_MODULE_PATH:='$$(TARGET_OUT)/lib/gstreamer-0.10' \
	> $@
