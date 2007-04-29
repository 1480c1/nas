/*\  XMMS - Cross-platform multimedia player
|*|  Copyright (C) 1998-1999  Peter Alm, Mikael Alm, Olle Hallnas,
|*|                          Thomas Nilsson and 4Front Technologies
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
#include <gtk/gtk.h>

static GtkWidget *dialog, *button, *label;

void nas_about(void)
{

	dialog = gtk_dialog_new();
	gtk_window_set_title(GTK_WINDOW(dialog), "About NAS Driver 0.1");
	gtk_container_border_width(GTK_CONTAINER(dialog), 5);
	label = gtk_label_new("XMMS Network Audio System Driver 0.1\n\n \
Written by Willem Monsuwe (willem@stack.nl)\n\n\
Network Audio System  copyright  Network Computing Devices, Inc.\n\n\
This program is free software; you can redistribute it and/or modify\n\
it under the terms of the GNU General Public License as published by\n\
the Free Software Foundation; either version 2 of the License, or\n\
(at your option) any later version.\n\
\n\
This program is distributed in the hope that it will be useful,\n\
but WITHOUT ANY WARRANTY; without even the implied warranty of\n\
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n\
GNU General Public License for more details.\n\
\n\
You should have received a copy of the GNU General Public License\n\
along with this program; if not, write to the Free Software\n\
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307,\n\
USA.");
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox), label, TRUE, TRUE, 0);
	gtk_widget_show(label);

	button = gtk_button_new_with_label(" Close ");
	gtk_signal_connect_object(GTK_OBJECT(button), "clicked", GTK_SIGNAL_FUNC(gtk_widget_destroy), GTK_OBJECT(dialog));
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->action_area), button, FALSE, FALSE, 0);
	gtk_widget_show(button);

	gtk_widget_show(dialog);
	gtk_widget_grab_focus(button);
}
