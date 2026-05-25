#include "game/play.h"

#include <stdio.h>
#include <stdlib.h>
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

GameLogic* OpenGameLogic(int stage_id) {
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

    GameLogic* game = malloc(sizeof(GameLogic));

    game->loss = loss;
    game->score = score;

    game->long_notes = long_notes;
    game->short_notes = short_notes;

    game->info = info;
    game->audio = audio;
    game->player = player;
    game->config = config;
    game->stage_info = stage_info;

    game->isPause = 0;
    game->isEnd = 0;

    game->started = -1;
    game->pausedAt = 0.0f;
    game->totalPausedTime = 0.0f;

    game->stage_id = stage_id;
    game->laneCount = laneCount;

    free(stage_path);
    free(resources_path);
    free(audio_path);
    free(video_path);
    free(preview_path);
    free(pattern_path);

    return game;
}

int CloseGameLogic(GameLogic* game) {
    CloseLoss(game->loss);
    CloseScore(game->score);

    CloseLongNoteList(game->long_notes);
    CloseShortNoteList(game->short_notes);

    CloseInfo(game->info);
    UnloadMusicStream(game->audio);
    CloseVideo(game->player);
    CloseConfigInfo(game->config);

    CloseStageInfo(game->stage_info);

    free(game);

    return 0;
}

float GameLogicGetElapsed(GameLogic* game) {
    if (game->started < 0) {
        return -1.0f;
    }

    if (game->isPause) {
        return game->pausedAt - game->started - game->totalPausedTime;
    }

    return GetTime() - game->started - game->totalPausedTime;
}

void GameLogicPlay(GameLogic* game) {
    game->started = GetTime();
    game->totalPausedTime = 0.0f;

    PlayMusicStream(game->audio);
}

void GameLogicPause(GameLogic* game) {
    if (game->isPause) {
        return;
    }

    PauseMusicStream(game->audio);

    game->isPause = 1;
    game->pausedAt = GetTime();
}

void GameLogicResume(GameLogic* game) {
    if (!game->isPause) {
        return;
    }

    float now = GetTime();

    game->totalPausedTime += now - game->pausedAt;

    ResumeMusicStream(game->audio);

    game->isPause = 0;
}

void GameLogicRestart(GameLogic* game) {
    LossReset(game->loss);
    ScoreReset(game->score);

    CloseLongNoteList(game->long_notes);
    CloseShortNoteList(game->short_notes);

    LongNoteList* new_long_notes = NewLongNoteList();
    ShortNoteList* new_short_notes = NewShortNoteList();

    char* pattern_path = malloc(512);
    snprintf(pattern_path, 512, FILE_STAGE_PATTERN_PATH, game->stage_id);

    OpenPatternFile(pattern_path, new_short_notes, new_long_notes);

    free(pattern_path);

    game->long_notes = new_long_notes;
    game->short_notes = new_short_notes;

    StopMusicStream(game->audio);
    SeekMusicStream(game->audio, 0.0f);

    game->isPause = 0;
    game->isEnd = 0;
    game->pausedAt = 0.0f;
    game->totalPausedTime = 0.0f;
    game->started = GetTime();

    PlayMusicStream(game->audio);
}

int GameLogicInputRender(GameLogic* game) {
    float elapsed = GameLogicGetElapsed(game);

    if (game->started < 0) {
        elapsed = 0.0f;
    }

    if (IsKeyPressed(ConfigInfoGetFullscreenKey(game->config))) {
        ToggleFullscreen();
    }

    if (IsKeyPressed(ConfigInfoGetRestartKey(game->config))) {
        GameLogicRestart(game);
        return 0;
    }

    if (IsKeyPressed(ConfigInfoGetPauseKey(game->config))) {
        if (game->isPause) {
            GameLogicResume(game);
        } else {
            GameLogicPause(game);
        }
    }

    LongNoteListKeyPressRender(game->long_notes, game->loss, game->score, game->config, game->laneCount, elapsed);
    ShortNoteListKeyPressRender(game->short_notes, game->loss, game->score, game->config, game->laneCount, elapsed);

    return 0;
}

int GameLogicOutputRender(GameLogic* game, Fonts* font) {
    float elapsed = GameLogicGetElapsed(game);

    if (game->started < 0) {
        elapsed = 0.0f;
    }

    if (elapsed > GetMusicTimeLength(game->audio)) {
        game->isEnd = 1;
    }

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
    ScoreRenderAtLane(game->score, font, game->laneCount, elapsed);

    LossRender(game->loss, font, game->laneCount);

    EndDrawing();

    return 0;
}
