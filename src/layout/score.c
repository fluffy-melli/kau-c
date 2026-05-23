#include "layout/score.h"

#include <math.h>
#include <stdlib.h>
#include "layout/string.h"
#include "constant/info.h"
#include "constant/lane.h"
#include "constant/note.h"
#include "constant/score.h"
#include "constant/verdict.h"

Score* NewScore() {
    Score* score = malloc(sizeof(Score));
    if (!score) {
        return NULL;
    }

    score->maxCombo = 0;
    score->currentCombo = 0;

    score->score = 0;

    score->totalLoss = 0.0f;
    score->userLoss = 0.0f;

    score->lastElapsed = -999.0f;
    score->lastLossSecond = 0.0f;

    return score;
}

void CloseScore(Score* score) {
    if (score) {
        free(score);
    }
}

int ScoreRender(Score* score, Fonts* fonts) {
    if (!score) {
        return -1;
    }

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    int imagePadding = screenWidth * INFO_IMAGE_PADDING;

    int imageSize = screenWidth * INFO_IMAGE_SIZE;

    int infoHeight = imageSize + imagePadding * 2;

    int infoYPos = (screenHeight - infoHeight) * INFO_CENTER_Y;

    int langCountFontSize = screenWidth * INFO_LANGCOUNT_FONT_SIZE;
    int langCountSpacing = screenWidth * INFO_LANGCOUNT_SPACING;

    int langCountHeight = langCountFontSize + langCountSpacing * 2;

    int langCountYPos = infoYPos + imageSize + imagePadding * 2;

    int scoreXPos = screenWidth * SCORE_GAP_X;
    int scoreYPos = langCountYPos + langCountHeight + screenHeight * SCORE_GAP_Y;

    int scoreWidth = screenWidth * SCORE_WIDTH;
    int scoreHeight = screenHeight * SCORE_HEIGHT;

    int enterY = screenHeight * SCORE_ENTER_Y;

    DrawRectangle(
        scoreXPos,
        scoreYPos,
        scoreWidth,
        scoreHeight,
        SCORE_BACKGROUND_COLOR
    );

    int textXPos = scoreXPos + 30;
    int textXRightPos = scoreXPos + scoreWidth - 30;

    int textYPos = scoreYPos + 20;

    int scoreFontSize = screenHeight * SCORE_SCORE_FONT_SIZE;
    int scoreSpacing = screenHeight * SCORE_SCORE_SPACING;

    DrawOutline(
        fonts,
        FONT_EXTRA_BOLD,
        "Score",
        textXPos,
        textYPos,
        2,
        scoreSpacing,
        scoreFontSize,
        SCORE_SCORE_OUTLINE_COLOR
    );

    DrawString(
        fonts,
        FONT_EXTRA_BOLD,
        "Score",
        textXPos,
        textYPos,
        scoreSpacing,
        scoreFontSize,
        SCORE_SCORE_COLOR
    );

    DrawOutlineAtRight(
        fonts,
        FONT_EXTRA_BOLD,
        TextFormat("%d", score->score),
        textXRightPos,
        textYPos,
        2,
        scoreSpacing,
        scoreFontSize,
        SCORE_NUMBER_OUTLINE_COLOR
    );

    DrawStringAtRight(
        fonts,
        FONT_EXTRA_BOLD,
        TextFormat("%d", score->score),
        textXRightPos,
        textYPos,
        scoreSpacing,
        scoreFontSize,
        SCORE_NUMBER_COLOR
    );

    int comboFontSize = screenHeight * SCORE_COMBO_FONT_SIZE;
    int comboSpacing = screenHeight * SCORE_COMBO_SPACING;

    textYPos += scoreFontSize + enterY;

    DrawOutline(
        fonts,
        FONT_EXTRA_BOLD,
        "Combo",
        textXPos,
        textYPos,
        2,
        comboSpacing,
        comboFontSize,
        SCORE_COMBO_OUTLINE_COLOR
    );

    DrawString(
        fonts,
        FONT_EXTRA_BOLD,
        "Combo",
        textXPos,
        textYPos,
        comboSpacing,
        comboFontSize,
        SCORE_COMBO_COLOR
    );

    DrawOutlineAtRight(
        fonts,
        FONT_EXTRA_BOLD,
        TextFormat("%d", score->currentCombo),
        textXRightPos,
        textYPos,
        2,
        comboSpacing,
        comboFontSize,
        SCORE_NUMBER_OUTLINE_COLOR
    );

    DrawStringAtRight(
        fonts,
        FONT_EXTRA_BOLD,
        TextFormat("%d", score->currentCombo),
        textXRightPos,
        textYPos,
        comboSpacing,
        comboFontSize,
        SCORE_NUMBER_COLOR
    );

    int maxComboFontSize = screenHeight * SCORE_MAXCOMBO_FONT_SIZE;
    int maxComboSpacing = screenHeight * SCORE_MAXCOMBO_SPACING;

    textYPos += comboFontSize + enterY;

    DrawOutline(
        fonts,
        FONT_EXTRA_BOLD,
        "Max Combo",
        textXPos,
        textYPos,
        2,
        maxComboSpacing,
        maxComboFontSize,
        SCORE_MAXCOMBO_OUTLINE_COLOR
    );

    DrawString(
        fonts,
        FONT_EXTRA_BOLD,
        "Max Combo",
        textXPos,
        textYPos,
        maxComboSpacing,
        maxComboFontSize,
        SCORE_MAXCOMBO_COLOR
    );

    DrawOutlineAtRight(
        fonts,
        FONT_EXTRA_BOLD,
        TextFormat("%d", score->maxCombo),
        textXRightPos,
        textYPos,
        2,
        maxComboSpacing,
        maxComboFontSize,
        SCORE_NUMBER_OUTLINE_COLOR
    );

    DrawStringAtRight(
        fonts,
        FONT_EXTRA_BOLD,
        TextFormat("%d", score->maxCombo),
        textXRightPos,
        textYPos,
        maxComboSpacing,
        maxComboFontSize,
        SCORE_NUMBER_COLOR
    );

    int accFontSize = screenHeight * SCORE_ACC_FONT_SIZE;
    int accSpacing = screenHeight * SCORE_ACC_SPACING;

    textYPos += maxComboFontSize + enterY;

    DrawOutline(
        fonts,
        FONT_EXTRA_BOLD,
        "Accuracy",
        textXPos,
        textYPos,
        2,
        accSpacing,
        accFontSize,
        SCORE_ACC_OUTLINE_COLOR
    );

    DrawString(
        fonts,
        FONT_EXTRA_BOLD,
        "Accuracy",
        textXPos,
        textYPos,
        accSpacing,
        accFontSize,
        SCORE_ACC_COLOR
    );

    float accuracy = 0.0f;
    if (score->totalLoss > 0.0f) {
        accuracy = ((score->totalLoss - score->userLoss) / score->totalLoss) * 100.0f;
        if (accuracy < 0.0f) {
            accuracy = 0.0f;
        } else if (accuracy > 100.0f) {
            accuracy = 100.0f;
        }
    }

    DrawOutlineAtRight(
        fonts,
        FONT_EXTRA_BOLD,
        TextFormat("%.2f%%", accuracy),
        textXRightPos,
        textYPos,
        2,
        accSpacing,
        accFontSize,
        SCORE_NUMBER_OUTLINE_COLOR
    );

    DrawStringAtRight(
        fonts,
        FONT_EXTRA_BOLD,
        TextFormat("%.2f%%", accuracy),
        textXRightPos,
        textYPos,
        accSpacing,
        accFontSize,
        SCORE_NUMBER_COLOR
    );

    int tlFontSize = screenHeight * SCORE_TL_FONT_SIZE;
    int tlSpacing = screenHeight * SCORE_TL_SPACING;

    textYPos += accFontSize + enterY;

    DrawOutline(
        fonts,
        FONT_EXTRA_BOLD,
        "Total Loss",
        textXPos,
        textYPos,
        2,
        tlSpacing,
        tlFontSize,
        SCORE_TL_OUTLINE_COLOR
    );

    DrawString(
        fonts,
        FONT_EXTRA_BOLD,
        "Total Loss",
        textXPos,
        textYPos,
        tlSpacing,
        tlFontSize,
        SCORE_TL_COLOR
    );

    DrawOutlineAtRight(
        fonts,
        FONT_EXTRA_BOLD,
        TextFormat("%dms", (int)(score->userLoss * 1000.0f)),
        textXRightPos,
        textYPos,
        2,
        tlSpacing,
        tlFontSize,
        SCORE_NUMBER_OUTLINE_COLOR
    );

    DrawStringAtRight(
        fonts,
        FONT_EXTRA_BOLD,
        TextFormat("%dms", (int)(score->userLoss * 1000.0f)),
        textXRightPos,
        textYPos,
        tlSpacing,
        tlFontSize,
        SCORE_NUMBER_COLOR
    );
    
    return 0;
}

int ScoreRenderAtLane(Score* score, Fonts* fonts, int laneCount, float elapsed) {
    if (!score) {
        return -1;
    }

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    int lineWidth = screenWidth * LANE_WIDTH;
    int noteWidth = screenWidth * NOTE_WIDTH;

    int infoXPos = screenWidth * INFO_GAP;
    int infoWidth = screenWidth * INFO_WIDTH;

    int fieldXPos = lineWidth + infoWidth + infoXPos * 2;

    int scoreXPos = fieldXPos + noteWidth * laneCount / 2;
    int scoreYPos = screenHeight - screenHeight * SCORE_SHOW_Y;

    float timeDiff = elapsed - score->lastElapsed;

    int showFontSize = screenHeight * SCORE_SHOW_FONT_SIZE;
    int showSpacing = screenHeight * SCORE_SHOW_SPACING;

    if (timeDiff >= 0.0f && timeDiff <= 1.0f) {
        float absLossSecond = fabsf(score->lastLossSecond);

        if (absLossSecond > VERDICT_IGNORE_SECONDS) {
            DrawOutlineAtCenter(
                fonts,
                FONT_EXTRA_BOLD,
                "miss",
                scoreXPos,
                scoreYPos,
                2,
                showSpacing,
                showFontSize,
                SCORE_SHOW_OUTLINE_COLOR
            );

            DrawStringAtCenter(
                fonts,
                FONT_EXTRA_BOLD,
                "miss",
                scoreXPos,
                scoreYPos,
                showSpacing,
                showFontSize,
                SCORE_SHOW_COLOR
            );
            return 0;
        }

        if (score->lastLossSecond < -0.0001f && (int)(absLossSecond * 1000.0f) != 0) {
            DrawOutlineAtCenter(
                fonts,
                FONT_EXTRA_BOLD,
                TextFormat("+%dms", (int)(absLossSecond * 1000.0f)),
                scoreXPos,
                scoreYPos,
                2,
                showSpacing,
                showFontSize,
                SCORE_SHOW_OUTLINE_COLOR
            );

            DrawStringAtCenter(
                fonts,
                FONT_EXTRA_BOLD,
                TextFormat("+%dms", (int)(absLossSecond * 1000.0f)),
                scoreXPos,
                scoreYPos,
                showSpacing,
                showFontSize,
                SCORE_SHOW_COLOR
            );
        } else if (score->lastLossSecond > 0.0001f && (int)(absLossSecond * 1000.0f) != 0) {
            DrawOutlineAtCenter(
                fonts,
                FONT_EXTRA_BOLD,
                TextFormat("-%dms", (int)(absLossSecond * 1000.0f)),
                scoreXPos,
                scoreYPos,
                2,
                showSpacing,
                showFontSize,
                SCORE_SHOW_OUTLINE_COLOR
            );

            DrawStringAtCenter(
                fonts,
                FONT_EXTRA_BOLD,
                TextFormat("-%dms", (int)(absLossSecond * 1000.0f)),
                scoreXPos,
                scoreYPos,
                showSpacing,
                showFontSize,
                SCORE_SHOW_COLOR
            );
        } else {
            DrawOutlineAtCenter(
                fonts,
                FONT_EXTRA_BOLD,
                "0ms",
                scoreXPos,
                scoreYPos,
                2,
                showSpacing,
                showFontSize,
                SCORE_SHOW_OUTLINE_COLOR
            );

            DrawStringAtCenter(
                fonts,
                FONT_EXTRA_BOLD,
                "0ms",
                scoreXPos,
                scoreYPos,
                showSpacing,
                showFontSize,
                SCORE_SHOW_COLOR
            );
        }
    }

    return 0;
}
