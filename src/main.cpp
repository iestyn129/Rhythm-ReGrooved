#include "cstdio"
#include "hk/hook/Trampoline.h"
#include "hk/svc/api.h"

// Runs on startup
HkTrampoline<void, u64*> initHook = hk::hook::trampoline([](u64* a1) -> void {
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


extern "C" void hkMain() {
    initHook.installAtMainOffset(0x50C9C0);
    mainLoopHook.installAtMainOffset(0x509e10);
    loadFileHook.installAtMainOffset(0x4E3990);
}
