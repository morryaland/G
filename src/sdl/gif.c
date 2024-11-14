#include "gif.h"
#include "sdl.h"

GIF_ANIMATION *gif_load(const char *path)
{
  GIF_ANIMATION *gif = malloc(sizeof(GIF_ANIMATION));
  gif->t = NULL;
  gif->a = IMG_LoadAnimation(path);
  gif->count = 0;
  gif->time_start_frame = 0;
  return gif;
}

SDL_Texture *gif_animation(GIF_ANIMATION *a)
{
  unsigned long tn, fr;
  tn = SDL_GetPerformanceCounter();
  fr = SDL_GetPerformanceFrequency();
  if (!a->time_start_frame) {
    a->time_start_frame = tn;
    a->t = SDL_CreateTextureFromSurface(game_renderer, a->a->frames[0]);
  }
  if (a->a->count == 1)
    return a->t;
  unsigned long delta_us = (double)(tn - a->time_start_frame) / fr * 1000;
  if (delta_us > a->a->delays[a->count]) {
    a->time_start_frame = tn;
    a->count++;
    if (a->count > a->a->count - 1)
      a->count = 0;
    SDL_DestroyTexture(a->t);
    a->t = SDL_CreateTextureFromSurface(game_renderer, a->a->frames[a->count]);
  }
  return a->t;
}

void gif_unload(GIF_ANIMATION **a)
{
  IMG_FreeAnimation((**a).a);
  SDL_DestroyTexture((**a).t);
  free(*a);
  *a = NULL;
}
