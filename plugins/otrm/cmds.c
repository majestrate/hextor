#include "cmds.h"

int otrm_cmds_init()
{
  int result;
  result = cmd_version_init();
  if (result != RV_SUCCESS)
  {
    //print error?
  }
  return RV_SUCCESS;
}
