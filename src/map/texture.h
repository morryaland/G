#ifndef __TEXTUR__
#define __TEXTUR__

#include <SDL2/SDL_surface.h>

/* Texture
 *
 * */
typedef struct _texture {
  unsigned short texture_c;
  struct { short x, y; } *cords;
  SDL_Surface *sprite;
} TEXTURE;

TEXTURE *texture_load(SDL_Surface *s, unsigned short t_c, void *cords);

void texture_unload(TEXTURE **t);

#endif
