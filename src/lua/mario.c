
#include <lua5.1/lua.h>
#include <lua5.1/lauxlib.h>
#include <lua5.1/lualib.h>
#include "lua/mario.h"

#include "types.h"
#include "game/level_update.h"
#include "sm64.h"

static int l_get(lua_State *lvm) {
	lua_createtable(lvm, 0, 1);
	
	lua_pushnumber(lvm, gMarioState->forwardVel);
	lua_setfield(lvm, -2, "forward_vel");

	return 1;
}

static int l_set(lua_State *lvm) {
	lua_pushstring(lvm, "forward_vel");
	lua_gettable(lvm,  -2);
	gMarioState->forwardVel = lua_tonumber(lvm, -1);
	
	return 0;
}

struct luaL_Reg mario_api[] = {
	{"get", l_get},
	{"set", l_set},
	{NULL, NULL}
};

void lua_register_mario(lua_State *lvm) {
	luaL_openlib(lvm, "mario", mario_api, 0);
}
