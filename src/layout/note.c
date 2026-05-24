#include "layout/note.h"

#include <math.h>
#include <stdlib.h>
#include <raylib.h>
#include "constant/note.h"
#include "constant/info.h"
#include "constant/lane.h"
#include "constant/verdict.h"
#include "config/config.h"

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

int ShortNoteListRender(ShortNoteList* list, Score* score, ConfigInfoJSON *config, int laneCount, float elapsed) {
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

        float yPos = ShortNoteGetYPos(note, judgmentYPos, elapsed, ConfigInfoGetDropSpeed(config));
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

int ShortNoteListKeyPressRender(ShortNoteList* list, Score* score, ConfigInfoJSON *config, int laneCount, float elapsed) {
    if (!list) {
        return -1;
    }

    for (int i = 0; i < list->length; i++) {
        ShortNote* note = &list->notes[i];
        
        int pressKey = ConfigInfoIsPressed(config, laneCount, note->lane);

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

        score->score += (int) ((VERDICT_IGNORE_SECONDS - fabsf(time)) * 1000.0f) / ConfigInfoGetDropSpeed(config);
    }

    return 0;
}

float LongNoteGetYPos(float target_seconds, int judgmentY, float elapsed, float dropSpeedSeconds) {
    if (elapsed < target_seconds - dropSpeedSeconds) {
        return -1;
    }

    float dropProgress = (elapsed - (target_seconds - dropSpeedSeconds)) / dropSpeedSeconds;

    float yPos = dropProgress * judgmentY;

    return yPos;
}

static void GetNoteColors(int laneCount, int lane, Color* outNormalColor, Color* outTailColor) {
    switch (laneCount) {
        case 4:
            if (lane == 1 || lane == 2) {
                *outNormalColor = NOTE_4K_INNER_COLOR;
                *outTailColor = NOTE_4K_INNER_TAIL_COLOR;
            } else {
                *outNormalColor = NOTE_4K_OUTER_COLOR;
                *outTailColor = NOTE_4K_OUTER_TAIL_COLOR;
            }
            break;
        case 5:
            if (lane == 2) {
                *outNormalColor = NOTE_5K_MIDEL_COLOR;
                *outTailColor = NOTE_5K_MIDEL_TAIL_COLOR;
            } else if (lane == 1 || lane == 3) {
                *outNormalColor = NOTE_5K_INNER_COLOR;
                *outTailColor = NOTE_5K_INNER_TAIL_COLOR;
            } else {
                *outNormalColor = NOTE_5K_OUTER_COLOR;
                *outTailColor = NOTE_5K_OUTER_TAIL_COLOR;
            }
            break;
        case 6:
            if (lane == 2 || lane == 3) {
                *outNormalColor = NOTE_6K_MIDEL_COLOR;
                *outTailColor = NOTE_6K_MIDEL_TAIL_COLOR;
            } else if (lane == 1 || lane == 4) {
                *outNormalColor = NOTE_6K_INNER_COLOR;
                *outTailColor = NOTE_6K_INNER_TAIL_COLOR;
            } else {
                *outNormalColor = NOTE_6K_OUTER_COLOR;
                *outTailColor = NOTE_6K_OUTER_TAIL_COLOR;
            }
            break;
        default:
            *outNormalColor = WHITE;
            *outTailColor = (Color){ 255, 255, 255, 100 };
            break;
    }
}

int LongNoteListRender(LongNoteList* list, Score* score, ConfigInfoJSON *config, int laneCount, float elapsed) {
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
        LongNote* note = &list->notes[i];

        float headY = -1.0f;
        float tailY = -1.0f;

        if (note->isPressed) {
            headY = judgmentYPos - noteHeight / 2;
            tailY = LongNoteGetYPos(note->arrival_seconds + note->length_seconds, judgmentYPos, elapsed, ConfigInfoGetDropSpeed(config));
        } else {
            headY = LongNoteGetYPos(note->arrival_seconds, judgmentYPos, elapsed, ConfigInfoGetDropSpeed(config));
            tailY = LongNoteGetYPos(note->arrival_seconds + note->length_seconds, judgmentYPos, elapsed, ConfigInfoGetDropSpeed(config));
        }

        if (headY < 0 && tailY < 0) {
            continue;
        }

        int laneXPos = fieldXPos + noteWidth * note->lane;

        Color normalColor, tailColor;
        GetNoteColors(laneCount, note->lane, &normalColor, &tailColor);

        float clampedTailY = (tailY < 0) ? 0 : tailY;
        float bodyHeight = headY - clampedTailY;

        if (bodyHeight > 0) {
            DrawRectangle(
                laneXPos,
                clampedTailY,
                noteWidth,
                bodyHeight,
                tailColor
            );
        }

        if (headY >= 0 && headY <= screenHeight) {
            DrawRectangle(
                laneXPos,
                headY,
                noteWidth,
                noteHeight,
                normalColor
            );
        }
    }

    return 0;
}

int LongNoteListKeyPressRender(LongNoteList* list, Score* score, ConfigInfoJSON *config, int laneCount, float elapsed) {
    if (!list) {
        return -1;
    }

    for (int i = 0; i < list->length; i++) {
        LongNote* note = &list->notes[i];

        if (note->isPressed == 0) {
            if (elapsed > note->arrival_seconds + VERDICT_IGNORE_SECONDS) {
                score->totalLoss += VERDICT_IGNORE_SECONDS * 2;
                score->userLoss += VERDICT_IGNORE_SECONDS * 2;
                score->currentCombo = 0;
                score->lastElapsed = elapsed;
                score->lastLossSecond = VERDICT_IGNORE_SECONDS + 9999.0f;

                LongNoteListRemove(list, i);
                i--;
                continue;
            }

            int pressKey = ConfigInfoIsPressed(config, laneCount, note->lane);

            if (pressKey) {
                float time = elapsed - note->arrival_seconds;

                if (fabsf(time) <= VERDICT_IGNORE_SECONDS) {
                    note->isPressed = 1;

                    if (fabsf(time) <= VERDICT_COMBO_SECONDS) {
                        score->currentCombo++;
                        if (score->currentCombo > score->maxCombo) {
                            score->maxCombo = score->currentCombo;
                        }
                    } else {
                        score->currentCombo = 0;
                    }

                    score->lastElapsed = elapsed;
                    score->lastLossSecond = time;

                    score->totalLoss += VERDICT_IGNORE_SECONDS;
                    score->userLoss += fabsf(time);

                    score->score += (int) ((VERDICT_IGNORE_SECONDS - fabsf(time)) * 1000.0f) / ConfigInfoGetDropSpeed(config);
                }
            }
        } else {
            if (elapsed > note->arrival_seconds + note->length_seconds + VERDICT_IGNORE_SECONDS) {
                score->totalLoss += VERDICT_IGNORE_SECONDS;
                score->userLoss += VERDICT_IGNORE_SECONDS;
                score->currentCombo = 0;
                score->lastElapsed = elapsed;
                score->lastLossSecond = VERDICT_IGNORE_SECONDS + 9999.0f;

                LongNoteListRemove(list, i);
                i--;
                continue;
            }

            int isDown = ConfigInfoIsDown(config, laneCount, note->lane);
            int released = ConfigInfoIsReleased(config, laneCount, note->lane);

            if (released || !isDown) {
                float time = elapsed - (note->arrival_seconds + note->length_seconds);

                if (fabsf(time) <= VERDICT_IGNORE_SECONDS) {
                    if (fabsf(time) <= VERDICT_COMBO_SECONDS) {
                        score->currentCombo++;
                        if (score->currentCombo > score->maxCombo) {
                            score->maxCombo = score->currentCombo;
                        }
                    } else {
                        score->currentCombo = 0;
                    }

                    score->lastElapsed = elapsed;
                    score->lastLossSecond = time;

                    score->totalLoss += VERDICT_IGNORE_SECONDS;
                    score->userLoss += fabsf(time);

                    score->score += (int) ((VERDICT_IGNORE_SECONDS - fabsf(time)) * 1000.0f) / ConfigInfoGetDropSpeed(config);

                    LongNoteListRemove(list, i);
                    i--;
                    continue;
                } else if (time < -VERDICT_IGNORE_SECONDS) {
                    score->totalLoss += VERDICT_IGNORE_SECONDS;
                    score->userLoss += VERDICT_IGNORE_SECONDS;
                    score->currentCombo = 0;
                    score->lastElapsed = elapsed;
                    score->lastLossSecond = VERDICT_IGNORE_SECONDS + 9999.0f;

                    LongNoteListRemove(list, i);
                    i--;
                    continue;
                }
            }
        }
    }

    return 0;
}
