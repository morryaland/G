#include "../map/map.h"
#include "../player/player.h"
#include "sdl.h"

SDL_Window *game_window;
SDL_Renderer *game_renderer;
SDL_Event game_window_event;
CAMERA game_camera;

void campos()
{
  game_camera.x = player->x;
  game_camera.y = player->y;
}

SDL_Rect *screen_proection(SDL_Rect *r)
{
  int w, h;
  SDL_GetWindowSize(game_window, &w, &h);
  float f = (float)PIX_PER_UNIT / game_camera.f;
  r->x = r->x * f - game_camera.x * f + w / 2 - f / 2;
  r->y = r->y * f - game_camera.y * f + h / 2 - f / 2;
  r->w *= f;
  r->h *= f;
  return r;
}

void sdl_init()
{
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_DisplayMode dm;
  SDL_GetCurrentDisplayMode(0, &dm);
  SDL_CreateWindowAndRenderer(dm.w ?: DEFAULT_WINDOW_WIDTH, dm.h ?: DEFAULT_WINDOW_HEIGHT, SDL_WINDOW_FULLSCREEN, &game_window, &game_renderer);
  game_camera.f = 2;
}

void render_map(MAP *(*m)())
{ 
  MAP *map = m();
  /* Background */
  SDL_RenderCopy(game_renderer, gif_animation(map->background), NULL, screen_proection(&(SDL_Rect){.x = -map->w / 2, .y = -map->h / 2, .w = map->w, .h = map->h}));
  for (int i = 0; i < map->texture_c; i++)
    for (int j = 0; j < map->texture_map[i]->texture_c; j++) {
      short x = map->texture_map[i]->cords[j].x;
      short y = map->texture_map[i]->cords[j].y;
      SDL_RenderCopy(game_renderer, gif_animation(map->texture_map[i]->sprite), NULL, screen_proection(&(SDL_Rect){.x = x, .y = y, .w = 1, .h = 1}));
    }
}

void render_player()
{
  SDL_RenderCopy(game_renderer, gif_animation(player->sprites[player->state]), NULL, screen_proection(&(SDL_Rect){.x = player->x, .y = player->y, .w = 1, .h = 1}));
}
