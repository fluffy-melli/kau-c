#include "layout/loss.h"

#include <stdlib.h>
#include "layout/string.h"
#include "constant/info.h"
#include "constant/loss.h"
#include "constant/lane.h"
#include "constant/note.h"
#include "constant/verdict.h"

Loss* NewLoss() {
    Loss* list = malloc(sizeof(Loss));
    if (!list) {
        return NULL;
    }

    list->length = 0;
    list->lossed = NULL;

    return list;
}

void CloseLoss(Loss* list) {
    if (!list) {
        return;
    }

    free(list->lossed);
    free(list);
}

int LossAdd(Loss* list, float lossed) {
    if (!list) {
        return -1;
    }
    
    float* temp = realloc(list->lossed, (list->length + 1) * sizeof(float));
    if (!temp) {
        return -1;
    }

    list->lossed = temp;
    list->lossed[list->length] = lossed;
    list->length++;

    if (list->length >= LOSS_LENGTH) {
        LossRemove(list, 0);
    }

    return 0;
}

int LossRemove(Loss* list, int index) {
    if (!list || index < 0 || index >= list->length) {
        return -1;
    }

    for (int i = index; i < list->length - 1; i++) {
        list->lossed[i] = list->lossed[i + 1];
    }

    float* new_loss = realloc(list->lossed, sizeof(float) * (list->length - 1));
    if (!new_loss && list->length - 1 > 0) {
        return -1;
    }

    list->lossed = new_loss;
    list->length--;

    return 0;
}

int LossRender(Loss* list, Fonts* fonts, int laneCount) {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    int lineWidth = screenWidth * LANE_WIDTH;
    int noteWidth = screenWidth * NOTE_WIDTH;

    int infoXPos = screenWidth * INFO_GAP;
    int infoWidth = screenWidth * INFO_WIDTH;

    int fieldXPos = lineWidth + infoWidth + infoXPos * 2;

    int laneWidth = noteWidth * laneCount;

    int lossXGap = screenWidth * LOSS_GAP;

    int lossXPos = fieldXPos + lossXGap;
    int lossYPos = screenHeight * LOSS_CENTER_Y;

    int lossHeight = screenHeight * LOSS_HEIGHT;

    int drawWidth = laneWidth - lossXGap * 2;

    DrawRectangle(
        lossXPos,
        lossYPos,
        drawWidth,
        lossHeight,
        LOSS_BACKGROUND_COLOR
    );

    int earlyFontSize = screenWidth * LOSS_EARLY_FONT_SIZE;
    int earlySpacing = screenWidth * LOSS_EARLY_SPACING;

    DrawString(
        fonts,
        FONT_EXTRA_BOLD,
        "Early",
        lossXPos - 6,
        lossYPos + lossHeight + 7,
        earlySpacing,
        earlyFontSize,
        LOSS_EARLY_COLOR
    );

    int lateFontSize = screenWidth * LOSS_LATE_FONT_SIZE;
    int lateSpacing = screenWidth * LOSS_LATE_SPACING;

    DrawStringAtRight(
        fonts,
        FONT_EXTRA_BOLD,
        "Late",
        lossXPos + drawWidth + 6,
        lossYPos + lossHeight + 7,
        lateSpacing,
        lateFontSize,
        LOSS_LATE_COLOR
    );

    int lossLineSize = screenWidth * LOSS_LINE_SIZE;
    float totalLoss = 0;

    for (int i = 0; i < list->length; i++) {
        float lossVal = list->lossed[i];

        totalLoss += lossVal;

        float ratio = (lossVal + VERDICT_IGNORE_SECONDS) / (VERDICT_IGNORE_SECONDS * 2.0f);

        int targetX = lossXPos + (int) (ratio * drawWidth);

        if (ratio < 0.0f || ratio > 1.0f) {
            continue;
        }

        if (list->length - 1 == i) {
            DrawLineEx(
                ((Vector2) {
                    (float)targetX - lossLineSize / 2,
                    (float)lossYPos
                }),
                ((Vector2) {
                    (float)targetX - lossLineSize / 2,
                    (float)(lossYPos + lossHeight)
                }),
                lossLineSize,
                LOSS_LINE_NOW_COLOR
            );
        } else {
            DrawLineEx(
                ((Vector2) {
                    (float)targetX - lossLineSize / 2,
                    (float)lossYPos
                }),
                ((Vector2) {
                    (float)targetX - lossLineSize / 2,
                    (float)(lossYPos + lossHeight)
                }),
                lossLineSize,
                LOSS_LINE_OLD_COLOR
            );
        }
    }

    float accLoss = totalLoss / list->length;

    float accLossRatio = (accLoss + VERDICT_IGNORE_SECONDS) / (VERDICT_IGNORE_SECONDS * 2.0f);
    int accLossTargetX = lossXPos + (int) (accLossRatio * drawWidth);

    if (accLossRatio < 0.0f || accLossRatio > 1.0f) {
        return 0;
    }

    int accLineSize = screenWidth * LOSS_ACC_LINE_SIZE;

    DrawLineEx(
        ((Vector2) {
            (float)accLossTargetX,
            (float)lossYPos - lateFontSize / 2
        }),
        ((Vector2) {
            (float)accLossTargetX - accLineSize / 2,
            (float)lossYPos - lateFontSize / 2 - accLineSize
        }),
        1.0f,
        LOSS_LINE_ACC_COLOR
    );

    DrawLineEx(
        ((Vector2) {
            (float)accLossTargetX,
            (float)lossYPos - lateFontSize / 2
        }),
        ((Vector2) {
            (float)accLossTargetX + accLineSize / 2,
            (float)lossYPos - lateFontSize / 2 - accLineSize
        }),
        1.0f,
        LOSS_LINE_ACC_COLOR
    );

    float comboPlusRatio = (VERDICT_COMBO_SECONDS + VERDICT_IGNORE_SECONDS) / (VERDICT_IGNORE_SECONDS * 2.0f);
    int comboPlusTargetX = lossXPos + (int) (comboPlusRatio * drawWidth);

    float comboMinusRatio = (-VERDICT_COMBO_SECONDS + VERDICT_IGNORE_SECONDS) / (VERDICT_IGNORE_SECONDS * 2.0f);
    int comboMinusTargetX = lossXPos + (int) (comboMinusRatio * drawWidth);

    DrawRectangle(
        comboMinusTargetX,
        lossYPos - 2,
        comboPlusTargetX - comboMinusTargetX,
        lossHeight + 4,
        LOSS_COMBO_BACKGROUND_COLOR
    );

    return 0;
}
