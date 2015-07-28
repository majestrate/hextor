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
  otrm_command_instance *item, *tmp = NULL;
  char this_word[32] = {0x0};
  char generic_help[256] = {0x0};
  if (is_help)
  {
    snprintf(this_word,32,"%s",cdata->word[3]);
    snprintf(generic_help,256,"/otrm help <topic>\nTopics:\n");
    HASH_ITER(hh,commands,item,tmp) {
      snprintf(generic_help,256,"  %s\n",item->name);
    }
  } else {
    snprintf(this_word,32,"%s",cdata->word[2]);
  }
  /* hextor_printf */
  /*   ( cdata->plugin, "otrm_receive_input: \"%s\" \"%s\", \"%s\"\n", */
  /*     this_word,(char*)(cdata->word[2]),(char*)(cdata->word_eol[3]) */
  /*     ); */
  HASH_ITER(hh,commands,item,tmp) {
    if (strncmp(this_word,item->name,OTRM_NAME_LEN)==0)
    { // found matching command
      if (is_help == True)
      {
        char usage_info[256] = {0x0};
        snprintf
          ( usage_info, 256,
            "usage: /otrm %s\nsummary: %s\ndescription:\n%s\n",
            item->info.usage,
            item->info.summary,
            item->info.description
            );
        hextor_print
          ( cdata->plugin,
            usage_info
            );
      }
      else
      {
        if (item->info.func_handler != NULL)
          item->info.func_handler(cdata);
      }

      return RV_SUCCESS;
    }
  }
  // we made it this far, means cmd not found
  if (is_help == True)
  {
    hextor_print
      ( cdata->plugin,
        generic_help
        );
    if (cdata->word[3] != NULL)
    {
      char help_error[256];
      snprintf
        ( help_error, 256,
          "Help topic \"%s\" not found.\n",
          cdata->word[3]
          );
      hextor_print
        ( cdata->plugin,
          help_error
          );
    }
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
