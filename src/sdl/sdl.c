#include "../map/map.h"
#include "sdl.h"

SDL_Window *game_window;
SDL_Renderer *game_renderer;
SDL_Event game_window_event;

void sdl_init()
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_DisplayMode dm;
  SDL_GetCurrentDisplayMode(0, &dm);
  SDL_CreateWindowAndRenderer(dm.w ?: DEFAULT_WINDOW_WIDTH, dm.h ?: DEFAULT_WINDOW_HEIGHT, SDL_WINDOW_FULLSCREEN, &game_window, &game_renderer);
}

void render_map(MAP *m)
{ 
 
}
