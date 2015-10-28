libdir = $(hextorlibdir)

lib_LTLIBRARIES = otr.la
otr_la_SOURCES = otr_key.c otr_ops.c otr_util.c hextor_otr.c hextor-formats.c
otr_la_CFLAGS = $(OTR_CFLAGS) $(GLIB_CFLAGS) $(GCRYPT_CFLAGS) -I$(top_srcdir)/src/common
otr_la_LIBADD = $(OTR_LIBS) $(GLIB_LIBS) $(GCRYPT_LIBS)
otr_la_LDFLAGS = -avoid-version -module

otr-formats.h hextor-formats.c: formats.txt
	$(AM_V_GEN) python makeformats.py $<

EXTRA_DIST = formats.txt makeformats.py otr.h otr-formats.h hextor_otr.h

