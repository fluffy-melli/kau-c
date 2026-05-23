#pragma once

#include "layout/string.h"

typedef struct {
    int perfect;
    int great;
    int good;
    int bad;
    int miss;
} Score;

Score* NewScore();
void CloseScore(Score* score);

int ScoreRender(Score* score, Fonts* fonts);
