#include <stdlib.h>
#include "global_entity.h"
#include "entity.h"

GLOBAL_ENTITY *global_entity_init(char *name, ENTITY **e_list, unsigned short e_c, SDL_Surface **s, unsigned char s_c)
{
  GLOBAL_ENTITY *ge = malloc(sizeof(GLOBAL_ENTITY));
  ge->entities = e_list;
  ge->entity_c = e_c;
  ge->sprites = s;
  ge->state_c = s_c;
  strcpy(ge->name, name);
  return ge;
}

ENTITY *entity_init(short local_id)
{
  ENTITY *e = malloc(sizeof(ENTITY));
  e->local_id = local_id;
  e->x = e->y = 0;
  e->flags.colision = 1;
  return e;
}

void entity_destroy(ENTITY **e)
{
  free(*e);
  *e = NULL;
}

void global_entity_destory(GLOBAL_ENTITY **e)
{
  for (int i = 0; i < (**e).state_c; i++) {
    SDL_free((**e).sprites[i]);
  }
  for (int i = 0; i < (**e).entity_c; i++) {
    SDL_free((**e).entities[i]);
  }
  free((**e).sprites);
  free(*e);
}
