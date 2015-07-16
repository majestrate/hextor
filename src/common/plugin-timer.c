/* Hextor
 * Copyright (C) 1998-2010 Peter Zelezny.
 * Copyright (C) 2009-2013 Berke Viktor.
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

#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "hextor-plugin.h"

#ifdef WIN32
#define g_ascii_strcasecmp stricmp
#endif

#define _(x) hextor_gettext(ph,x)

static hextor_plugin *ph;       /* plugin handle */
static GSList *timer_list = NULL;

#define STATIC
#define HELP                                                            \
    "Usage: TIMER [-refnum <num>] [-repeat <num>] <seconds> <command>\n" \
    "       TIMER [-quiet] -delete <num>"

typedef struct
{
    hextor_hook *hook;
    hextor_context *context;
    char *command;
    int ref;
    int repeat;
    int timeout;
    unsigned int forever:1;
} timer;

static void
timer_del (timer *tim)
{
    timer_list = g_slist_remove (timer_list, tim);
    g_free (tim->command);
    hextor_unhook (ph, tim->hook);
    g_free (tim);
}

static void
timer_del_ref (int ref, int quiet)
{
    GSList *list;
    timer *tim;

    list = timer_list;
    while (list)
    {
        tim = list->data;
        if (tim->ref == ref)
        {
            timer_del (tim);
            if (!quiet)
                hextor_printf (ph, _("Timer %d deleted.\n"), ref);
            return;
        }
        list = list->next;
    }
    if (!quiet)
        hextor_print (ph, _("No such ref number found.\n"));
}

static int
timeout_cb (timer *tim)
{
    if (hextor_set_context (ph, tim->context))
    {
        hextor_command (ph, tim->command);

        if (tim->forever)
            return 1;

        tim->repeat--;
        if (tim->repeat > 0)
            return 1;
    }

    timer_del (tim);
    return 0;
}

static void
timer_add (int ref, int timeout, int repeat, char *command)
{
    timer *tim;
    GSList *list;

    if (ref == 0)
    {
        ref = 1;
        list = timer_list;
        while (list)
        {
            tim = list->data;
            if (tim->ref >= ref)
                ref = tim->ref + 1;
            list = list->next;
        }
    }

    tim = g_new (timer, 1);
    tim->ref = ref;
    tim->repeat = repeat;
    tim->timeout = timeout;
    tim->command = g_strdup (command);
    tim->context = hextor_get_context (ph);
    tim->forever = FALSE;

    if (repeat == 0)
        tim->forever = TRUE;

    tim->hook = hextor_hook_timer (ph, timeout, (void *)timeout_cb, tim);
    timer_list = g_slist_append (timer_list, tim);
}

static void
timer_showlist (void)
{
    GSList *list;
    timer *tim;

    if (timer_list == NULL)
    {
        hextor_print (ph, _("No timers installed.\n"));
        hextor_print (ph, _(HELP));
        return;
    }
    /*  00000 00000000 0000000 abc */
    hextor_print (ph, _("\026 Ref#  Seconds  Repeat  Command \026\n"));
    list = timer_list;
    while (list)
    {
        tim = list->data;
        hextor_printf (ph, _("%5d %8.1f %7d  %s\n"), tim->ref, tim->timeout / 1000.0f,
                       tim->repeat, tim->command);
        list = list->next;
    }
}

static int
timer_cb (char *word[], char *word_eol[], void *userdata)
{
    int repeat = 1;
    double timeout;
    int offset = 0;
    int ref = 0;
    int quiet = FALSE;
    char *command;

    if (!word[2][0])
    {
        timer_showlist ();
        return HEXTOR_EAT_HEXTOR;
    }

    if (g_ascii_strcasecmp (word[2], "-quiet") == 0)
    {
        quiet = TRUE;
        offset++;
    }

    if (g_ascii_strcasecmp (word[2 + offset], "-delete") == 0)
    {
        timer_del_ref (atoi (word[3 + offset]), quiet);
        return HEXTOR_EAT_HEXTOR;
    }

    if (g_ascii_strcasecmp (word[2 + offset], "-refnum") == 0)
    {
        ref = atoi (word[3 + offset]);
        offset += 2;
    }

    if (g_ascii_strcasecmp (word[2 + offset], "-repeat") == 0)
    {
        repeat = atoi (word[3 + offset]);
        offset += 2;
    }

    timeout = atof (word[2 + offset]);
    command = word_eol[3 + offset];

    if (timeout < 0.1 || timeout * 1000 > INT_MAX || !command[0])
        hextor_print (ph, HELP);
    else
        timer_add (ref, (int) timeout * 1000, repeat, command);

    return HEXTOR_EAT_HEXTOR;
}

int
#ifdef STATIC
timer_plugin_init
#else
hextor_plugin_init
#endif
(hextor_plugin *plugin_handle, char **plugin_name,
 char **plugin_desc, char **plugin_version, char *arg)
{
    /* we need to save this for use with any hextor_* functions */
    ph = plugin_handle;

    *plugin_name = "Timer";
    *plugin_desc = "IrcII style /TIMER command";
    *plugin_version = "";

    hextor_hook_command (ph, "TIMER", HEXTOR_PRI_NORM, timer_cb, _(HELP), 0);

    return 1;       /* return 1 for success */
}
