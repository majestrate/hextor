/* X-Chat
 * Copyright (C) 1998 Peter Zelezny.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fe-gtk.h"

#include "../common/hextor.h"
#include "../common/hextorc.h"
#include "gtkutil.h"
#include "ascii.h"
#include "maingui.h"

static const unsigned char table[]=
{
    /* Line 1 */ '\n',
    0xc2,0xa1,0xc2,0xbf,0xc2,0xa2,0xc2,0xa3,0xe2,0x82,0xac,0xc2,0xa5,0xc2,0xa6,0xc2,
    0xa7,0xc2,0xa8,0xc2,0xa9,0xc2,0xae,0xc2,0xaa,0xc2,0xab,0xc2,0xbb,0xc2,0xac,0xc2,
    0xad,0xc2,0xaf,0xe2,0x99,0xaa,
    /* Line 2 */ '\n',
    0xc2,0xba,0xc2,0xb9,0xc2,0xb2,0xc2,0xb3,0xc2,0xb4,0xc2,0xb5,0xc3,0x9e,0xc3,0xbe,
    0xc2,0xb6,0xc2,0xb7,0xc2,0xb8,0xc2,0xb0,0xc2,0xbc,0xc2,0xbd,0xc2,0xbe,0xc3,0x97,
    0xc2,0xb1,0xc3,0xb7,
    /* Line 3 */ '\n',
    0xc3,0x80,0xc3,0x81,0xc3,0x82,0xc3,0x83,0xc3,0x84,0xc3,0x85,0xc3,0x86,0xc4,0x82,
    0xc4,0x84,0x20,0xc3,0x87,0xc4,0x86,0xc4,0x8c,0xc5,0x92,0x20,0xc4,0x8e,0xc4,0x90,
    0x20,
    /* Line 4 */ '\n',
    0xc3,0xa0,0xc3,0xa1,0xc3,0xa2,0xc3,0xa3,0xc3,0xa4,0xc3,0xa5,0xc3,0xa6,0xc4,0x83,
    0xc4,0x85,0x20,0xc3,0xa7,0xc4,0x87,0xc4,0x8d,0xc5,0x93,0x20,0xc4,0x8f,0xc4,0x91,
    0x20,
    /* Line 5 */ '\n',
    0xc3,0x88,0xc3,0x89,0xc3,0x8a,0xc3,0x8b,0xc4,0x98,0xc4,0x9a,0x20,0xc4,0x9e,0x20,
    0xc3,0x8c,0xc3,0x8d,0xc3,0x8e,0xc3,0x8f,0xc4,0xb0,0x20,0xc4,0xb9,0xc4,0xbd,0xc5,
    0x81,
    /* Line 6 */ '\n',
    0xc3,0xa8,0xc3,0xa9,0xc3,0xaa,0xc3,0xab,0xc4,0x99,0xc4,0x9b,0x20,0xc4,0x9f,0x20,
    0xc3,0xac,0xc3,0xad,0xc3,0xae,0xc3,0xaf,0xc4,0xb1,0x20,0xc4,0xba,0xc4,0xbe,0xc5,
    0x82,
    /* Line 7 */ '\n',
    0xc3,0x91,0xc5,0x83,0xc5,0x87,0x20,0xc3,0x92,0xc3,0x93,0xc3,0x94,0xc3,0x95,0xc3,
    0x96,0xc3,0x98,0xc5,0x90,0x20,0xc5,0x94,0xc5,0x98,0x20,0xc5,0x9a,0xc5,0x9e,0xc5,
    0xa0,
    /* Line 8 */ '\n',
    0xc3,0xb1,0xc5,0x84,0xc5,0x88,0x20,0xc3,0xb2,0xc3,0xb3,0xc3,0xb4,0xc3,0xb5,0xc3,
    0xb6,0xc3,0xb8,0xc5,0x91,0x20,0xc5,0x95,0xc5,0x99,0x20,0xc5,0x9b,0xc5,0x9f,0xc5,
    0xa1,
    /* Line 9 */ '\n',
    0x20,0xc5,0xa2,0xc5,0xa4,0x20,0xc3,0x99,0xc3,0x9a,0xc3,0x9b,0xc5,0xb2,0xc3,0x9c,
    0xc5,0xae,0xc5,0xb0,0x20,0xc3,0x9d,0xc3,0x9f,0x20,0xc5,0xb9,0xc5,0xbb,0xc5,0xbd,
    /* Line 10 */ '\n',
    0x20,0xc5,0xa3,0xc5,0xa5,0x20,0xc3,0xb9,0xc3,0xba,0xc3,0xbb,0xc5,0xb3,0xc3,0xbc,
    0xc5,0xaf,0xc5,0xb1,0x20,0xc3,0xbd,0xc3,0xbf,0x20,0xc5,0xba,0xc5,0xbc,0xc5,0xbe,
    /* Line 11 */ '\n',
    0xd0,0x90,0xd0,0x91,0xd0,0x92,0xd0,0x93,0xd0,0x94,0xd0,0x95,0xd0,0x81,0xd0,0x96,
    0xd0,0x97,0xd0,0x98,0xd0,0x99,0xd0,0x9a,0xd0,0x9b,0xd0,0x9c,0xd0,0x9d,0xd0,0x9e,
    0xd0,0x9f,0xd0,0xa0,
    /* Line 12 */ '\n',
    0xd0,0xb0,0xd0,0xb1,0xd0,0xb2,0xd0,0xb3,0xd0,0xb4,0xd0,0xb5,0xd1,0x91,0xd0,0xb6,
    0xd0,0xb7,0xd0,0xb8,0xd0,0xb9,0xd0,0xba,0xd0,0xbb,0xd0,0xbc,0xd0,0xbd,0xd0,0xbe,
    0xd0,0xbf,0xd1,0x80,
    /* Line 13 */ '\n',
    0xd0,0xa1,0xd0,0xa2,0xd0,0xa3,0xd0,0xa4,0xd0,0xa5,0xd0,0xa6,0xd0,0xa7,0xd0,0xa8,
    0xd0,0xa9,0xd0,0xaa,0xd0,0xab,0xd0,0xac,0xd0,0xad,0xd0,0xae,0xd0,0xaf,
    /* Line 14 */ '\n',
    0xd1,0x81,0xd1,0x82,0xd1,0x83,0xd1,0x84,0xd1,0x85,0xd1,0x86,0xd1,0x87,0xd1,0x88,
    0xd1,0x89,0xd1,0x8a,0xd1,0x8b,0xd1,0x8c,0xd1,0x8d,0xd1,0x8e,0xd1,0x8f,0
};

static gboolean
ascii_enter (GtkWidget * wid, GdkEventCrossing *event, GtkWidget *label)
{
    char buf[64];
    const char *text;
    gunichar u;

    text = gtk_button_get_label (GTK_BUTTON (wid));
    u = g_utf8_get_char (text);
    sprintf (buf, "%s U+%04X", text, u);
    gtk_label_set_text (GTK_LABEL (label), buf);

    return FALSE;
}

static void
ascii_click (GtkWidget * wid, gpointer userdata)
{
    int tmp_pos;
    const char *text;

    if (current_sess)
    {
        text = gtk_button_get_label (GTK_BUTTON (wid));
        wid = current_sess->gui->input_box;
        tmp_pos = SPELL_ENTRY_GET_POS (wid);
        SPELL_ENTRY_INSERT (wid, text, -1, &tmp_pos);
        SPELL_ENTRY_SET_POS (wid, tmp_pos);
    }
}

void
ascii_open (void)
{
    int i, len;
    const unsigned char *table_pos;
    char name[8];
    GtkWidget *frame, *label, *but, *hbox = NULL, *vbox, *win;

    win = mg_create_generic_tab ("charmap", _("Character Chart"), TRUE, TRUE,
                                 NULL, NULL, 0, 0, &vbox, NULL);
    gtk_container_set_border_width (GTK_CONTAINER (win), 5);
    gtkutil_destroy_on_esc (win);

    label = gtk_label_new (NULL);

    table_pos = table;
    i = 0;
    while (table_pos[0] != 0)
    {
        if (table_pos[0] == '\n' || i == 0)
        {
            table_pos++;
            hbox = gtk_hbox_new (0, 0);
            gtk_container_add (GTK_CONTAINER (vbox), hbox);
            gtk_widget_show (hbox);
            i++;
            continue;
        }

        i++;
        len = g_utf8_skip[table_pos[0]];
        memcpy (name, table_pos, len);
        name[len] = 0;

        but = gtk_button_new_with_label (name);
        gtk_widget_set_size_request (but, 28, -1);
        g_signal_connect (G_OBJECT (but), "clicked",
                          G_CALLBACK (ascii_click), NULL);
        g_signal_connect (G_OBJECT (but), "enter_notify_event",
                          G_CALLBACK (ascii_enter), label);
        gtk_box_pack_start (GTK_BOX (hbox), but, 0, 0, 0);
        gtk_widget_show (but);

        table_pos += len;
    }

    frame = gtk_frame_new ("");
    gtk_container_add (GTK_CONTAINER (hbox), frame);
    gtk_container_add (GTK_CONTAINER (frame), label);
    gtk_widget_show (label);
    gtk_widget_show (frame);

    gtk_widget_show (win);
}
