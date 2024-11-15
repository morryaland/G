#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "../sdl/gif.h"
#include "../define.h"

typedef struct _player {
  float x, y, w, h;
  unsigned char state;
  unsigned char state_c;
  GIF_ANIMATION **sprites;
  char region_map_name[PATH_MAX]; /* location/map */
  int flags;
} PLAYER;

extern PLAYER *player;

void player_init(char *default_map, float x, float y, float w, float h);

void player_set_map(char *map_name);

void player_set_state(unsigned char state);

void player_move(float x, float y);

void player_destroy();

#endif
