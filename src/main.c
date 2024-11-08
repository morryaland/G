#include "game.h"
#include "sdl/sdl.h"
#include "player/player.h"

int main()
{
  sdl_init();
  player_init("void/void", 0, 0);
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
    render_map(player_map);
    SDL_RenderPresent(game_renderer);
  }
  return 0;
}
