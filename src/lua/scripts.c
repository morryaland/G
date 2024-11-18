#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

lua_State *lua_state;

void lua_init()
{
  lua_state = luaL_newstate();
  luaL_openlibs(lua_state);
  luaopen_base(lua_state);
  luaopen_string(lua_state);
}
