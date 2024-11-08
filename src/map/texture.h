#ifndef __TEXTUR__
#define __TEXTUR__

#include <SDL2/SDL_image.h>

/* Texture
 *
 * */
typedef struct _texture {
  unsigned short texture_c;
  struct { short x, y; } *cords;
  IMG_Animation *sprite;
} TEXTURE;

TEXTURE *texture_load(IMG_Animation *s, unsigned short t_c, void *cords);

void texture_unload(TEXTURE **t);

#endif
