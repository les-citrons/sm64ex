
#include <lua5.1/lua.h>
#include <lua5.1/lauxlib.h>
#include <lua5.1/lualib.h>

#include "lua/controller.h"
#include "game/game_init.h"
#include "include/PR/os_cont.h"

static void buttons_to_table(lua_State *lvm, u16 buttons) {
	lua_createtable(lvm, 0, 14);

	lua_pushboolean(lvm, buttons & A_BUTTON ? 1 : 0);
	lua_setfield(lvm, -2, "a_button");
	lua_pushboolean(lvm, buttons & B_BUTTON ? 1 : 0);
	lua_setfield(lvm, -2, "b_button");
	lua_pushboolean(lvm, buttons & L_TRIG ? 1 : 0);
	lua_setfield(lvm, -2, "l_trig");
	lua_pushboolean(lvm, buttons & R_TRIG ? 1 : 0);
	lua_setfield(lvm, -2, "r_trig");
	lua_pushboolean(lvm, buttons & Z_TRIG ? 1 : 0);
	lua_setfield(lvm, -2, "z_trig");
	lua_pushboolean(lvm, buttons & START_BUTTON ? 1 : 0);
	lua_setfield(lvm, -2, "start_button");
	lua_pushboolean(lvm, buttons & U_JPAD ? 1 : 0);
	lua_setfield(lvm, -2, "u_jpad");
	lua_pushboolean(lvm, buttons & L_JPAD ? 1 : 0);
	lua_setfield(lvm, -2, "l_jpad");
	lua_pushboolean(lvm, buttons & R_JPAD ? 1 : 0);
	lua_setfield(lvm, -2, "r_jpad");
	lua_pushboolean(lvm, buttons & D_JPAD ? 1 : 0);
	lua_setfield(lvm, -2, "d_jpad");
	lua_pushboolean(lvm, buttons & U_CBUTTONS ? 1 : 0);
	lua_setfield(lvm, -2, "u_cbutton");
	lua_pushboolean(lvm, buttons & L_CBUTTONS ? 1 : 0);
	lua_setfield(lvm, -2, "l_cbutton");
	lua_pushboolean(lvm, buttons & R_CBUTTONS ? 1 : 0);
	lua_setfield(lvm, -2, "r_cbutton");
	lua_pushboolean(lvm, buttons & D_CBUTTONS ? 1 : 0);
	lua_setfield(lvm, -2, "d_cbutton");
}

static int l_get(lua_State *lvm) {
	lua_createtable(lvm, 0, 5);

	buttons_to_table(lvm, gPlayer1Controller->buttonPressed);
	lua_setfield(lvm, -2, "pressed");

	buttons_to_table(lvm, gPlayer1Controller->buttonDown);
	lua_setfield(lvm, -2, "down");

	lua_pushnumber(lvm, gPlayer1Controller->stickX);
	lua_setfield(lvm, -2, "stick_x");

	lua_pushnumber(lvm, gPlayer1Controller->stickY);
	lua_setfield(lvm, -2, "stick_y");

	lua_pushnumber(lvm, gPlayer1Controller->stickMag);
	lua_setfield(lvm, -2, "stick_mag");

	return 1;
}

struct luaL_Reg lua_controller_api[] = {
	{"get", l_get},
	{NULL, NULL}
};

void lua_register_controller(lua_State *lvm) {
	luaL_openlib(lvm, "controller", lua_controller_api, 0);
}
