#include "layout/note.h"

#include <math.h>
#include <stdlib.h>
#include <raylib.h>
#include "constant/note.h"
#include "constant/info.h"
#include "constant/lane.h"
#include "constant/verdict.h"

float ShortNoteGetYPos(ShortNote* note, int judgmentY, float elapsed, float dropSpeedSeconds) {
    if (!note) {
        return -1;
    }

    if (elapsed < note->arrival_seconds - dropSpeedSeconds) {
        return -1;
    }

    float dropProgress = (elapsed - (note->arrival_seconds - dropSpeedSeconds)) / dropSpeedSeconds;

    float yPos = dropProgress * judgmentY;

    return yPos;
}

int ShortNoteListRender(ShortNoteList* list, Score* score, int laneCount, float elapsed) {
    if (!list) {
        return -1;
    }

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    int lineWidth = screenWidth * LANE_WIDTH;

    int noteWidth = screenWidth * NOTE_WIDTH;
    int noteHeight = screenHeight * NOTE_HEIGHT;

    int judgmentYPos = screenHeight - (screenHeight * LANE_JUDGEMENT_Y);

    int infoXPos = screenWidth * INFO_GAP;
    int infoWidth = screenWidth * INFO_WIDTH;

    int fieldXPos = infoWidth + infoXPos * 2 + lineWidth;

    for (int i = 0; i < list->length; i++) {
        ShortNote* note = &list->notes[i];

        float yPos = ShortNoteGetYPos(note, judgmentYPos, elapsed, DROP_SPEED_SECONDS);
        if (yPos < 0) {
            continue;
        }

        if (yPos > screenHeight) {
            score->totalLoss += VERDICT_IGNORE_SECONDS;
            score->userLoss += VERDICT_IGNORE_SECONDS;
            score->lastElapsed = elapsed;
            score->lastLossSecond = VERDICT_IGNORE_SECONDS + 9999.0f;
            score->currentCombo = 0;
            ShortNoteListRemove(list, i);
            i--;
            continue;
        }

        int laneXPos = fieldXPos + noteWidth * note->lane;

        switch (laneCount) {
            case 4:
                if (note->lane == 1 || note->lane == 2) {
                    DrawRectangle(
                        laneXPos,
                        yPos,
                        noteWidth,
                        noteHeight,
                        NOTE_4K_INNER_COLOR
                    );
                } else {
                    DrawRectangle(
                        laneXPos,
                        yPos,
                        noteWidth,
                        noteHeight,
                        NOTE_4K_OUTER_COLOR
                    );
                }
                break;
            case 5:
                if (note->lane == 2) {
                    DrawRectangle(
                        laneXPos,
                        yPos,
                        noteWidth,
                        noteHeight,
                        NOTE_5K_MIDEL_COLOR
                    );
                } else if (note->lane == 1 || note->lane == 3) {
                    DrawRectangle(
                        laneXPos,
                        yPos,
                        noteWidth,
                        noteHeight,
                        NOTE_5K_INNER_COLOR
                    );
                } else {
                    DrawRectangle(
                        laneXPos,
                        yPos,
                        noteWidth,
                        noteHeight,
                        NOTE_5K_OUTER_COLOR
                    );
                }
                break;
            case 6:
                if (note->lane == 2 || note->lane == 3) {
                    DrawRectangle(
                        laneXPos,
                        yPos,
                        noteWidth,
                        noteHeight,
                        NOTE_6K_MIDEL_COLOR
                    );
                } else if (note->lane == 1 || note->lane == 4) {
                    DrawRectangle(
                        laneXPos,
                        yPos,
                        noteWidth,
                        noteHeight,
                        NOTE_6K_INNER_COLOR
                    );
                } else {
                    DrawRectangle(
                        laneXPos,
                        yPos,
                        noteWidth,
                        noteHeight,
                        NOTE_6K_OUTER_COLOR
                    );
                }
                break;
            default:
                DrawRectangle(
                    laneXPos,
                    yPos,
                    noteWidth,
                    noteHeight,
                    WHITE
                );
        }
    }

    return 0;
}

int ShortNoteListKeyPressRender(ShortNoteList* list, Score* score, int laneCount, float elapsed) {
    if (!list) {
        return -1;
    }

    for (int i = 0; i < list->length; i++) {
        ShortNote* note = &list->notes[i];
        
        int pressKey;
        
        switch (laneCount) {
            case 4:
                if (note->lane == 0) {
                    pressKey = IsKeyPressed(LANE_4K_1);
                } else if (note->lane == 1) {
                    pressKey = IsKeyPressed(LANE_4K_2);
                } else if (note->lane == 2) {
                    pressKey = IsKeyPressed(LANE_4K_3);
                } else if (note->lane == 3) {
                    pressKey = IsKeyPressed(LANE_4K_4);
                } else {
                    pressKey = 0;
                }
                break;
            case 5:
                if (note->lane == 0) {
                    pressKey = IsKeyPressed(LANE_5K_1);
                } else if (note->lane == 1) {
                    pressKey = IsKeyPressed(LANE_5K_2);
                } else if (note->lane == 2) {
                    pressKey = IsKeyPressed(LANE_5K_3) || IsKeyPressed(LANE_5K_4);
                } else if (note->lane == 3) {
                    pressKey = IsKeyPressed(LANE_5K_5);
                } else if (note->lane == 4) {
                    pressKey = IsKeyPressed(LANE_5K_6);
                } else {
                    pressKey = 0;
                }
                break;
            case 6:
                if (note->lane == 0) {
                    pressKey = IsKeyPressed(LANE_6K_1);
                } else if (note->lane == 1) {
                    pressKey = IsKeyPressed(LANE_6K_2);
                } else if (note->lane == 2) {
                    pressKey = IsKeyPressed(LANE_6K_3);
                } else if (note->lane == 3) {
                    pressKey = IsKeyPressed(LANE_6K_4);
                } else if (note->lane == 4) {
                    pressKey = IsKeyPressed(LANE_6K_5);
                } else if (note->lane == 5) {
                    pressKey = IsKeyPressed(LANE_6K_6);
                } else {
                    pressKey = 0;
                }
                break;
            default:
                pressKey = 0;
                break;
        }

        if (!pressKey) {
            continue;
        }

        float time = elapsed - note->arrival_seconds;

        if (fabsf(time) > VERDICT_IGNORE_SECONDS) {
            continue;
        }

        if (fabsf(time) <= VERDICT_COMBO_SECONDS) {
            score->currentCombo++;
            if (score->currentCombo > score->maxCombo) {
                score->maxCombo = score->currentCombo;
            }
        } else {
            score->currentCombo = 0;
        }

        ShortNoteListRemove(list, i);
        i--;

        score->lastElapsed = elapsed;
        score->lastLossSecond = time;

        score->totalLoss += VERDICT_IGNORE_SECONDS;
        score->userLoss += fabsf(time);

        score->score += (int) ((VERDICT_IGNORE_SECONDS - fabsf(time)) * 1000.0f) / DROP_SPEED_SECONDS;
    }

    return 0;
}
