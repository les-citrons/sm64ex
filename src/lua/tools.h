
#ifndef __LUA_TOOLS_H
#define __LUA_TOOLS_H

#include <lua5.1/lua.h>
#include <lua5.1/lauxlib.h>
#include <lua5.1/lualib.h>

#include "types.h"

void vec3f_to_table(lua_State *lvm, Vec3f v);
void table_to_vec3f(lua_State *lvm, Vec3f v);
void vec3s_to_table(lua_State *lvm, Vec3s v);
void table_to_vec3s(lua_State *lvm, Vec3s v);

#endif
