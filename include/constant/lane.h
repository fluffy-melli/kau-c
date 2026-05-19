#pragma once

#include <raylib.h>

#define LANE_CENTER      0.10000f // 0.0f ~ 1.0f
#define LANE_LINE_WIDTH  0.00468f // 1280: 6
#define LANE_NOTE_WIDTH  0.05625f // 1280: 74
#define LANE_NOTE_HEIGHT 0.03333f // 720:  24
#define LANE_JUDGEMENT_Y 0.13888f // 720: 100 (screen bottom)

#define LANE_BACKGROUND_COLOR ((Color) {0, 0, 0, 150})
#define LANE_JUDGEMENT_COLOR  ((Color) {248, 229, 73, 150})
#define LANE_LINE_COLOR       ((Color) {255, 255, 255, 150})

#define LANE_KEY_PRESS_COLOR  ((Color) {255, 255, 255, 100})

#define LANE_4K_1 KEY_A // a
#define LANE_4K_2 KEY_S // s
#define LANE_4K_3 KEY_K // k
#define LANE_4K_4 KEY_L // l
