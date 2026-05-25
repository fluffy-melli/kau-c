#include "game/compete.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <raylib.h>

#include "note/short.h"
#include "stage/info.h"
#include "stage/pattern.h"
#include "layout/note.h"
#include "layout/lane.h"
#include "layout/loss.h"
#include "layout/info.h"
#include "layout/video.h"
#include "layout/score.h"
#include "layout/string.h"
#include "constant/file.h"
#include "config/config.h"

#include "constant/protocol.h"
#include "compete/protocol.h"

CompeteLogic* OpenCompeteLogic(int stage_id, int room_id) {
    ConfigInfoJSON* config = OpenConfigInfo(FILE_CONFIG_PATH);

    char* stage_path = malloc(512);
    snprintf(stage_path, 512, FILE_STAGE_PATH, stage_id);

    StageInfoJSON* stage_info = OpenStageInfo(stage_path);

    char* resources_path = malloc(512);
    snprintf(resources_path, 512, FILE_STAGE_RESOURCES_PATH, stage_id);

    char* audio_path = malloc(512);
    snprintf(audio_path, 512, "%s/%s", resources_path, StageInfoGetAudioPath(stage_info));

    char* video_path = malloc(512);
    snprintf(video_path, 512, "%s/%s", resources_path, StageInfoGetVideoPath(stage_info));

    char* preview_path = malloc(512);
    snprintf(preview_path, 512, "%s/%s", resources_path, StageInfoGetPreviewPath(stage_info));

    const char* title = StageInfoGetTitle(stage_info);
    const char* artist = StageInfoGetArtist(stage_info);

    int laneCount = StageInfoGetLaneCount(stage_info);

    Loss* loss = NewLoss();
    Score* score = NewScore();

    LongNoteList* long_notes = NewLongNoteList();
    ShortNoteList* short_notes = NewShortNoteList();

    char* pattern_path = malloc(512);
    snprintf(pattern_path, 512, FILE_STAGE_PATTERN_PATH, stage_id);

    OpenPatternFile(pattern_path, short_notes, long_notes);

    Info* info = LoadInfo(preview_path, title, artist);
    Music audio = LoadMusicStream(audio_path);
    VideoPlayer* player = OpenVideo(video_path);

    audio.looping = 0;

    CompeteLogic* game = malloc(sizeof(CompeteLogic));

    game->loss = loss;
    game->score = score;

    game->long_notes = long_notes;
    game->short_notes = short_notes;

    game->info = info;
    game->audio = audio;
    game->player = player;
    game->config = config;
    game->stage_info = stage_info;

    game->isEnd = 0;
    game->isAllReady = 0;

    game->started = -1;

    game->stage_id = stage_id;
    game->laneCount = laneCount;

    game->udpClient = NewUDPClient();

    game->states = (PlayerReadyState*)malloc(sizeof(PlayerReadyState) * PROTOCOL_MAX_USER_SIZE);
    game->exchangeStates = (PlayerExchangeState*)malloc(sizeof(PlayerExchangeState) * PROTOCOL_MAX_USER_SIZE);
    if (game->exchangeStates != NULL) {
        memset(game->exchangeStates, 0, sizeof(PlayerExchangeState) * PROTOCOL_MAX_USER_SIZE);
    }

    if (game->udpClient != NULL) {
        UDPClientSetRoomID(game->udpClient, room_id);
    }

    free(stage_path);
    free(resources_path);
    free(audio_path);
    free(video_path);
    free(preview_path);
    free(pattern_path);

    return game;
}

int CloseCompeteLogic(CompeteLogic* game) {
    CloseLoss(game->loss);
    CloseScore(game->score);

    CloseLongNoteList(game->long_notes);
    CloseShortNoteList(game->short_notes);

    CloseInfo(game->info);
    UnloadMusicStream(game->audio);
    CloseVideo(game->player);
    CloseConfigInfo(game->config);

    CloseStageInfo(game->stage_info);

    if (game->udpClient != NULL) {
        closesocket(game->udpClient->sock);
        WSACleanup();
        free(game->udpClient);
    }
    if (game->states != NULL) {
        free(game->states);
    }
    if (game->exchangeStates != NULL) {
        free(game->exchangeStates);
    }

    free(game);

    return 0;
}

float CompeteLogicGetElapsed(CompeteLogic* game) {
    if (game->started < 0) {
        return -1.0f;
    }
    return GetTime() - game->started;
}

void CompeteLogicPlay(CompeteLogic* game) {
    game->started = GetTime();

    PlayMusicStream(game->audio);
}

int CompeteLogicInputRender(CompeteLogic* game) {
    float elapsed = GetTime() - game->started;

    if (game->started < 0) {
        elapsed = 0.0f;
    }

    if (IsKeyPressed(ConfigInfoGetFullscreenKey(game->config))) {
        ToggleFullscreen();
    }

    if (IsKeyPressed(KEY_R)) {
        if (game->udpClient != NULL) {
            UDPClientSetReady(game->udpClient, 1);
        }
    }
    
    if (IsKeyPressed(KEY_U)) {
        if (game->udpClient != NULL) {
            UDPClientSetReady(game->udpClient, 0);
        }
    }

    LongNoteListKeyPressRender(game->long_notes, game->loss, game->score, game->config, game->laneCount, elapsed);
    ShortNoteListKeyPressRender(game->short_notes, game->loss, game->score, game->config, game->laneCount, elapsed);

    return 0;
}

int CompeteLogicOutputRender(CompeteLogic* game, Fonts* font) {
    float elapsed = CompeteLogicGetElapsed(game);

    if (game->started < 0) {
        elapsed = 0.0f;
    }

    if (elapsed > GetMusicTimeLength(game->audio)) {
        game->isEnd = 1;
        UDPClientSetReady(game->udpClient, 2);
        UDPClientRecvReadyStates(game->udpClient, game->states, PROTOCOL_MAX_USER_SIZE);
        if (game->udpClient != NULL && game->exchangeStates != NULL) {
            UDPClientRecvExchangeStates(
                game->udpClient,
                game->exchangeStates,
                PROTOCOL_MAX_USER_SIZE,
                game->score->score,
                (int32_t)(game->score->totalLoss * 1000.0f),
                (int32_t)(game->score->userLoss * 1000.0f),
                game->score->currentCombo,
                game->score->maxCombo
            );
        }
    }

    if (game->isAllReady == 0 && game->udpClient != NULL && game->states != NULL) {
        int count = UDPClientRecvReadyStates(game->udpClient, game->states, PROTOCOL_MAX_USER_SIZE);
        
        if (count > 0 && count == PROTOCOL_MAX_USER_SIZE) {
            int checkReady = 1;
            for (int i = 0; i < count; i++) {
                if (game->states[i].ready == 0) {
                    checkReady = 0;
                    break;
               }
            }
            game->isAllReady = checkReady;
        }

        if (game->isAllReady == 1) {
            CompeteLogicPlay(game);
        }
    }

    if (game->started > 0) {
        UDPClientRecvExchangeStates(
            game->udpClient,
            game->exchangeStates,
            PROTOCOL_MAX_USER_SIZE,
            game->score->score,
            (int32_t)(game->score->totalLoss * 1000.0f),
            (int32_t)(game->score->userLoss * 1000.0f),
            game->score->currentCombo,
            game->score->maxCombo
        );
    }

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    BeginDrawing();
    ClearBackground(BLACK);

    UpdateMusicStream(game->audio);

    VideoImageRender(game->player, elapsed);

    LaneLineRender(game->laneCount);
    LaneKeyPressRender(game->config, game->laneCount);

    ShortNoteListRender(game->short_notes, game->loss, game->score, game->config, game->laneCount, elapsed);
    LongNoteListRender(game->long_notes, game->loss, game->score, game->config, game->laneCount, elapsed);

    VideoProgressRender(game->player, elapsed);
    InfoRender(game->info, font, game->laneCount);
    ScoreRender(game->score, font);

    if (game->udpClient != NULL) {
        ScoreAnotherRender(
            game->exchangeStates,
            PROTOCOL_MAX_USER_SIZE,
            game->udpClient->player_uid,
            font
        );
    }
    ScoreRenderAtLane(game->score, font, game->laneCount, elapsed);

    LossRender(game->loss, font, game->laneCount);

    if (game->isAllReady == 0) {
        DrawStringAtCenter(
            font,
            FONT_BOLD,
            "Waiting Players",
            screenWidth / 2,
            screenHeight / 2,
            2,
            30,
            RED
        );
    }

    EndDrawing();

    return 0;
}
