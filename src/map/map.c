#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../define.h"
#include "../xml.h"
#include "map.h"

MAP *map_load(const char *map_name)
{
  MAP *m = malloc(sizeof(MAP));
  char path[256] = {};
  strcat(path, ASSETS_DIR);
  strcat(path, LOCATION_DIR);
  strcat(path, map_name);
  strcat(path, MAP_FILE_FORMAT);

  char * buffer = 0;
  long length;
  FILE * f = fopen (path, "rb");
  if (!f) {
    fprintf(stderr, "file: \"%s\" dont open\n", path);
    exit(-1);
  }
  fseek (f, 0, SEEK_END);
  length = ftell (f);
  fseek (f, 0, SEEK_SET);
  buffer = malloc (length);
  fread (buffer, 1, length, f);
  fclose (f);

  struct xml_document *d = xml_parse_document((uint8_t*)buffer, length);
  if (!d) {
    fprintf(stderr, "document: \"%s\" dont parse\nsrc: %s\n", path, buffer);
    exit(-1);
  }
  struct xml_node *root = xml_document_root(d);
  int node_c = xml_node_children(root);
  if (node_c < 3) {
      fprintf(stderr, "file: %s number of child nodes\n", path);
      exit(-1);
  }
  for (int i = 0; i < node_c; i++) {
    struct xml_node *node = xml_node_child(root, i);
    struct xml_string *nname = xml_node_name(node);
    struct xml_string *ncontent = xml_node_content(node);
    char name[64] = {};
    char content[256] = {};
    xml_string_copy(nname, name, xml_string_length(nname));
    xml_string_copy(ncontent, content, xml_string_length(ncontent));

    if (!strcmp(name, "Width")) {
      m->w = strtol(content, NULL, 10);
    }
    else if (!strcmp(name, "Height")) {
      m->h = strtol(content, NULL, 10);
    }
    else if (!strcmp(name, "Background")) {
      char bpath[256] = {};
      strcat(bpath, ASSETS_DIR);
      strcat(bpath, LOCATION_DIR);
      strcat(bpath, content);
      strcat(bpath, IMG_FILE_FORMAT);
      m->background = img(bpath);
    }
    else {
      fprintf(stderr, "handler for %s not found in file: %s\n", name, path);
      exit(-1);
    }

  }

  free(buffer);
  xml_document_free(d, false);
  return m;
}

void map_unload(MAP **m)
{
  SDL_free((**m).background);
  free(*m);
  *m = NULL;
}
