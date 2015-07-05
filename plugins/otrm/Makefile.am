libdir = $(hexchatlibdir)
ortm_dir = $(top_srcdir)/plugins/otrm

lib_LTLIBRARIES = otrm.la
otrm_la_SOURCES = otrm.c cmds/core.c cmds/version.c cmds.c
otrm_la_LDFLAGS = $(PLUGIN_LDFLAGS) -module -lotr
otrm_la_LIBADD = $(GLIB_LIBS)
otrm_la_CFLAGS = $(GLIB_CFLAGS) -std=c99 -I$(top_srcdir)/src/common -I$(otrm_dir)/ut/include
