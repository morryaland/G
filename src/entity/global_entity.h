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
GLOBAL_ENTITY *entity_list;

void entity_list_init()
{
  entity_list = (GLOBAL_ENTITY[ENTITY_MAX]){};
  entity_list[ID_ERROR]  = (GLOBAL_ENTITY){ .name = "ERROR",  .id = ID_ERROR,  .state_c = 1,
    .sprites = (SDL_Surface*[]){ IMG_ERROR }};
  entity_list[ID_PLAYER] = (GLOBAL_ENTITY){ .name = "player", .id = ID_PLAYER, .state_c = 4,
    .sprites = (SDL_Surface*[]){ IMG_PLAYER_BACK, IMG_PLAYER_FORWARD, IMG_PLAYER_LEFT, IMG_PLAYER_RIGHT }};
}

#endif
