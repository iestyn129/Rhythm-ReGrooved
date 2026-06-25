#include "hk/svc/api.h"
#include "lua.h"
#include "chart.h"

lua_State* gLua = nullptr;


void initLua() {
    gLua = luaL_newstate();
    luaL_openlibs(gLua);

    lua_pushcfunction(gLua, lua_print);
    lua_setglobal(gLua, "print");

    lua_pushcfunction(gLua, lua_rest);
    lua_setglobal(gLua, "rest");
    lua_pushcfunction(gLua, lua_spawn_cue);
    lua_setglobal(gLua, "spawn_cue");
}


void runScript(const char* script) {
    luaL_loadbuffer(gLua, script, static_cast<int>(strlen(script)), "runScript");
    lua_pcall(gLua, 0, 0, 0);
}


int lua_print(lua_State* L) {
    const int argc = lua_gettop(L);
    char buf[1024];

    for (int i = 1; i <= argc; i++) {
        const char* str = lua_tostring(L, i);

        if (str != nullptr) {
            sprintf(buf, "%s", str);
            hk::svc::OutputDebugString(buf, 1024);
        }
    }

    return 0;
}


int lua_rest(lua_State* L) {
    const lua_Integer ticks = luaL_checkinteger(L, 1);

    chartRest(static_cast<s32>(ticks));

    return 0;
}



int lua_spawn_cue(lua_State* L) {
    const lua_Integer cueIdx = luaL_checkinteger(L, 1);

    chartSpawnCue(static_cast<s32>(cueIdx));

    return 0;
}
