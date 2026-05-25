#pragma once

#include "layout/string.h"

typedef struct {
    int length;
    float* lossed;
} Loss;

Loss* NewLoss();
void CloseLoss(Loss* list);

int LossAdd(Loss* list, float lossed);
int LossRemove(Loss* list, int index);
int LossReset(Loss* list);

int LossRender(Loss* list, Fonts* fonts, int laneCount);
