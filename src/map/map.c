#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../sdl/sdl.h"
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
  char path[PATH_MAX] = "";
  snprintf(path, sizeof(path), "%s%s%s%s", ASSETS_DIR, LOCATION_DIR, map_name, MAP_FILE_FORMAT);

  FILE *f = fopen(path, "rb");
  if (!f) {
    fprintf(stderr, "file: \"%s\" doesn't open\n", path);
    map_unload(&m);
    return NULL;
  }

  struct xml_document *d = xml_open_document(f);
  if (!d) {
    fprintf(stderr, "document: \"%s\" doesn't open\n", path);
    xml_document_free(d, true);
    map_unload(&m);
    return NULL;
  }

  struct xml_node *root = xml_document_root(d);
  int node_c = xml_node_children(root);

  for (int i = 0; i < node_c; i++) {
    struct xml_node *rchild = xml_node_child(root, i);

    struct xml_string *rchild_name = xml_node_name(rchild);
    struct xml_string *rchild_content = xml_node_content(rchild);
    char name[NAME_MAX] = "";
    char content[PATH_MAX] = "";
    xml_string_copy(rchild_name, name, xml_string_length(rchild_name));
    xml_string_copy(rchild_content, content, xml_string_length(rchild_content));

    if (!strcmp(name, "Width")) {
      m->w = strtol(content, NULL, 10);
    }
    else if (!strcmp(name, "Height")) {
      m->h = strtol(content, NULL, 10);
    }
    else if (!strcmp(name, "Background")) {
      char bpath[PATH_MAX] = "";
      snprintf(bpath, sizeof(bpath), "%s%s%s%s", ASSETS_DIR, LOCATION_DIR, content, IMG_FILE_FORMAT);
      m->background = gif_load(bpath);
    }
    else if (!strcmp(name, "Texture")) {
      char texture_name[PATH_MAX] = "";
      struct xml_string *__texture_name = xml_node_attribute_content(rchild, 0);
      xml_string_copy(__texture_name, texture_name, xml_string_length(__texture_name));
      char tpath[256] = "";
      snprintf(tpath, sizeof(tpath), "%s%s%s%s", ASSETS_DIR, LOCATION_DIR, texture_name, IMG_FILE_FORMAT);

      int ch_c = xml_node_children(rchild);
      struct { int x, y, w, h; } *rs = calloc(ch_c, sizeof(struct { int x, y, w, h; }));
      for (int i = 0; i < ch_c; i++) {
        struct xml_node *r = xml_node_child(rchild, i);
        struct xml_string *cx = xml_node_attribute_content(r, 0);
        struct xml_string *cy = xml_node_attribute_content(r, 1);
        struct xml_string *cw = xml_node_attribute_content(r, 2);
        struct xml_string *ch = xml_node_attribute_content(r, 3);
        char x[10] = "";
        char y[10] = "";
        char w[10] = "";
        char h[10] = "";
        xml_string_copy(cx, x, xml_string_length(cx));
        xml_string_copy(cy, y, xml_string_length(cy));
        xml_string_copy(cw, w, xml_string_length(cw));
        xml_string_copy(ch, h, xml_string_length(ch));

        rs[i].x = strtol(x, NULL, 10);
        rs[i].y = strtol(y, NULL, 10);
        rs[i].w = strtol(w, NULL, 10);
        rs[i].h = strtol(h, NULL, 10);
      }
      m->texture_map = realloc(m->texture_map, sizeof(TEXTURE*) * (m->texture_c + 1));
      m->texture_map[m->texture_c] = texture_load(gif_load(tpath), ch_c, rs);
      m->texture_c++;
    }
    else if (!strcmp(name, "GlobalEntity")) {
      char entity_name[PATH_MAX] = "";
      struct xml_string *__entity_name = xml_node_attribute_content(rchild, 0);
      xml_string_copy(__entity_name, entity_name, xml_string_length(__entity_name));

      unsigned long ch_c = xml_node_children(rchild);
      unsigned short e_c, s_c;
      e_c = s_c = 0;
      ENTITY **entity_list = NULL;
      GIF_ANIMATION **sprite_list = NULL;
      for (int i = 0; i < ch_c; i++) {
        struct xml_node *gechild = xml_node_child(rchild, i);

        struct xml_string *__gechild_name = xml_node_name(gechild);
        struct xml_string *__gechild_content = xml_node_content(gechild);
        char gechild_name[64] = "";
        char gechild_content[256] = "";
        xml_string_copy(__gechild_name, gechild_name, xml_string_length(__gechild_name));
        xml_string_copy(__gechild_content, gechild_content, xml_string_length(__gechild_content));

        if (!strcmp(gechild_name, "Entity")) {
          entity_list = realloc(entity_list, sizeof(ENTITY*) * (e_c + 1));

          struct xml_string *cx = xml_node_attribute_content(gechild, 0);
          struct xml_string *cy = xml_node_attribute_content(gechild, 1);
          struct xml_string *cw = xml_node_attribute_content(gechild, 2);
          struct xml_string *ch = xml_node_attribute_content(gechild, 3);
          char x[64] = "";
          char y[64] = "";
          char w[64] = "";
          char h[64] = "";
          xml_string_copy(cx, x, xml_string_length(cx));
          xml_string_copy(cy, y, xml_string_length(cy));
          xml_string_copy(cw, w, xml_string_length(cw));
          xml_string_copy(ch, h, xml_string_length(ch));

          entity_list[e_c] = entity_init(e_c, strtof(x, NULL), strtof(y, NULL), strtof(w, NULL), strtof(h, NULL), 0xFF);
          e_c++;
        }
        else if (!strcmp(gechild_name, "Sprite")) {
          sprite_list = realloc(sprite_list, sizeof(GIF_ANIMATION*) * (s_c + 1));
          char spath[PATH_MAX] = "";
          snprintf(spath, sizeof(spath), "%s%s%s%s%s%s", ASSETS_DIR, ENTITY_DIR, entity_name, "/", gechild_content, IMG_FILE_FORMAT);
          sprite_list[s_c] = gif_load(spath);
          s_c++;
        }
        else {
          fprintf(stderr, "handler for %s not found in file: %s\n", gechild_name, path);
          xml_document_free(d, true);
          free(m);
          return NULL;
        }
      }
      GLOBAL_ENTITY *ge = global_entity_init(entity_name, entity_list, e_c, sprite_list, s_c);
      m->entity = realloc(m->entity, sizeof(GLOBAL_ENTITY*) * (m->entity_c + 1));
      m->entity[m->entity_c] = ge;
      m->entity_c++;
    }
    else {
      fprintf(stderr, "handler for %s not found in file: %s\n", name, path);
      xml_document_free(d, true);
      map_unload(&m);
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
  if ((**m).background)
    gif_unload(&(**m).background);
  if ((**m).texture_map) {
    for (int i = 0; i < (**m).texture_c; i++) {
      texture_unload(&(**m).texture_map[i]);
    }
    free((**m).texture_map);
  }
  if ((**m).entity) {
    for (int i = 0; i < (**m).entity_c; i++) {
      global_entity_destroy(&(**m).entity[i]);
    }
    free((**m).entity);
  }
  free(*m);
  *m = NULL;
}
