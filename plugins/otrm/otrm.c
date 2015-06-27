#include "hexchat-plugin.h"
#include <stdio.h>
#include <string.h>
#include <libotr/proto.h>
#include <libotr/message.h>
#include <libotr/userstate.h>

#define True 1
#define False 0
#define RV_SUCCESS 1
#define RV_ERROR 0

/** @file plugins/otrm/otrm.c OTR implementation for hexchat
 *
 * Author: Kevin C. Krinke <kevin@krinke.ca>
 * License: GPLv2
 */

#define PNAME "OTRM"
#define PDESC "Off The Record Messaging"
#define PVERSION "1.0"

static hexchat_plugin *g_plugin; ///< plugin handle
static OtrlUserState *g_userstate;  ///< OTR User State

static int
otrm_cb (char *word[], char *word_eol[], void *userdata)
{
  if (strncmp(word[2],"version",7)==0) {
    hexchat_print (g_plugin, "OTRM Plugin v"PVERSION", libotr v"OTRL_VERSION"\n");
    return HEXCHAT_EAT_ALL; /* eat this command so HexChat and other plugins can't process it */
  }

  hexchat_print (g_plugin, "usage: /otrm {help|version}\n");
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
  OTRL_INIT;

  g_userstate = otrl_userstate_create();

  /* we need to save this for use with any hexchat_* functions */
  g_plugin = plugin_handle;

  /* tell HexChat our info */
  *plugin_name = PNAME;
  *plugin_desc = PDESC;
  *plugin_version = PVERSION;

  hexchat_hook_command (g_plugin, "otrm", HEXCHAT_PRI_NORM, otrm_cb, "Usage: /OTRM {help|version}", 0);

  hexchat_print (g_plugin, PNAME" plugin loaded.\n");

  return 1;       /* return 1 for success */
}

int
hexchat_plugin_deinit (void)
{
  otrl_userstate_free(*g_userstate);
  hexchat_print (g_plugin, PNAME" plugin unloaded.\n");
  return 1;       /* return 1 for success */
}
