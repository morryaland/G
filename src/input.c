#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#include "nuklear.h"
#include "nuklear_sdl_renderer.h"
#include "input.h"
#include "dev_mode.h"

void event()
{
  const Uint8 *key_state_arr = SDL_GetKeyboardState(NULL);
  while (SDL_PollEvent(&game_window_event)) {
    switch (game_window_event.type) {
      case SDL_QUIT:
        exit(0);
        break;
      case SDL_KEYDOWN:
        if (key_state_arr[SDL_SCANCODE_UP] && !(key_state_arr[SDL_SCANCODE_DOWN])) {
          player_move(___player->x, ___player->y - 1);
          player_set_state(2);
        }
        else if (!key_state_arr[SDL_SCANCODE_UP] && key_state_arr[SDL_SCANCODE_DOWN]) {
          player_move(___player->x, ___player->y + 1);
          player_set_state(0);
        }
        if (key_state_arr[SDL_SCANCODE_RIGHT] && !key_state_arr[SDL_SCANCODE_LEFT]) {
          player_move(___player->x + 1, ___player->y);
          player_set_state(1);
        }
        else if (!key_state_arr[SDL_SCANCODE_RIGHT] && key_state_arr[SDL_SCANCODE_LEFT]) {
          player_move(___player->x - 1, ___player->y);
          player_set_state(3);
        }
        if (key_state_arr[SDL_SCANCODE_LALT] && key_state_arr[SDL_SCANCODE_F4]) {
          dev_mode_switch();
        }
        break;
      default:
        break;
    }
    nk_sdl_handle_event(&game_window_event);
  }
}
