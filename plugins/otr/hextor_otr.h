#include "config.h"
#include <hextor-plugin.h>

#define MODULE_NAME "otr"

#define PNAME "OTR"
#define PDESC "Off-The-Record Messaging for Hextor"
#define PVERSION PACKAGE_VERSION
#define OTR_HELP "OTR <version|finish|trust|auth|authabort|genkey|set>"

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
