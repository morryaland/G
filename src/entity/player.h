#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "entity.h"

typedef struct _player {
  ENTITY e;
  char *region_map_name; /* location/map */
} PLAYER;

#endif
