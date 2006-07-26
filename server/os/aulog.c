/*
 * aulog.c - provide a global logging function - varargs based for verbosity
 *           and debugging.
 *
 * $Id$
 *
 * Jon Trulson 9/11/99
 */

#include <stdio.h>
#include <stdarg.h>
#include "aulog.h"
#include "NasConfig.h"

#include "dixstruct.h"
#include "globals.h"

#if defined(DIA_USE_SYSLOG)
# include <syslog.h>
#endif

void
osLogMsg(char *fmt, ...)
{
    va_list ap;
    static char buf[LOG_BUFSIZE];
    static char errfile[LOG_FILENMSZ];
    static FILE *errfd = NULL;

    va_start(ap, fmt);

    (void) vsprintf(buf, fmt, ap);

    va_end(ap);

#if defined(DIA_USE_SYSLOG)

    if (NasConfig.DoDebug) {    /* debugging to stderr if on */
        errfd = stderr;
        if (errfd != NULL) {
            fprintf(errfd, "%s", buf);
            fflush(errfd);
        }
    } else {
        openlog("nas", LOG_PID, LOG_DAEMON);
        syslog(LOG_DEBUG, buf);
        closelog();
    }

#else /* we just send to stdout */

    errfd = stderr;

    if (errfd != NULL) {
        fprintf(errfd, "%s", buf);
        fflush(errfd);
    }
#endif /* DIA_USE_SYSLOG */

    return;

}
