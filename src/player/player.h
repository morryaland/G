#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "../define.h"

typedef struct _player {
  float x, y;
  unsigned char state;
  unsigned char state_c;
  IMG_Animation **sprites;
  char region_map_name[PATH_MAX]; /* location/map */
  int flags;
} PLAYER;

extern PLAYER *player;

void player_init(char *default_map, float x, float y);

void player_set_map(char *map_name);

void player_set_state(unsigned char state);

void player_move(float x, float y);

void player_destroy();

#endif
