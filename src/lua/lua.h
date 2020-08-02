#ifndef __LUA_H
#define __LUA_H

#include <lua5.1/lua.h>
#include <lua5.1/lauxlib.h>
#include <lua5.1/lualib.h>

#define SCRIPTDIR "scripts"

void init_lua();
void cleanup_lua();
void lua_do_event(const char *handler_name);

#endif
