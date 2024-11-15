#ifndef __SDL_H__
#define __SDL_H__

#include <SDL2/SDL.h>
#include "../map/map.h"

typedef struct _camera {
  float x;
  float y;
  float f;
} CAMERA;

extern SDL_Window *game_window;
extern SDL_Renderer *game_renderer;
extern SDL_Event game_window_event;
extern CAMERA game_camera;

void campos();

void sdl_init();

void render_map(MAP *(*m)());

void render_entity(MAP *(*m)());

void render_player();

#endif
