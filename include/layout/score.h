#pragma once

#include "layout/string.h"
#include "compete/protocol.h"

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

int ScoreAnotherRender(PlayerExchangeState* exchange, int count, int32_t localPlayerUid, Fonts* fonts);
