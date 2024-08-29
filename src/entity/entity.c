#include <stdlib.h>
#include "entity.h"

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
