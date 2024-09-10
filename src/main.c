#include "sdl/sdl.h"

int main()
{
  sdl_init();
  for (;;) {
    SDL_RenderClear(game_renderer);
    SDL_RenderPresent(game_renderer);
  }
  return 0;
}
