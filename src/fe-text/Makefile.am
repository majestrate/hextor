localedir = $(datadir)/locale

bin_PROGRAMS = hextor-text

AM_CPPFLAGS = $(COMMON_CFLAGS) -DLOCALEDIR=\"$(localedir)\"

hextor_text_LDADD = ../common/libhextorcommon.a $(COMMON_LIBS)
hextor_text_SOURCES = fe-text.c fe-text.h

