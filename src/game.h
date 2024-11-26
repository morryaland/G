#ifndef __GAME_H__
#define __GAME_H__

#include "map/map.h"
#include "player/player.h"

typedef struct _camera {
  float x;
  float y;
  float f;
} CAMERA;

extern CAMERA game_camera;

void cam_move(float x, float y);

void move(float *tx, float *ty, float x, float y);

MAP *player_map();

#endif
