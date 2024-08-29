#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "global_entity.h"

/* Game entity
 *
 * */
typedef struct _entity {
  unsigned short id, local_id;
  unsigned char state;
  float x, y;
  struct {
    unsigned char colision:1;
  } flags;
} ENTITY;

/* создаёт новую сущность */
ENTITY *entity_init(short local_id, short id );

/* получает глобальное имя сущьности */
char *entity_get_name(ENTITY *e);

/* получает спрайт сущности */
SDL_Surface *entity_get_sprite(ENTITY *e);

#endif
