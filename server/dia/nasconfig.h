/*
 * nasconfig.h
 *
 * $Id$
 *
 * Jon Trulson 9/19/99
 */

#ifndef NASCONFIG_H_INCLUDED
#define NASCONFIG_H_INCLUDED

#ifdef NASCONFIG_INSTANTIATE
# define GEXTERN
#else
# define GEXTERN extern
#endif /* NASCONFIG_INSTANTIATE */

				/* Configure types */

#define CTYPE_NULL    (0)
#define CTYPE_BOOL    (1)
#define CTYPE_STRING  (2)
#define CTYPE_NUMERIC (3)

				/* global configurables */
typedef struct {
  int DoDebug;
  int DoVerbose;
  int DoDeviceRelease;
  int DoDaemon;
} NasConfig_t;

GEXTERN NasConfig_t NasConfig;

				/* defined in server's config.c file */
void ddaSetConfig(int token, void *value);

				/* A special token for ddaSetConfig */
#define CONF_SET_SECTION (-1)

void diaInitGlobalConfig(void);	/* init function */

#undef GEXTERN
#endif /* NASCONFIG_H_INCLUDED */
