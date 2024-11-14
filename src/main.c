#include "game.h"
#include "sdl/sdl.h"
#include "player/player.h"

int main()
{
  sdl_init();
  player_init("void/void", 0, 0);
  float count;
  for (;;) {
    count++;
    while (SDL_PollEvent(&game_window_event)) {
      switch (game_window_event.type) {
        case SDL_QUIT:
          exit(0);
          break;
        default:
          break;
      }
      switch (game_window_event.key.keysym.sym) {
        case SDLK_RIGHT:
          player_move(player->x + 1, player->y);
          break;
        case SDLK_LEFT:
          player_move(player->x - 1, player->y);
          break;
        case SDLK_DOWN:
          player_move(player->x, player->y + 1);
          break;
        case SDLK_UP:
          player_move(player->x, player->y - 1);
          break;
      }
    }
    SDL_RenderClear(game_renderer);
    campos();
    render_map(player_map);
    render_player();
    SDL_RenderPresent(game_renderer);
  }
  return 0;
}
