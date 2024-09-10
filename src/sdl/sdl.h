#ifndef __SDL_H__
#define __SDL_H__

#include <SDL2/SDL.h>
#include "../map/map.h"

extern SDL_Window *game_window;
extern SDL_Renderer *game_renderer;

void sdl_init();

void render_map();

#endif
