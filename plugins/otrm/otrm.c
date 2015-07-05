#include "constants.h"
#include "cmds.h"

static hexchat_plugin *g_plugin = NULL;    ///< plugin handle
static OtrlUserState g_userstate;  ///< OTR User State

static int otrm_cb (char *word[], char *word_eol[], void *userdata)
{
  /* char *s; */
  int result;
  if (strncmp(word[1],"otrm",4) == 0)
  {
    otrm_command_data *cdata;
    cdata = (otrm_command_data*)malloc(sizeof(otrm_command_data));
    cdata->plugin = g_plugin;
    for (int i=0;i<32;i++)
    {
      /* s = (char*)malloc(sizeof(char)*256); */
      /* memset(s,0x0,256); */
      /* if (word[i]!=0x0) */
      /* { */
      /*   snprintf(s,256,"%s",(char*)(word[i])); */
      /*   cdata->word[i] = s; */
      /* } */
      cdata->word[i] = word[i];
      //hexchat_printf(g_plugin,"word[%d]: %s\n",i,cdata->word[i]);
    }
    for (int i=0;i<32;i++)
    {
      /* s = (char*)malloc(sizeof(char)*256); */
      /* memset(s,0x0,256); */
      /* if (word_eol[i]!=0x0) */
      /* { */
      /*   snprintf(s,256,"%s",(char*)(word_eol[i])); */
      /*   cdata->word_eol[i] = s; */
      /* } */
      cdata->word_eol[i] = word_eol[i];
      //hexchat_printf(g_plugin,"word[%d]: %s\n",i,cdata->word_eol[i]);
    }
    cdata->userdata = userdata;
    result = otrm_receive_input(cdata);
    if (result != RV_SUCCESS)
    {
      // basic usage info
      hexchat_print (g_plugin, "usage: /otrm help\n");
    }

    free(cdata);
    return HEXCHAT_EAT_ALL;
  }
  return HEXCHAT_EAT_NONE;
}

void hexchat_plugin_get_info (char **name, char **desc, char **version, void **reserved)
{
  *name = PLUGIN_NAME;
  *desc = PLUGIN_DESC;
  *version = PLUGIN_VERSION;
}

int hexchat_plugin_init (hexchat_plugin *plugin_handle, char **plugin_name, char **plugin_desc, char **plugin_version, char *arg)
{
  OTRL_INIT;

  g_userstate = otrl_userstate_create();

  /* we need to save this for use with any hexchat_* functions */
  if (g_plugin==NULL)
    g_plugin = plugin_handle;

  /* tell HexChat our info */
  *plugin_name = PLUGIN_NAME;
  *plugin_desc = PLUGIN_DESC;
  *plugin_version = PLUGIN_VERSION;

  otrm_cmds_init();
  otrm_startup_commands();

  hexchat_hook_command(g_plugin, "otrm", HEXCHAT_PRI_NORM, otrm_cb,
                       "usage: /otrm help", 0);

  hexchat_print(g_plugin, PLUGIN_NAME" plugin loaded.\n");
  return RV_SUCCESS;
}

int hexchat_plugin_deinit (void)
{
  otrm_shutdown_commands();
  otrl_userstate_free(g_userstate);
  hexchat_print(g_plugin, PLUGIN_NAME" plugin unloaded.\n");
  return RV_SUCCESS;
}
