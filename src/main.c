#include <stdio.h>
#include <raylib.h>
#include "stage/info.h"
#include "layout/lane.h"
#include "layout/info.h"
#include "layout/video.h"
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
    int laneCount = 4;

    StageInfoJSON* stage_info = OpenStageInfo(TextFormat(FILE_STAGE_PATH, stage_id));

    const char* resources_path = TextFormat(FILE_STAGE_RESOURCES_PATH, stage_id);

    const char* audio_path = TextFormat("%s/%s", resources_path, StageInfoGetAudioPath(stage_info));
    const char* video_path = TextFormat("%s/%s", resources_path, StageInfoGetVideoPath(stage_info));
    const char* preview_path = TextFormat("%s/%s", resources_path, StageInfoGetPreviewPath(stage_info));

    const char* title = StageInfoGetTitle(stage_info);
    const char* artist = StageInfoGetArtist(stage_info);
    
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

        if (IsKeyPressed(KEY_UP)) {
            if (laneCount < 6) {
                laneCount++;
            }
        }

        if (IsKeyPressed(KEY_DOWN)) {
            if (laneCount > 4) {
                laneCount--;
            }
        }

        UpdateMusicStream(audio);

        float elapsed = GetMusicTimePlayed(audio);

        VideoImageRender(player, elapsed);

        LaneLineRender(laneCount);
        LaneKeyPressRender(laneCount);

        VideoProgressRender(player, elapsed);
        InfoRender(info, fonts, laneCount);

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
