#pragma once

#include "layout/string.h"

typedef struct {
    float totalLoss;
    float userLoss;

    float lastElapsed;
    float lastLossSecond;
} Score;

Score* NewScore();
void CloseScore(Score* score);

int ScoreRender(Score* score, Fonts* fonts);
int ScoreRenderAtLane(Score* score, Fonts* fonts, int laneCount, float elapsed);
