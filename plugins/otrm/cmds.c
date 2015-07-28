#include "cmds.h"

// include command headers here
#include "cmd_version.h"

int otrm_cmds_init()
{
  // register commands here
  cmd_version_init();
  return RV_SUCCESS;
}
