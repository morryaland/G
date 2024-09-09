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
  unsigned short entity_c;
  unsigned char state_c;
  ENTITY **entities;
  SDL_Surface **sprites;
} GLOBAL_ENTITY;

GLOBAL_ENTITY *global_entity_init(char *name, ENTITY **e_list, unsigned short e_c, SDL_Surface **s, unsigned char s_c);

void global_entity_destroy(GLOBAL_ENTITY **e);

#endif
