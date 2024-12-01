#ifndef __SDL_H__
#define __SDL_H__

#include <SDL.h>
#include "../map/map.h"

extern SDL_Window *game_window;
extern SDL_Renderer *game_renderer;
extern SDL_Event game_window_event;
extern uint64_t game_timer;
extern uint64_t game_freque;

void sdl_init();

void render_map(MAP *(*m)());

void render_entity_map(MAP *(*m)());

void render_entities(GLOBAL_ENTITY **e, int entity_c);

void render_player();

#endif
