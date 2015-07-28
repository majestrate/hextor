#include "cmd_version.h"

// private function definitions
// public function definitions

int cmd_version_init()
{
  return
    otrm_register_command
    ( "version",
      "version",
      "Displays the OTRM plugin and LibOTR version numbers.",
      "  Outputs the current OTRM plugin version as well as the\n"
      "  version number of the LibOTR library used by the plugin.\n"
      "  See https://otr.im/ for more information about Off-the-\n"
      "  Record Messaging and LibOTR.",
      cmd_version_handler,
      cmd_version_startup,
      cmd_version_shutdown
      );
}

void cmd_version_handler(otrm_command_data *cdata)
{
  hextor_print
    ( cdata->plugin,
      "OTRM Plugin v"PLUGIN_VERSION", libotr v"OTRL_VERSION"\n"
      );
  return;
}

void cmd_version_startup(void*ptr)
{
  return;
}

void cmd_version_shutdown(void*ptr)
{
  return;
}
