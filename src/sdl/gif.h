#ifndef __GIF_H__
#define __GIF_H__

#include <SDL2/SDL_image.h>

typedef struct {
  IMG_Animation *a;
  SDL_Texture *t;
  unsigned long count;
  unsigned long time_start_frame;
} GIF_ANIMATION;

GIF_ANIMATION *gif_load(const char *path);

SDL_Texture *gif_animation(GIF_ANIMATION *);

void gif_unload(GIF_ANIMATION **);

#endif
