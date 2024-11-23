#include "player.h"

PLAYER *player;

void player_init(char *default_map, float x, float y, float w, float h, int flags)
{
  player = malloc(sizeof(PLAYER));
  player_set_map(default_map);
  player->flags = flags;
  ENTITY **e = malloc(sizeof(ENTITY*));
  e[0] = entity_init(0, x, y, w, h, flags);
  GIF_ANIMATION **s = malloc(sizeof(GIF_ANIMATION*) * PLAYER_SPRITE);
  char ipath[PATH_MAX];
  for (int i = 0; i < PLAYER_SPRITE; i++) {
    snprintf(ipath, sizeof(ipath), "%s%s%s%sp%d%s", ASSETS_DIR, ENTITY_DIR, "player", "/", i + 1, IMG_FILE_FORMAT);
    s[i] = gif_load(ipath);
  }
  player->entity = global_entity_init("player", e, 1, s, PLAYER_SPRITE);
}

void player_set_map(char *map_name)
{
  strcpy(player->region_map_name, map_name);
}

void player_destroy()
{
  global_entity_destroy(&player->entity);
  free(player);
  player = NULL;
}
