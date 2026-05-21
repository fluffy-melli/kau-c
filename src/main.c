#include <raylib.h>
#include "layout/lane.h"
#include "layout/info.h"
#include "layout/video.h"
#include "constant/file.h"

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT);

    InitWindow(1280, 720, "kau");
    InitAudioDevice();

    Font font = LoadFont("resources/font/NotoSansKR-Bold.ttf");
    SetTextureFilter(font.texture, TEXTURE_FILTER_TRILINEAR);

    int uid = 0;
    int laneCount = 4;

    VideoPlayer* player = OpenVideo(TextFormat(PLAY_VIDEO_PATH, uid));
    Music audio = LoadMusicStream(TextFormat(PLAY_AUDIO_PATH, uid));
    audio.looping = 0;
    Info* info = LoadInfo(TextFormat(PLAY_PREIMAGE_PATH, uid), "", "");

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

        InfoRender(info, font, laneCount);
        LaneLineRender(laneCount);
        LaneKeyPressRender(laneCount);

        VideoProgressRender(player, elapsed);

        EndDrawing();
    }

    UnloadFont(font);
    CloseInfo(info);
    CloseVideo(player);
    UnloadMusicStream(audio);

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
