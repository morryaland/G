#include "CuTest.h"
#include "../src/map/map.h"

#define MAP_NAME "void/void"

void Test_map_load(CuTest *tc)
{
  MAP test_map = {
    .w = 128,
    .h = 256,
    .background = img(ASSETS_DIR LOCATION_DIR MAP_NAME IMG_FILE_FORMAT)
  };
  MAP *load_map = map_load(MAP_NAME);
  CuAssertPtrNotNull(tc, load_map);
  CuAssertIntEquals(tc, load_map->w, test_map.w);
  CuAssertIntEquals(tc, load_map->h, test_map.h);
}
