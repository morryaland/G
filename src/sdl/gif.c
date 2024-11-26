#include "gif.h"
#include "sdl.h"

GIF_ANIMATION *gif_load(const char *path)
{
  GIF_ANIMATION *gif = malloc(sizeof(GIF_ANIMATION));
  IMG_Animation *a = IMG_LoadAnimation(path);
  gif->len = a->count;
  gif->w = a->w;
  gif->h = a->h;
  gif->t = malloc(sizeof(SDL_Texture*) * gif->len);
  gif->d = malloc(sizeof(int) * gif->len);
  for (int i = 0; i < gif->len; i++) {
    gif->t[i] = SDL_CreateTextureFromSurface(game_renderer, a->frames[i]);
    gif->d[i] = a->delays[i];
  }
  IMG_FreeAnimation(a);
  gif->count = 0;
  gif->time_start_frame = 0;
  return gif;
}

SDL_Texture *gif_animation(GIF_ANIMATION *a)
{
  if (!a->time_start_frame) {
    a->time_start_frame = game_timer;
  }
  if (a->len == 1)
    return a->t[0];
  unsigned long delta_us = (double)(game_timer - a->time_start_frame) / game_freque * 1000;
  if (delta_us > a->d[a->count]) {
    a->time_start_frame = game_timer;
    a->count++;
    if (a->count > a->len - 1)
      a->count = 0;
  }
  return a->t[a->count];
}

void gif_unload(GIF_ANIMATION **a)
{
  for (int i = 0; i < (**a).len; i++) {
    SDL_DestroyTexture((**a).t[i]);
  }
  free((**a).t);
  free((**a).d);
  free(*a);
  *a = NULL;
}
