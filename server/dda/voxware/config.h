/*
*
*	config.h - describes abilities (desired or actual) of soundcard fd
*
* $NCDId: @(#)config.h,v 1.1 1996/04/24 17:00:31 greg Exp $
*/


typedef struct
{
  int fd;
  int wordSize;
  int isStereo;
  int curSampleRate;
  int minSampleRate;
  int maxSampleRate;
  int fragSize;
  int minFrags;
  int maxFrags;
  char	*device;
  int isPCSpeaker;
} SndStat;
