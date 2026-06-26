#include "nn/fs.h"
#include "chart.h"
#include "game.h"
#include "lua.h"

s64 gChartHandler = 0;
s64 gScene = 0;


s64 runLuaChart(const char* scriptName) {
    char scriptPath[1024];

    sprintf(scriptPath, "sd://groove//%s.lua", scriptName);

    nn::fs::MountSdCard("sd");

    nn::fs::FileHandle file{};
    if (nn::fs::OpenFile(&file, scriptPath, nn::fs::OpenMode_Read).IsSuccess()) {
        s64 fileSize = 0;
        nn::fs::GetFileSize(&fileSize, file);

        auto buffer = new char[fileSize + 1];

        u64 bytesRead = 0;
        nn::fs::ReadFile(&bytesRead, file, 0, buffer, fileSize);

        buffer[fileSize] = '\0';

        nn::fs::CloseFile(file);

        runScript(buffer);

        delete[] buffer;
    }

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


void chartSpawnCue4(u32 a1, u32 a2, u32 a3, u32 a4) {
    cue4_sub_7100204620(gChartHandler + 11416, gScene, a1, a2, a3, a4);
}
