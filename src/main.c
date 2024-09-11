#include "sdl/sdl.h"

int main()
{
  sdl_init();
  for (;;) {
    while (SDL_PollEvent(&game_window_event)) {
      switch (game_window_event.type) {
        case SDL_QUIT:
          exit(0);
          break;
        default:
          break;
      }
    }
    SDL_RenderClear(game_renderer);
    SDL_RenderPresent(game_renderer);
  }
  return 0;
}
