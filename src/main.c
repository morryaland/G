#include "game.h"
#include "input.h"
#include "sdl/sdl.h"
#include "player/player.h"

int main()
{
  sdl_init();
  player_init("void/void", 0, 0, 1, 1, 0xFF);
  for (;;) {
    event();
    SDL_RenderClear(game_renderer);
    cam_move(___player->x, ___player->y);
    render_map(player_map);
    render_player();
    render_entity(player_map);
    SDL_RenderPresent(game_renderer);
  }
  return 0;
}
