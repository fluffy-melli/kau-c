#pragma once

#include "note/short.h"
#include "stage/info.h"
#include "layout/note.h"
#include "layout/lane.h"
#include "layout/loss.h"
#include "layout/info.h"
#include "layout/video.h"
#include "layout/score.h"
#include "config/config.h"

typedef struct {
    Loss* loss;
    Score* score;

    LongNoteList* long_notes;
    ShortNoteList* short_notes;

    Info* info;
    Music audio;
    VideoPlayer* player;
    ConfigInfoJSON* config;
    StageInfoJSON* stage_info;

    int isPause;
    int isEnd;

    // TODO: Later, Replace int-based timer later
    float started;
    float pausedAt;
    float totalPausedTime;

    int stage_id;
    int laneCount;
} GameLogic;

GameLogic* OpenGameLogic(int stage_id);
int CloseGameLogic(GameLogic* game);

float GameLogicGetElapsed(GameLogic* game);

void GameLogicPlay(GameLogic* game);
void GameLogicPause(GameLogic* game);
void GameLogicResume(GameLogic* game);
void GameLogicRestart(GameLogic* game);


int GameLogicInputRender(GameLogic* game); // TODO: Later, Separate thread processing
int GameLogicOutputRender(GameLogic* game, Fonts* font);
