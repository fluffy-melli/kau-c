#include <raylib.h>
#include "layout/lane.h"
#include "layout/debug.h"
#include "video/player.h"

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(1280, 720, "kau");
    InitAudioDevice();

    SetTargetFPS(60);

    Font font = LoadFont("resources/NotoSansKR-Bold.ttf");
    Music music = LoadMusicStream("resources/audio.mp3");
    VideoPlayer* player = OpenVideo("resources/video.mp4");

    PlayMusicStream(music);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        UpdateMusicStream(music);
        RenderVideo(player, GetMusicTimePlayed(music));

        LaneLineRender(4);
        LaneKeyPressRender(4);

        DebugInfoRender(font);

        EndDrawing();
    }

    UnloadFont(font);
    UnloadMusicStream(music);

    CloseVideo(player);

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
