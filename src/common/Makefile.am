## Process this file with automake to produce Makefile.in

include $(top_srcdir)/m4/clang-analyze.am

noinst_LIBRARIES = libhextorcommon.a

AM_CPPFLAGS = $(COMMON_CFLAGS) -I$(top_srcdir)

EXTRA_DIST = \
	cfgfiles.h \
	chanopt.h \
	ctcp.h \
	dcc.h \
	fe.h \
	hextor.h \
	hextorc.h \
	hextor-plugin.h \
	history.h \
	ignore.h \
	inbound.h \
	inet.h \
	make-te.c \
	modes.h \
	network.h \
	notify.h \
	outbound.h \
	plugin.h \
	plugin-identd.h \
	plugin-timer.h \
	proto-irc.h \
	server.h \
	servlist.h \
	ssl.h \
	ssl.c	\
	text.h \
	typedef.h \
	textenums.h \
	textevents.h \
	textevents.in \
	tree.h \
	url.h \
	userlist.h \
	util.h

if USE_OPENSSL
ssl_c = ssl.c
endif

SUBDIRS = .

if DO_PLUGIN
include_HEADERS = hextor-plugin.h
endif

noinst_PROGRAMS = make-te

libhextorcommon_a_SOURCES = cfgfiles.c chanopt.c ctcp.c dcc.c hextor.c \
	history.c ignore.c inbound.c marshal.c modes.c network.c notify.c \
	outbound.c plugin.c plugin-identd.c plugin-timer.c proto-irc.c server.c servlist.c \
	$(ssl_c) text.c tree.c url.c userlist.c util.c
libhextorcommon_a_CFLAGS = $(LIBPROXY_CFLAGS)

textenums.h: textevents.h

textevents.h: $(srcdir)/textevents.in make-te
	$(AM_V_GEN) ./make-te < $< > $@ 2> textenums.h

marshal.h: $(srcdir)/marshalers.list
	$(AM_V_GEN) $(GLIB_GENMARSHAL) --prefix=_hextor_marshal --header $< > $@

marshal.c: $(srcdir)/marshalers.list
	$(AM_V_GEN) $(GLIB_GENMARSHAL) --prefix=_hextor_marshal --body $< > $@


if DO_STATIC_ANALYSIS
analyze_plists = $(libhextorcommon_a_SOURCES:%.c=%.plist)
all-local: $(analyze_plists)
MOSTLYCLEANFILES = $(analyze_plists)
endif

BUILT_SOURCES = textenums.h textevents.h marshal.c marshal.h

CLEANFILES = $(BUILT_SOURCES)
