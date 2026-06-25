#include "chart.h"

s64 gChartHandler = 0;
s64 gScene = 0;


void chartRest(s32 length) {
    rest_sub_7100514B90(gScene, length);
}


void chartSpawnCue(s32 cueIdx) {
    cue_sub_7100217610(gChartHandler + 11424, gScene, cueIdx);
}
