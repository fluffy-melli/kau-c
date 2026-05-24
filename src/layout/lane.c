#include "layout/lane.h"

#include <raylib.h>
#include "constant/info.h"
#include "constant/lane.h"
#include "constant/note.h"
#include "config/config.h"

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

void LaneKeyPressRender(ConfigInfoJSON *config, int laneCount) {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    int lineWidth = screenWidth * LANE_WIDTH;
    int noteWidth = screenWidth * NOTE_WIDTH;

    int infoXPos = screenWidth * INFO_GAP;
    int infoWidth = screenWidth * INFO_WIDTH;

    int fieldXPos = lineWidth + infoWidth + infoXPos * 2;

    switch (laneCount) {
        case 4:
            if (ConfigInfoIsDown(config, laneCount, 0)) {
                DrawRectangle(
                    fieldXPos,
                    0,
                    noteWidth,
                    screenHeight,
                    LANE_KEY_PRESS_COLOR
                );
            }

            if (ConfigInfoIsDown(config, laneCount, 1)) {
                DrawRectangle(
                    fieldXPos + noteWidth,
                    0,
                    noteWidth,
                    screenHeight,
                    LANE_KEY_PRESS_COLOR
                );
            }

            if (ConfigInfoIsDown(config, laneCount, 2)) {
                DrawRectangle(
                    fieldXPos + noteWidth * 2,
                    0,
                    noteWidth,
                    screenHeight,
                    LANE_KEY_PRESS_COLOR
                );
            }

            if (ConfigInfoIsDown(config, laneCount, 3)) {
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
            if (ConfigInfoIsDown(config, laneCount, 0)) {
                DrawRectangle(
                    fieldXPos,
                    0,
                    noteWidth,
                    screenHeight,
                    LANE_KEY_PRESS_COLOR
                );
            }

            if (ConfigInfoIsDown(config, laneCount, 1)) {
                DrawRectangle(
                    fieldXPos + noteWidth,
                    0,
                    noteWidth,
                    screenHeight,
                    LANE_KEY_PRESS_COLOR
                );
            }

            if (ConfigInfoIsDown(config, laneCount, 2)) {
                DrawRectangle(
                    fieldXPos + noteWidth * 2,
                    0,
                    noteWidth,
                    screenHeight,
                    LANE_KEY_PRESS_COLOR
                );
            }

            if (ConfigInfoIsDown(config, laneCount, 3)) {
                DrawRectangle(
                    fieldXPos + noteWidth * 3,
                    0,
                    noteWidth,
                    screenHeight,
                    LANE_KEY_PRESS_COLOR
                );
            }

            if (ConfigInfoIsDown(config, laneCount, 4)) {
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
            if (ConfigInfoIsDown(config, laneCount, 0)) {
                DrawRectangle(
                    fieldXPos,
                    0,
                    noteWidth,
                    screenHeight,
                    LANE_KEY_PRESS_COLOR
                );
            }

            if (ConfigInfoIsDown(config, laneCount, 1)) {
                DrawRectangle(
                    fieldXPos + noteWidth,
                    0,
                    noteWidth,
                    screenHeight,
                    LANE_KEY_PRESS_COLOR
                );
            }

            if (ConfigInfoIsDown(config, laneCount, 2)) {
                DrawRectangle(
                    fieldXPos + noteWidth * 2,
                    0,
                    noteWidth,
                    screenHeight,
                    LANE_KEY_PRESS_COLOR
                );
            }

            if (ConfigInfoIsDown(config, laneCount, 3)) {
                DrawRectangle(
                    fieldXPos + noteWidth * 3,
                    0,
                    noteWidth,
                    screenHeight,
                    LANE_KEY_PRESS_COLOR
                );
            }

            if (ConfigInfoIsDown(config, laneCount, 4)) {
                DrawRectangle(
                    fieldXPos + noteWidth * 4,
                    0,
                    noteWidth,
                    screenHeight,
                    LANE_KEY_PRESS_COLOR
                );
            }

            if (ConfigInfoIsDown(config, laneCount, 5)) {
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
