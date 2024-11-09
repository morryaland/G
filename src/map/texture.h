#ifndef __TEXTUR__
#define __TEXTUR__

#include "../sdl/gif.h"

/* Texture
 *
 * */
typedef struct _texture {
  unsigned short texture_c;
  struct { short x, y; } *cords;
  GIF_ANIMATION *sprite;
} TEXTURE;

TEXTURE *texture_load(GIF_ANIMATION *s, unsigned short t_c, void *cords);

void texture_unload(TEXTURE **t);

#endif
