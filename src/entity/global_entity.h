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
  short id;
  unsigned char state_c;
  SDL_Surface **sprites;
} GLOBAL_ENTITY;

typedef struct _entity_list {
  GLOBAL_ENTITY ERROR;
  GLOBAL_ENTITY player;
} ENTITY_LIST;

extern ENTITY_LIST entity_list;
ENTITY_LIST entity_list;

void entity_list_init()
{
  entity_list = (ENTITY_LIST){
    .ERROR  = { .name = "ERROR",  .id = -1, .state_c = 1, .sprites = (SDL_Surface*[]){ IMG_ERROR }},
    .player = { .name = "player", .id = 1, .state_c = 4, .sprites = (SDL_Surface*[]){ IMG_PLAYER_BACK, IMG_PLAYER_FORWARD, IMG_PLAYER_LEFT, IMG_PLAYER_RIGHT }},
  };
}

#endif
