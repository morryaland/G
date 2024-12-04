#include "game.h"
#include "sdl/sdl.h"
#include "move_stack.h"

CAMERA game_camera;
double game_fps;
static MAP *load_map;

void fps_calc()
{
  static unsigned long time_last;
  game_fps = 1 / ((double)(game_timer - time_last) / game_freque);
  time_last = game_timer;
}

void cam_init()
{
  game_camera.f = 1;
  ENTITY **e = malloc(sizeof(ENTITY*));
  e[0] = entity_init(0, 0, 0, 0, 0, 0);
  game_camera.e = global_entity_init("camera", e, 1, NULL, 0);
}

void cam_move(float x, float y)
{
  move(&_game_camera->mstackid, _game_camera->speed, &_game_camera->x, &_game_camera->y, x, y);
}

MAP *player_map()
{
  if (!player) {
    fprintf(stderr, "player is null\n");
  }
  else if (!load_map) {
    load_map = map_load(player->location_map_name);
  }
  else if (strcmp(load_map->location_map_name, player->location_map_name)) {
    map_unload(&load_map);
    load_map = map_load(player->location_map_name);
  }
  return load_map;
}
