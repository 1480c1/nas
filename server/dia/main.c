/*
 * Copyright 1993 Network Computing Devices, Inc.
 *
 * Permission to use, copy, modify, distribute, and sell this software and
 * its documentation for any purpose is hereby granted without fee, provided
 * that the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name Network Computing Devices, Inc. not be
 * used in advertising or publicity pertaining to distribution of this 
 * software without specific, written prior permission.
 * 
 * THIS SOFTWARE IS PROVIDED `AS-IS'.  NETWORK COMPUTING DEVICES, INC.,
 * DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING WITHOUT
 * LIMITATION ALL IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, OR NONINFRINGEMENT.  IN NO EVENT SHALL NETWORK
 * COMPUTING DEVICES, INC., BE LIABLE FOR ANY DAMAGES WHATSOEVER, INCLUDING
 * SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES, INCLUDING LOSS OF USE, DATA,
 * OR PROFITS, EVEN IF ADVISED OF THE POSSIBILITY THEREOF, AND REGARDLESS OF
 * WHETHER IN AN ACTION IN CONTRACT, TORT OR NEGLIGENCE, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 * 
 * $NCDId: @(#)main.c,v 1.5 1995/11/29 18:15:38 greg Exp $
 */
/***********************************************************
Some portions derived from: 

Copyright 1987 by Digital Equipment Corporation, Maynard, Massachusetts,
and the Massachusetts Institute of Technology, Cambridge, Massachusetts.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the names of Digital or MIT not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.  

DIGITAL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
DIGITAL BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/

/*
 * $Id$
 */

#include <stdio.h>
#include <audio/audio.h>
#include <audio/Aproto.h>
#include "NasConfig.h"
#include "misc.h"
#include "os.h"
#include "resource.h"
#include "dixstruct.h"
#include "opaque.h"
#include "servermd.h"
#include "site.h"
#include "globals.h"
#include "nasconfig.h"

extern void     OsInit(), InitClient(), ResetWellKnownSockets(),
                Dispatch(), FreeAllResources();
extern int      AuInitSetupReply();
extern void 	AuInitProcVectors();
extern Bool     InitClientResources();

extern char *display;

static int restart = 0;
FILE    *yyin;			/* for the config parser */

void
NotImplemented()
{
    FatalError("Not implemented");
}

/*
 *  Find the config file
 */

static FILE     *openConfigFile (char *path)
{
  static char   buf[1024];
  FILE *config;

  strcat (buf, path);
  strcat (buf, "nasd.conf");
  if ((config = fopen (buf, "r")) != NULL)
    return config;
  else
    return NULL;
}


int
main(argc, argv)
    int		argc;
    char	*argv[];
{
    int		i;

    /* Notice if we're restart.  Probably this is because we jumped through
     * uninitialized pointer */
    if (restart)
	FatalError("server restarted. Jumped through uninitialized pointer?\n");
    else
	restart = 1;

    /* Init the globals... */
    diaInitGlobals();

				/* Now parse the config file */
    if ((yyin = openConfigFile (NASCONFSEARCHPATH)) != NULL)
      yyparse();

    /* These are needed by some routines which are called from interrupt
     * handlers, thus have no direct calling path back to main and thus
     * can't be passed argc, argv as parameters */
    argcGlobal = argc;
    argvGlobal = argv;
    display = "0";
    ProcessCommandLine(argc, argv);

				/* JET - we don't actually become a
				   daemon, so what's the point?
				   REVISIT */

    /* We're running as a daemon, so close stdin, stdout and stderr
       before we start the main loop */

    close(0);
    close(1);
    close(2);

    /* And cd to / so we don't hold anything up; core files will also
       go there. */
    chdir("/");

    while(1)
    {
	serverGeneration++;
	/* Perform any operating system dependent initializations you'd like */
	OsInit();		
	if(serverGeneration == 1)
	{
	    CreateWellKnownSockets();
	    AuInitProcVectors();
	    clients = (ClientPtr *)xalloc(MAXCLIENTS * sizeof(ClientPtr));
	    if (!clients)
		FatalError("couldn't create client array");
	    for (i=1; i<MAXCLIENTS; i++) 
		clients[i] = NullClient;
	    serverClient = (ClientPtr)xalloc(sizeof(ClientRec));
	    if (!serverClient)
		FatalError("couldn't create server client");
	    InitClient(serverClient, 0, (pointer)NULL);
	}
	else
	    ResetWellKnownSockets ();
        clients[0] = serverClient;
        currentMaxClients = 1;

	if (!InitClientResources(serverClient))      /* for root resources */
	    FatalError("couldn't init server resources");

	if (!AuInitSetupReply())
	    FatalError("could not create audio connection block info");

	Dispatch();

	FreeAllResources();

	if (dispatchException & DE_TERMINATE)
	{
	    break;
	}
    }
    exit(0);
}
