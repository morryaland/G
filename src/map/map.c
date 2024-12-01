#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "../define.h"
#include "../xml.h"

static MAP *map_init(const char *name)
{
  MAP *m = malloc(sizeof(MAP));
  m->texture_map = NULL;
  m->entities = NULL;
  strcpy(m->location_map_name, name);
  m->texture_c = m->entity_c = 0;
  return m;
}

static struct xml_node *node_name_content(char *name, char *content, struct xml_node *n, int i)
{
  struct xml_node *chnode = xml_node_child(n, i);
  struct xml_string *chnode_name = xml_node_name(chnode);
  struct xml_string *chnode_content = xml_node_content(chnode);
  if (name)
    xml_string_copy(chnode_name, (uint8_t*)name, xml_string_length(chnode_name));
  if (content)
    xml_string_copy(chnode_content, (uint8_t*)content, xml_string_length(chnode_content));
  return chnode;
}

void attribute_name_content(char *name, char *content, struct xml_node *n, int i)
{
  struct xml_string *node_name = xml_node_attribute_name(n, i);
  struct xml_string *node_content = xml_node_attribute_content(n, i);
  if (name)
    xml_string_copy(node_name, (uint8_t*)name, xml_string_length(node_name));
  if (content)
    xml_string_copy(node_content, (uint8_t*)content, xml_string_length(node_content));
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
    char name[NAME_MAX] = "";
    char content[PATH_MAX] = "";
    struct xml_node *rchild = node_name_content(name, content, root, i);

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
        int attr_c = xml_node_attributes(r);
        for (int j = 0; j < attr_c; j++) {
          char att_val[10] = "";
          char att_name[NAME_MAX] = "";
          attribute_name_content(att_name, att_val, r, j);
         
          if (!strcmp(att_name, "x"))
            rs[i].x = strtol(att_val, NULL, 10);
          else if (!strcmp(att_name, "y"))
            rs[i].y = strtol(att_val, NULL, 10);
          else if (!strcmp(att_name, "w"))
            rs[i].w = strtol(att_val, NULL, 10);
          else if (!strcmp(att_name, "h"))
            rs[i].h = strtol(att_val, NULL, 10);
        }
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
        char gechild_name[64] = "";
        char gechild_content[256] = "";
        struct xml_node *gechild = node_name_content(gechild_name, gechild_content, rchild, i);

        if (!strcmp(gechild_name, "Entity")) {
          entity_list = realloc(entity_list, sizeof(ENTITY*) * (e_c + 1));
          char x[64] = "";
          char y[64] = "";
          char w[64] = "";
          char h[64] = "";
          attribute_name_content(NULL, x, gechild, 0);
          attribute_name_content(NULL, y, gechild, 1);
          attribute_name_content(NULL, w, gechild, 2);
          attribute_name_content(NULL, h, gechild, 3);

          char luapath[PATH_MAX] = "";        
          snprintf(luapath, sizeof(luapath), "%s%s%s%s%s%s", ASSETS_DIR, ENTITY_DIR, entity_name, "/", gechild_content, LUA_FILE_FORMAT);

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
      m->entities = realloc(m->entities, sizeof(GLOBAL_ENTITY*) * (m->entity_c + 1));
      m->entities[m->entity_c] = ge;
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
  if ((**m).entities) {
    for (int i = 0; i < (**m).entity_c; i++) {
      global_entity_destroy(&(**m).entities[i]);
    }
    free((**m).entities);
  }
  free(*m);
  *m = NULL;
}
