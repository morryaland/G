#include "CuTest.h"
#include "../src/map/map.h"
#include "../src/entity/entity.h"

#define MAP_NAME "void/void"

void Test_map_load(CuTest *tc)
{
  MAP test_map = {
    .w = 128,
    .h = 256,
    .background = img(ASSETS_DIR LOCATION_DIR MAP_NAME IMG_FILE_FORMAT),
    .location_map_name = MAP_NAME
  };
  MAP *load_map = map_load(MAP_NAME);
  CuAssertPtrNotNull(tc, load_map);
  CuAssertPtrNotNull(tc, load_map->background);
  CuAssertPtrNotNull(tc, load_map->texture_map);
  CuAssertPtrNotNull(tc, load_map->texture_map[0]->sprite);
  CuAssertPtrNotNull(tc, load_map->texture_map[0]->cords);
  CuAssertIntEquals(tc, load_map->texture_map[0]->cords[0].x, 1);
  CuAssertIntEquals(tc, load_map->w, test_map.w);
  CuAssertIntEquals(tc, load_map->h, test_map.h);
  CuAssertStrEquals(tc, load_map->location_map_name, test_map.location_map_name);
  SDL_FreeSurface(test_map.background);
  map_unload(&load_map);
}

void Valgrind_texture()
{
  /* Texture test */
  struct { short x, y; } *c = calloc(2, sizeof(float) + sizeof(float));
  TEXTURE *t = texture_load(img(ASSETS_DIR LOCATION_DIR MAP_NAME IMG_FILE_FORMAT), 2, c);
  texture_unload(&t);
}

void Valgrind_map()
{
  /* Map test */
  MAP *m = map_load(MAP_NAME);
  map_unload(&m);
}
