#pragma once

#include "layout/score.h"
#include "note/short.h"
#include "config/config.h"

float ShortNoteGetYPos(ShortNote* note, int judgmentY, float elapsed, float dropSpeedSeconds);
int ShortNoteListRender(ShortNoteList* list, Score* score, ConfigInfoJSON *config, int laneCount, float elapsed);
int ShortNoteListKeyPressRender(ShortNoteList* list, Score* score, ConfigInfoJSON *config, int laneCount, float elapsed);
