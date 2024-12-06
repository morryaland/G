#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#include "nuklear.h"
#include "nuklear_sdl_renderer.h"
#include "move_stack.h"
#include "dev_mode.h"
#include "game.h"

bool dev_mode_enable;
struct nk_context *dev_mode_ctx;

static void entity_info(GLOBAL_ENTITY *e, int id)
{
  if (nk_tree_push_id(dev_mode_ctx, NK_TREE_TAB, e->name, NK_MINIMIZED, id)) {
    if (e->state_c && nk_tree_push_id(dev_mode_ctx, NK_TREE_TAB, "sprites", NK_MINIMIZED, id)) {
      nk_layout_row_dynamic(dev_mode_ctx, 200, 2);
      for (int i = 0; i < e->state_c; i++) {
        if (nk_group_begin(dev_mode_ctx, e->sprites[i]->path, NK_WINDOW_TITLE | NK_WINDOW_BORDER | NK_WINDOW_NO_SCROLLBAR)) {
          struct nk_image img = nk_image_ptr(gif_animation(e->sprites[i]));
          nk_draw_image(nk_window_get_canvas(dev_mode_ctx), nk_window_get_content_region(dev_mode_ctx), &img, nk_rgba(255, 255, 255, 255));
          nk_group_end(dev_mode_ctx);
        }
      }
      nk_tree_pop(dev_mode_ctx);
    }
    if (e->entity_c && nk_tree_push_id(dev_mode_ctx, NK_TREE_TAB, "entities", NK_MINIMIZED, id)) {
      for (int i = 0; i < e->entity_c; i++) {
        nk_layout_row_dynamic(dev_mode_ctx, 30, 1);
        nk_labelf_wrap(dev_mode_ctx, "local id: %d mid: %d state %d x: %f y: %f speed %f", e->entities[i]->local_id, e->entities[i]->mstackid, e->entities[i]->state, e->entities[i]->x, e->entities[i]->y, e->entities[i]->speed);
      }
      nk_tree_pop(dev_mode_ctx);
    }
    nk_tree_pop(dev_mode_ctx);
  }
}

void dev_window_init(SDL_Window *window, SDL_Renderer *renderer)
{
  dev_mode_ctx = nk_sdl_init(window, renderer);
  float font_scale;
  SDL_RenderGetScale(game_renderer, NULL, &font_scale);
  struct nk_font_atlas *atlas;
  struct nk_font_config config = nk_font_config(0);
  struct nk_font *font;
  nk_sdl_font_stash_begin(&atlas);
  font = nk_font_atlas_add_default(atlas, 13 * font_scale, &config);
  nk_sdl_font_stash_end();
  font->handle.height /= font_scale;
  nk_style_set_font(dev_mode_ctx, &font->handle);
}

void dev_mode_switch()
{
  dev_mode_enable = !dev_mode_enable;
  SDL_ShowCursor(dev_mode_enable ? 1 : 0);
}

void dev_window_render()
{
  MAP *map = player_map();
  int ww, wh, id = 0;
  SDL_GetWindowSize(game_window, &ww, &wh);
  struct nk_style *s = &dev_mode_ctx->style;
  nk_style_push_color(dev_mode_ctx, &s->window.background, nk_rgba(40,40,60,200));
  nk_style_push_style_item(dev_mode_ctx, &s->window.fixed_background, nk_style_item_color(nk_rgba(40,40,60,200)));
  if (dev_mode_enable && nk_begin(dev_mode_ctx, "dev mode", nk_rect(0, 0, ww / 3, wh), NK_WINDOW_BORDER)) {
    nk_layout_row_dynamic(dev_mode_ctx, 25, 1);
    nk_labelf(dev_mode_ctx, NK_TEXT_LEFT, "fps: %f", game_fps);
    nk_layout_row_dynamic(dev_mode_ctx, 25, 1);
    nk_labelf(dev_mode_ctx, NK_TEXT_LEFT, "map: %s", map->location_map_name);
    nk_layout_row_dynamic(dev_mode_ctx, 100, 1);
    if (map->background && nk_group_begin(dev_mode_ctx, map->background->path, NK_WINDOW_TITLE | NK_WINDOW_BORDER | NK_WINDOW_NO_SCROLLBAR)) {
      struct nk_image img = nk_image_ptr(gif_animation(map->background));
      nk_draw_image(nk_window_get_canvas(dev_mode_ctx), nk_window_get_content_region(dev_mode_ctx), &img, nk_rgba(255, 255, 255, 255));
      nk_group_end(dev_mode_ctx);
    }
    nk_layout_row_dynamic(dev_mode_ctx, 25, 1);
    nk_labelf(dev_mode_ctx, NK_TEXT_LEFT, "cam f: %f", game_camera.f);
    entity_info(game_camera.e, ++id);
    nk_labelf(dev_mode_ctx, NK_TEXT_LEFT, "player map: %s", player->location_map_name);
    entity_info(player->entity, ++id);
    if (nk_tree_push(dev_mode_ctx, NK_TREE_TAB, "Entities", NK_MINIMIZED)) {
      for (int i = 0; i < map->entity_c; i++) {
        entity_info(map->entities[i], ++id);
      }
      nk_tree_pop(dev_mode_ctx);
    }
    if (nk_tree_push(dev_mode_ctx, NK_TREE_TAB, "Move stack", NK_MINIMIZED)) {
      for (int i = 0; i < game_move_stack.stack_c; i++) {
        nk_layout_row_dynamic(dev_mode_ctx, 25, 1);
        nk_labelf(dev_mode_ctx, NK_TEXT_LEFT, "%d: %d", i, *game_move_stack.stack[i].id);
      }
      nk_tree_pop(dev_mode_ctx);
    }
    nk_end(dev_mode_ctx);
  }
  nk_style_pop_color(dev_mode_ctx);
  nk_style_pop_style_item(dev_mode_ctx);
}
