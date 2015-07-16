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

#ifndef HEXTOR_COMMONPLUGIN_H
#define HEXTOR_COMMONPLUGIN_H

#ifdef PLUGIN_C
struct _hextor_plugin
{
    /* Keep these in sync with hextor-plugin.h */
    /* !!don't change the order, to keep binary compat!! */
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
                           const char *format, ...);
    void (*hextor_command) (hextor_plugin *ph,
                            const char *command);
    void (*hextor_commandf) (hextor_plugin *ph,
                             const char *format, ...);
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
    void *(*hextor_read_fd) (hextor_plugin *ph);
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

    /* PRIVATE FIELDS! */
    void *handle;           /* from dlopen */
    char *filename; /* loaded from */
    char *name;
    char *desc;
    char *version;
    session *context;
    void *deinit_callback;  /* pointer to hextor_plugin_deinit */
    unsigned int fake:1;            /* fake plugin. Added by hextor_plugingui_add() */
    unsigned int free_strings:1;            /* free name,desc,version? */
};
#endif

GModule *module_load (char *filename);
char *plugin_load (session *sess, char *filename, char *arg);
int plugin_reload (session *sess, char *name, int by_filename);
void plugin_add (session *sess, char *filename, void *handle, void *init_func, void *deinit_func, char *arg, int fake);
int plugin_kill (char *name, int by_filename);
void plugin_kill_all (void);
void plugin_auto_load (session *sess);
int plugin_emit_command (session *sess, char *name, char *word[], char *word_eol[]);
int plugin_emit_server (session *sess, char *name, char *word[], char *word_eol[],
                        time_t server_time);
int plugin_emit_print (session *sess, char *word[], time_t server_time);
int plugin_emit_dummy_print (session *sess, char *name);
int plugin_emit_keypress (session *sess, unsigned int state, unsigned int keyval, gunichar key);
GList* plugin_command_list(GList *tmp_list);
int plugin_show_help (session *sess, char *cmd);
void plugin_command_foreach (session *sess, void *userdata, void (*cb) (session *sess, void *userdata, char *name, char *usage));

#endif
