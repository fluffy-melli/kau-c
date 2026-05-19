#include <raylib.h>
#include "video/player.h"

int main() {
    InitAudioDevice();
    InitWindow(1280, 720, "raylib");

    Font font = LoadFont("resources/NotoSansKR-Bold.ttf");
    Music music = LoadMusicStream("resources/audio.mp3");
    VideoPlayer* player = OpenVideo("resources/video.mp4");

    PlayMusicStream(music);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        UpdateMusicStream(music);
        RenderVideo(player, GetMusicTimePlayed(music));

        EndDrawing();
    }

    UnloadFont(font);
    UnloadMusicStream(music);

    CloseVideo(player);

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
