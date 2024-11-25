#include "input.h"

void event()
{
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
          player_move(___player->x + 1, ___player->y);
          break;
        case SDLK_LEFT:
          player_move(___player->x - 1, ___player->y);
          break;
        case SDLK_DOWN:
          player_move(___player->x, ___player->y + 1);
          break;
        case SDLK_UP:
          player_move(___player->x, ___player->y - 1);
          break;
      }
    }

}
