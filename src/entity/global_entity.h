#ifndef __GLOBAL_ENTITY_H__
#define __GLOBAL_ENTITY_H__

#include "entity.h"
#include "../sdl/gif.h"
#include "../define.h"

/* Entity
 *
 * */
typedef struct _global_entity {
  char name[256];
  unsigned short entity_c;
  unsigned char state_c;
  ENTITY **entities;
  GIF_ANIMATION **sprites;
} GLOBAL_ENTITY;

GLOBAL_ENTITY *global_entity_init(char *name, ENTITY **e_list, unsigned short e_c, GIF_ANIMATION **s, unsigned char s_c);

void global_entity_destroy(GLOBAL_ENTITY **e);

#endif
