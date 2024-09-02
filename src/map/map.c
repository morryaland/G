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
  m->texture_map = NULL;
  m->entity = NULL;
  strcpy(m->location_map_name, map_name);
  m->texture_c = m->entity_c = 0;

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
    struct xml_node *rchild = xml_node_child(root, i);
    struct xml_string *rchild_name = xml_node_name(rchild);
    struct xml_string *rchild_content = xml_node_content(rchild);
    char name[64] = {};
    char content[256] = {};
    xml_string_copy(rchild_name, name, xml_string_length(rchild_name));
    xml_string_copy(rchild_content, content, xml_string_length(rchild_content));

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
    else if (!strcmp(name, "Texture")) {
      char tpath[256] = {};
      struct xml_string *_texture_name = xml_node_attribute_content(rchild, 0);
      char texture_name[64] = {};
      xml_string_copy(_texture_name, texture_name, xml_string_length(_texture_name));
      strcat(tpath, ASSETS_DIR);
      strcat(tpath, LOCATION_DIR);
      strcat(tpath, texture_name);
      strcat(tpath, IMG_FILE_FORMAT);
      m->texture_map = realloc(m->texture_map, sizeof(TEXTURE) * (m->texture_c + 1));
      m->texture_map[m->texture_c].sprite = img(tpath);
      int ch_c = m->texture_map[m->texture_c].texture_c = xml_node_children(rchild);
      m->texture_map[m->texture_c].cords = calloc(ch_c, sizeof(short) + sizeof(short));
      for (int i = 0; i < ch_c; i++) {
        struct xml_node *cord = xml_node_child(rchild, i);
        struct xml_string *cx = xml_node_attribute_content(rchild, 0);
        struct xml_string *cy = xml_node_attribute_content(rchild, 1);
        char x[64] = {};
        char y[64] = {};
        xml_string_copy(cx, x, xml_string_length(cx));
        xml_string_copy(cy, y, xml_string_length(cy));

        m->texture_map[m->texture_c].cords[i].x = strtol(x, NULL, 10);
        m->texture_map[m->texture_c].cords[i].y = strtol(y, NULL, 10);
      }
      m->texture_c++;
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
