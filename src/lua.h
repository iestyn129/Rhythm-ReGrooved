#pragma once

#include "lua.hpp"

extern lua_State* gLua;

extern void initLua();
extern void runScript(const char* script);
extern "C" int lua_print(lua_State* L);
extern "C" int lua_set_marking_criteria(lua_State* L);
extern "C" int lua_rest(lua_State* L);
extern "C" int lua_spawn_cue(lua_State* L);
extern "C" int lua_spawn_cue2(lua_State* L);
extern "C" int lua_spawn_cue3(lua_State* L);
extern "C" int lua_spawn_cue4(lua_State* L);
