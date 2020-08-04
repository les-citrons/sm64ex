
#include <lua5.1/lua.h>
#include <lua5.1/lauxlib.h>
#include <lua5.1/lualib.h>
#include "lua/mario.h"
#include "lua/tools.h"

#include "types.h"
#include "game/level_update.h"
#include "sm64.h"

static int l_get(lua_State *lvm) {
	lua_createtable(lvm, 0, 8);
	
	lua_pushnumber(lvm, gMarioState->health);
	lua_setfield(lvm, -2, "health");

	lua_pushnumber(lvm, gMarioState->numLives);
	lua_setfield(lvm, -2, "num_lives");

	lua_pushnumber(lvm, gMarioState->numCoins);
	lua_setfield(lvm, -2, "num_coins");

	lua_pushnumber(lvm, gMarioState->invincTimer);
	lua_setfield(lvm, -2, "invinc_timer");

	lua_pushnumber(lvm, gMarioState->forwardVel);
	lua_setfield(lvm, -2, "forward_vel");

	vec3f_to_table(lvm, gMarioState->pos);
	lua_setfield(lvm, -2, "pos");

	vec3f_to_table(lvm, gMarioState->vel);
	lua_setfield(lvm, -2, "vel");

	vec3s_to_table(lvm, gMarioState->faceAngle);
	lua_setfield(lvm, -2, "face_angle");

	return 1;
}

static int l_set(lua_State *lvm) {
	lua_pushstring(lvm, "health");
	lua_gettable(lvm,  -2);
	gMarioState->health = lua_tonumber(lvm, -1);
	lua_pop(lvm, 1);

	lua_pushstring(lvm, "num_lives");
	lua_gettable(lvm,  -2);
	gMarioState->numLives = lua_tonumber(lvm, -1);
	lua_pop(lvm, 1);

	lua_pushstring(lvm, "num_coins");
	lua_gettable(lvm,  -2);
	gMarioState->numCoins = lua_tonumber(lvm, -1);
	lua_pop(lvm, 1);

	lua_pushstring(lvm, "invinc_timer");
	lua_gettable(lvm,  -2);
	gMarioState->invincTimer = lua_tonumber(lvm, -1);
	lua_pop(lvm, 1);

	lua_pushstring(lvm, "forward_vel");
	lua_gettable(lvm,  -2);
	gMarioState->forwardVel = lua_tonumber(lvm, -1);
	lua_pop(lvm, 1);

	lua_pushstring(lvm, "pos");
	lua_gettable(lvm,  -2);
	table_to_vec3f(lvm, gMarioState->pos);
	lua_pop(lvm, 1);

	lua_pushstring(lvm, "vel");
	lua_gettable(lvm,  -2);
	table_to_vec3f(lvm, gMarioState->vel);
	lua_pop(lvm, 1);

	lua_pushstring(lvm, "face_angle");
	lua_gettable(lvm,  -2);
	table_to_vec3s(lvm, gMarioState->faceAngle);
	lua_pop(lvm, 1);
	
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
