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

void screen_proection(SDL_Rect *sp, float x, float y, float w, float h)
{
  int ww, wh;
  SDL_GetWindowSize(game_window, &ww, &wh);
  float f = (float)PIX_PER_UNIT / game_camera.f;
  sp->x = x * f - game_camera.x * f + ww / 2 - f / 2;
  sp->y = y * f - game_camera.y * f + wh / 2 - f / 2;
  sp->w = w * f;
  sp->h = h * f;
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
  SDL_Rect sp;
  /* Background */
  screen_proection(&sp, -map->w / 2, -map->h / 2, map->w, map->h);
  SDL_RenderCopy(game_renderer, gif_animation(map->background), NULL, &sp);
  for (int i = 0; i < map->texture_c; i++)
    for (int j = 0; j < map->texture_map[i]->texture_c; j++) {
      int x = map->texture_map[i]->cords[j].x;
      int y = map->texture_map[i]->cords[j].y;
      int w = map->texture_map[i]->cords[j].w;
      int h = map->texture_map[i]->cords[j].h;
      screen_proection(&sp, x, y, w, h);
      SDL_RenderCopy(game_renderer, gif_animation(map->texture_map[i]->sprite), NULL, &sp);
    }
}

void render_entity(MAP *(*m)())
{
  MAP *map = m();
  SDL_Rect sp;
}

void render_player()
{
  SDL_Rect sp;
  screen_proection(&sp, player->x, player->y, player->w, player->h);
  SDL_RenderCopy(game_renderer, gif_animation(player->sprites[player->state]), NULL, &sp);
}
