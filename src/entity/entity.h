#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "global_entity.h"

/* Game entity
 *
 * */
typedef struct _entity {
  short id, local_id;
  //TODO: состояние 1, 2, 3...
  float x, y;
  struct {
    unsigned char colision:1;
    unsigned char up:1;
    unsigned char doun:1;
    unsigned char left:1;
    unsigned char right:1;
  } flags;
} ENTITY;

/* создаёт новую сущьность */
ENTITY *entity_init(short local_id /*TODO: тип сущьности */);

/* получает глобальное имя сущьности */
char *entity_get_name(ENTITY *e);

#endif

