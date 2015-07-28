/** @file otrm/cmds/core.h  OTRM Plugin Command Core Helpers
 */

#ifndef _OTRM_CMDS_CORE_H_
#define _OTRM_CMDS_CORE_H_

#include "cmd_header.h"
#include "ut/include/uthash.h"

#define OTRM_NAME_LEN 32
#define OTRM_USAGE_LEN 64
#define OTRM_SUMMARY_LEN 64
#define OTRM_DESCRIPTION_LEN 256

typedef struct
{
  hextor_plugin *plugin;
  OtrlUserState *userstate;
  void *userdata;
  char *word[32];
  char *word_eol[32];
} otrm_command_data;

typedef struct
{
  char name[OTRM_NAME_LEN];
  char usage[OTRM_USAGE_LEN];
  char summary[OTRM_SUMMARY_LEN];
  char description[OTRM_DESCRIPTION_LEN];
  void (*func_handler)(otrm_command_data *data);
  void (*func_startup)(void*);
  void (*func_shutdown)(void*);
} otrm_command_info;

typedef struct
{
  char name[OTRM_NAME_LEN];
  otrm_command_info info;
  UT_hash_handle hh;
} otrm_command_instance;

int otrm_register_command(const char *name, const char *usage, const char *summary, const char *description, void (*func_handler)(otrm_command_data *data),void (*func_startup)(void*),void (*func_shutdown)(void*));
int otrm_receive_input(otrm_command_data *cdata);
int otrm_startup_commands();
int otrm_shutdown_commands();

#endif //_OTRM_CMDS_CORE_H_
