#include "CuTest.h"
#include "../src/map/map.h"
#include "../src/entity/entity.h"
#include "../src/player/player.h"

#define MAP_NAME "void/void"

void Test_map_load(CuTest *tc)
{
  MAP test_map = {
    .w = 128,
    .h = 256,
    .background = gif_load(ASSETS_DIR LOCATION_DIR MAP_NAME IMG_FILE_FORMAT),
    .location_map_name = MAP_NAME
  };
  MAP *load_map = map_load(MAP_NAME);
  CuAssertPtrNotNull(tc, load_map);
  CuAssertPtrNotNull(tc, load_map->background);
  CuAssertPtrNotNull(tc, load_map->texture_map);
  CuAssertPtrNotNull(tc, load_map->texture_map[0]->sprite);
  CuAssertPtrNotNull(tc, load_map->texture_map[0]->cords);
  CuAssertIntEquals(tc, load_map->texture_map[0]->cords[0].x, 1);
  CuAssertPtrNotNull(tc, load_map->entity);
  CuAssertPtrNotNull(tc, load_map->entity[0]->entities);
  CuAssertPtrNotNull(tc, load_map->entity[0]->sprites);
  CuAssertPtrNotNull(tc, load_map->entity[0]->entities[0]);
  CuAssertPtrNotNull(tc, load_map->entity[0]->sprites[0]);
  CuAssertIntEquals(tc, load_map->w, test_map.w);
  CuAssertIntEquals(tc, load_map->h, test_map.h);
  CuAssertStrEquals(tc, load_map->location_map_name, test_map.location_map_name);
  gif_unload(&test_map.background);
  map_unload(&load_map);
}

void Test_player(CuTest *tc)
{
  player_init("void/void", 1.1, 2.2);
  CuAssertStrEquals(tc, player->region_map_name, "void/void");
  CuAssertIntEquals(tc, player->state_c, PLAYER_SPRITE);
  CuAssertPtrNotNull(tc, player->sprites);
  CuAssertPtrNotNull(tc, player->sprites[0]);
  CuAssertPtrNotNull(tc, player->sprites[1]);
  player_destroy();
}

void Test_global_entity(CuTest *tc)
{
  ENTITY **e_list = malloc(sizeof(ENTITY*) * 2);
  int flags = 0xFF;
  e_list[0] = entity_init(0, 1.1, 34.4, flags);
  e_list[1] = entity_init(1, 2.3, -13, flags);
  GIF_ANIMATION **s = malloc(sizeof(GIF_ANIMATION*) * 1);
  s[0] = gif_load(ASSETS_DIR ENTITY_DIR "ERROR/ERROR" IMG_FILE_FORMAT);
  GLOBAL_ENTITY *ge = global_entity_init("ERROR", e_list, 2, s, 1);
  CuAssertPtrNotNull(tc, ge->entities);
  CuAssertPtrNotNull(tc, ge->entities[0]);
  CuAssertDblEquals(tc, ge->entities[0]->x, 1.1, 0.1);
  CuAssertPtrNotNull(tc, ge->sprites);
  CuAssertPtrNotNull(tc, ge->sprites[0]);
  CuAssertStrEquals(tc, ge->name, "ERROR");
  CuAssertIntEquals(tc, ge->state_c, 1);
  CuAssertIntEquals(tc, ge->entity_c, 2);
  global_entity_destroy(&ge);
}

void Valgrind_player()
{
  player_init("void/void", 1.1, 2.2);
  player_destroy();
}

void Valgrind_texture()
{
  /* Texture test */
  struct { short x, y; } *c = calloc(2, sizeof(float) + sizeof(float));
  TEXTURE *t = texture_load(gif_load(ASSETS_DIR LOCATION_DIR MAP_NAME IMG_FILE_FORMAT), 2, c);
  texture_unload(&t);
}

void Valgrind_map()
{
  /* Map test */
  MAP *m = map_load(MAP_NAME);
  map_unload(&m);
}
