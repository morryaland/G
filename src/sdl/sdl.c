#include "sdl.h"
#include "../player/player.h"
#include "../game.h"

SDL_Window *game_window;
SDL_Renderer *game_renderer;
SDL_Event game_window_event;
uint64_t game_timer;
uint64_t game_freque;

void screen_proection(SDL_Rect *sp, float x, float y, float w, float h)
{
  int ww, wh;
  SDL_GetWindowSize(game_window, &ww, &wh);
  float f = (float)PIX_PER_UNIT / game_camera.f;
  sp->x = x * f - _game_camera->x * f + ww / 2 - f / 2;
  sp->y = y * f - _game_camera->y * f + wh / 2 - f / 2;
  sp->w = w * f;
  sp->h = h * f;
}

void sdl_init()
{
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_DisplayMode dm;
  SDL_GetCurrentDisplayMode(0, &dm);
  SDL_CreateWindowAndRenderer(dm.w ?: DEFAULT_WINDOW_WIDTH, dm.h ?: DEFAULT_WINDOW_HEIGHT, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI, &game_window, &game_renderer);
  int render_w, render_h;
  int window_w, window_h;
  float scale_x, scale_y;
  SDL_GetRendererOutputSize(game_renderer, &render_w, &render_h);
  SDL_GetWindowSize(game_window, &window_w, &window_h);
  scale_x = (float)(render_w) / (float)(window_w);
  scale_y = (float)(render_h) / (float)(window_h);
  SDL_RenderSetScale(game_renderer, scale_x, scale_y);
}

void render_map(MAP *(*m)())
{ 
  MAP *map = m();
  SDL_Rect sp;
  /* Background */
  screen_proection(&sp, -map->w / 2, -map->h / 2, map->w, map->h);
  if (map->background)
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

void render_entity_map(MAP *(*m)())
{
  MAP *map = m();
  render_entities(map->entities, map->entity_c);
}

void render_entities(GLOBAL_ENTITY **e, int entity_c)
{
  SDL_Rect sp;
  for (int i = 0; i < entity_c; i++)
    for (int j = 0; j < e[i]->entity_c; j++) {
      float x = e[i]->entities[j]->x;
      float y = e[i]->entities[j]->y;
      float w = e[i]->entities[j]->w;
      float h = e[i]->entities[j]->h;
      screen_proection(&sp, x, y, w, h);
      SDL_RenderCopy(game_renderer, gif_animation(e[i]->sprites[e[i]->entities[j]->state]), NULL, &sp);
    }
}

void render_player()
{
  SDL_Rect sp;
  screen_proection(&sp, ___player->x, ___player->y, ___player->w, ___player->h);
  SDL_RenderCopy(game_renderer, gif_animation(__player->sprites[___player->state]), NULL, &sp);
}
