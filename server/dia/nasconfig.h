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

				/* global configurables */
typedef struct {
  int DoDebug;
  int DoVerbose;
  int DoDeviceRelease;
  int DoMixerInitDevOpts;
  int DoDaemon;
} NasConfig_t;

GEXTERN NasConfig_t NasConfig;

void diaInitGlobalConfig(void);	/* init function */

#undef GEXTERN
#endif /* NASCONFIG_H_INCLUDED */
