#pragma once

#include "layout/score.h"
#include "note/short.h"
#include "note/long.h"
#include "config/config.h"

float ShortNoteGetYPos(float target_seconds, int judgmentY, float elapsed, float dropSpeedSeconds);
int ShortNoteListRender(ShortNoteList* list, Score* score, ConfigInfoJSON *config, int laneCount, float elapsed);
int ShortNoteListKeyPressRender(ShortNoteList* list, Score* score, ConfigInfoJSON *config, int laneCount, float elapsed);

float LongNoteGetYPos(float target_seconds, int judgmentY, float elapsed, float dropSpeedSeconds);
int LongNoteListRender(LongNoteList* list, Score* score, ConfigInfoJSON *config, int laneCount, float elapsed);
int LongNoteListKeyPressRender(LongNoteList* list, Score* score, ConfigInfoJSON *config, int laneCount, float elapsed);
