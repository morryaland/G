#include <stdlib.h>
#include <math.h>
#include "game.h"
#include "move_stack.h"
#include "sdl/sdl.h"

static GLOBAL_MOVE_STACK game_move_stack;

static int find_free()
{
  for (int i = 0; i < game_move_stack.stack_c; i++) {
    if (*game_move_stack.stack[i].id < 0)
      return i;
  }
  return -1;
}

static int _move(MOVE_STACK *m)
{
  unsigned long delta_us = (double)(game_timer - m->ts) / game_freque * 1000;
  if (delta_us > m->te) {
    *m->tx = m->ex;
    *m->ty = m->ey;
    return 1;
  }
  float x, y;
  x = (m->ex - m->sx);
  y = (m->ey - m->sy);
  float xy = 1, yx = 1;
  if (fabsf(x) < fabsf(y))
    xy = x / y;
  else
    yx = y / x;
  x = x ? (x < 0) ? -1 * xy : 1 * xy : 0;
  y = y ? (y < 0) ? -1 * yx : 1 * yx : 0;
  *m->tx += x / game_fps * m->speed;
  *m->ty += y / game_fps * m->speed;
  return 0;
}

void move_stack()
{
  for (int i = 0; i < game_move_stack.stack_c; i++) {
    if (*game_move_stack.stack[i].id >= 0) {
      if (_move(game_move_stack.stack + i)) {
        *game_move_stack.stack[i].id = -1;
      }
    }
    else if (i == game_move_stack.stack_c - 1) {
      game_move_stack.stack = realloc(game_move_stack.stack, sizeof(MOVE_STACK) * (game_move_stack.stack_c - 1));
      game_move_stack.stack_c--;
    }
  }
}

void move_stack_free()
{
  free(game_move_stack.stack);
}

void move_stack_add(int *id, float speed, float *tx, float *ty, float x, float y)
{
  if (*id >= 0) {
    return;
  }
  int free = find_free();
  if (free < 0) {
    game_move_stack.stack = realloc(game_move_stack.stack, sizeof(MOVE_STACK) * (game_move_stack.stack_c + 1));
    free = game_move_stack.stack_c;
    game_move_stack.stack_c++;
  }
  *id = free;
  game_move_stack.stack[free].sx = *tx;
  game_move_stack.stack[free].sy = *ty;
  game_move_stack.stack[free].ex = x;
  game_move_stack.stack[free].ey = y;
  game_move_stack.stack[free].tx = tx;
  game_move_stack.stack[free].ty = ty;
  game_move_stack.stack[free].id = id;
  game_move_stack.stack[free].ts = game_timer;
  game_move_stack.stack[free].te = (sqrtf((x - *tx) * (x - *tx) + (y - *ty) * (y - *ty)) * 1000) / speed;
  game_move_stack.stack[free].speed = speed;
}
