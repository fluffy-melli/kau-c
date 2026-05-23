#pragma once

#include "layout/score.h"
#include "note/short.h"

float ShortNoteGetYPos(ShortNote* note, int judgmentY, float elapsed, float dropSpeedSeconds);
int ShortNoteListRender(ShortNoteList* list, Score* score, int laneCount, float elapsed);
int ShortNoteListKeyPressRender(ShortNoteList* list, Score* score, int laneCount, float elapsed);
