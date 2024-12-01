#ifndef __DEV_MODE_H__
#define __DEV_MODE_H__

#include "stdbool.h"
#include "sdl/sdl.h"

extern bool dev_mode_enable;
extern struct nk_context *dev_mode_ctx;

void dev_window_init(SDL_Window *window, SDL_Renderer *renderer);

void dev_window_render();

void dev_mode_switch();

#endif
