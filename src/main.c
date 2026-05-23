#include <stdio.h>
#include <raylib.h>
#include "note/short.h"
#include "stage/info.h"
#include "layout/note.h"
#include "layout/lane.h"
#include "layout/info.h"
#include "layout/video.h"
#include "layout/score.h"
#include "layout/string.h"
#include "constant/file.h"

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

    Score* score = NewScore();
    ShortNoteList* short_notes = NewShortNoteList();

    ShortNoteListAdd(short_notes, 0, 1.0f);
    ShortNoteListAdd(short_notes, 1, 1.5f);
    ShortNoteListAdd(short_notes, 2, 2.0f);
    ShortNoteListAdd(short_notes, 3, 2.5f);
    ShortNoteListAdd(short_notes, 4, 3.0f);
    ShortNoteListAdd(short_notes, 3, 3.5f);
    ShortNoteListAdd(short_notes, 2, 4.0f);
    ShortNoteListAdd(short_notes, 1, 4.5f);
    ShortNoteListAdd(short_notes, 0, 5.0f);

    int stage_id = 0;

    StageInfoJSON* stage_info = OpenStageInfo(TextFormat(FILE_STAGE_PATH, stage_id));

    const char* resources_path = TextFormat(FILE_STAGE_RESOURCES_PATH, stage_id);

    const char* audio_path = TextFormat("%s/%s", resources_path, StageInfoGetAudioPath(stage_info));
    const char* video_path = TextFormat("%s/%s", resources_path, StageInfoGetVideoPath(stage_info));
    const char* preview_path = TextFormat("%s/%s", resources_path, StageInfoGetPreviewPath(stage_info));

    const char* title = StageInfoGetTitle(stage_info);
    const char* artist = StageInfoGetArtist(stage_info);

    int laneCount = StageInfoGetLaneCount(stage_info);
    
    Info* info = LoadInfo(preview_path, title, artist);
    Music audio = LoadMusicStream(audio_path);
    audio.looping = 0;
    VideoPlayer* player = OpenVideo(video_path);

    HideCursor();
    PlayMusicStream(audio);
    SetMusicVolume(audio, 0.1f);
    
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        if (IsKeyPressed(KEY_F11)) {
            ToggleFullscreen();
        }

        UpdateMusicStream(audio);

        float elapsed = GetMusicTimePlayed(audio);

        VideoImageRender(player, elapsed);

        LaneLineRender(laneCount);
        LaneKeyPressRender(laneCount);

        ShortNoteListRender(short_notes, score, laneCount, elapsed);
        ShortNoteListKeyPressRender(short_notes, score, laneCount, elapsed);

        VideoProgressRender(player, elapsed);
        InfoRender(info, fonts, laneCount);
        ScoreRender(score, fonts);
        ScoreRenderAtLane(score, fonts, laneCount, elapsed);

        EndDrawing();
    }

    CloseInfo(info);
    CloseVideo(player);
    CloseFonts(fonts);
    CloseStageInfo(stage_info);
    UnloadMusicStream(audio);

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
