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
#include <gtk/gtk.h>

static GtkWidget *configure_win = NULL, *vbox, *notebook;
static GtkWidget *srv_vbox, *server_frame, *server_box, *server_entry;
static GtkWidget *buffer_frame, *buffer_vbox, *buffer_table;
static GtkWidget *buffer_size_box, *buffer_size_label, *buffer_size_spin;
static GtkObject *buffer_size_adj;
static GtkWidget *bbox, *ok, *cancel;

static void configure_win_ok_cb(GtkWidget *w, gpointer data)
{
	ConfigFile *cfgfile;
	gchar *filename;

	if (nas_cfg.server) g_free(nas_cfg.server);
	nas_cfg.server = g_strdup(gtk_entry_get_text(GTK_ENTRY(server_entry)));

	nas_cfg.bufsize = (gint) GTK_ADJUSTMENT(buffer_size_adj)->value;

	filename = g_strconcat(g_get_home_dir(), "/.xmms/config", NULL);
	cfgfile = xmms_cfg_open_file(filename);
	if (!cfgfile) cfgfile = xmms_cfg_new();

	xmms_cfg_write_string(cfgfile, "NAS", "server", nas_cfg.server);
	xmms_cfg_write_int(cfgfile, "NAS", "buffer_size", nas_cfg.bufsize);
	xmms_cfg_write_file(cfgfile, filename);
	xmms_cfg_free(cfgfile);

	g_free(filename);

	gtk_widget_destroy(configure_win);
}

void nas_configure(void)
{
	if (!configure_win)
	{
		configure_win = gtk_window_new(GTK_WINDOW_DIALOG);
		gtk_signal_connect(GTK_OBJECT(configure_win), "destroy",
			GTK_SIGNAL_FUNC(gtk_widget_destroyed), &configure_win);
		gtk_window_set_title(GTK_WINDOW(configure_win),
			"NAS Driver configuration");
		gtk_window_set_policy(GTK_WINDOW(configure_win),
			FALSE, FALSE, FALSE);
		gtk_window_set_position(GTK_WINDOW(configure_win),
			GTK_WIN_POS_MOUSE);
		gtk_container_border_width(GTK_CONTAINER(configure_win), 10);

		vbox = gtk_vbox_new(FALSE, 10);
		gtk_container_add(GTK_CONTAINER(configure_win), vbox);

		notebook = gtk_notebook_new();
		gtk_box_pack_start(GTK_BOX(vbox), notebook, TRUE, TRUE, 0);

		srv_vbox = gtk_vbox_new(FALSE, 5);
		gtk_container_set_border_width(GTK_CONTAINER(srv_vbox), 5);

		server_frame = gtk_frame_new("Audio server:");
		gtk_box_pack_start(GTK_BOX(srv_vbox), server_frame,
			FALSE, FALSE, 0);

		server_box = gtk_hbox_new(FALSE, 0);
		gtk_container_set_border_width(GTK_CONTAINER(server_box), 5);
		gtk_container_add(GTK_CONTAINER(server_frame), server_box);

		server_entry = gtk_entry_new();
		gtk_entry_set_text(GTK_ENTRY(server_entry), nas_cfg.server);
		gtk_box_pack_start(GTK_BOX(server_box), server_entry,
					TRUE, TRUE, 0);

		gtk_widget_show(server_entry);
		gtk_widget_show(server_box);
		gtk_widget_show(server_frame);

		gtk_widget_show(srv_vbox);
		gtk_notebook_append_page(GTK_NOTEBOOK(notebook),
				srv_vbox, gtk_label_new("Server"));

		buffer_frame = gtk_frame_new("Buffering:");
		gtk_container_set_border_width(GTK_CONTAINER(buffer_frame), 5);

		buffer_vbox = gtk_vbox_new(FALSE, 0);
		gtk_container_add(GTK_CONTAINER(buffer_frame), buffer_vbox);

		buffer_table = gtk_table_new(2, 1, TRUE);
		gtk_container_set_border_width(GTK_CONTAINER(buffer_table), 5);
		gtk_box_pack_start(GTK_BOX(buffer_vbox), buffer_table,
					FALSE, FALSE, 0);

		buffer_size_box = gtk_hbox_new(FALSE, 5);
		gtk_table_attach_defaults(GTK_TABLE(buffer_table),
					buffer_size_box, 0, 1, 0, 1);
		buffer_size_label = gtk_label_new("Buffer size (ms):");
		gtk_box_pack_start(GTK_BOX(buffer_size_box),
				buffer_size_label, FALSE, FALSE, 0);
		gtk_widget_show(buffer_size_label);
		buffer_size_adj = gtk_adjustment_new(nas_cfg.bufsize,
					200, 10000, 100, 100, 100);
		buffer_size_spin = gtk_spin_button_new(
				GTK_ADJUSTMENT(buffer_size_adj), 8, 0);
		gtk_widget_set_usize(buffer_size_spin, 60, -1);
		gtk_box_pack_start(GTK_BOX(buffer_size_box),
				buffer_size_spin, FALSE, FALSE, 0);
		gtk_widget_show(buffer_size_spin);
		gtk_widget_show(buffer_size_box);

		gtk_widget_show(buffer_table);
		gtk_widget_show(buffer_vbox);
		gtk_widget_show(buffer_frame);
		gtk_notebook_append_page(GTK_NOTEBOOK(notebook),
				buffer_frame, gtk_label_new("Buffering"));

		gtk_widget_show(notebook);

		bbox = gtk_hbutton_box_new();
		gtk_button_box_set_layout(GTK_BUTTON_BOX(bbox),
					GTK_BUTTONBOX_END);
		gtk_button_box_set_spacing(GTK_BUTTON_BOX(bbox), 5);
		gtk_box_pack_start(GTK_BOX(vbox), bbox, FALSE, FALSE, 0);

		ok = gtk_button_new_with_label("Ok");
		gtk_signal_connect(GTK_OBJECT(ok), "clicked",
				GTK_SIGNAL_FUNC(configure_win_ok_cb), NULL);
		GTK_WIDGET_SET_FLAGS(ok, GTK_CAN_DEFAULT);
		gtk_box_pack_start(GTK_BOX(bbox), ok, TRUE, TRUE, 0);
		gtk_widget_show(ok);
		gtk_widget_grab_default(ok);

		cancel = gtk_button_new_with_label("Cancel");
		gtk_signal_connect_object(GTK_OBJECT(cancel), "clicked",
				GTK_SIGNAL_FUNC(gtk_widget_destroy),
				GTK_OBJECT(configure_win));
		GTK_WIDGET_SET_FLAGS(cancel, GTK_CAN_DEFAULT);
		gtk_box_pack_start(GTK_BOX(bbox), cancel, TRUE, TRUE, 0);
		gtk_widget_show(cancel);

		gtk_widget_show(bbox);
		gtk_widget_show(vbox);
		gtk_widget_show(configure_win);
	}
	else
		gdk_window_raise(configure_win->window);
}
