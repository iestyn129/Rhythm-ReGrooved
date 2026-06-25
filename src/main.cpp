#include "hk/hook/Trampoline.h"
#include "hk/svc/api.h"
#include "arm_neon.h"
#include "chart.h"
#include "game.h"
#include "lua.h"


// Runs on startup
HkTrampoline<void, u64*> initHook = hk::hook::trampoline([](u64* a1) -> void {
    runScript(R"(print("hello from lua"))");

    initHook.orig(a1);
});


// Runs every frame
HkTrampoline<void, int> mainLoopHook = hk::hook::trampoline([](int a1) -> void {
    mainLoopHook.orig(a1);
});


HkTrampoline<void*, char*, u32*, u32, s32, s32, char, char> loadFileHook = hk::hook::trampoline([](
    char* a1, unsigned int* a2, unsigned int a3, int a4, int a5, char a6, char a7
) -> void* {
    void* ret = loadFileHook.orig(a1, a2, a3, a4, a5, a6, a7);

    char msg[1024];
    sprintf(msg, "loaded file '%s' at %p. (a2: %p, a3: %d, a4: %d, a5: %d, a6: %d, read only?: %d)", a1, ret, a2, a3, a4, a5, a6, a7);
    hk::svc::OutputDebugString(msg, 1024);

    return ret;
});


HkTrampoline<void*, void*, char*> setAnimHook = hk::hook::trampoline([](void* a1, char* a2) -> void* {

    char msg[1024];
    sprintf(msg, "%p - %s", a1, a2);
    hk::svc::OutputDebugString(msg, 1024);

    return setAnimHook.orig(a1, a2);;
});


HkTrampoline restHook = [](TrampolineStatic(), u32* a1, s64 a2) -> u32* {
    return orig(a1, 120);
};


HkTrampoline sceneHook = [](TrampolineStatic(), s32 a1, s64 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) -> int32x2_t {
    switch (a1) {
    case 44:
        a1 = 43;
        break;
    case 52:
        a1 = 51;
        break;
    case 6:
        a1 = 158;
        break;
    case 68:
        a1 = 67;
        break;
    case 123:
        a1 = 121;
        break;
    default:
        break;
    }

    return orig(a1, a2, a3, a4, a5, a6, a7);
};


HkTrampoline trundlingCueHook = [](TrampolineStatic(), s64 a1, s64 a2) -> s64 {
    gChartHandler = a1;
    gScene = a2;

    return runLuaChart("trundling");
};


HkTrampoline discDogCueHook = [](TrampolineStatic(), s64 a1, s64 a2) -> s64 {
    gChartHandler = a1;
    gScene = a2;

    return runLuaChart("discdog");
};


HkTrampoline beastCueHook = [](TrampolineStatic(), s64 a1, s64 a2) -> s64 {
    gChartHandler = a1;
    gScene = a2;

    return runLuaChart("beast");
};


HkTrampoline brollyCueHook = [](TrampolineStatic(), s64 a1, s64 a2) -> s64 {
    gChartHandler = a1;
    gScene = a2;

    return runLuaChart("brolly");
};


extern "C" void hkMain() {
    initLua();

    initHook.installAtMainOffset(0x50C9C0);
    mainLoopHook.installAtMainOffset(0x509e10);
    //loadFileHook.installAtMainOffset(0x4E3990);
    //setAnimHook.installAtMainOffset(0x4F80D0);
    //restHook.installAtMainOffset(0x514B90);
    //sceneHook.installAtMainOffset(0x488800);
    trundlingCueHook.installAtMainOffset(0x42C900);
    discDogCueHook.installAtMainOffset(0x329B70);
    beastCueHook.installAtMainOffset(0x34FDE0);
    brollyCueHook.installAtMainOffset(0x38FE40);
}
