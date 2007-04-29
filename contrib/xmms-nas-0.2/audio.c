/*\  XMMS - Cross-platform multimedia player
|*|  Copyright (C) 1998-1999  Peter Alm, Mikael Alm, Olle Hallnas,
|*|                           Thomas Nilsson and 4Front Technologies
|*|
|*|  Network Audio System driver by Willem Monsuwe (willem@stack.nl)
|*|
|*|  This program is free software; you can redistribute it and/or modify
|*|  it under the terms of the GNU General Public License as published by
|*|  the Free Software Foundation; either version 2 of the License, or
|*|  (at your option) any later version.
|*|
|*|  This program is distributed in the hope that it will be useful,
|*|  but WITHOUT ANY WARRANTY; without even the implied warranty of
|*|  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
|*|  GNU General Public License for more details.
|*|
|*|  You should have received a copy of the GNU General Public License
|*|  along with this program; if not, write to the Free Software
|*|  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
\*/
#include "nas.h"
#include <xmms/configfile.h>
#include <errno.h>
#include <audio/audiolib.h>

static AuServer*  aud = 0;
static AuFlowID   flow;
static AuDeviceID dev;

static gint buf_free = -1;

static gint do_pause = 0, paused = 0, written = 0, really = 0;
static gint bps;
static struct timeval last_tv;
static unsigned char format;
static int set_vol, volume = 100;

NASConfig nas_cfg;

void nas_init(void)
{
	ConfigFile *cfgfile;
	gchar *filename;

	memset(&nas_cfg, 0, sizeof(NASConfig));

	nas_cfg.server = g_strdup("");;
	nas_cfg.bufsize = 2500;

	filename = g_strconcat(g_get_home_dir(), "/.xmms/config", NULL);
	if ((cfgfile = xmms_cfg_open_file(filename)))
	{
		xmms_cfg_read_string(cfgfile, "NAS", "server",
					&nas_cfg.server);
		xmms_cfg_read_int(cfgfile, "NAS", "buffer_size",
					&nas_cfg.bufsize);
		xmms_cfg_free(cfgfile);
	}
}

static void
set_volume(void)
{
	AuDeviceAttributes* da;
	if (!aud) return;
	da = AuGetDeviceAttributes(aud, dev, NULL);
	AuDeviceGain(da) = AuFixedPointFromSum(volume, 0);
	AuSetDeviceAttributes(aud, AuDeviceIdentifier(da),
				AuCompDeviceGainMask, da, NULL);
	AuFreeDeviceAttributes(aud, 1, da);
	set_vol = volume;
}

void
nas_get_volume(int* l, int* r)
{
	*l = *r = volume;
}

void
nas_set_volume(int l, int r)
{
	volume = (l > r) ? l : r;
}

gint
nas_get_written_time(void)
{
	gint r;
	if (!aud) return 0;
	r = (gint) (((gfloat) written * 1000) / (gfloat) (bps));
	if (r < 0) r = 0;
	return r;
}

gint
nas_get_output_time(void)
{
	static struct timeval tv;
	gint r;
	if (!aud) return 0;
	r = (gint) (((gfloat) (really - 32768) * 1000) / (gfloat) (bps));
	if (!paused)
		gettimeofday(&tv, 0);
	r += (tv.tv_sec - last_tv.tv_sec) * 1000;
	r += tv.tv_usec / 1000;
	r -= last_tv.tv_usec / 1000;
	if (r < 0) r = 0;
	return r;
}

gint
nas_playing(void)
{
	AuElementState* aesp;
	AuElementState aes = {
		flow,
		AuElementAll,
		AuStateStart,
		0
	};
	gint pl = 0, i = 1;

	if (!aud) return 0;
	aesp = AuGetElementStates(aud, &i, &aes, NULL);
	if ((i > 0) && (aesp[0].state == AuStateStart)) pl = 1;
	AuFreeElementStates(aud, i, aesp);
	return pl;
}

gint
nas_free(void)
{
	int dp;
	if (set_vol != volume) set_volume();
	dp = do_pause;
	if (dp != paused) {
		if (dp)
			AuPauseFlow(aud, flow, NULL);
		else
			AuStartFlow(aud, flow, NULL);
		AuFlush(aud);
		paused = dp;
		gettimeofday(&last_tv, 0);
	}
	if (dp) return 0;
	if (buf_free < 8192) {
		gint n = AuEventsQueued(aud, AuEventsQueuedAfterReading);
		while (--n >= 0) {
			AuEvent ev;
			AuNextEvent(aud, AuTrue, &ev);
			AuDispatchEvent(aud, &ev);
		}
		AuFlush(aud);
	}
	return buf_free;
}

void
nas_write(void* ptr, gint len)
{
	if (!aud) return;
	if (set_vol != volume) set_volume();
	if (paused) return;
	while (len > buf_free) {
		AuEvent ev;
		AuNextEvent(aud, AuTrue, &ev);
		AuDispatchEvent(aud, &ev);
	}
	buf_free -= len;
	AuWriteElement(aud, flow, 0, len, ptr, AuFalse, NULL);
	written += len;
}

void
nas_close(void)
{
	if (!aud) return;
	AuStopFlow(aud, flow, NULL);
	AuCloseServer(aud);
	aud = 0;
}

void
nas_flush(gint time)
{
	if (!aud) return;
	AuStopFlow(aud, flow, NULL);
	AuFlush(aud);
	gettimeofday(&last_tv, 0);
	really = written = (time / 10) * (bps / 100);
	buf_free = -1;
	AuStartFlow(aud, flow, NULL);
}

void
nas_pause(short p)
{
	do_pause = p;
}

static unsigned char
aformat_to_au_format(AFormat fmt)
{
	switch (fmt)
	{
		case FMT_U8:
			return AuFormatLinearUnsigned8;
		case FMT_S8:
			return AuFormatLinearSigned8;
		case FMT_U16_LE:
#ifndef WORDS_BIGENDIAN
		case FMT_U16_NE:
#endif
			return AuFormatLinearUnsigned16LSB;
		case FMT_U16_BE:
#ifdef WORDS_BIGENDIAN
		case FMT_U16_NE:
#endif
			return AuFormatLinearUnsigned16MSB;
		case FMT_S16_LE:
#ifndef WORDS_BIGENDIAN
		case FMT_S16_NE:
#endif
			return AuFormatLinearSigned16LSB;
		case FMT_S16_BE:
#ifdef WORDS_BIGENDIAN
		case FMT_S16_NE:
#endif
			return AuFormatLinearSigned16MSB;
	}
	return AuNone;
}

static AuDeviceID
find_device(gint nch)
{
	gint i;
	for (i = 0; i < AuServerNumDevices(aud); i++) {
		if ((AuDeviceKind(AuServerDevice(aud, i)) ==
				AuComponentKindPhysicalOutput) &&
			AuDeviceNumTracks(AuServerDevice(aud, i)) == nch) {
			return AuDeviceIdentifier(AuServerDevice(aud, i));
		}
	}
	return AuNone;
}

static AuBool
event_handler(AuServer* aud, AuEvent* ev, AuEventHandlerRec* hnd)
{
	switch (ev->type) {
	case AuEventTypeElementNotify: {
		AuElementNotifyEvent* event = (AuElementNotifyEvent *)ev;

		switch (event->kind) {
		case AuElementNotifyKindLowWater:
			if (buf_free >= 0) {
				really += event->num_bytes;
				gettimeofday(&last_tv, 0);
				buf_free += event->num_bytes;
			} else {
				buf_free = event->num_bytes;
			}
			break;
		case AuElementNotifyKindState:
			switch (event->cur_state) {
			case AuStatePause:
				if (event->reason != AuReasonUser) {
					if (buf_free >= 0) {
						really += event->num_bytes;
						gettimeofday(&last_tv, 0);
						buf_free += event->num_bytes;
					} else {
						buf_free = event->num_bytes;
					}
				}
				break;
			}
		}
	}
	}
	return AuTrue;
}

gint
nas_open(AFormat fmt, gint rate, gint nch)
{
	AuElement elms[3];
	gint buffer_size;

	format = aformat_to_au_format(fmt);
	bps = rate * nch * AuSizeofFormat(format);;

	buffer_size = (nas_cfg.bufsize * rate) / 1000;
	if (buffer_size < 4096)
		buffer_size = 4096;

	aud = AuOpenServer(nas_cfg.server, 0, NULL, 0, NULL, NULL);
	if (!aud) return 0;
	dev = find_device(nch);
	if ((dev == AuNone) || (!(flow = AuCreateFlow(aud, NULL)))) {
		AuCloseServer(aud);
		aud = 0;
		return 0;
	}
	set_volume();

	AuMakeElementImportClient(elms, rate, format, nch, AuTrue,
				buffer_size, buffer_size / 2, 0, NULL);
	AuMakeElementExportDevice(elms+1, 0, dev, rate,
				AuUnlimitedSamples, 0, NULL);
	AuSetElements(aud, flow, AuTrue, 2, elms, NULL);
	AuRegisterEventHandler(aud, AuEventHandlerIDMask, 0, flow,
				event_handler, (AuPointer) NULL);

	gettimeofday(&last_tv, 0);
	really = written = 0;
	paused = do_pause = 0;
	buf_free = -1;
	AuStartFlow(aud, flow, NULL);
	return 1;
}
