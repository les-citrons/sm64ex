#include <lua5.1/lua.h>
#include <lua5.1/lauxlib.h>
#include <lua5.1/lualib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

#include "lua/mario.h"
#include "lua.h"

// Node in linked list of lua VM handles
// Each script gets its own VM
struct lua_script_node {
	lua_State *lvm;
	struct lua_script_node *next;
	struct lua_script_node *prev;
	char *name;
};

struct lua_script_node *lua_scripts = NULL;

void push_script(lua_State *lvm, const char *name) {
	struct lua_script_node *new;
	if (lua_scripts == NULL) {
		lua_scripts = malloc(sizeof(struct lua_script_node));
		new = lua_scripts;
	} else {
		struct lua_script_node *s;
		for (s = lua_scripts; s->next != NULL; s = s->next);
		new = malloc(sizeof(struct lua_script_node));
		s->next = new;
		new->prev = s;
	}
	new->lvm = lvm;
	new->next = NULL;
	new->name = malloc(strlen(name) + 1);
	strcpy(new->name, name);
}

void rem_script(struct lua_script_node *s) {
	if (s->prev != NULL) s->prev->next = s->next;
	else lua_scripts = s->next;
	if (s->next != NULL) s->next->prev = s->prev;

	lua_close(s->lvm);
	free(s->name);
	free(s);
}

void init_lua() {
	DIR *script_dir = opendir(SCRIPTDIR);
	if (script_dir == NULL) {
		if (errno != ENOTDIR && errno != ENOENT)
			perror("Error loading scripts");
		return;
	}
	
	for (struct dirent *d = readdir(script_dir); d != NULL; d = readdir(script_dir)) {
		if (strcmp(".", d->d_name) == 0 || strcmp("..", d->d_name) == 0)
			continue;

		lua_State *lvm = lua_open();
		luaL_openlibs(lvm);
		lua_register_mario(lvm);

		char script_path[strlen(d->d_name) + strlen(SCRIPTDIR) + 2];
		strcpy(script_path, SCRIPTDIR);
		strcat(script_path, "/");
		strcat(script_path, d->d_name);
		printf("Loading script %s\n", script_path);
		if (luaL_loadfile(lvm, script_path) || lua_pcall(lvm, 0, 0, 0)) {
			fprintf(stderr, "Error loading %s: %s\n", script_path, lua_tostring(lvm, -1));
			lua_close(lvm);
			continue;
		}

		push_script(lvm, d->d_name);
	}
}

void cleanup_lua() {
	if (lua_scripts != NULL)
		for (struct lua_script_node *s = lua_scripts; s != NULL; s = s->next)
			lua_close(s->lvm);
}

void lua_do_event(const char *handler_name) {
	if (lua_scripts == NULL) return;
	for (struct lua_script_node *s = lua_scripts; s != NULL; s = s->next) {
		luaL_checkstack(s->lvm, 2, s->name);
		lua_getglobal(s->lvm, handler_name);
		if (!lua_isnil(s->lvm, -1)) {
			if (lua_pcall(s->lvm, 0, 0, 0)) {
				fprintf(stderr, "%s\n", lua_tostring(s->lvm, -1));
				rem_script(s);
			}
		} else lua_pop(s->lvm, 1);
	}
}

