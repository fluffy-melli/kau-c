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
#include "compete/protocol.h"

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

    int isEnd;
    int isAllReady;

    // TODO: Later, Replace int-based timer later
    float started;

    int stage_id;
    int laneCount;

    UDPClient* udpClient;

    PlayerReadyState* states;
    PlayerExchangeState* exchangeStates;
} CompeteLogic;

CompeteLogic* OpenCompeteLogic(int stage_id, int room_id);
int CloseCompeteLogic(CompeteLogic* game);

void CompeteLogicPlay(CompeteLogic* game);

int CompeteLogicInputRender(CompeteLogic* game); // TODO: Later, Separate thread processing
int CompeteLogicOutputRender(CompeteLogic* game, Fonts* font);
