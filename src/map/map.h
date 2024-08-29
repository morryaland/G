#ifndef __MAP_H__
#define __MAP_H__

#include <stdio.h>
#include <SDL2/SDL_surface.h>
#include "texture.h"
#include "../entity/entity.h"

/* Game map
 *
 * */
typedef struct _map {
  char *name;
  short w, h;
  short texture_c;
  short entity_c;
  TEXTURE *background;
  TEXTURE *texture_map;
  ENTITY *entity;
  struct{
    unsigned char loop:1; /* the entity teleports to the other side of the map */
  } flags;
} MAP;

MAP *map_load();

void map_unload(MAP *m);

#endif
