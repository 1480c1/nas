/* $NCDId: @(#)gram.y,v 1.1 1996/04/24 17:01:03 greg Exp $ */

%{
#include <stdio.h>
#include <ctype.h>
#include "config.h"

extern SndStat sndStatOut, sndStatIn, *confStat;

static char	*ptr;

extern int yylineno;

extern int beVerbose;

extern void setVerboseOn(), setDebugOn();
%}

%union
{
    int num;
    char *ptr;
};

%token <num> INPUTSECTION OUTPUTSECTION ENDSECTION WORDSIZE FRAGSIZE MAXFRAGS
%token <num> MINFRAGS MAXRATE MINRATE NUMCHANS DEVICE NUMBER DEBUG VERBOSE
%token <ptr> STRING 

%type <ptr> string
%type <num> number 

%start auconfig 

%%
auconfig	: globstmts sectconfigs
		;

globstmts	: /* Empty */
		| globstmts globstmt
		;

globstmt	: VERBOSE
			{ setVerboseOn (); }
		| DEBUG
			{ setDebugOn () ; }
		;

sectconfigs	: /* Empty */
		| sectconfigs sectconfig
		;

sectconfig	: inputconfig
		| outputconfig
		;

inputconfig	: inputword stmts ENDSECTION
		;

inputword	: INPUTSECTION
			{ confStat = &sndStatIn; }
		;

outputconfig	: outputword stmts ENDSECTION
		;

outputword	: OUTPUTSECTION
			{ confStat = &sndStatOut; }
		;

stmts		: /* Empty */
		| stmts stmt
		;

stmt		: error
		| DEVICE string
			{
			  confStat->device = $2;
			  if (!strcmp ($2, "/dev/pcaudio") || !strcmp($2, "/dev/pcdsp"))
			    confStat->isPCSpeaker = 1;
			}
		| WORDSIZE number
			{
			   if ($2 != 8 && $2 != 16) {
			     fprintf(stderr, "*** Wordsize not 8 or 16, setting to 8\n");
			     confStat->wordSize = 8;
			   }
			   else
			     confStat->wordSize = $2;
			}
		| FRAGSIZE number
			{ 
			  int i, j, k;

			  /* Determine if it is a power of two */
			  k = 0;
			  j = $2;
			  for (i = 0; i < 32; i++) {
 			    if (j & 0x1)
			      k++;
			    j >>= 1;
			  }
			  if (k != 1) {
			    fprintf(stderr, "*** Fragment size should be a power of two - setting to 256\n");
			    confStat->fragSize = 256;
			  }
			  else
			    confStat->fragSize = $2;
			  if (beVerbose)
			    fprintf(stderr, "Fragsize set to %d\n", confStat->fragSize);
			}
		| MINFRAGS number
			{
			  if ($2 < 2 || $2 > 32) {
			    fprintf (stderr, "*** Minfrags out of range - setting to 2\n");
			    confStat->minFrags = 2;
			  }
			  else
			    confStat->minFrags = $2;
			  if (beVerbose)
			    fprintf(stderr, "+++ Minfrags set to %d\n", confStat->minFrags);
			}
		| MAXFRAGS number
			{
			  if ($2 < 2 || $2 > 32) {
			    fprintf (stderr, "*** Maxfrags out of range - setting to 32\n");
			    confStat->maxFrags = 32;
			  }
			  else
			    confStat->maxFrags = $2;
			  if (beVerbose)
			    fprintf(stderr, "+++ Maxfrags set to %d\n", confStat->maxFrags);
			}
		| NUMCHANS number
			{
			  if ($2 != 1 && $2 != 2) {
			    fprintf(stderr, "*** Number of channels wrong, setting to 1\n");
			    confStat->isStereo = 0;
			  }
			  else
			    confStat->isStereo = $2 - 1;
			}
		| MAXRATE number
			{confStat->maxSampleRate = $2; }
		| MINRATE number
			{ confStat->minSampleRate = $2; }

string		: STRING		{ ptr = (char *)malloc(strlen($1)+1);
					  strcpy(ptr, $1);
					  RemoveDQuote(ptr);
					  $$ = ptr;
					}
number		: NUMBER		{ $$ = $1; }
		;

%%
yyerror(s) char *s;
{
    fprintf (stderr, "error in input file:  %s\n", s ? s : "");
}
RemoveDQuote(str)
char *str;
{
    register char *i, *o;
    register n;
    register count;

    for (i=str+1, o=str; *i && *i != '\"'; o++)
    {
	if (*i == '\\')
	{
	    switch (*++i)
	    {
	    case 'n':
		*o = '\n';
		i++;
		break;
	    case 'b':
		*o = '\b';
		i++;
		break;
	    case 'r':
		*o = '\r';
		i++;
		break;
	    case 't':
		*o = '\t';
		i++;
		break;
	    case 'f':
		*o = '\f';
		i++;
		break;
	    case '0':
		if (*++i == 'x')
		    goto hex;
		else
		    --i;
	    case '1': case '2': case '3':
	    case '4': case '5': case '6': case '7':
		n = 0;
		count = 0;
		while (*i >= '0' && *i <= '7' && count < 3)
		{
		    n = (n<<3) + (*i++ - '0');
		    count++;
		}
		*o = n;
		break;
	    hex:
	    case 'x':
		n = 0;
		count = 0;
		while (i++, count++ < 2)
		{
		    if (*i >= '0' && *i <= '9')
			n = (n<<4) + (*i - '0');
		    else if (*i >= 'a' && *i <= 'f')
			n = (n<<4) + (*i - 'a') + 10;
		    else if (*i >= 'A' && *i <= 'F')
			n = (n<<4) + (*i - 'A') + 10;
		    else
			break;
		}
		*o = n;
		break;
	    case '\n':
		i++;	/* punt */
		o--;	/* to account for o++ at end of loop */
		break;
	    case '\"':
	    case '\'':
	    case '\\':
	    default:
		*o = *i++;
		break;
	    }
	}
	else
	    *o = *i++;
    }
    *o = '\0';
}

