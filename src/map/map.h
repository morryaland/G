#ifndef __MAP_H__
#define __MAP_H__

#include <stdio.h>
#include <SDL2/SDL_surface.h>
#include "texture.h"
#include "../entity/global_entity.h"

/* Game map
 *
 * */
typedef struct _map {
  char location_map_name[PATH_MAX]; /* location/map */
  short w, h;
  short texture_c;
  short entity_c;
  TEXTURE **texture_map;
  GLOBAL_ENTITY **entity;
  SDL_Surface *background;
  struct{
    unsigned char loop:1; /* the entity teleports to the other side of the map */
  } flags;
} MAP;

MAP *map_load(const char *name);

void map_unload(MAP **m);

#endif
