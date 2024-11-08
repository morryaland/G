#include "../map/map.h"
#include "sdl.h"

SDL_Window *game_window;
SDL_Renderer *game_renderer;
SDL_Event game_window_event;
CAMERA game_camera;

void screen_proection()
{

}

SDL_Rect cam_rect(SDL_Rect *r)
{

}

void sdl_init()
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_DisplayMode dm;
  SDL_GetCurrentDisplayMode(0, &dm);
  SDL_CreateWindowAndRenderer(dm.w ?: DEFAULT_WINDOW_WIDTH, dm.h ?: DEFAULT_WINDOW_HEIGHT, SDL_WINDOW_FULLSCREEN, &game_window, &game_renderer);
}
 
void render_map(MAP *(*m)())
{ 
  MAP *map = m();
  static int count = 0;
  static unsigned long ts, tn, fr; //TODO
  tn = SDL_GetPerformanceCounter();
  fr = SDL_GetPerformanceFrequency();
  if (!ts)
    ts = tn;
  unsigned long delta_us = (double)(tn - ts) / fr * 1000;
  if (delta_us > map->background->delays[count]) {
    ts = tn;
    count++;
    if (count > map->background->count)
      count = 0;
  } // TODO
  SDL_Texture *t = SDL_CreateTextureFromSurface(game_renderer, map->background->frames[count]);
  SDL_RenderCopy(game_renderer, t, NULL, &(SDL_Rect){.x = 0, .y = 0, .w = map->background->w / 2, .h = map->background->h / 2});
  SDL_DestroyTexture(t);
}
