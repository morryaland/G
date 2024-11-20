/**
 * \file
 * \brief Entity header file
 * \author Muly
 *
 * TODO
 */
#ifndef __ENTITY_H__
#define __ENTITY_H__

/**
 * \brief Game local entity
 * \author Muly
 *
 * TODO
 */
typedef struct _entity {
  unsigned int local_id;
  unsigned char state;
  float x, y, w, h;
  int flags;
} ENTITY;

/**
 * TODO
 * \param local_id TODO
 * \param x TODO
 * \param y TODO
 * \param w TODO
 * \param h TODO
 * \param flags TODO
 * \return TODO
 */
ENTITY *entity_init(short local_id, float x, float y, float w, float h, int flags);

/**
 * TODO
 * \param entity TODO
 * \param state TODO
 */
void entity_set_state(ENTITY *e, unsigned char state);

void entity_move(ENTITY *e, float x, float y);

void entity_destroy(ENTITY **e);

#endif
