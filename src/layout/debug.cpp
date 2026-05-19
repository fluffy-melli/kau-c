#include "layout/debug.h"

#include <opencv2/opencv.hpp>

void DebugInfoRender(Font font) {
    if (DEBUG_ENABLED == 0) {
        return;
    }

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    float xPos = (float) screenWidth * DEBUG_CENTER_X;
    float yPos = (float) screenHeight * DEBUG_CENTER_Y;

    float width = (float) screenWidth * DEBUG_WIDTH;
    float height = (float) screenHeight * DEBUG_HEIGHT;

    float fontSize = (float) screenHeight * DEBUG_FONT_SIZE;

    DrawRectangle(
        (int) xPos,
        (int) yPos,
        (int) width,
        (int) height,
        DEBUG_BACKGROUND_COLOR
    );

    DrawTextEx(
        font,
        TextFormat("FPS: %d", GetFPS()),
        (Vector2) { xPos + 10, yPos + 5 },
        fontSize,
        2.0f,
        DEBUG_TEXT_COLOR
    );

    #if defined(__GNUC__)
        DrawTextEx(
            font,
            TextFormat("GCC: %s", __VERSION__),
            (Vector2){ xPos + 10, yPos + fontSize + 5 },
            fontSize,
            2.0f,
            DEBUG_TEXT_COLOR
        );

    #elif defined(_MSC_VER)
        DrawTextEx(
            font,
            TextFormat("MSVC: v%d", _MSC_VER),
            (Vector2) { xPos + 10, yPos + fontSize + 5 },
            fontSize,
            2.0f,
            DEBUG_TEXT_COLOR
        );

    #elif defined(__clang__)
        DrawTextEx(
            font,
            TextFormat("Clang: %s", __VERSION__),
            (Vector2){ xPos + 10, yPos + fontSize + 5 },
            fontSize,
            2.0f,
            DEBUG_TEXT_COLOR
        );
    
    #endif

    DrawTextEx(
        font,
        TextFormat("Raylib: v%s", RAYLIB_VERSION),
        (Vector2) { xPos + 10, yPos + fontSize * 2 + 5 },
        fontSize,
        2.0f,
        DEBUG_TEXT_COLOR
    );

    DrawTextEx(
        font,
        TextFormat("OpenCV: v%s", CV_VERSION),
        (Vector2) { xPos + 10, yPos + fontSize * 3 + 5 },
        fontSize,
        2.0f,
        DEBUG_TEXT_COLOR
    );
}
