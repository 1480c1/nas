/* config.c - configuration setting and functions for this server 
 *
 * $Id$
 *
 */

#include "nasconfig.h"
#include "config.h"
#include "aulog.h"
#include "../../dia/gram.h"


extern SndStat sndStatOut, sndStatIn, *confStat;
extern int VOXMixerInit;

void ddaSetConfig(int token, void *value)
{
  int num;
  char *str;

  /* a switch statement based on the lex/yacc token (defined in 
     ../../dia/gram.h) is done here... Ignore any token not handled
     or understood by this server */

  switch(token)
    {
    case CONF_SET_SECTION:
      num = (int) value;

      if (num == INPUTSECTION)
	{			/* we're in the input section */
	  confStat = &sndStatIn;
	}
      else
	{                       /* we're in the output section */
          confStat = &sndStatOut;
        }
      break;

    case DEVICE:
      str = (char *) value;
     
      confStat->device = str;
      if (!strcmp (str, "/dev/pcaudio") || !strcmp(str, "/dev/pcdsp"))
	confStat->isPCSpeaker = 1;
      break;

    case WORDSIZE:
      num = (int) value;

      if (num != 8 && num != 16) 
	{
	  osLogMsg("*** Wordsize (%d) not 8 or 16, setting to 8\n", num);
	  confStat->wordSize = 8;
	}
      else
	confStat->wordSize = num;
      break;

    case FRAGSIZE:
      num = (int) value;

      {
	int i, j, k;
	
	/* Determine if it is a power of two */
	k = 0;
	j = num;
	for (i = 0; i < 32; i++) {
	  if (j & 0x1)
	    k++;
	  j >>= 1;
	}
	if (k != 1) {
	  osLogMsg("*** Fragment size should be a power of two - setting to 256\n");
	  confStat->fragSize = 256;
	}
	else
	  confStat->fragSize = num;
	if (NasConfig.DoDebug)
	  osLogMsg("Fragsize set to %d\n", confStat->fragSize);
      }
      break;

    case MINFRAGS:
      num = (int) value;

      if (num < 2 || num > 32) 
	{
	  osLogMsg("*** Minfrags out of range - setting to 2\n");
	  confStat->minFrags = 2;
	}
      else
	confStat->minFrags = num;

      if (NasConfig.DoDebug)
	osLogMsg("+++ Minfrags set to %d\n", confStat->minFrags);
      break;

    case MAXFRAGS:
      num = (int) value;

      if (num < 2 || num > 32) 
	{
	  osLogMsg("*** Maxfrags out of range - setting to 32\n");
	  confStat->maxFrags = 32;
	}
      else
	confStat->maxFrags = num;

      if (NasConfig.DoDebug)
	osLogMsg("+++ Maxfrags set to %d\n", confStat->maxFrags);
      break;

    case NUMCHANS:
      num = (int) value;

      if (num != 1 && num != 2) 
	{
	  osLogMsg("*** Number of channels wrong, setting to 1\n");
	  confStat->isStereo = 0;
	}
      else
	confStat->isStereo = num - 1;
      break;

    case MAXRATE:
      num = (int) value;

      confStat->maxSampleRate = num;
      break;

    case MINRATE:
      num = (int) value;

      confStat->minSampleRate = num;
      break;

    case MIXERINIT:
      num = (int) value;

      VOXMixerInit = num;
      break;

    default:			/* ignore any other tokens */
      if (NasConfig.DoDebug > 5)
	osLogMsg("ddaSetConfig() : unknown token %d, ignored\n", token);

      break;
    }

  return;			/* that's it... */
}
      
