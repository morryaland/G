#include "player.h"

PLAYER *player;

void player_init(char *default_map, float x, float y, float w, float h)
{
  player = malloc(sizeof(PLAYER));
  player_set_map(default_map);
  player_move(x, y);
  player->w = w;
  player->h = h;
  player->state = 0;
  player->flags = 0xFF;
  player->state_c = PLAYER_SPRITE;
  player->sprites = malloc(sizeof(IMG_Animation*) * PLAYER_SPRITE);
  char ipath[PATH_MAX];
  for (int i = 0; i < PLAYER_SPRITE; i++) {
    snprintf(ipath, sizeof(ipath), "%s%sp%d%s", ASSETS_DIR, PLAYER_DIR, i + 1, IMG_FILE_FORMAT);
    player->sprites[i] = gif_load(ipath);
  }
}

void player_set_state(unsigned char state)
{
  player->state = state;
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
  for (int i = 0; i < PLAYER_SPRITE; i++) {
    gif_unload(&player->sprites[i]);
  }
  free(player->sprites);
  free(player);
  player = NULL;
}
