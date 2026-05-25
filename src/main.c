#include <raylib.h>
#include "game/play.h"
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

    GameLogic* game = OpenGameLogic(stage_id);

    SetMusicVolume(game->audio, 0.1f);

    GameLogicPlay(game);
    
    while (!WindowShouldClose()) {
        GameLogicInputRender(game);
        GameLogicOutputRender(game, fonts);
    }

    CloseFonts(fonts);
    CloseGameLogic(game);

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
