#ifndef __TEXTUR__
#define __TEXTUR__

#include <SDL2/SDL_surface.h>

/*
 *
 * */
typedef struct _texture {
  short x, y;
  SDL_Surface *textur;
} TEXTUR;

#endif
