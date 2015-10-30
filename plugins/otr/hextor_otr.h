#include "config.h"
#include <hextor-plugin.h>

#define MODULE_NAME "otr"

#define PNAME "OTR"
#define PDESC "Off-The-Record Messaging for Hextor"
#define PVERSION PACKAGE_VERSION
#define OTR_HELP "usage: /otr <start|finish|trust|auth|authq|authabort|genkey|set|version|help>"

#define OTR_HELP_START "Initiate an OTR session. Only works in private chat dialogs.\n"
#define OTR_USAGE_START "usage: /otr start\n"

#define OTR_HELP_FINISH "End an OTR session. Only works in private chat dialogs.\n"
#define OTR_USAGE_FINISH "usage: /otr finish\n"

#define OTR_HELP_TRUST "Mark the other party's OTR key as trusted, bypassing the auth/authq process. Accepts an optional fingerpint to trust specific keys.\n"
#define OTR_USAGE_TRUST "usage: /otr trust [fingerprint]\n"

#define OTR_HELP_AUTH "Challenge the other party for authentication with a previously agreed shared secret.\n"
#define OTR_USAGE_AUTH "usage: /otr auth <secret>\n"

#define OTR_HELP_AUTHQ "Challenge the other party for authentication with a question. The other party must respond with the given answer. Only the question is transmitted to the other party.\n"
#define OTR_USAGE_AUTHQ "usage: /otr authq <question> <answer>\n"

#define OTR_HELP_AUTHABORT "Abort the current authentication challenge process.\n"
#define OTR_USAGE_AUTHABORT "usage: /otr authabort\n"

#define OTR_HELP_GENKEY "Generate new OTR keys.\n"
#define OTR_USAGE_GENKEY "usage: /otr genkey\n"

#define OTR_HELP_SET ""
#define OTR_USAGE_SET "usage: /otr set <policy|policy_known|ignore|finishonunload> <value>\n"

#define OTR_HELP_SET_POLICY ""
#define OTR_USAGE_SET_POLICY "usage: /otr set policy [value]\n"

#define OTR_HELP_SET_POLICY_KNOWN ""
#define OTR_USAGE_SET_POLICY_KNOWN "usage: /otr set policy_known [value]\n"

#define OTR_HELP_SET_IGNORE ""
#define OTR_USAGE_SET_IGNORE "usage: /otr set ignore [nick]\n"

#define OTR_HELP_SET_FINISHONUNLOAD ""
#define OTR_USAGE_SET_FINISHONUNLOAD "usage: /otr set finishonunload\n"

#define OTR_HELP_VERSION "Display the version numbers of hextor-otr and the libotr used.\n"
#define OTR_USAGE_VERSION "usage: /otr version\n"

#define OTR_HELP_HELP ""
#define OTR_USAGE_HELP_HELP "usage: /otr help <start|finish|trust|auth|authq|authabort|genkey|set|version>\n"


#define MAX_FORMAT_PARAMS 10

struct _IRC_CTX
{
	char *nick;
	char *address;
};

typedef struct _IRC_CTX IRC_CTX;

struct _FORMAT_REC
{
	char *tag;
	char *def;
};

typedef struct _FORMAT_REC FORMAT_REC;

enum
{
	MSGLEVEL_CRAP,
	MSGLEVEL_MSGS
} lvls;

extern hextor_plugin *ph; /* plugin handle */

#define statusbar_items_redraw(name) ;
#define get_irssi_dir() hextor_get_info (ph, "configdir")

void printformat (IRC_CTX *ircctx, const char *nick, int lvl, int fnum, ...);

#define otr_noticest(formatnum, ...) \
	printformat (NULL, NULL, MSGLEVEL_MSGS, formatnum, ##__VA_ARGS__)

#define otr_notice(server, nick, formatnum, ...) \
	printformat (server, nick, MSGLEVEL_MSGS, formatnum, ##__VA_ARGS__)

#define otr_infost(formatnum, ...) \
	printformat (NULL, NULL, MSGLEVEL_CRAP, formatnum, ##__VA_ARGS__)

#define otr_info(server, nick, formatnum, ...) \
	printformat (server, nick, MSGLEVEL_CRAP, formatnum, ##__VA_ARGS__)

#define otr_debug(server, nick, formatnum, ...)                                  \
	{                                                                            \
		if (debug)                                                               \
			printformat (server, nick, MSGLEVEL_MSGS, formatnum, ##__VA_ARGS__); \
	}
#define IRCCTX_DUP(ircctx) g_memdup (ircctx, sizeof(IRC_CTX));
#define IRCCTX_ADDR(ircctx) ircctx->address
#define IRCCTX_NICK(ircctx) ircctx->nick
#define IRCCTX_FREE(ircctx) g_free (ircctx)
