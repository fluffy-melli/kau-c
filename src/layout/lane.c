#include "layout/lane.h"

#include <raylib.h>
#include "constant/info.h"
#include "constant/lane.h"
#include "constant/note.h"

void LaneLineRender(int laneCount) {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    int lineWidth = screenWidth * LANE_WIDTH;

    int noteWidth = screenWidth * NOTE_WIDTH;
    int noteHeight = screenHeight * NOTE_HEIGHT;

    int infoXPos = screenWidth * INFO_GAP;
    int infoWidth = screenWidth * INFO_WIDTH;

    int fieldWidth = noteWidth * laneCount;
    int fieldXPos = infoWidth + infoXPos * 2 + lineWidth;

    int judgmentYPos = screenHeight - (screenHeight * LANE_JUDGEMENT_Y);

    DrawRectangle(
        fieldXPos,
        0,
        fieldWidth,
        judgmentYPos - noteHeight / 2,
        LANE_BACKGROUND_COLOR
    );

    DrawRectangle(
        fieldXPos,
        judgmentYPos - noteHeight / 2,
        fieldWidth,
        noteHeight,
        LANE_JUDGEMENT_COLOR
    );

    DrawRectangle(
        fieldXPos,
        judgmentYPos + noteHeight / 2,
        fieldWidth,
        screenHeight,
        LANE_BACKGROUND_COLOR
    );

    DrawRectangle(
        fieldXPos - lineWidth,
        0,
        lineWidth,
        screenHeight,
        LANE_LINE_COLOR
    );

    DrawRectangle(
        fieldXPos + fieldWidth,
        0,
        lineWidth,
        screenHeight,
        LANE_LINE_COLOR
    );
}

void LaneKeyPressRender(int laneCount) {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    int lineWidth = screenWidth * LANE_WIDTH;
    int noteWidth = screenWidth * NOTE_WIDTH;

    int infoXPos = screenWidth * INFO_GAP;
    int infoWidth = screenWidth * INFO_WIDTH;

    int fieldXPos = lineWidth + infoWidth + infoXPos * 2;

    switch (laneCount) {
        case 4:
            if (IsKeyDown(LANE_4K_1)) {
                DrawRectangle(
                    fieldXPos,
                    0,
                    noteWidth,
                    screenHeight,
                    LANE_KEY_PRESS_COLOR
                );
            }

            if (IsKeyDown(LANE_4K_2)) {
                DrawRectangle(
                    fieldXPos + noteWidth,
                    0,
                    noteWidth,
                    screenHeight,
                    LANE_KEY_PRESS_COLOR
                );
            }

            if (IsKeyDown(LANE_4K_3)) {
                DrawRectangle(
                    fieldXPos + noteWidth * 2,
                    0,
                    noteWidth,
                    screenHeight,
                    LANE_KEY_PRESS_COLOR
                );
            }

            if (IsKeyDown(LANE_4K_4)) {
                DrawRectangle(
                    fieldXPos + noteWidth * 3,
                    0,
                    noteWidth,
                    screenHeight,
                    LANE_KEY_PRESS_COLOR
                );
            }
            
            break;
        case 5:
            if (IsKeyDown(LANE_5K_1)) {
                DrawRectangle(
                    fieldXPos,
                    0,
                    noteWidth,
                    screenHeight,
                    LANE_KEY_PRESS_COLOR
                );
            }

            if (IsKeyDown(LANE_5K_2)) {
                DrawRectangle(
                    fieldXPos + noteWidth,
                    0,
                    noteWidth,
                    screenHeight,
                    LANE_KEY_PRESS_COLOR
                );
            }

            if (IsKeyDown(LANE_5K_3)) {
                DrawRectangle(
                    fieldXPos + noteWidth * 2,
                    0,
                    noteWidth,
                    screenHeight,
                    LANE_KEY_PRESS_COLOR
                );
            } else if (IsKeyDown(LANE_5K_4)) {
                DrawRectangle(
                    fieldXPos + noteWidth * 2,
                    0,
                    noteWidth,
                    screenHeight,
                    LANE_KEY_PRESS_COLOR
                );
            }

            if (IsKeyDown(LANE_5K_5)) {
                DrawRectangle(
                    fieldXPos + noteWidth * 3,
                    0,
                    noteWidth,
                    screenHeight,
                    LANE_KEY_PRESS_COLOR
                );
            }

            if (IsKeyDown(LANE_5K_6)) {
                DrawRectangle(
                    fieldXPos + noteWidth * 4,
                    0,
                    noteWidth,
                    screenHeight,
                    LANE_KEY_PRESS_COLOR
                );
            }

            break;
        case 6:
            if (IsKeyDown(LANE_6K_1)) {
                DrawRectangle(
                    fieldXPos,
                    0,
                    noteWidth,
                    screenHeight,
                    LANE_KEY_PRESS_COLOR
                );
            }

            if (IsKeyDown(LANE_6K_2)) {
                DrawRectangle(
                    fieldXPos + noteWidth,
                    0,
                    noteWidth,
                    screenHeight,
                    LANE_KEY_PRESS_COLOR
                );
            }

            if (IsKeyDown(LANE_6K_3)) {
                DrawRectangle(
                    fieldXPos + noteWidth * 2,
                    0,
                    noteWidth,
                    screenHeight,
                    LANE_KEY_PRESS_COLOR
                );
            }

            if (IsKeyDown(LANE_6K_4)) {
                DrawRectangle(
                    fieldXPos + noteWidth * 3,
                    0,
                    noteWidth,
                    screenHeight,
                    LANE_KEY_PRESS_COLOR
                );
            }

            if (IsKeyDown(LANE_6K_5)) {
                DrawRectangle(
                    fieldXPos + noteWidth * 4,
                    0,
                    noteWidth,
                    screenHeight,
                    LANE_KEY_PRESS_COLOR
                );
            }

            if (IsKeyDown(LANE_6K_6)) {
                DrawRectangle(
                    fieldXPos + noteWidth * 5,
                    0,
                    noteWidth,
                    screenHeight,
                    LANE_KEY_PRESS_COLOR
                );
            }

            break;
    }
}
