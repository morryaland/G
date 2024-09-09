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

ENTITY *entity_init(short local_id, float x, float y, void *flags)
{
  ENTITY *e = malloc(sizeof(ENTITY));
  e->local_id = local_id;
  e->x = x;
  e->y = y;
  memcpy(&e->flags, flags, sizeof(e->flags));
  return e;
}

void global_entity_destroy(GLOBAL_ENTITY **e)
{
  for (int i = 0; i < (**e).state_c; i++) {
    SDL_FreeSurface((**e).sprites[i]);
  }
  for (int i = 0; i < (**e).entity_c; i++) {
    free((**e).entities[i]);
  }
  free((**e).sprites);
  free((**e).entities);
  free(*e);
}
