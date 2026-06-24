#include "lua.h"
#include "hk/svc/api.h"

lua_State* gLua = nullptr;


void initLua() {
    gLua = luaL_newstate();
    luaL_openlibs(gLua);


    lua_pushcfunction(gLua, lua_print);
    lua_setglobal(gLua, "print");
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
