#pragma once

#include "layout/string.h"

typedef struct {
    int maxCombo;
    int currentCombo;

    int score;

    float totalLoss;
    float userLoss;

    float lastElapsed;
    float lastLossSecond;
} Score;

Score* NewScore();
void CloseScore(Score* score);

void ScoreReset(Score* score);

int ScoreRender(Score* score, Fonts* fonts);
int ScoreRenderAtLane(Score* score, Fonts* fonts, int laneCount, float elapsed);
