#include "nn/fs.h"
#include "chart.h"
#include "game.h"
#include "lua.h"

s64 gChartHandler = 0;
s64 gScene = 0;


s64 runLuaChart(const char* scriptName) {
    char scriptPath[1024];

    sprintf(scriptPath, "sd://groove//%s.lua", scriptName);

    runLuaScript(scriptPath);

    return sub_7100514DF0(gScene);
}


s64 chartSetMarkingCriteria(char* criteria) {
    return sub_7100138A90(gChartHandler, criteria);
}


s64 chartRest(s32 length) {
    return rest_sub_7100514B90(gScene, length);
}


void chartSpawnCue(s32 cueIdx) {
    cue_sub_7100217610(gChartHandler + 11424, gScene, cueIdx);
}


void chartSpawnCue2(u32 type, u32 duration, s32 cueIdx, char a3) {
    cue2_sub_710018CFE0(gChartHandler + 11416, gScene, type, duration, cueIdx, a3);
}


void chartSpawnCue3(s32 cueIdx) {
    cue3_sub_71001AF3F0(gChartHandler + 11416, gScene, cueIdx);
}


void chartSpawnCue4(u32 duration, u32 cueIdx, u32 a3, u32 a4) {
    cue4_sub_7100204620(gChartHandler + 11416, gScene, duration, cueIdx, a3, a4);
}
