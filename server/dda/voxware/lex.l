/* $NCDId: @(#)lex.l,v 1.1 1996/04/24 17:01:06 greg Exp $ */

%{
#include "gram.h"
#include "config.h"

extern int ParseError;

%}

string				\"([^"]|\\.)*\"
number				[0-9]+
%%

[Dd][Ee][Bb][Uu][Gg]			{ return DEBUG; }
[Vv][Ee][Rr][Bb][Oo][Ss][Ee]		{ return VERBOSE; }
[Ii][Nn][Pp][Uu][Tt][Ss][Ee][Cc][Tt][Ii][Oo][Nn] { return INPUTSECTION; }
[Oo][Uu][Tt][Pp][Uu][Tt][Ss][Ee][Cc][Tt][Ii][Oo][Nn] { return OUTPUTSECTION; }
[Ee][Nn][Dd]			{ return ENDSECTION; }
[Ww][Oo][Rr][Dd][Ss][Ii][Zz][Ee]	{ return WORDSIZE; }
[Ff][Rr][Aa][Gg][Ss][Ii][Zz][Ee]	{ return FRAGSIZE; }
[Mm][Ii][Nn][Ff][Rr][Aa][Gg][Ss]	{ return MINFRAGS; }
[Mm][Aa][Xx][Ff][Rr][Aa][Gg][Ss]	{ return MAXFRAGS; }
[Nn][Uu][Mm][Cc][Hh][Aa][Nn][Ss]	{ return NUMCHANS; }
[Mm][Aa][Xx][Rr][Aa][Tt][Ee]		{ return MAXRATE; }
[Mm][Ii][Nn][Rr][Aa][Tt][Ee]		{ return MINRATE; }
[Dd][Ee][Vv][Ii][Cc][Ee]		{ return DEVICE; }



{string}			{ yylval.ptr = (char *)yytext; return STRING; }
{number}			{ (void)sscanf((char *)yytext, "%d", &yylval.num);
				  return (NUMBER);
				}
\#[^\n]*\n			{;}
[\n\t ]				{;}
.				{
				  fprintf (stderr, 
					   "ignoring character \"%s\"\n",
					   yytext);
				  ParseError = 1;
				}
%%
#ifndef yywrap
yywrap() { return(1);}
#endif
