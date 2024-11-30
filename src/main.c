#include "game.h"
#include "input.h"
#include "sdl/sdl.h"
#include "player/player.h"

int main()
{
  sdl_init();
  player_init("void/void", 0, 0, 1, 1, 0xFF);
  game_camera.f = 2;
  game_camera.speed = 3;
  game_camera.mstackid = -1;
  for (;;) {
    game_timer = SDL_GetPerformanceCounter();
    game_freque = SDL_GetPerformanceFrequency();
    fps_calc();
    event();
    cam_move(___player->x, ___player->y);
    entity_move(player_map()->entity[0]->entities[0], player_map()->entity[0]->entities[0]->x + rand() % 4 - 2, player_map()->entity[0]->entities[0]->x + rand() % 4 - 2);
    entity_move(player_map()->entity[0]->entities[1], player_map()->entity[0]->entities[1]->x + rand() % 4 - 2, player_map()->entity[0]->entities[1]->y + rand() % 4 - 2);
    move_stack();
    SDL_RenderClear(game_renderer);
    render_map(player_map);
    render_player();
    render_entity(player_map);
    SDL_RenderPresent(game_renderer);
  }
  return 0;
}
