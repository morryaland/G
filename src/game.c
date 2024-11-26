#include "game.h"

CAMERA game_camera;
static MAP *load_map;



void move(float *tx, float *ty, float x, float y)
{
  *tx = x;
  *ty = y;
}

void cam_move(float x, float y)
{
  move(&game_camera.x, &game_camera.y, x, y);
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
