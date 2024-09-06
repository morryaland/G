#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "global_entity.h"

typedef struct _player {
  GLOBAL_ENTITY *p;
  char *region_map_name; /* location/map */
} PLAYER;

#endif
