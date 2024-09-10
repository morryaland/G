#include "player.h"

PLAYER *player;

void player_init(char *start_map, float x, float y)
{
  player = malloc(sizeof(PLAYER));
  player_set_map(start_map);
  player_move(x, y);
  player->state = 0;
  player->state_c = PLAYER_SPRITE;
  player->sprites = malloc(sizeof(SDL_Surface*) * PLAYER_SPRITE);
  char ipath[PATH_MAX];
  for (int i = 0; i < PLAYER_SPRITE; i++) {
    snprintf(ipath, sizeof(ipath), "%s%sp%d%s", ASSETS_DIR, PLAYER_DIR, i + 1, IMG_FILE_FORMAT);
    player->sprites[i] = img(ipath);
  }
}

void player_set_flags(void *flags)
{
  memcpy(&player->flags, flags, sizeof(player->flags));
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
    SDL_FreeSurface(player->sprites[i]);
  }
  free(player->sprites);
  free(player);
  player = NULL;
}
