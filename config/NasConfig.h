/*
 * NasConfig.h - some configurable features, probably candidates for
 *              autoconf'ing
 *
 * $Id$
 *
 * Jon Trulson 9/11/99
 */

/* define this if you want the logger to use syslog.  Otherwise
 * stderr will be used 
 */
  
#ifndef hpux
#define DIA_USE_SYSLOG 
#endif

/*
 * the location of the directory in which to find config files 
 *  by default if NASCONFSEARCHPATH isn't defined.
 */

#ifndef NASCONFSEARCHPATH
#define NASCONFSEARCHPATH "/etc/nas/"
#endif

