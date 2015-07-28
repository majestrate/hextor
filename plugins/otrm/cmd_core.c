#include "cmd_core.h"

static otrm_command_instance *commands = NULL;


int otrm_register_command(const char *name, const char *usage, const char *summary, const char *description, void (*func_handler)(otrm_command_data *data),void (*func_startup)(void*),void (*func_shutdown)(void*))
{
  otrm_command_instance *item = NULL;
  HASH_FIND_STR(commands,name,item);
  if (item != NULL)
    return RV_ERROR;
  item = NULL;
  item = (otrm_command_instance*)malloc(sizeof(otrm_command_instance));
  memset(item,0x0,sizeof(otrm_command_instance));
  snprintf(item->name,OTRM_NAME_LEN,"%s",name);
  snprintf(item->info.name,OTRM_NAME_LEN,"%s",name);
  snprintf(item->info.usage,OTRM_USAGE_LEN,"%s",usage);
  snprintf(item->info.summary,OTRM_SUMMARY_LEN,"%s",summary);
  snprintf(item->info.description,OTRM_DESCRIPTION_LEN,"%s",description);
  item->info.func_handler = func_handler;
  item->info.func_startup = func_startup;
  item->info.func_shutdown = func_shutdown;
  HASH_ADD_STR(commands,name,item);
  return RV_SUCCESS;
}

int otrm_startup_commands()
{
  otrm_command_instance *item, *tmp = NULL;
  HASH_ITER(hh, commands, item, tmp) {
    if (item->info.func_startup != NULL)
      item->info.func_startup((void*)(NULL));
  }
  return RV_SUCCESS;
}

int otrm_receive_input(otrm_command_data *cdata)
{
  int is_help = (strncmp((char*)(cdata->word[2]),"help",4)==0) ? True : False;
  int is_help_cmd = (is_help && (cdata->word[3] != NULL && strlen(cdata->word[3]) > 0)) ? True : False;
  int op_id = (is_help) ? 3 : 2;
  otrm_command_instance *item, *tmp = NULL;
  if (is_help)
  {
    if (is_help_cmd)
    {
      HASH_ITER(hh,commands,item,tmp) {
        if (strncmp(cdata->word[op_id],item->name,OTRM_NAME_LEN)==0)
        {
          hextor_printf
            ( cdata->plugin,
              "usage: %s\nsummary: %s\ndescription:\n%s",
              item->info.usage,
              item->info.summary,
              item->info.description
              );
          return RV_SUCCESS;
        }
      } // end HASH_ITER
      hextor_printf
        ( cdata->plugin,
          "Help topic \"%s\" not found.",
          cdata->word[op_id]
          );
      return RV_SUCCESS;
    } // end is_help_cmd
  }
  else // !is_help
  {
    HASH_ITER(hh,commands,item,tmp) {
      if (strncmp(cdata->word[op_id],item->name,OTRM_NAME_LEN)==0)
      { // found matching command
        if (item->info.func_handler != NULL)
          item->info.func_handler(cdata);
        return RV_SUCCESS;
      }
    }
  } // end is_help

  if (cdata->word[op_id] != NULL && strlen(cdata->word[op_id]) > 0)
  {
    hextor_printf
      ( cdata->plugin,
        "Command \"%s\" not found.",
        cdata->word[op_id]
        );
  }
  else
  {
    hextor_print(cdata->plugin,"/otrm help <topic>");
    hextor_print(cdata->plugin, "Available Topics:");
    HASH_ITER(hh,commands,item,tmp) {
      hextor_printf(cdata->plugin, " %s", item->name);
    }
    return RV_SUCCESS;
  }
  return RV_ERROR;
}

int otrm_shutdown_commands()
{
  otrm_command_instance *item, *tmp = NULL;
  HASH_ITER(hh, commands, item, tmp) {
    if (item->info.func_shutdown != NULL)
      item->info.func_shutdown((void*)(NULL));
    HASH_DEL(commands,item);
    free(item);
  }
  return RV_SUCCESS;
}
