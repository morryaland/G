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
  SDL_RenderCopy(game_renderer, gif_animation(map->background), NULL, &(SDL_Rect){.x = 0, .y = 0, .w = map->background->a->w, .h = map->background->a->h});
}
