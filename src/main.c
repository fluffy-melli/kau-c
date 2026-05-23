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

    int stage_id = 0;

    StageInfoJSON* stage_info = OpenStageInfo(TextFormat(FILE_STAGE_PATH, stage_id));

    const char* resources_path = TextFormat(FILE_STAGE_RESOURCES_PATH, stage_id);

    const char* audio_path = TextFormat("%s/%s", resources_path, StageInfoGetAudioPath(stage_info));
    const char* video_path = TextFormat("%s/%s", resources_path, StageInfoGetVideoPath(stage_info));
    const char* preview_path = TextFormat("%s/%s", resources_path, StageInfoGetPreviewPath(stage_info));

    const char* title = StageInfoGetTitle(stage_info);
    const char* artist = StageInfoGetArtist(stage_info);

    int laneCount = StageInfoGetLaneCount(stage_info);

    Score* score = NewScore();
    ShortNoteList* short_notes = NewShortNoteList();

    switch (laneCount) {
        case 4:
            for (int i = 0; i < 500; i++) {
                int period = 6;
                int x = i % period;
                int lane = x < 4 ? x : 6 - x;

                ShortNoteListAdd(short_notes, lane, 1.0f + i * 0.5f);
            }
            break;
        case 5:
            for (int i = 0; i < 500; i++) {
                int period = 8;
                int x = i % period;
                int lane = x < 5 ? x : 8 - x;

                ShortNoteListAdd(short_notes, lane, 1.0f + i * 0.5f);
            }
            break;
        case 6:
            for (int i = 0; i < 500; i++) {
                int period = 10;
                int x = i % period;
                int lane = x < 6 ? x : 10 - x;

                ShortNoteListAdd(short_notes, lane, 1.0f + i * 0.5f);
            }
            break;
    }
    
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

        float elapsed = GetTime(); //GetMusicTimePlayed(audio);

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
