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

void cam_move(float x, float y)
{
  move(&game_camera.mstackid, game_camera.speed, &game_camera.x, &game_camera.y, x, y);
}

MAP *player_map()
{
  if (!player) {
    fprintf(stderr, "player is null\n");
  }
  else if (!load_map) {
    load_map = map_load(player->region_map_name);
  }
  else if (strcmp(load_map->location_map_name, player->region_map_name)) {
    map_unload(&load_map);
    load_map = map_load(player->region_map_name);
  }
  return load_map;
}
