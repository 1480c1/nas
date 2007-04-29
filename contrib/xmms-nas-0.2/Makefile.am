lib_LTLIBRARIES = libnas.la

CFLAGS = @GTK_CFLAGS@ @NAS_CFLAGS@ -W -Wall -D_REENTRANT -I$(top_srcdir)

libnas_la_LDFLAGS = -export-dynamic -avoid-version
libnas_la_SOURCES = nas.c nas.h about.c audio.c nasconf.c

LIBS = @NAS_LIBS@
