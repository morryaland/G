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
  CuAssertPtrNotNull(tc, load_map->texture_map[0].sprite);
  CuAssertPtrNotNull(tc, load_map->texture_map[0].cords);
  CuAssertIntEquals(tc, load_map->w, test_map.w);
  CuAssertIntEquals(tc, load_map->h, test_map.h);
  CuAssertStrEquals(tc, load_map->location_map_name, test_map.location_map_name);
}

void Test_entity(CuTest *tc)
{
  ENTITY entity = {
    .x = 1,
    .y = 2,
    .id = ID_PLAYER,
    .local_id = 0,
    .state = 0,
    .flags.colision = 1
  };
  entity_list_init();
  ENTITY *e = entity_init(0, ID_PLAYER);
  e->x = 1;
  e->y = 2;
  e->state = 0;
  CuAssertIntEquals(tc, e->x, entity.x);
  CuAssertIntEquals(tc, e->y, entity.y);
  CuAssertIntEquals(tc, e->state, entity.state);
  CuAssertIntEquals(tc, e->id, entity.id);
  CuAssertIntEquals(tc, e->local_id, entity.local_id);
  CuAssertIntEquals(tc, e->flags.colision, entity.flags.colision);
  CuAssertStrEquals(tc, entity_get_name(e), NAME_PLAYER);
}
