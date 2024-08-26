#ifndef __MAP_H__
#define __MAP_H__

#include <stdio.h>
#include "textur.h"
#include "../entity/entity.h"

/* Game map
 *
 * */
typedef struct _map {
  char *name;
  short w, h;
  short texture_c;
  TEXTUR *texture_map;
  short entity_c;
  ENTITY *entity;
  struct{
    unsigned char loop:1; /* the entity teleports to the other side of the map */
  } flags;
} MAP;

MAP *map_load(FILE *fd);

void map_unload(MAP *m);

#endif
