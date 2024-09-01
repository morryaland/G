#include <stdlib.h>
#include "entity.h"

GLOBAL_ENTITY *entity_list;

void entity_list_init()
{
  entity_list = (GLOBAL_ENTITY[ENTITY_MAX]){};
  entity_list[ID_ERROR]  = (GLOBAL_ENTITY){ .name = "ERROR",  .id = ID_ERROR,  .state_c = 1,
    .sprites = (SDL_Surface*[]){ IMG_ERROR }};
  entity_list[ID_PLAYER] = (GLOBAL_ENTITY){ .name = "player", .id = ID_PLAYER, .state_c = 4,
    .sprites = (SDL_Surface*[]){ IMG_PLAYER_BACK, IMG_PLAYER_FORWARD, IMG_PLAYER_LEFT, IMG_PLAYER_RIGHT }};
}

ENTITY *entity_init(short local_id, short id )
{
  ENTITY *e = malloc(sizeof(ENTITY));
  e->local_id = local_id;
  e->id = id;
  e->x = e->y = 0;
  e->flags.colision = 1;
  return e;
}

char *entity_get_name(ENTITY *e)
{
  return entity_list[e->id].name;
}

SDL_Surface *entity_update_sprite(ENTITY *e)
{
  return entity_list[e->id].sprites[e->state];
}
