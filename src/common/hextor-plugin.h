/* Hextor
 * Copyright (C) 1998-2010 Peter Zelezny.
 * Copyright (C) 2009-2013 Berke Viktor.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

/* You can distribute this header with your plugins for easy compilation */
#ifndef HEXTOR_PLUGIN_H
#define HEXTOR_PLUGIN_H

#include <time.h>

#define HEXTOR_PRI_HIGHEST	127
#define HEXTOR_PRI_HIGH		64
#define HEXTOR_PRI_NORM		0
#define HEXTOR_PRI_LOW		(-64)
#define HEXTOR_PRI_LOWEST	(-128)

#define HEXTOR_FD_READ		1
#define HEXTOR_FD_WRITE		2
#define HEXTOR_FD_EXCEPTION	4
#define HEXTOR_FD_NOTSOCKET	8

#define HEXTOR_EAT_NONE		0	/* pass it on through! */
#define HEXTOR_EAT_HEXTOR		1	/* don't let Hextor see this event */
#define HEXTOR_EAT_PLUGIN	2	/* don't let other plugins see this event */
#define HEXTOR_EAT_ALL		(HEXTOR_EAT_HEXTOR|HEXTOR_EAT_PLUGIN)	/* don't let anything see this event */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _hextor_plugin hextor_plugin;
typedef struct _hextor_list hextor_list;
typedef struct _hextor_hook hextor_hook;
#ifndef PLUGIN_C
typedef struct _hextor_context hextor_context;
#endif
typedef struct
{
	time_t server_time_utc; /* 0 if not used */
} hextor_event_attrs;

#ifndef PLUGIN_C
struct _hextor_plugin
{
	/* these are only used on win32 */
	hextor_hook *(*hextor_hook_command) (hextor_plugin *ph,
		    const char *name,
		    int pri,
		    int (*callback) (char *word[], char *word_eol[], void *user_data),
		    const char *help_text,
		    void *userdata);
	hextor_hook *(*hextor_hook_server) (hextor_plugin *ph,
		   const char *name,
		   int pri,
		   int (*callback) (char *word[], char *word_eol[], void *user_data),
		   void *userdata);
	hextor_hook *(*hextor_hook_print) (hextor_plugin *ph,
		  const char *name,
		  int pri,
		  int (*callback) (char *word[], void *user_data),
		  void *userdata);
	hextor_hook *(*hextor_hook_timer) (hextor_plugin *ph,
		  int timeout,
		  int (*callback) (void *user_data),
		  void *userdata);
	hextor_hook *(*hextor_hook_fd) (hextor_plugin *ph,
		   int fd,
		   int flags,
		   int (*callback) (int fd, int flags, void *user_data),
		   void *userdata);
	void *(*hextor_unhook) (hextor_plugin *ph,
	      hextor_hook *hook);
	void (*hextor_print) (hextor_plugin *ph,
	     const char *text);
	void (*hextor_printf) (hextor_plugin *ph,
	      const char *format, ...)
#ifdef __GNUC__
	__attribute__((format(printf, 2, 3)))
#endif
	;
	void (*hextor_command) (hextor_plugin *ph,
	       const char *command);
	void (*hextor_commandf) (hextor_plugin *ph,
		const char *format, ...)
#ifdef __GNUC__
	__attribute__((format(printf, 2, 3)))
#endif
	;
	int (*hextor_nickcmp) (hextor_plugin *ph,
	       const char *s1,
	       const char *s2);
	int (*hextor_set_context) (hextor_plugin *ph,
		   hextor_context *ctx);
	hextor_context *(*hextor_find_context) (hextor_plugin *ph,
		    const char *servname,
		    const char *channel);
	hextor_context *(*hextor_get_context) (hextor_plugin *ph);
	const char *(*hextor_get_info) (hextor_plugin *ph,
		const char *id);
	int (*hextor_get_prefs) (hextor_plugin *ph,
		 const char *name,
		 const char **string,
		 int *integer);
	hextor_list * (*hextor_list_get) (hextor_plugin *ph,
		const char *name);
	void (*hextor_list_free) (hextor_plugin *ph,
		 hextor_list *xlist);
	const char * const * (*hextor_list_fields) (hextor_plugin *ph,
		   const char *name);
	int (*hextor_list_next) (hextor_plugin *ph,
		 hextor_list *xlist);
	const char * (*hextor_list_str) (hextor_plugin *ph,
		hextor_list *xlist,
		const char *name);
	int (*hextor_list_int) (hextor_plugin *ph,
		hextor_list *xlist,
		const char *name);
	void * (*hextor_plugingui_add) (hextor_plugin *ph,
		     const char *filename,
		     const char *name,
		     const char *desc,
		     const char *version,
		     char *reserved);
	void (*hextor_plugingui_remove) (hextor_plugin *ph,
			void *handle);
	int (*hextor_emit_print) (hextor_plugin *ph,
			const char *event_name, ...);
	int (*hextor_read_fd) (hextor_plugin *ph,
			void *src,
			char *buf,
			int *len);
	time_t (*hextor_list_time) (hextor_plugin *ph,
		hextor_list *xlist,
		const char *name);
	char *(*hextor_gettext) (hextor_plugin *ph,
		const char *msgid);
	void (*hextor_send_modes) (hextor_plugin *ph,
		  const char **targets,
		  int ntargets,
		  int modes_per_line,
		  char sign,
		  char mode);
	char *(*hextor_strip) (hextor_plugin *ph,
	     const char *str,
	     int len,
	     int flags);
	void (*hextor_free) (hextor_plugin *ph,
	    void *ptr);
	int (*hextor_pluginpref_set_str) (hextor_plugin *ph,
		const char *var,
		const char *value);
	int (*hextor_pluginpref_get_str) (hextor_plugin *ph,
		const char *var,
		char *dest);
	int (*hextor_pluginpref_set_int) (hextor_plugin *ph,
		const char *var,
		int value);
	int (*hextor_pluginpref_get_int) (hextor_plugin *ph,
		const char *var);
	int (*hextor_pluginpref_delete) (hextor_plugin *ph,
		const char *var);
	int (*hextor_pluginpref_list) (hextor_plugin *ph,
		char *dest);
	hextor_hook *(*hextor_hook_server_attrs) (hextor_plugin *ph,
		   const char *name,
		   int pri,
		   int (*callback) (char *word[], char *word_eol[],
							hextor_event_attrs *attrs, void *user_data),
		   void *userdata);
	hextor_hook *(*hextor_hook_print_attrs) (hextor_plugin *ph,
		  const char *name,
		  int pri,
		  int (*callback) (char *word[], hextor_event_attrs *attrs,
						   void *user_data),
		  void *userdata);
	int (*hextor_emit_print_attrs) (hextor_plugin *ph, hextor_event_attrs *attrs,
									 const char *event_name, ...);
	hextor_event_attrs *(*hextor_event_attrs_create) (hextor_plugin *ph);
	void (*hextor_event_attrs_free) (hextor_plugin *ph,
									  hextor_event_attrs *attrs);
};
#endif


hextor_hook *
hextor_hook_command (hextor_plugin *ph,
		    const char *name,
		    int pri,
		    int (*callback) (char *word[], char *word_eol[], void *user_data),
		    const char *help_text,
		    void *userdata);

hextor_event_attrs *hextor_event_attrs_create (hextor_plugin *ph);

void hextor_event_attrs_free (hextor_plugin *ph, hextor_event_attrs *attrs);

hextor_hook *
hextor_hook_server (hextor_plugin *ph,
		   const char *name,
		   int pri,
		   int (*callback) (char *word[], char *word_eol[], void *user_data),
		   void *userdata);

hextor_hook *
hextor_hook_server_attrs (hextor_plugin *ph,
		   const char *name,
		   int pri,
		   int (*callback) (char *word[], char *word_eol[],
							hextor_event_attrs *attrs, void *user_data),
		   void *userdata);

hextor_hook *
hextor_hook_print (hextor_plugin *ph,
		  const char *name,
		  int pri,
		  int (*callback) (char *word[], void *user_data),
		  void *userdata);

hextor_hook *
hextor_hook_print_attrs (hextor_plugin *ph,
		  const char *name,
		  int pri,
		  int (*callback) (char *word[], hextor_event_attrs *attrs,
						   void *user_data),
		  void *userdata);

hextor_hook *
hextor_hook_timer (hextor_plugin *ph,
		  int timeout,
		  int (*callback) (void *user_data),
		  void *userdata);

hextor_hook *
hextor_hook_fd (hextor_plugin *ph,
		int fd,
		int flags,
		int (*callback) (int fd, int flags, void *user_data),
		void *userdata);

void *
hextor_unhook (hextor_plugin *ph,
	      hextor_hook *hook);

void
hextor_print (hextor_plugin *ph,
	     const char *text);

void
hextor_printf (hextor_plugin *ph,
	      const char *format, ...)
#ifdef __GNUC__
	__attribute__((format(printf, 2, 3)))
#endif
;

void
hextor_command (hextor_plugin *ph,
	       const char *command);

void
hextor_commandf (hextor_plugin *ph,
		const char *format, ...)
#ifdef __GNUC__
	__attribute__((format(printf, 2, 3)))
#endif
;

int
hextor_nickcmp (hextor_plugin *ph,
	       const char *s1,
	       const char *s2);

int
hextor_set_context (hextor_plugin *ph,
		   hextor_context *ctx);

hextor_context *
hextor_find_context (hextor_plugin *ph,
		    const char *servname,
		    const char *channel);

hextor_context *
hextor_get_context (hextor_plugin *ph);

const char *
hextor_get_info (hextor_plugin *ph,
		const char *id);

int
hextor_get_prefs (hextor_plugin *ph,
		 const char *name,
		 const char **string,
		 int *integer);

hextor_list *
hextor_list_get (hextor_plugin *ph,
		const char *name);

void
hextor_list_free (hextor_plugin *ph,
		 hextor_list *xlist);

const char * const *
hextor_list_fields (hextor_plugin *ph,
		   const char *name);

int
hextor_list_next (hextor_plugin *ph,
		 hextor_list *xlist);

const char *
hextor_list_str (hextor_plugin *ph,
		hextor_list *xlist,
		const char *name);

int
hextor_list_int (hextor_plugin *ph,
		hextor_list *xlist,
		const char *name);

time_t
hextor_list_time (hextor_plugin *ph,
		 hextor_list *xlist,
		 const char *name);

void *
hextor_plugingui_add (hextor_plugin *ph,
		     const char *filename,
		     const char *name,
		     const char *desc,
		     const char *version,
		     char *reserved);

void
hextor_plugingui_remove (hextor_plugin *ph,
			void *handle);

int 
hextor_emit_print (hextor_plugin *ph,
		  const char *event_name, ...);

int 
hextor_emit_print_attrs (hextor_plugin *ph, hextor_event_attrs *attrs,
						  const char *event_name, ...);

char *
hextor_gettext (hextor_plugin *ph,
	       const char *msgid);

void
hextor_send_modes (hextor_plugin *ph,
		  const char **targets,
		  int ntargets,
		  int modes_per_line,
		  char sign,
		  char mode);

char *
hextor_strip (hextor_plugin *ph,
	     const char *str,
	     int len,
	     int flags);

void
hextor_free (hextor_plugin *ph,
	    void *ptr);

int
hextor_pluginpref_set_str (hextor_plugin *ph,
		const char *var,
		const char *value);

int
hextor_pluginpref_get_str (hextor_plugin *ph,
		const char *var,
		char *dest);

int
hextor_pluginpref_set_int (hextor_plugin *ph,
		const char *var,
		int value);
int
hextor_pluginpref_get_int (hextor_plugin *ph,
		const char *var);

int
hextor_pluginpref_delete (hextor_plugin *ph,
		const char *var);

int
hextor_pluginpref_list (hextor_plugin *ph,
		char *dest);

#if !defined(PLUGIN_C) && defined(WIN32)
#ifndef HEXTOR_PLUGIN_HANDLE
#define HEXTOR_PLUGIN_HANDLE (ph)
#endif
#define hextor_hook_command ((HEXTOR_PLUGIN_HANDLE)->hextor_hook_command)
#define hextor_event_attrs_create ((HEXTOR_PLUGIN_HANDLE)->hextor_event_attrs_create)
#define hextor_event_attrs_free ((HEXTOR_PLUGIN_HANDLE)->hextor_event_attrs_free)
#define hextor_hook_server ((HEXTOR_PLUGIN_HANDLE)->hextor_hook_server)
#define hextor_hook_server_attrs ((HEXTOR_PLUGIN_HANDLE)->hextor_hook_server_attrs)
#define hextor_hook_print ((HEXTOR_PLUGIN_HANDLE)->hextor_hook_print)
#define hextor_hook_print_attrs ((HEXTOR_PLUGIN_HANDLE)->hextor_hook_print_attrs)
#define hextor_hook_timer ((HEXTOR_PLUGIN_HANDLE)->hextor_hook_timer)
#define hextor_hook_fd ((HEXTOR_PLUGIN_HANDLE)->hextor_hook_fd)
#define hextor_unhook ((HEXTOR_PLUGIN_HANDLE)->hextor_unhook)
#define hextor_print ((HEXTOR_PLUGIN_HANDLE)->hextor_print)
#define hextor_printf ((HEXTOR_PLUGIN_HANDLE)->hextor_printf)
#define hextor_command ((HEXTOR_PLUGIN_HANDLE)->hextor_command)
#define hextor_commandf ((HEXTOR_PLUGIN_HANDLE)->hextor_commandf)
#define hextor_nickcmp ((HEXTOR_PLUGIN_HANDLE)->hextor_nickcmp)
#define hextor_set_context ((HEXTOR_PLUGIN_HANDLE)->hextor_set_context)
#define hextor_find_context ((HEXTOR_PLUGIN_HANDLE)->hextor_find_context)
#define hextor_get_context ((HEXTOR_PLUGIN_HANDLE)->hextor_get_context)
#define hextor_get_info ((HEXTOR_PLUGIN_HANDLE)->hextor_get_info)
#define hextor_get_prefs ((HEXTOR_PLUGIN_HANDLE)->hextor_get_prefs)
#define hextor_list_get ((HEXTOR_PLUGIN_HANDLE)->hextor_list_get)
#define hextor_list_free ((HEXTOR_PLUGIN_HANDLE)->hextor_list_free)
#define hextor_list_fields ((HEXTOR_PLUGIN_HANDLE)->hextor_list_fields)
#define hextor_list_next ((HEXTOR_PLUGIN_HANDLE)->hextor_list_next)
#define hextor_list_str ((HEXTOR_PLUGIN_HANDLE)->hextor_list_str)
#define hextor_list_int ((HEXTOR_PLUGIN_HANDLE)->hextor_list_int)
#define hextor_plugingui_add ((HEXTOR_PLUGIN_HANDLE)->hextor_plugingui_add)
#define hextor_plugingui_remove ((HEXTOR_PLUGIN_HANDLE)->hextor_plugingui_remove)
#define hextor_emit_print ((HEXTOR_PLUGIN_HANDLE)->hextor_emit_print)
#define hextor_emit_print_attrs ((HEXTOR_PLUGIN_HANDLE)->hextor_emit_print_attrs)
#define hextor_list_time ((HEXTOR_PLUGIN_HANDLE)->hextor_list_time)
#define hextor_gettext ((HEXTOR_PLUGIN_HANDLE)->hextor_gettext)
#define hextor_send_modes ((HEXTOR_PLUGIN_HANDLE)->hextor_send_modes)
#define hextor_strip ((HEXTOR_PLUGIN_HANDLE)->hextor_strip)
#define hextor_free ((HEXTOR_PLUGIN_HANDLE)->hextor_free)
#define hextor_pluginpref_set_str ((HEXTOR_PLUGIN_HANDLE)->hextor_pluginpref_set_str)
#define hextor_pluginpref_get_str ((HEXTOR_PLUGIN_HANDLE)->hextor_pluginpref_get_str)
#define hextor_pluginpref_set_int ((HEXTOR_PLUGIN_HANDLE)->hextor_pluginpref_set_int)
#define hextor_pluginpref_get_int ((HEXTOR_PLUGIN_HANDLE)->hextor_pluginpref_get_int)
#define hextor_pluginpref_delete ((HEXTOR_PLUGIN_HANDLE)->hextor_pluginpref_delete)
#define hextor_pluginpref_list ((HEXTOR_PLUGIN_HANDLE)->hextor_pluginpref_list)
#endif

#ifdef __cplusplus
}
#endif
#endif
