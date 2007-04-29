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
#ifndef NAS_H
#define NAS_H

/*#include "config.h" JET */

#include <gtk/gtk.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>

#include <fcntl.h>
#include <pthread.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <xmms/plugin.h>
#include <xmms/configfile.h>

extern OutputPlugin op;

typedef struct {
	char* server;
	gint bufsize;
} NASConfig;

extern NASConfig nas_cfg;

void nas_init(void);
void nas_about(void);

void nas_get_volume(int* l, int* r);
void nas_set_volume(int l, int r);

int nas_playing(void);
int nas_free(void);
void nas_write(void* ptr, int length);
void nas_close(void);
void nas_flush(int time);
void nas_pause(short p);
int nas_open(AFormat fmt, int rate, int nch);
int nas_get_output_time(void);
int nas_get_written_time(void);
void nas_set_audio_params(void);
void nas_configure(void);

#endif
