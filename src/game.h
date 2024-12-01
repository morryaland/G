#ifndef __GAME_H__
#define __GAME_H__

#include "map/map.h"
#include "move_stack.h"
#include "player/player.h"

#define _game_camera game_camera.e[0].entities[0]

typedef struct _camera {
  GLOBAL_ENTITY *e;
  float f;
} CAMERA;

extern CAMERA game_camera;
extern double game_fps;

void cam_init();

void cam_move(float x, float y);

void fps_calc();

MAP *player_map();

#endif
