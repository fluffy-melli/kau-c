#include "layout/lane.h"

#include <raylib.h>
#include "constant/info.h"
#include "constant/lane.h"

void LaneLineRender(int laneCount) {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    float lineWidth = (float) screenWidth * LANE_LINE_WIDTH;

    float noteWidth = (float) screenWidth * LANE_NOTE_WIDTH;
    float noteHeight = (float) screenHeight * LANE_NOTE_HEIGHT;

    float infoXPos = (float) screenWidth * INFO_GAP;
    float infoWidth = (float) screenWidth * INFO_WIDTH;

    float fieldWidth = (float) noteWidth * laneCount;
    float fieldXPos = infoWidth + infoXPos * 2 + lineWidth;

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

    float infoXPos = (float) screenWidth * INFO_GAP;
    float infoWidth = (float) screenWidth * INFO_WIDTH;

    float fieldXPos = infoWidth + infoXPos * 2;

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
        case 5:
            if (IsKeyDown(LANE_5K_1)) {
                DrawRectangle(
                    (int) fieldXPos,
                    0,
                    (int) noteWidth,
                    screenHeight,
                    LANE_KEY_PRESS_COLOR
                );
            }

            if (IsKeyDown(LANE_5K_2)) {
                DrawRectangle(
                    (int) fieldXPos + noteWidth,
                    0,
                    (int) noteWidth,
                    screenHeight,
                    LANE_KEY_PRESS_COLOR
                );
            }

            if (IsKeyDown(LANE_5K_3)) {
                DrawRectangle(
                    (int) fieldXPos + noteWidth * 2,
                    0,
                    (int) noteWidth,
                    screenHeight,
                    LANE_KEY_PRESS_COLOR
                );
            } else if (IsKeyDown(LANE_5K_4)) {
                DrawRectangle(
                    (int) fieldXPos + noteWidth * 2,
                    0,
                    (int) noteWidth,
                    screenHeight,
                    LANE_KEY_PRESS_COLOR
                );
            }

            if (IsKeyDown(LANE_5K_5)) {
                DrawRectangle(
                    (int) fieldXPos + noteWidth * 3,
                    0,
                    (int) noteWidth,
                    screenHeight,
                    LANE_KEY_PRESS_COLOR
                );
            }

            if (IsKeyDown(LANE_5K_6)) {
                DrawRectangle(
                    (int) fieldXPos + noteWidth * 4,
                    0,
                    (int) noteWidth,
                    screenHeight,
                    LANE_KEY_PRESS_COLOR
                );
            }

            break;
        case 6:
            if (IsKeyDown(LANE_6K_1)) {
                DrawRectangle(
                    (int) fieldXPos,
                    0,
                    (int) noteWidth,
                    screenHeight,
                    LANE_KEY_PRESS_COLOR
                );
            }

            if (IsKeyDown(LANE_6K_2)) {
                DrawRectangle(
                    (int) fieldXPos + noteWidth,
                    0,
                    (int) noteWidth,
                    screenHeight,
                    LANE_KEY_PRESS_COLOR
                );
            }

            if (IsKeyDown(LANE_6K_3)) {
                DrawRectangle(
                    (int) fieldXPos + noteWidth * 2,
                    0,
                    (int) noteWidth,
                    screenHeight,
                    LANE_KEY_PRESS_COLOR
                );
            }

            if (IsKeyDown(LANE_6K_4)) {
                DrawRectangle(
                    (int) fieldXPos + noteWidth * 3,
                    0,
                    (int) noteWidth,
                    screenHeight,
                    LANE_KEY_PRESS_COLOR
                );
            }

            if (IsKeyDown(LANE_6K_5)) {
                DrawRectangle(
                    (int) fieldXPos + noteWidth * 4,
                    0,
                    (int) noteWidth,
                    screenHeight,
                    LANE_KEY_PRESS_COLOR
                );
            }

            if (IsKeyDown(LANE_6K_6)) {
                DrawRectangle(
                    (int) fieldXPos + noteWidth * 5,
                    0,
                    (int) noteWidth,
                    screenHeight,
                    LANE_KEY_PRESS_COLOR
                );
            }

            break;
    }
}
