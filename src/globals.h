#ifndef __GLOBALS_H__
#define __GLOBALS_H__

extern int g_iScreenWidth;
extern int g_iScreenHeight;
extern lua_State *g_luaState;
extern item g_items[ITEMS_MAX];
extern skill g_skills[SKILLS_MAX];
extern quest g_quests[QUESTS_MAX];
extern npc g_npc[NPC_MAX];
extern font g_font;
extern map g_map;
extern audio g_audio;
extern input_state g_input_state;
extern input_control g_keybinds[IN_MAX];

#ifdef SCREEN_SDL2
extern SDL_Window *g_sdlWindow;
extern SDL_Renderer *g_sdlRenderer;
extern SDL_Joystick **g_sdlJoysticksAll;  // NULL-terminated.
extern SDL_Joystick *g_sdlJoystick;
#endif

#endif
