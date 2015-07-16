/* Hextor
 * Copyright (C) 2015 Patrick Griffis.
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

#include "config.h"
#include <glib.h>

#include "../common/hextor-plugin.h"
#include "../common/inbound.h" /* For alert_match_word() */
#include "notifications/notification-backend.h"

static hextor_plugin *ph;

static gboolean
should_alert (void)
{
    int omit_away, omit_focused, omit_tray;

    if (hextor_get_prefs (ph, "gui_focus_omitalerts", NULL, &omit_focused) == 3 && omit_focused)
    {
        const char *status = hextor_get_info (ph, "win_status");

        if (status && !g_strcmp0 (status, "active"))
            return FALSE;
    }

    if (hextor_get_prefs (ph, "away_omit_alerts", NULL, &omit_away) == 3 && omit_away)
    {
        if (hextor_get_info (ph, "away"))
            return FALSE;
    }

    if (hextor_get_prefs (ph, "gui_tray_quiet", NULL, &omit_tray) == 3 && omit_tray)
    {
        int tray_enabled;

        if (hextor_get_prefs (ph, "gui_tray", NULL, &tray_enabled) == 3 && tray_enabled)
        {
            const char *status = hextor_get_info (ph, "win_status");

            if (status && g_strcmp0 (status, "hidden") != 0)
                return FALSE;
        }
    }

    return TRUE;
}

static gboolean
is_ignored (char *nick)
{
    const char *no_hilight;

    if (hextor_get_prefs (ph, "irc_no_hilight", &no_hilight, NULL) == 1 && no_hilight)
    {
        return alert_match_word (nick, (char*)no_hilight);
    }
    return FALSE;
}

static void
show_notification (const char *title, const char *text)
{
    char *stripped_title, *stripped_text;

    /* Strip all colors */
    stripped_title = hextor_strip (ph, title, -1, 7);
    stripped_text = hextor_strip (ph, text, -1, 7);

    notification_backend_show (stripped_title, stripped_text);

    hextor_free (ph, stripped_title);
    hextor_free (ph, stripped_text);
}

static void
show_notificationf (const char *text, const char *format, ...)
{
    va_list args;
    char *buf;

    va_start (args, format);
    buf = g_strdup_vprintf (format, args);
    va_end (args);

    show_notification (buf, text);
    g_free (buf);
}

static int
incoming_hilight_cb (char *word[], gpointer userdata)
{
    int hilight;

    if (hextor_get_prefs (ph, "input_balloon_hilight", NULL, &hilight) == 3 && hilight && should_alert())
    {
        show_notificationf (word[2], _("Highlighted message from: %s (%s)"), word[1], hextor_get_info (ph, "channel"));
    }
    return HEXTOR_EAT_NONE;
}

static int
incoming_message_cb (char *word[], gpointer userdata)
{
    int message;

    if (hextor_get_prefs (ph, "input_balloon_chans", NULL, &message) == 3 && message && should_alert ())
    {
        show_notificationf (word[2], _("Channel message from: %s (%s)"), word[1], hextor_get_info (ph, "channel"));
    }
    return HEXTOR_EAT_NONE;
}

static int
incoming_priv_cb (char *word[], gpointer userdata)
{
    int priv;

    if (hextor_get_prefs (ph, "input_balloon_priv", NULL, &priv) == 3 && priv && should_alert ())
    {
        const char *network = hextor_get_info (ph, "network");
        if (!network)
            network = hextor_get_info (ph, "server");

        if (userdata != NULL) /* Special event */
        {
            if (GPOINTER_TO_INT (userdata) == 3)
            {
                if (!is_ignored (word[2]))
                    show_notificationf (word[1], _("File offer from: %s (%s)"), word[2], network);
            }
            else if (GPOINTER_TO_INT (userdata) == 2)
            {
                if (!is_ignored (word[2]))
                    show_notificationf (word[1], _("Invited to channel by: %s (%s)"), word[2], network);
            }
            else
            {
                if (!is_ignored (word[1]))
                    show_notificationf (word[2], _("Notice from: %s (%s)"), word[1], network);
            }
        }
        else
            show_notificationf (word[2], _("Private message from: %s (%s)"), word[1], network);
    }
    return HEXTOR_EAT_NONE;
}

static int
tray_cmd_cb (char *word[], char *word_eol[], gpointer userdata)
{
    if (word[2] && !g_ascii_strcasecmp (word[2], "-b") && word[3] && word[4])
    {
        if (should_alert ())
            show_notification (word[3], word_eol[4]);
        return HEXTOR_EAT_ALL;
    }

    return HEXTOR_EAT_NONE;
}

int
notification_plugin_init (hextor_plugin *plugin_handle, char **plugin_name, char **plugin_desc, char **plugin_version, char *arg)
{
    if (!notification_backend_init ())
        return 0;

    ph = plugin_handle;
    *plugin_name = "";
    *plugin_desc = "";
    *plugin_version = "";

    hextor_hook_print (ph, "Channel Msg Hilight", HEXTOR_PRI_LOWEST, incoming_hilight_cb, NULL);
    hextor_hook_print (ph, "Channel Action Hilight", HEXTOR_PRI_LOWEST, incoming_hilight_cb, NULL);

    hextor_hook_print (ph, "Channel Message", HEXTOR_PRI_LOWEST, incoming_message_cb, NULL);
    hextor_hook_print (ph, "Channel Action", HEXTOR_PRI_LOWEST, incoming_message_cb, NULL);
    hextor_hook_print (ph, "Channel Notice", HEXTOR_PRI_LOWEST, incoming_message_cb, NULL);

    hextor_hook_print (ph, "Private Message", HEXTOR_PRI_LOWEST, incoming_priv_cb, NULL);
    hextor_hook_print (ph, "Private Message to Dialog", HEXTOR_PRI_LOWEST, incoming_priv_cb, NULL);
    hextor_hook_print (ph, "Private Action", HEXTOR_PRI_LOWEST, incoming_priv_cb, NULL);
    hextor_hook_print (ph, "Private Action to Dialog", HEXTOR_PRI_LOWEST, incoming_priv_cb, NULL);

    /* Special events treated as priv */
    hextor_hook_print (ph, "Notice", HEXTOR_PRI_LOWEST, incoming_priv_cb, GINT_TO_POINTER (1));
    hextor_hook_print (ph, "Invited", HEXTOR_PRI_LOWEST, incoming_priv_cb, GINT_TO_POINTER (2));
    hextor_hook_print (ph, "DCC Offer", HEXTOR_PRI_LOWEST, incoming_priv_cb, GINT_TO_POINTER (3));

    hextor_hook_command (ph, "TRAY", HEXTOR_PRI_HIGH, tray_cmd_cb, NULL, NULL);

    return 1;
}


int
notification_plugin_deinit (void)
{
    notification_backend_deinit ();
    return 1;
}
