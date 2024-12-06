#include <stdlib.h>
#include "global_entity.h"
#include "../sdl/sdl.h"
#include "../game.h"

GLOBAL_ENTITY *global_entity_init(char *name, ENTITY **e_list, unsigned short e_c, GIF_ANIMATION **s, unsigned char s_c)
{
  GLOBAL_ENTITY *ge = malloc(sizeof(GLOBAL_ENTITY));
  ge->entities = e_list;
  ge->entity_c = e_c;
  ge->sprites = s;
  ge->state_c = s_c;
  strcpy(ge->name, name);
  return ge;
}

ENTITY *entity_init(short local_id, float x, float y, float w, float h, int flags)
{
  ENTITY *e = malloc(sizeof(ENTITY));
  e->local_id = local_id;
  e->x = x;
  e->y = y;
  e->w = w;
  e->h = h;
  e->speed = 5;
  e->state = 0;
  e->mstackid = -1;
  e->flags = flags;
  return e;
}

void entity_set_state(ENTITY *e, unsigned char state)
{
  e->state = state;
}

void entity_move(ENTITY *e, float x, float y)
{
  move(&e->mstackid, e->speed, &e->x, &e->y, x, y);
}

void entity_destroy(ENTITY **e)
{
  free(*e);
  *e = NULL;
}

void global_entity_destroy(GLOBAL_ENTITY **e)
{
  for (int i = 0; i < (**e).state_c; i++) {
    gif_unload(&(**e).sprites[i]);
  }
  for (int i = 0; i < (**e).entity_c; i++) {
    entity_destroy(&(**e).entities[i]);
  }
  free((**e).sprites);
  free((**e).entities);
  free(*e);
}
