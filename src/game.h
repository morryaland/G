#ifndef __GAME_H__
#define __GAME_H__

#include "map/map.h"
#include "move_stack.h"
#include "player/player.h"

typedef struct _camera {
  float x;
  float y;
  float f;
  float speed;
  int mstackid;
} CAMERA;

extern CAMERA game_camera;
extern double game_fps;

void cam_move(float x, float y);

void fps_calc();

MAP *player_map();

#endif
