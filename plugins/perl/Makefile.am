
EXTRA_DIST=generate_header lib/Hextor.pm lib/Xchat.pm lib/Hextor/Embed.pm lib/Hextor/List/Network.pm \
	lib/Hextor/List/Network/Entry.pm lib/Hextor/List/Network/AutoJoin.pm lib/IRC.pm

libdir = $(hextorlibdir)

lib_LTLIBRARIES = perl.la
perl_la_SOURCES = perl.c
perl_la_LDFLAGS = $(PERL_LDFLAGS) $(PLUGIN_LDFLAGS) -module
perl_la_LIBADD = $(GLIB_LIBS)
perl_la_CFLAGS = $(PERL_CFLAGS) $(GLIB_CFLAGS) -I$(top_srcdir)/src/common

BUILT_SOURCES = hextor.pm.h irc.pm.h
CLEANFILES = $(BUILT_SOURCES)

hextor.pm.h irc.pm.h: lib/Hextor.pm lib/Xchat.pm lib/Hextor/Embed.pm \
	lib/Hextor/List/Network.pm lib/Hextor/List/Network/Entry.pm \
	lib/Hextor/List/Network/AutoJoin.pm lib/IRC.pm
	cd $(srcdir); perl generate_header
