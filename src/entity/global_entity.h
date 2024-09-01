#ifndef __GLOBAL_ENTITY_H__
#define __GLOBAL_ENTITY_H__

#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_image.h>
#include "../define.h"

/* Entity
 *
 * */
typedef struct _global_entity {
  char *name;
  unsigned short id;
  unsigned char state_c;
  SDL_Surface **sprites;
} GLOBAL_ENTITY;

extern GLOBAL_ENTITY *entity_list;

void entity_list_init();

#endif
