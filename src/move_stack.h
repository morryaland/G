#ifndef __MOVE_STACK_H__
#define __MOVE_STACK_H__

#include <stdbool.h>


typedef struct _move_stack {
  float *tx, *ty;
  float ex, ey;
  float sx, sy;
  float speed;
  unsigned long ts;
  unsigned long te;
  unsigned long tl;
  int *id;
} MOVE_STACK;

typedef struct _global_move_stack {
  MOVE_STACK *stack;
  int stack_c;
} GLOBAL_MOVE_STACK;

void move_stack();

void move_stack_free();

void move_stack_add(int *id, float speed, float *tx, float *ty, float x, float y);

#define move(id, speed, tx, ty, x, y) move_stack_add(id, speed, tx, ty, x, y)

#endif
