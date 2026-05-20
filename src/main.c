#include <raylib.h>
#include "layout/lane.h"
#include "layout/video.h"
#include "constant/file.h"

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);

    InitWindow(1280, 720, "kau");
    InitAudioDevice();

    Font font = LoadFont("resources/font/NotoSansKR-Bold.ttf");

    int uid = 0;

    VideoPlayer* player = OpenVideo(uid);
    Music audio = LoadMusicStream(TextFormat(PLAY_AUDIO_PATH, uid));
    audio.looping = 0;

    PlayMusicStream(audio);
    SetMusicVolume(audio, 0.3f);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        UpdateMusicStream(audio);

        float elapsed = GetMusicTimePlayed(audio);

        VideoImageRender(player, elapsed);

        LaneLineRender(4);
        LaneKeyPressRender(4);

        VideoProgressRender(player, elapsed);

        EndDrawing();
    }

    UnloadFont(font);
    CloseVideo(player);

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
