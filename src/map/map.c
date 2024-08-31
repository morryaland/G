#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../define.h"
#include "../xml.h"
#include "map.h"

MAP *map_load(const char *name)
{
  MAP *m = malloc(sizeof(MAP));
  char *path = (char[256]){};
  strcat(path, ASSETS_DIR);
  strcat(path, name);
  strcat(path, MAP_FILE_FORMAT);

  char * buffer = 0;
  long length;
  FILE * f = fopen (path, "rb");
  if (!f) {
    return NULL;
  }
  fseek (f, 0, SEEK_END);
  length = ftell (f);
  fseek (f, 0, SEEK_SET);
  buffer = malloc (length);
  if (!buffer) {
    return NULL;
  }
  fread (buffer, 1, length, f);
  fclose (f);

  struct xml_document *d = xml_parse_document((uint8_t*)buffer, length);
  if (!d) {
    return NULL;
  }
  struct xml_node *root = xml_document_root(d);

  free(buffer);
  xml_document_free(d, false);
}

void map_unload(MAP **m)
{
  free(*m);
  *m = NULL;
}
