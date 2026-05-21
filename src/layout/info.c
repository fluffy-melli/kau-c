#include "layout/info.h"

#include <stdlib.h>
#include <raylib.h>
#include "constant/info.h"

Info* LoadInfo(const char* image_path, const char* title, const char* artist) {
    Info* info = malloc(sizeof(Info));

    info->title = title;
    info->artist = artist;

    Image image = LoadImage(image_path);

    info->texture = LoadTextureFromImage(image);

    UnloadImage(image);

    return info;
}

void CloseInfo(Info* info) {
    if (!info) {
        return;
    }

    UnloadTexture(info->texture);

    free(info);
}

int InfoRender(Info* info, Font font, int laneCount) {
    if (!info) {
        return -1;
    }

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    float padding = (float) screenWidth * INFO_IMAGE_PADDING;

    float imageSize = (float) screenWidth * INFO_IMAGE_SIZE;

    float infoWidth = (float) screenWidth * INFO_WIDTH;
    float infoHeight = imageSize + padding * 2;

    float infoXPos = (float) screenWidth * INFO_GAP;
    float infoYPos = ((float) screenHeight - infoHeight) * INFO_CENTER_Y;

    DrawRectangle(
        (int) infoXPos,
        (int) infoYPos,
        (int) infoWidth,
        (int) infoHeight,
        INFO_BACKGROUND_COLOR
    );

    float imageXPos = infoXPos + padding;
    float imageYPos = infoYPos + padding;

    DrawTexturePro(
        info->texture,
        (Rectangle){
            0.0f,
            0.0f,
            (float) info->texture.width,
            (float) info->texture.height
        },
        (Rectangle){
            imageXPos,
            imageYPos,
            imageSize,
            imageSize
        },
        (Vector2){0, 0},
        0.0f,
        WHITE
    );

    float titleFontSize = (float) screenWidth * INFO_TITLE_FONT_SIZE;
    float artistFontSize = (float) screenWidth * INFO_ARTIST_FONT_SIZE;

    float titleSpacing = (float) screenWidth * INFO_TITLE_SPACING;
    float artistSpacing = (float) screenWidth * INFO_ARTIST_SPACING;

    float textXPos = imageXPos + imageSize + padding;
    float textYPos = imageYPos;

    Vector2 titleTextPos = {
        textXPos + 10,
        textYPos + 5
    };

    DrawTextEx(
        font,
        info->title,
        (Vector2){
            titleTextPos.x - 2,
            titleTextPos.y
        },
        titleFontSize,
        titleSpacing,
        INFO_TITLE_SHADOW_COLOR
    );

    DrawTextEx(
        font,
        info->title,
        (Vector2){
            titleTextPos.x + 2,
            titleTextPos.y
        },
        titleFontSize,
        titleSpacing,
        INFO_TITLE_SHADOW_COLOR
    );

    DrawTextEx(
        font,
        info->title,
        (Vector2){
            titleTextPos.x,
            titleTextPos.y - 2
        },
        titleFontSize,
        titleSpacing,
        INFO_TITLE_SHADOW_COLOR
    );
    
    DrawTextEx(
        font,
        info->title,
        (Vector2){
            titleTextPos.x,
            titleTextPos.y + 2
        },
        titleFontSize,
        titleSpacing,
        INFO_TITLE_SHADOW_COLOR
    );

    DrawTextEx(
        font,
        info->title,
        (Vector2){
            titleTextPos.x - 2,
            titleTextPos.y - 2
        },
        titleFontSize,
        titleSpacing,
        INFO_TITLE_SHADOW_COLOR
    );

    DrawTextEx(
        font,
        info->title,
        (Vector2){
            titleTextPos.x + 2,
            titleTextPos.y - 2
        },
        titleFontSize,
        titleSpacing,
        INFO_TITLE_SHADOW_COLOR
    );

    DrawTextEx(
        font,
        info->title,
        (Vector2){
            titleTextPos.x - 2,
            titleTextPos.y + 2
        },
        titleFontSize,
        titleSpacing,
        INFO_TITLE_SHADOW_COLOR
    );

    DrawTextEx(
        font,
        info->title,
        (Vector2){
            titleTextPos.x + 2,
            titleTextPos.y + 2
        },
        titleFontSize,
        titleSpacing,
        INFO_TITLE_SHADOW_COLOR
    );

    DrawTextEx(
        font,
        info->title,
        titleTextPos,
        titleFontSize,
        titleSpacing,
        INFO_TITLE_COLOR
    );

    Vector2 artistTextPos = {
        textXPos + 10,
        textYPos + titleFontSize + artistSpacing * 2
    };

    DrawTextEx(
        font,
        info->artist,
        (Vector2){
            artistTextPos.x - 2,
            artistTextPos.y
        },
        artistFontSize,
        artistSpacing,
        INFO_ARTIST_SHADOW_COLOR
    );

    DrawTextEx(
        font,
        info->artist,
        (Vector2){
            artistTextPos.x,
            artistTextPos.y - 2
        },
        artistFontSize,
        artistSpacing,
        INFO_ARTIST_SHADOW_COLOR
    );

    DrawTextEx(
        font,
        info->artist,
        (Vector2){
            artistTextPos.x,
            artistTextPos.y + 2
        },
        artistFontSize,
        artistSpacing,
        INFO_ARTIST_SHADOW_COLOR
    );

    DrawTextEx(
        font,
        info->artist,
        (Vector2){
            artistTextPos.x - 2,
            artistTextPos.y - 2
        },
        artistFontSize,
        artistSpacing,
        INFO_ARTIST_SHADOW_COLOR
    );

    DrawTextEx(
        font,
        info->artist,
        (Vector2){
            artistTextPos.x + 2,
            artistTextPos.y - 2
        },
        artistFontSize,
        artistSpacing,
        INFO_ARTIST_SHADOW_COLOR
    );

    DrawTextEx(
        font,
        info->artist,
        (Vector2){
            artistTextPos.x - 2,
            artistTextPos.y + 2
        },
        artistFontSize,
        artistSpacing,
        INFO_ARTIST_SHADOW_COLOR
    );

    DrawTextEx(
        font,
        info->artist,
        (Vector2){
            artistTextPos.x + 2,
            artistTextPos.y + 2
        },
        artistFontSize,
        artistSpacing,
        INFO_ARTIST_SHADOW_COLOR
    );

    DrawTextEx(
        font,
        info->artist,
        artistTextPos,
        artistFontSize,
        artistSpacing,
        INFO_ARTIST_COLOR
    );

    float langCountFontSize = (float) screenWidth * INFO_LANGCOUNT_FONT_SIZE;
    float langCountSpacing = (float) screenWidth * INFO_LANGCOUNT_SPACING;

    float langCountWidth = imageSize + padding * 2;
    float langCountHeight = langCountFontSize + langCountSpacing * 2;

    float langCountYPos = imageYPos + imageSize + padding - 1;

    DrawRectangle(
        (int) infoXPos,
        (int) langCountYPos,
        (int) langCountWidth,
        (int) langCountHeight,
        INFO_LANGCOUNT_BACKGROUND_COLOR
    );

    DrawTriangle(
        (Vector2){
            ((int) infoXPos + (int)langCountWidth),
            (int) langCountYPos
        },
        (Vector2){
            ((int)infoXPos + (int)langCountWidth),
            (int) (langCountYPos + (int)langCountHeight)
        },
        (Vector2){
            ((int)infoXPos + (int)langCountWidth + (int)langCountHeight),
            ((int)langCountYPos)
        },
        INFO_LANGCOUNT_BACKGROUND_COLOR
    );

    const char* laneText = TextFormat("%dK", laneCount);

    Vector2 laneTextSize = MeasureTextEx(
        font,
        laneText,
        langCountFontSize,
        langCountSpacing
    );

    Vector2 laneTextPos = {
        (infoXPos + imageSize / 2 + padding) - laneTextSize.x / 2.0f,
        langCountYPos + (langCountHeight - laneTextSize.y) / 2.0f
    };

    DrawTextEx(
        font,
        laneText,
        (Vector2){
            laneTextPos.x - 2,
            laneTextPos.y
        },
        langCountFontSize,
        langCountSpacing,
        INFO_LANGCOUNT_SHADOW_COLOR
    );
    
    DrawTextEx(
        font,
        laneText,
        (Vector2){
            laneTextPos.x + 2,
            laneTextPos.y
        },
        langCountFontSize,
        langCountSpacing,
        INFO_LANGCOUNT_SHADOW_COLOR
    );

    DrawTextEx(
        font,
        laneText,
        (Vector2){
            laneTextPos.x,
            laneTextPos.y - 2
        },
        langCountFontSize,
        langCountSpacing,
        INFO_LANGCOUNT_SHADOW_COLOR
    );

    DrawTextEx(
        font,
        laneText,
        (Vector2){
            laneTextPos.x,
            laneTextPos.y + 2
        },
        langCountFontSize,
        langCountSpacing,
        INFO_LANGCOUNT_SHADOW_COLOR
    );

    DrawTextEx(
        font,
        laneText,
        (Vector2){
            laneTextPos.x - 2,
            laneTextPos.y - 2
        },
        langCountFontSize,
        langCountSpacing,
        INFO_LANGCOUNT_SHADOW_COLOR
    );

    DrawTextEx(
        font,
        laneText,
        (Vector2){
            laneTextPos.x + 2,
            laneTextPos.y - 2
        },
        langCountFontSize,
        langCountSpacing,
        INFO_LANGCOUNT_SHADOW_COLOR
    );

    DrawTextEx(
        font,
        laneText,
        (Vector2){
            laneTextPos.x - 2,
            laneTextPos.y + 2
        },
        langCountFontSize,
        langCountSpacing,
        INFO_LANGCOUNT_SHADOW_COLOR
    );

    DrawTextEx(
        font,
        laneText,
        (Vector2){
            laneTextPos.x + 2,
            laneTextPos.y + 2
        },
        langCountFontSize,
        langCountSpacing,
        INFO_LANGCOUNT_SHADOW_COLOR
    );

    DrawTextEx(
        font,
        laneText,
        laneTextPos,
        langCountFontSize,
        langCountSpacing,
        INFO_LANGCOUNT_COLOR
    );

    return 0;
}
