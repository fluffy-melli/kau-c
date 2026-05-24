#include <stdio.h>
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

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT);

    InitWindow(1280, 720, "kau");
    InitAudioDevice();

    Fonts* fonts = OpenFonts(
        FILE_FONT_LIGHT_PATH,
        FILE_FONT_REGULAR_PATH,
        FILE_FONT_BOLD_PATH,
        FILE_FONT_EXTRA_BOLD_PATH
    );

    ConfigInfoJSON* config = OpenConfigInfo(FILE_CONFIG_PATH);

    int stage_id = 0;

    StageInfoJSON* stage_info = OpenStageInfo(TextFormat(FILE_STAGE_PATH, stage_id));

    const char* resources_path = TextFormat(FILE_STAGE_RESOURCES_PATH, stage_id);

    const char* audio_path = TextFormat("%s/%s", resources_path, StageInfoGetAudioPath(stage_info));
    const char* video_path = TextFormat("%s/%s", resources_path, StageInfoGetVideoPath(stage_info));
    const char* preview_path = TextFormat("%s/%s", resources_path, StageInfoGetPreviewPath(stage_info));

    const char* title = StageInfoGetTitle(stage_info);
    const char* artist = StageInfoGetArtist(stage_info);

    int laneCount = StageInfoGetLaneCount(stage_info);

    Loss* loss = NewLoss();
    Score* score = NewScore();
    ShortNoteList* short_notes = NewShortNoteList();
    LongNoteList* long_notes = NewLongNoteList();

    OpenPatternFile(TextFormat(FILE_STAGE_PATTERN_PATH, stage_id), short_notes, long_notes);
    
    Info* info = LoadInfo(preview_path, title, artist);
    Music audio = LoadMusicStream(audio_path);
    audio.looping = 0;
    VideoPlayer* player = OpenVideo(video_path);

    HideCursor();
    PlayMusicStream(audio);
    SetMusicVolume(audio, 0.1f);

    float started = GetTime();
    
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        if (IsKeyPressed(KEY_F11)) {
            ToggleFullscreen();
        }

        UpdateMusicStream(audio);

        float elapsed = GetTime() - started; //GetMusicTimePlayed(audio);

        VideoImageRender(player, elapsed);

        LaneLineRender(laneCount);
        LaneKeyPressRender(config, laneCount);

        ShortNoteListRender(short_notes, loss, score, config, laneCount, elapsed);
        ShortNoteListKeyPressRender(short_notes, loss, score, config, laneCount, elapsed);

        LongNoteListRender(long_notes, loss, score, config, laneCount, elapsed);
        LongNoteListKeyPressRender(long_notes, loss, score, config, laneCount, elapsed);

        VideoProgressRender(player, elapsed);
        InfoRender(info, fonts, laneCount);
        ScoreRender(score, fonts);
        ScoreRenderAtLane(score, fonts, laneCount, elapsed);

        LossRender(loss, fonts, laneCount);

        EndDrawing();
    }

    CloseInfo(info);
    CloseVideo(player);
    CloseFonts(fonts);
    CloseStageInfo(stage_info);
    UnloadMusicStream(audio);

    CloseShortNoteList(short_notes);
    CloseLongNoteList(long_notes);
    CloseScore(score);
    CloseLoss(loss);
    CloseConfigInfo(config);

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
