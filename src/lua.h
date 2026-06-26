#pragma once

#include "hk/prim/traits/Integer.h"
#include "lua.hpp"

extern lua_State* gLua;

extern void initLua();
extern void runLua(const char* script);
extern void runLuaScript(const char* scriptPath);
extern "C" s32 lua_print(lua_State* L);
extern "C" s32 lua_set_marking_criteria(lua_State* L);
extern "C" s32 lua_rest(lua_State* L);
extern "C" s32 lua_spawn_cue(lua_State* L);
extern "C" s32 lua_spawn_cue2(lua_State* L);
extern "C" s32 lua_spawn_cue3(lua_State* L);
extern "C" s32 lua_spawn_cue4(lua_State* L);
