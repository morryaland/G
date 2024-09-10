#ifndef __ENTITY_H__
#define __ENTITY_H__

/* Game entity
 *
 * */
typedef struct _entity {
  unsigned short local_id;
  unsigned char state;
  float x, y;
  int flags;
} ENTITY;

/* создаёт новую сущность */
ENTITY *entity_init(short local_id, float x, float y, int flags);

void entity_set_state(ENTITY *e, unsigned char state);

void entity_move(ENTITY *e, float x, float y);

void entity_destroy(ENTITY **e);

#endif
