#include "hexchat-plugin.h"

/**
 * OTRM - libotr plugin for hexchat
 *
 * Author: Kevin C. Krinke <kevin@krinke.ca>
 * License: GPLv2
 */

#define PNAME "OTRM"
#define PDESC "Off The Record Messaging"
#define PVERSION "1.0"

static hexchat_plugin *ph;      /* plugin handle */
static int enable = 1;

static int
otrm_cb (char *word[], char *word_eol[], void *userdata)
{
  if (!enable)
    {
      enable = 1;
      hexchat_print (ph, "OTRM now enabled!\n");
    }
  else
    {
      enable = 0;
      hexchat_print (ph, "OTRM now disabled!\n");
    }

  return HEXCHAT_EAT_ALL; /* eat this command so HexChat and other plugins can't process it */
}

void
hexchat_plugin_get_info (char **name, char **desc, char **version, void **reserved)
{
  *name = PNAME;
  *desc = PDESC;
  *version = PVERSION;
}

int
hexchat_plugin_init (hexchat_plugin *plugin_handle, char **plugin_name, char **plugin_desc, char **plugin_version, char *arg)
{
  /* we need to save this for use with any hexchat_* functions */
  ph = plugin_handle;

  /* tell HexChat our info */
  *plugin_name = PNAME;
  *plugin_desc = PDESC;
  *plugin_version = PVERSION;

  hexchat_hook_command (ph, "otrm", HEXCHAT_PRI_NORM, otrm_cb, "Usage: /OTRM {help}", 0);

  hexchat_print (ph, PNAME" loaded successfully!\n");

  return 1;       /* return 1 for success */
}