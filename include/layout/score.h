#pragma once

#include "layout/string.h"

typedef struct {
    int perfect;
    int great;
    int good;
    int bad;
    int miss;

    float lastElapsed;
    float lastLossSecond;
} Score;

Score* NewScore();
void CloseScore(Score* score);

int ScoreRender(Score* score, Fonts* fonts);
int ScoreRenderAtLane(Score* score, Fonts* fonts, int laneCount, float elapsed);
