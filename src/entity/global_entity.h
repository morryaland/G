#ifndef __GLOBAL_ENTITY_H__
#define __GLOBAL_ENTITY_H__

#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_image.h>
#include "entity.h"
#include "../define.h"

/* Entity
 *
 * */
typedef struct _global_entity {
  char name[256];
  ENTITY *entities;
  unsigned short entity_c;
  unsigned char state_c;
  SDL_Surface **sprites;
} GLOBAL_ENTITY;

void global_entity_destroy(GLOBAL_ENTITY *e);

#endif
