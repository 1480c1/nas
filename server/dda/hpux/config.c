/* config.c - configuration setting and functions for this server 
 *
 * $Id$
 *
 */

#include "nasconfig.h"
#include "config.h"
#include "aulog.h"
#include "../../dia/gram.h"

/* for hpux */
#include <sys/audio.h>

extern int OutputDevType;

void ddaSetConfig(int token, void *value)
{
  int num;
  char *str;

  /* a switch statement based on the lex/yacc token (defined in 
     ../../dia/gram.h) is done here... Ignore any token not handled
     or understood by this server */

  switch(token)
    {

    case OUTDEVTYPE:
      str = (char *) value;
      if (!strcmp(str, "ext") ||
	  !strcmp(str, "EXT"))
	{
	  OutputDevType = AUDIO_OUT_EXTERNAL;
	  if (NasConfig.DoDebug)
	    osLogMsg("### Intializing to AUDIO_OUT_EXTERNAL\n");
	}
      else if (!strcmp(str, "int") ||
	  !strcmp(str, "INT"))
	{
	  OutputDevType = AUDIO_OUT_INTERNAL;
	  if (NasConfig.DoDebug)
	    osLogMsg("### Intializing to AUDIO_OUT_INTERNAL\n");
	}
      else			/* default - external */
	{
	  OutputDevType = AUDIO_OUT_EXTERNAL;
	  osLogMsg("ddaSetConfig(): unknown OutDevType '%s'\n", str);
	}

      break;

    default:			/* ignore any other tokens */
      if (NasConfig.DoDebug > 5)
	osLogMsg("ddaSetConfig(): WARNING: unknown token %d, ignored\n", token);

      break;
    }

  return;			/* that's it... */
}
      
