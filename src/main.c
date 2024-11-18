#include "game.h"
#include "sdl/sdl.h"
#include "player/player.h"

int main()
{
  sdl_init();
  player_init("void/void", 0, 0, 1, 1);
  for (;;) {
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
          player_move(player->x + 0.5, player->y);
          break;
        case SDLK_LEFT:
          player_move(player->x - 0.5, player->y);
          break;
        case SDLK_DOWN:
          player_move(player->x, player->y + 0.5);
          break;
        case SDLK_UP:
          player_move(player->x, player->y - 0.5);
          break;
      }
    }
    SDL_RenderClear(game_renderer);
    cam_move(player->x, player->x);
    render_map(player_map);
    render_player();
    render_entity(player_map);
    SDL_RenderPresent(game_renderer);
  }
  return 0;
}
