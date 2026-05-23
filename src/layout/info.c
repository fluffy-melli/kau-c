#include "layout/info.h"

#include <stdlib.h>
#include <raylib.h>
#include "layout/string.h"
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

int InfoRender(Info* info, Fonts* fonts, int laneCount) {
    if (!info) {
        return -1;
    }

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    int padding = screenWidth * INFO_IMAGE_PADDING;

    int imageSize = screenWidth * INFO_IMAGE_SIZE;

    int infoWidth = screenWidth * INFO_WIDTH;
    int infoHeight = imageSize + padding * 2;

    int infoXPos = screenWidth * INFO_GAP;
    int infoYPos = (screenHeight - infoHeight) * INFO_CENTER_Y;

    DrawRectangle(
        infoXPos,
        infoYPos,
        infoWidth,
        infoHeight,
        INFO_BACKGROUND_COLOR
    );

    int imageXPos = infoXPos + padding;
    int imageYPos = infoYPos + padding;

    int enterY = screenHeight * INFO_ENTER_Y;

    DrawTexturePro(
        info->texture,
        (Rectangle){
            (float) 0,
            (float) 0,
            (float) info->texture.width,
            (float) info->texture.height
        },
        (Rectangle){
            (float) imageXPos,
            (float) imageYPos,
            (float) imageSize,
            (float) imageSize
        },
        (Vector2){(float) 0, (float) 0},
        (float) 0,
        WHITE
    );

    int titleFontSize = screenWidth * INFO_TITLE_FONT_SIZE;
    int titleSpacing = screenWidth * INFO_TITLE_SPACING;

    int textXPos = imageXPos + imageSize + padding + 10;
    int textYPos = imageYPos + 5;

    DrawOutline(
        fonts,
        FONT_EXTRA_BOLD,
        info->title,
        textXPos,
        textYPos,
        2,
        titleSpacing,
        titleFontSize,
        INFO_TITLE_OUTLINE_COLOR
    );

    DrawString(
        fonts,
        FONT_EXTRA_BOLD,
        info->title,
        textXPos,
        textYPos,
        titleSpacing,
        titleFontSize,
        INFO_TITLE_COLOR
    );

    int artistFontSize = screenWidth * INFO_ARTIST_FONT_SIZE;
    int artistSpacing = screenWidth * INFO_ARTIST_SPACING;

    textYPos += titleFontSize + titleSpacing + enterY;

    DrawOutline(
        fonts,
        FONT_BOLD,
        info->artist,
        textXPos,
        textYPos,
        2,
        artistSpacing,
        artistFontSize,
        INFO_ARTIST_OUTLINE_COLOR
    );

    DrawString(
        fonts,
        FONT_BOLD,
        info->artist,
        textXPos,
        textYPos,
        artistSpacing,
        artistFontSize,
        INFO_ARTIST_COLOR
    );

    int langCountFontSize = screenWidth * INFO_LANGCOUNT_FONT_SIZE;
    int langCountSpacing = screenWidth * INFO_LANGCOUNT_SPACING;

    int langCountWidth = imageSize + padding * 2;
    int langCountHeight = langCountFontSize + langCountSpacing * 2;

    int langCountYPos = imageYPos + imageSize + padding;

    DrawRectangle(
        infoXPos,
        langCountYPos,
        langCountWidth,
        langCountHeight,
        INFO_LANGCOUNT_BACKGROUND_COLOR
    );

    DrawTriangle(
        (Vector2){
            (float) (infoXPos + langCountWidth),
            (float) langCountYPos
        },
        (Vector2){
            (float) (infoXPos + langCountWidth),
            (float) (langCountYPos + langCountHeight)
        },
        (Vector2){
            (float) (infoXPos + langCountWidth + langCountHeight),
            (float) langCountYPos
        },
        INFO_LANGCOUNT_BACKGROUND_COLOR
    );

    const char* laneText = TextFormat("%d Lines", laneCount);

    DrawOutlineAtCenter(
        fonts,
        FONT_EXTRA_BOLD,
        laneText,
        infoXPos + imageSize / 2 + padding,
        langCountYPos + langCountHeight / 2,
        2,
        langCountSpacing,
        langCountFontSize,
        INFO_LANGCOUNT_OUTLINE_COLOR
    );

    DrawStringAtCenter(
        fonts,
        FONT_EXTRA_BOLD,
        laneText,
        infoXPos + imageSize / 2 + padding,
        langCountYPos + langCountHeight / 2,
        langCountSpacing,
        langCountFontSize,
        INFO_LANGCOUNT_COLOR
    );

    return 0;
}
