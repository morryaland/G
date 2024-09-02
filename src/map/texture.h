#ifndef __TEXTUR__
#define __TEXTUR__

#include <SDL2/SDL_surface.h>

/*
 *
 * */
typedef struct _texture {
  short texture_c;
  struct { short x, y; } *cords;
  SDL_Surface *sprite;
} TEXTURE;

#endif
