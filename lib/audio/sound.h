/*
 * Copyright 1993 Network Computing Devices, Inc.
 * 
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name Network Computing Devices, Inc. not be
 * used in advertising or publicity pertaining to distribution of this
 * software without specific, written prior permission.
 * 
 * THIS SOFTWARE IS PROVIDED 'AS-IS'.  NETWORK COMPUTING DEVICES, INC.,
 * DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING WITHOUT
 * LIMITATION ALL IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, OR NONINFRINGEMENT.  IN NO EVENT SHALL NETWORK
 * COMPUTING DEVICES, INC., BE LIABLE FOR ANY DAMAGES WHATSOEVER, INCLUDING
 * SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES, INCLUDING LOSS OF USE, DATA,
 * OR PROFITS, EVEN IF ADVISED OF THE POSSIBILITY THEREOF, AND REGARDLESS OF
 * WHETHER IN AN ACTION IN CONTRACT, TORT OR NEGLIGENCE, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 * 
 * $NCDId: @(#)sound.h,v 1.22 1995/12/06 01:24:53 greg Exp $
 */

/*
 * generic sound file handling
 */

#ifndef _SOUND_H_
#define _SOUND_H_

#include	<audio/snd.h>
#include	<audio/voc.h>
#include	<audio/wave.h>
#include	<audio/aiff.h>
#include	<audio/8svx.h>
#include	<audio/audio.h>

#ifndef NeedFunctionPrototypes
#if defined(FUNCPROTO) || __STDC__ || defined(__cplusplus) || defined(c_plusplus)
#define NeedFunctionPrototypes 1
#else
#define NeedFunctionPrototypes 0
#endif
#endif						/* NeedFunctionPrototypes */

#ifndef _SoundConst
#if __STDC__ || defined(__cplusplus) || defined(c_plusplus) || (FUNCPROTO&4)
#define _SoundConst const
#else
#define _SoundConst				/**/
#endif
#endif						/* _SoundConst */

#ifndef _FUNCPROTOBEGIN
#ifdef __cplusplus			/* for C++ V2.0 */
#define _FUNCPROTOBEGIN extern "C" {	/* do not leave open across includes */
#define _FUNCPROTOEND }
#else
#define _FUNCPROTOBEGIN
#define _FUNCPROTOEND
#endif
#endif /* _FUNCPROTOBEGIN */

/*
 * !!! WARNING !!!
 * 
 * Applications should not reference this structure directly.  They should use
 * the macros defined below.
 */
typedef struct
{
    int             fileFormat,
                    dataFormat,
                    numTracks,
                    sampleRate,
                    numSamples;
    char           *comment;
    void           *formatInfo;
}               SoundRec, *Sound;

char *SoundFileFormatString(Sound s);
int   SoundValidDataFormat(int _f, int _d);

#define SoundFileFormat(_s)	((_s)->fileFormat)
#define SoundDataFormat(_s) 	((_s)->dataFormat)
#define SoundDataFormatString(_s) (AuFormatToString(SoundDataFormat(_s)))
#define SoundNumTracks(_s)	((_s)->numTracks)
#define SoundSampleRate(_s)	((_s)->sampleRate)
#define SoundNumSamples(_s)	((_s)->numSamples)
#define SoundComment(_s)	((_s)->comment)
#define SoundBytesPerSample(_s)	(AuSizeofFormat(SoundDataFormat(_s)))
#define SoundNumBytes(_s)						      \
    (SoundNumSamples(_s) * SoundBytesPerSample(_s) * SoundNumTracks(_s))
#define SoundValidateDataFormat(_s)					      \
    SoundValidDataFormat(SoundFileFormat(_s), SoundDataFormat(_s))

#define SoundUnknownNumSamples	0xffffffff

_FUNCPROTOBEGIN

extern          Sound
SoundOpenFileForReading(
#if NeedFunctionPrototypes
			_SoundConst char *	/* file name */
#endif
);

extern          Sound
SoundOpenFileForWriting(
#if NeedFunctionPrototypes
			_SoundConst char *,	/* file name */
			Sound			/* sound */
#endif
);

#define SoundDestroy SoundCloseFile

extern int
SoundCloseFile(
#if NeedFunctionPrototypes
	       Sound
#endif
);

extern int
SoundReadFile(
#if NeedFunctionPrototypes
	      char *,				/* buffer */
	      int,				/* num bytes */
	      Sound
#endif
);

extern int
SoundWriteFile(
#if NeedFunctionPrototypes
	      char *,				/* buffer */
	      int,				/* num bytes */
	      Sound
#endif
);

extern          Sound
SoundCreate(
#if NeedFunctionPrototypes
	    int,				/* file format */
	    int,				/* data format */
	    int,				/* num tracks */
	    int,				/* sample rate */
	    int,				/* num samples */
	    _SoundConst char *			/* comment */
#endif
);

extern int
SoundStringToFileFormat(
#if NeedFunctionPrototypes
			_SoundConst char *	/* string */
#endif
);

extern int
SoundAbbrevToFileFormat(
#if NeedFunctionPrototypes
			_SoundConst char *	/* string */
#endif
);

extern int
SoundRewindFile(
#if NeedFunctionPrototypes
		Sound
#endif
);

extern int
SoundSeekFile(
#if NeedFunctionPrototypes
	      int,				/* number of audio bytes */
	      Sound
#endif
);

extern int
SoundTellFile(
#if NeedFunctionPrototypes
	      Sound
#endif
);

extern int
SoundFlushFile(
#if NeedFunctionPrototypes
		Sound
#endif
);

_FUNCPROTOEND

#define SoundDataFormatBit(_i)		(1L << (_i))

char *SoundFileFormatToString(int _i);
char *SoundFileFormatToAbbrev(int _i);
char *SoundFileFormatToSuffixes(int _i);

/*
 * these must be in the same order as the formats are defined in
 * _SoundFileInfo in sound.c
 */
enum _SoundFileFormatsID
{
    SoundFileFormatSnd,
    SoundFileFormatVoc,
    SoundFileFormatWave,
    SoundFileFormatAiff,
    SoundFileFormatSvx,

    SoundFileFormatNone				/* must be last */
};

/* for backwards compatibility */
#define SND_MAGIC	SoundFileFormatSnd
#define VOC_MAGIC	SoundFileFormatVoc
#define WAVE_MAGIC	SoundFileFormatWave
#define AIFF_MAGIC	SoundFileFormatAiff
#define SVX_MAGIC	SoundFileFormatSvx

typedef struct
{
    char           *string,
                   *abbrev,
                   *suffixes;
    AuUint32        dataFormats;
    void           *(*openFileForReading) (),
                   *(*openFileForWriting) ();
    int             (*readFile) (),
                    (*writeFile) (),
                    (*closeFile) (),
                    (*rewindFile) (),
                    (*seekFile) (),
                    (*tellFile) (),
                    (*flushFile) (),
                    (*toSound) (),
                    (*fromSound) ();
}               SoundInfo;

extern _SoundConst int SoundNumFileFormats;

#endif						/* _SOUND_H_ */
