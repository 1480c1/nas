/* config.c - configuration setting and functions for this server 
 *
 * $Id$
 *
 */

#include "nasconfig.h"
#include "config.h"
#include "aulog.h"
#include "../../dia/gram.h"

void ddaSetConfig(int token, void *value)
{
  int num;
  char *str;

  /* a switch statement based on the lex/yacc token (defined in 
     ../../dia/gram.h) is done here... Ignore any token not handled
     or understood by this server */

  switch(token)
    {

      /* nothing here yet for SGI */

    default:			/* ignore any other tokens */
      if (NasConfig.DoDebug > 5)
	osLogMsg("ddaSetConfig(): WARNING: unknown token %d, ignored\n", token);

      break;
    }

  return;			/* that's it... */
}
      
