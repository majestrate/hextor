libdir = $(hexchatlibdir)

lib_LTLIBRARIES = otrm.la
otrm_la_SOURCES = otrm.c
otrm_la_LDFLAGS = $(PLUGIN_LDFLAGS) -module -lotr
otrm_la_LIBADD = $(GLIB_LIBS)
otrm_la_CFLAGS = $(GLIB_CFLAGS) -I$(top_srcdir)/src/common
