#include "player.h"

PLAYER *player;

void player_init(char *start_map, float x, float y)
{
  player = malloc(sizeof(player));
  player_set_map(start_map);
  player_move(x, y);
  //TODO: sprite load
}

void player_set_map(char *map_name)
{
  strcpy(player->region_map_name, map_name);
}

void player_move(float x, float y)
{
  player->x = x;
  player->y = y;
}

void player_destroy()
{
  free(player);
}
