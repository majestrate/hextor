
include $(top_srcdir)/m4/clang-analyze.am

localedir = $(datadir)/locale

bin_PROGRAMS = hextor

AM_CPPFLAGS = $(GUI_CFLAGS) -DLOCALEDIR=\"$(localedir)\"

hextor_LDADD = ../common/libhextorcommon.a $(GUI_LIBS)

EXTRA_DIST = \
	ascii.h banlist.h chanlist.h chanview.h chanview-tabs.c \
	chanview-tree.c custom-list.h editlist.h fe-gtk.h fkeys.h gtkutil.h joind.h \
	maingui.h menu.h notifygui.h  notifications palette.h pixmaps.h plugin-notification.h \
	plugin-tray.h plugingui.c plugingui.h rawlog.h sexy-iso-codes.h \
	sexy-spell-entry.h textgui.h urlgrab.h userlistgui.h xtext.h \
	../../data/hextor.gresource.xml

BUILT_SOURCES = resources.c

CLEANFILES = $(BUILT_SOURCES)

if DO_PLUGIN
plugingui_c = plugingui.c
endif

if HAVE_ISO_CODES
iso_codes_c = sexy-iso-codes.c
endif

if USE_LIBNOTIFY
notify_c = notifications/notification-libnotify.c
else
if HAVE_GTK_MAC
notify_c = notifications/notification-osx.m
hextor_LDFLAGS = -framework Foundation
else
notify_c = notifications/notification-dummy.c
endif
endif

hextor_SOURCES = ascii.c banlist.c chanlist.c chanview.c custom-list.c \
	dccgui.c editlist.c fe-gtk.c fkeys.c gtkutil.c ignoregui.c joind.c menu.c \
	maingui.c notifygui.c $(notify_c) palette.c pixmaps.c plugin-tray.c $(plugingui_c) \
	plugin-notification.c rawlog.c resources.c servlistgui.c setup.c $(iso_codes_c) \
	sexy-spell-entry.c textgui.c urlgrab.c userlistgui.c xtext.c
hextor_CPPFLAGS = $(AM_CPPFLAGS) -I$(top_builddir)/src/common

resources.c: $(top_srcdir)/data/hextor.gresource.xml $(shell $(GLIB_COMPILE_RESOURCES) --sourcedir=$(top_srcdir)/data --generate-dependencies $(top_srcdir)/data/hextor.gresource.xml)
	$(AM_V_GEN) $(GLIB_COMPILE_RESOURCES) --target=$@ --sourcedir=$(top_srcdir)/data --generate-source $<

if DO_STATIC_ANALYSIS
analyze_plists = $(hextor_SOURCES:%.c=%.plist)
all-local: $(analyze_plists)
MOSTLYCLEANFILES = $(analyze_plists)
endif
