/*
 * nasconfig.c - init/configure some things...
 *
 * $Id$
 *
 * Jon Trulson, 9/19/1999
 */

#include "misc.h"
				/* the NasConfig structure is
				   instantiated from within
				   globals.c */
#include "nasconfig.h"

/* Initialize the global config items */

void diaInitGlobalConfig()
{
				/* init all the default values */
  NasConfig.DoDebug = FALSE;
  NasConfig.DoVerbose = FALSE;
  NasConfig.DoDeviceRelease = TRUE;
  NasConfig.DoDaemon = FALSE;

  				/* that be it */
  return;
}
