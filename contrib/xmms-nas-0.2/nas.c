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

OutputPlugin nas_op;

OutputPlugin *get_oplugin_info(void)
{
	memset(&nas_op, 0, sizeof(nas_op));
	nas_op.description = "NAS Driver " VERSION;
	nas_op.init = nas_init;
	nas_op.about = nas_about;
	nas_op.configure = nas_configure;
	nas_op.get_volume = nas_get_volume;
	nas_op.set_volume = nas_set_volume;
	nas_op.open_audio = nas_open;
	nas_op.write_audio = nas_write;
	nas_op.close_audio = nas_close;
	nas_op.flush = nas_flush;
	nas_op.pause = nas_pause;
	nas_op.buffer_free = nas_free;
	nas_op.buffer_playing = nas_playing;
	nas_op.output_time = nas_get_output_time;
	nas_op.written_time = nas_get_written_time;
	return &nas_op;
}
