#include "../map/map.h"
#include "sdl.h"

SDL_Window *game_window;
SDL_Renderer *game_renderer;

void sdl_init()
{
  SDL_DisplayMode dm;
  SDL_GetCurrentDisplayMode(0, &dm);
  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(dm.w, dm.h, SDL_WINDOW_FULLSCREEN, &game_window, &game_renderer);
}

void render_map(MAP *m)
{ 
 
}
