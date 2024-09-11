#ifndef __SDL_H__
#define __SDL_H__

#include <SDL2/SDL.h>
#include "../map/map.h"

extern SDL_Window *game_window;
extern SDL_Renderer *game_renderer;
extern SDL_Event game_window_event;

void sdl_init();

void render_map();

#endif
