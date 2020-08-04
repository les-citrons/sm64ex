
#include <lua5.1/lua.h>
#include <lua5.1/lauxlib.h>
#include <lua5.1/lualib.h>

#include "types.h"

void vec3f_to_table(lua_State *lvm, Vec3f v) {
	lua_createtable(lvm, 0, 3);
	
	lua_pushnumber(lvm, v[0]); 
	lua_setfield(lvm, -2, "x");

	lua_pushnumber(lvm, v[1]); 
	lua_setfield(lvm, -2, "y");

	lua_pushnumber(lvm, v[2]); 
	lua_setfield(lvm, -2, "z");
}

void table_to_vec3f(lua_State *lvm, Vec3f v) {
	lua_pushstring(lvm, "x");
	lua_gettable(lvm, -2);
	v[0] = lua_tonumber(lvm, -1);
	lua_pop(lvm, 1);

	lua_pushstring(lvm, "y");
	lua_gettable(lvm, -2);
	v[1] = lua_tonumber(lvm, -1);
	lua_pop(lvm, 1);
	
	lua_pushstring(lvm, "z");
	lua_gettable(lvm, -2);
	v[2] = lua_tonumber(lvm, -1);
	lua_pop(lvm, 1);
}

void vec3s_to_table(lua_State *lvm, Vec3s v) {
	lua_createtable(lvm, 0, 3);
	
	lua_pushnumber(lvm, v[0]); 
	lua_setfield(lvm, -2, "x");

	lua_pushnumber(lvm, v[1]); 
	lua_setfield(lvm, -2, "y");

	lua_pushnumber(lvm, v[2]); 
	lua_setfield(lvm, -2, "z");
}

void table_to_vec3s(lua_State *lvm, Vec3s v) {
	lua_pushstring(lvm, "x");
	lua_gettable(lvm, -2);
	v[0] = lua_tonumber(lvm, -1);
	lua_pop(lvm, 1);

	lua_pushstring(lvm, "y");
	lua_gettable(lvm, -2);
	v[1] = lua_tonumber(lvm, -1);
	lua_pop(lvm, 1);
	
	lua_pushstring(lvm, "z");
	lua_gettable(lvm, -2);
	v[2] = lua_tonumber(lvm, -1);
	lua_pop(lvm, 1);
}
