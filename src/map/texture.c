
#include "texture.h"

TEXTURE *texture_load(IMG_Animation *s, unsigned short t_c, void *cords)
{
  TEXTURE *t = malloc(sizeof(TEXTURE));
  t->sprite = s;
  t->texture_c = t_c;
  t->cords = cords;
  return t;
}

void texture_unload(TEXTURE **t)
{
  if (!*t)
    return;
  IMG_FreeAnimation((**t).sprite);
  free((**t).cords);
  free(*t);
  *t = NULL;
}
