/** @file otrm/cmds.h  OTRM Plugin Command Version
 */

#ifndef _OTRM_CMDS_VERSION_H_
#define _OTRM_CMDS_VERSION_H_

#include "header.h"

// public function declarations

int cmd_version_init();
void cmd_version_handler(otrm_command_data *cdata);
void cmd_version_startup(void*);
void cmd_version_shutdown(void*);

#endif //_OTRM_CMDS_VERSION_H_
