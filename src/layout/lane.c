#include "layout/lane.h"
#include "constant/lane.h"

#include <raylib.h>

void LaneLineRender(int laneCount) {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    float lineWidth = (float) screenWidth * LANE_LINE_WIDTH;

    float noteWidth = (float) screenWidth * LANE_NOTE_WIDTH;
    float noteHeight = (float) screenHeight * LANE_NOTE_HEIGHT;

    float fieldWidth = (float) noteWidth * laneCount;
    float fieldXPos = ((float) screenWidth - fieldWidth) * LANE_CENTER;

    float judgmentYPos = (float) screenHeight - ((float) screenHeight * LANE_JUDGEMENT_Y);

    DrawRectangle(
        (int) fieldXPos,
        0,
        (int) fieldWidth,
        (int) judgmentYPos - noteHeight / 2,
        LANE_BACKGROUND_COLOR
    );

    DrawRectangle(
        (int) fieldXPos,
        (int) judgmentYPos - noteHeight / 2,
        (int) fieldWidth,
        (int) noteHeight,
        LANE_JUDGEMENT_COLOR
    );

    DrawRectangle(
        (int) fieldXPos,
        (int) judgmentYPos + noteHeight / 2,
        (int) fieldWidth,
        (int) screenHeight,
        LANE_BACKGROUND_COLOR
    );

    DrawRectangle(
        (int) fieldXPos - lineWidth,
        0,
        (int) lineWidth,
        screenHeight,
        LANE_LINE_COLOR
    );

    DrawRectangle(
        (int) fieldXPos + fieldWidth,
        0,
        (int) lineWidth,
        screenHeight,
        LANE_LINE_COLOR
    );
}

void LaneKeyPressRender(int laneCount) {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    float noteWidth = (float) screenWidth * LANE_NOTE_WIDTH;

    float fieldWidth = (float) noteWidth * laneCount;
    float fieldXPos = ((float) screenWidth - fieldWidth) * LANE_CENTER;

    switch (laneCount) {
        case 4:
            if (IsKeyDown(LANE_4K_1)) {
                DrawRectangle(
                    (int) fieldXPos,
                    0,
                    (int) noteWidth,
                    screenHeight,
                    LANE_KEY_PRESS_COLOR
                );
            }

            if (IsKeyDown(LANE_4K_2)) {
                DrawRectangle(
                    (int) fieldXPos + noteWidth,
                    0,
                    (int) noteWidth,
                    screenHeight,
                    LANE_KEY_PRESS_COLOR
                );
            }

            if (IsKeyDown(LANE_4K_3)) {
                DrawRectangle(
                    (int) fieldXPos + noteWidth * 2,
                    0,
                    (int) noteWidth,
                    screenHeight,
                    LANE_KEY_PRESS_COLOR
                );
            }

            if (IsKeyDown(LANE_4K_4)) {
                DrawRectangle(
                    (int) fieldXPos + noteWidth * 3,
                    0,
                    (int) noteWidth,
                    screenHeight,
                    LANE_KEY_PRESS_COLOR
                );
            }
            break;
    }
}