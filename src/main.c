#include "map/map.h"

#define MAP_NAME "void/void"

int main()
{
  struct { short x, y; } *cords = calloc(2, sizeof(short) + sizeof(short));
  TEXTURE *t = texture_load(img(ASSETS_DIR LOCATION_DIR MAP_NAME IMG_FILE_FORMAT), 2, cords);
  texture_unload(&t);
  MAP *load_map = map_load(MAP_NAME);
  map_unload(&load_map);
  return 0;
}
