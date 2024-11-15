#include <lua.h>
#include <lualib.h>

lua_State *lua_state;

void lua_init()
{
  luaL_openlibs(lua_state);
  luaopen_base(lua_state);
  luaopen_string(lua_state);
}
