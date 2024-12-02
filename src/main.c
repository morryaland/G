#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#include "nuklear.h"
#include "nuklear_sdl_renderer.h"
#include "game.h"
#include "input.h"
#include "dev_mode.h"
#include "sdl/sdl.h"
#include "player/player.h"

int main()
{
  sdl_init();
  SDL_ShowCursor(0);
  dev_window_init(game_window, game_renderer);
  player_init("void/void", 0, 0, 1, 1, 0xFF);
  cam_init();
  for (;;) {
    game_timer = SDL_GetPerformanceCounter();
    game_freque = SDL_GetPerformanceFrequency();
    fps_calc();
    cam_move(___player->x, ___player->y);
    nk_input_begin(dev_mode_ctx);
    event();
    nk_sdl_handle_grab();
    nk_input_end(dev_mode_ctx);
    GLOBAL_ENTITY *ge = player_map()->entities[0];
    entity_move(ge->entities[0], ge->entities[0]->x + rand() % 3 - 1, ge->entities[0]->y + rand() % 3 - 1);
    entity_move(ge->entities[1], ge->entities[1]->x + rand() % 3 - 1, ge->entities[1]->y + rand() % 3 - 1);
    move_stack();
    SDL_RenderClear(game_renderer);
    render_map(player_map);
    render_player();
    render_entity_map(player_map);
    dev_window_render();
    nk_sdl_render(NK_ANTI_ALIASING_ON);
    SDL_RenderPresent(game_renderer);
  }
  return 0;
}
