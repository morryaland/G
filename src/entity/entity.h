#ifndef __ENTITY_H__
#define __ENTITY_H__

/* Game entity
 *
 * */
typedef struct _entity {
  unsigned short local_id;
  unsigned char state;
  float x, y;
  struct {
    unsigned char colision:1;
  } flags;
} ENTITY;

/* создаёт новую сущность */
ENTITY *entity_init(short local_id, float x, float y, void *flags);

void entity_destroy(ENTITY **e);

#endif
