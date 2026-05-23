#include "layout/score.h"

#include <stdlib.h>
#include "layout/string.h"
#include "constant/info.h"
#include "constant/score.h"

Score* NewScore() {
    Score* score = malloc(sizeof(Score));
    if (!score) {
        return NULL;
    }

    score->perfect = 0;
    score->great = 0;
    score->good = 0;
    score->bad = 0;
    score->miss = 0;

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

    int perfectFontSize = screenHeight * SCORE_PERFECT_FONT_SIZE;
    int perfectSpacing = screenHeight * SCORE_PERFECT_SPACING;

    int textXPos = scoreXPos + 30;
    int textXRightPos = scoreXPos + scoreWidth - 30;

    int textYPos = scoreYPos + 20;

    DrawOutline(
        fonts,
        FONT_EXTRA_BOLD,
        "PERFECT",
        textXPos,
        textYPos,
        2,
        perfectSpacing,
        perfectFontSize,
        SCORE_PERFECT_OUTLINE_COLOR
    );

    DrawString(
        fonts,
        FONT_EXTRA_BOLD,
        "PERFECT",
        textXPos,
        textYPos,
        perfectSpacing,
        perfectFontSize,
        SCORE_PERFECT_COLOR
    );

    DrawOutlineAtRight(
        fonts,
        FONT_EXTRA_BOLD,
        TextFormat("%d", score->perfect),
        textXRightPos,
        textYPos,
        2,
        perfectSpacing,
        perfectFontSize,
        SCORE_NUMBER_OUTLINE_COLOR
    );

    DrawStringAtRight(
        fonts,
        FONT_EXTRA_BOLD,
        TextFormat("%d", score->perfect),
        textXRightPos,
        textYPos,
        perfectSpacing,
        perfectFontSize,
        SCORE_NUMBER_COLOR
    );

    int greatFontSize = screenHeight * SCORE_GREAT_FONT_SIZE;
    int greatSpacing = screenHeight * SCORE_GREAT_SPACING;

    textYPos += perfectFontSize + perfectSpacing + enterY;

    DrawOutline(
        fonts,
        FONT_EXTRA_BOLD,
        "GREAT",
        textXPos,
        textYPos,
        2,
        greatSpacing,
        greatFontSize,
        SCORE_GREAT_OUTLINE_COLOR
    );

    DrawString(
        fonts,
        FONT_EXTRA_BOLD,
        "GREAT",
        textXPos,
        textYPos,
        greatSpacing,
        greatFontSize,
        SCORE_GREAT_COLOR
    );

    DrawOutlineAtRight(
        fonts,
        FONT_EXTRA_BOLD,
        TextFormat("%d", score->great),
        textXRightPos,
        textYPos,
        2,
        greatSpacing,
        greatFontSize,
        SCORE_NUMBER_OUTLINE_COLOR
    );

    DrawStringAtRight(
        fonts,
        FONT_EXTRA_BOLD,
        TextFormat("%d", score->great),
        textXRightPos,
        textYPos,
        greatSpacing,
        greatFontSize,
        SCORE_NUMBER_COLOR
    );

    int goodFontSize = screenHeight * SCORE_GOOD_FONT_SIZE;
    int goodSpacing = screenHeight * SCORE_GOOD_SPACING;

    textYPos += greatFontSize + greatSpacing + enterY;

    DrawOutline(
        fonts,
        FONT_EXTRA_BOLD,
        "GOOD",
        textXPos,
        textYPos,
        2,
        goodSpacing,
        goodFontSize,
        SCORE_GOOD_OUTLINE_COLOR
    );

    DrawString(
        fonts,
        FONT_EXTRA_BOLD,
        "GOOD",
        textXPos,
        textYPos,
        goodSpacing,
        goodFontSize,
        SCORE_GOOD_COLOR
    );

    DrawOutlineAtRight(
        fonts,
        FONT_EXTRA_BOLD,
        TextFormat("%d", score->good),
        textXRightPos,
        textYPos,
        2,
        goodSpacing,
        goodFontSize,
        SCORE_NUMBER_OUTLINE_COLOR
    );

    DrawStringAtRight(
        fonts,
        FONT_EXTRA_BOLD,
        TextFormat("%d", score->good),
        textXRightPos,
        textYPos,
        goodSpacing,
        goodFontSize,
        SCORE_NUMBER_COLOR
    );

    int badFontSize = screenHeight * SCORE_BAD_FONT_SIZE;
    int badSpacing = screenHeight * SCORE_BAD_SPACING;

    textYPos += goodFontSize + goodSpacing + enterY;

    DrawOutline(
        fonts,
        FONT_EXTRA_BOLD,
        "BAD",
        textXPos,
        textYPos,
        2,
        badSpacing,
        badFontSize,
        SCORE_BAD_OUTLINE_COLOR
    );

    DrawString(
        fonts,
        FONT_EXTRA_BOLD,
        "BAD",
        textXPos,
        textYPos,
        badSpacing,
        badFontSize,
        SCORE_BAD_COLOR
    );

    DrawOutlineAtRight(
        fonts,
        FONT_EXTRA_BOLD,
        TextFormat("%d", score->bad),
        textXRightPos,
        textYPos,
        2,
        badSpacing,
        badFontSize,
        SCORE_NUMBER_OUTLINE_COLOR
    );

    DrawStringAtRight(
        fonts,
        FONT_EXTRA_BOLD,
        TextFormat("%d", score->bad),
        textXRightPos,
        textYPos,
        badSpacing,
        badFontSize,
        SCORE_NUMBER_COLOR
    );

    int missFontSize = screenHeight * SCORE_MISS_FONT_SIZE;
    int missSpacing = screenHeight * SCORE_MISS_SPACING;

    textYPos += badFontSize + badSpacing + enterY;

    DrawOutline(
        fonts,
        FONT_EXTRA_BOLD,
        "MISS",
        textXPos,
        textYPos,
        2,
        missSpacing,
        missFontSize,
        SCORE_MISS_OUTLINE_COLOR
    );

    DrawString(
        fonts,
        FONT_EXTRA_BOLD,
        "MISS",
        textXPos,
        textYPos,
        missSpacing,
        missFontSize,
        SCORE_MISS_COLOR
    );

    DrawOutlineAtRight(
        fonts,
        FONT_EXTRA_BOLD,
        TextFormat("%d", score->miss),
        textXRightPos,
        textYPos,
        2,
        missSpacing,
        missFontSize,
        SCORE_NUMBER_OUTLINE_COLOR
    );

    DrawStringAtRight(
        fonts,
        FONT_EXTRA_BOLD,
        TextFormat("%d", score->miss),
        textXRightPos,
        textYPos,
        missSpacing,
        missFontSize,
        SCORE_NUMBER_COLOR
    );
    
    return 0;
}
