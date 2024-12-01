#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "../sdl/gif.h"
#include "../entity/global_entity.h"
#include "../define.h"

#define __player player->entity
#define ___player __player->entities[0]

typedef struct _player {
  GLOBAL_ENTITY *entity;
  char location_map_name[PATH_MAX]; /* location/map */
  int flags;
} PLAYER;

extern PLAYER *player;

void player_init(char *default_map, float x, float y, float w, float h, int flags);

void player_set_map(char *map_name);

#define player_set_state entity_set_state(___player, unsigned char state);

#define player_move(x, y) entity_move(___player, x, y)

void player_destroy();

#endif
