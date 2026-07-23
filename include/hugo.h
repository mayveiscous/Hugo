#pragma once

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

extern "C" int luaopen_hugo(lua_State* L);