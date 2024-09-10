#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "../define.h"

typedef struct _player {
  float x, y;
  unsigned char state;
  unsigned char state_c;
  SDL_Surface **sprites;
  char region_map_name[PATH_MAX]; /* location/map */
  struct {
    unsigned char colision:1;
  } flags;
} PLAYER;

extern PLAYER *player;

void player_init(char *start_map, float x, float y);

void player_set_map(char *map_name);

void player_set_flags(void *flags);

void player_set_state(unsigned char state);

void player_move(float x, float y);

void player_destroy();

#endif
