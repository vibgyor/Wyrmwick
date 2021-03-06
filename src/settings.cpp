#include "include.h"

settings* settings_init() {
	settings *s = (settings*) malloc(sizeof(settings));
	if (! s) {
		debug_print("Ran out of memory while trying to load settings.\n");
		sys_abort();
	}
		
	s->m_luaState = luaL_newstate();
	if (! s->m_luaState) {
		debug_print("Ran out of memory while trying to load settings.\n");
		sys_abort();
	}
	s->m_aWriters = table_new(sizeof(settings_writer), 0, 0);
	return s;
}

void settings_add_func(settings *s, const char *name, lua_CFunction func, void *userdata) {
	lua_pushlightuserdata(s->m_luaState, userdata);
	lua_pushcclosure(s->m_luaState, func, 1);
	lua_setglobal(s->m_luaState, name);
}

void settings_add_writer(settings *s, settings_writer_func swriter, void *userdata) {
	settings_writer sw = {swriter, userdata};
	table_append(s->m_aWriters, &sw);
}

int settings_load(settings *s, const char* path) {
	if (luaL_dofile(s->m_luaState, path)) {
		debug_print("Failed to load controls: %s\n", lua_tostring(s->m_luaState, -1));
		return 1;
	}
	return 0;
}

int settings_save(settings *s, const char* path) {
	FILE *file = fopen(path, "w");
	if (! file) {
		debug_print("Failed to save controls: %s\n", strerror(errno));
		return 1;
	}
	
	settings_writer *writers = (settings_writer*) s->m_aWriters->m_data;
	for (int i = 0; i < s->m_aWriters->m_len; i++) {
		int err = writers[i].m_func(file, writers[i].m_userdata);
		if (err) {
			return 1;
		}
	}
	
	fclose(file);
	return 0;
}

void settings_destroy(settings *s) {
	lua_close(s->m_luaState);
	table_free(s->m_aWriters);
	free(s);
}
