#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../define.h"
#include "../xml.h"
#include "texture.h"
#include "map.h"

static MAP *map_init(const char *name)
{
  MAP *m = malloc(sizeof(MAP));
  m->texture_map = NULL;
  m->entity = NULL;
  strcpy(m->location_map_name, name);
  m->texture_c = m->entity_c = 0;
  return m;
}

MAP *map_load(const char *map_name)
{
  MAP *m = map_init(map_name);
  char path[256] = "";
  strcat(path, ASSETS_DIR); strcat(path, LOCATION_DIR); strcat(path, map_name); strcat(path, MAP_FILE_FORMAT);

  FILE *f = fopen(path, "rb");
  if (!f) {
    fprintf(stderr, "file: \"%s\" doesn't open\n", path);
    exit(-1);
  }

  struct xml_document *d = xml_open_document(f);
  if (!d) {
    fprintf(stderr, "document: \"%s\" doesn't open\n", path);
    xml_document_free(d, true);
    free(m);
    return NULL;
  }

  struct xml_node *root = xml_document_root(d);
  int node_c = xml_node_children(root);
  if (node_c < 3) {
      fprintf(stderr, "file: \"%s\" number of child nodes\n", path);
      xml_document_free(d, true);
      free(m);
      return NULL;
  }

  for (int i = 0; i < node_c; i++) {
    struct xml_node *rchild = xml_node_child(root, i);
    struct xml_string *rchild_name = xml_node_name(rchild);
    struct xml_string *rchild_content = xml_node_content(rchild);
    char name[64] = "";
    char content[256] = "";
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
      char texture_name[128] = "";
      struct xml_string *__texture_name = xml_node_attribute_content(rchild, 0);
      xml_string_copy(__texture_name, texture_name, xml_string_length(__texture_name));
      char tpath[256] = "";
      strcat(tpath, ASSETS_DIR);
      strcat(tpath, LOCATION_DIR);
      strcat(tpath, texture_name);
      strcat(tpath, IMG_FILE_FORMAT);
      int ch_c = xml_node_children(rchild);
      struct { short x, y; } *cords = calloc(ch_c, sizeof(short) + sizeof(short));
      for (int i = 0; i < ch_c; i++) {
        struct xml_node *cord = xml_node_child(rchild, i);
        struct xml_string *cx = xml_node_attribute_content(cord, 0);
        struct xml_string *cy = xml_node_attribute_content(cord, 1);
        char x[64] = "";
        char y[64] = "";
        xml_string_copy(cx, x, xml_string_length(cx));
        xml_string_copy(cy, y, xml_string_length(cy));

        cords[i].x = strtol(x, NULL, 10);
        cords[i].y = strtol(y, NULL, 10);
      }
      m->texture_map = realloc(m->texture_map, sizeof(TEXTURE*) * (m->texture_c + 1));
      m->texture_map[m->texture_c] = texture_load(img(tpath), ch_c, cords);
      m->texture_c++;
    }
    else if (!strcmp(name, "GlobalEntity")) {
      //TODO
    }
    else {
      fprintf(stderr, "handler for %s not found in file: %s\n", name, path);
      xml_document_free(d, true);
      free(m);
      return NULL;
    }
  }

  xml_document_free(d, true);
  return m;
}

void map_unload(MAP **m)
{
  if (!*m)
    return;
  SDL_FreeSurface((**m).background);
  for (int i = 0; i < (**m).texture_c; i++) {
    texture_unload(&(**m).texture_map[i]);
  }
  free((**m).texture_map);
  free(*m);
  *m = NULL;
}
