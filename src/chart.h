#pragma once

extern s64 gChartHandler;
extern s64 gScene;

extern s64 runLuaChart(const char* scriptName);

extern s64 chartSetMarkingCriteria(char* criteria);
extern s64 chartRest(s32 length);
extern void chartSpawnCue(s32 cueIdx);
extern void chartSpawnCue2(u32 type, u32 duration, s32 cueIdx, char a3);
extern void chartSpawnCue3(s32 cueIdx);
extern void chartSpawnCue4(u32 duration, u32 cueIdx, u32 a3, u32 a4);
