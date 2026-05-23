#include "layout/string.h"

#include <stdlib.h>

Fonts* OpenFonts(const char* light_path, const char* regular_path, const char* bold_path, const char* extra_bold_path) {
    Fonts* fonts = malloc(sizeof(Fonts));
    if (!fonts) {
        return NULL;
    }

    fonts->Light = LoadFont(light_path);
    fonts->Regular = LoadFont(regular_path);
    fonts->Bold = LoadFont(bold_path);
    fonts->ExtraBold = LoadFont(extra_bold_path);

    SetTextureFilter(fonts->Light.texture, TEXTURE_FILTER_TRILINEAR);
    SetTextureFilter(fonts->Regular.texture, TEXTURE_FILTER_TRILINEAR);
    SetTextureFilter(fonts->Bold.texture, TEXTURE_FILTER_TRILINEAR);
    SetTextureFilter(fonts->ExtraBold.texture, TEXTURE_FILTER_TRILINEAR);

    return fonts;
}

void CloseFonts(Fonts* fonts) {
    if (!fonts) {
        return;
    }

    UnloadFont(fonts->Light);
    UnloadFont(fonts->Regular);
    UnloadFont(fonts->Bold);
    UnloadFont(fonts->ExtraBold);

    free(fonts);
}

Font SelectFont(Fonts* fonts, FontTypes type) {
    if (!fonts) {
        return (Font){0};
    }

    switch (type) {
        case FONT_LIGHT:
            return fonts->Light;
        case FONT_REGULAR:
            return fonts->Regular;
        case FONT_BOLD:
            return fonts->Bold;
        case FONT_EXTRA_BOLD:
            return fonts->ExtraBold;
        default:
            return fonts->Regular;
    }
}

void DrawString(Fonts* fonts, FontTypes type, const char* text, int x, int y, int spacing, int fontSize, Color color) {
    if (!fonts) {
        return;
    }

    Font font = SelectFont(fonts, type);

    DrawTextEx(
        font,
        text,
        (Vector2){
            x,
            y
        },
        fontSize,
        spacing,
        color
    );
}

void DrawStringAtCenter(Fonts* fonts, FontTypes type, const char* text, int x, int y, int spacing, int fontSize, Color color) {
    if (!fonts) {
        return;
    }

    Font font = SelectFont(fonts, type);

    Vector2 measure = MeasureTextEx(
        font,
        text,
        (float) fontSize,
        (float) spacing
    );

    int centerX = x - (int)(measure.x / 2.0f);
    int centerY = y - (int)(measure.y / 2.0f);

    DrawTextEx(
        font,
        text,
        (Vector2){
            (float) centerX,
            (float) centerY
        },
        (float) fontSize,
        (float) spacing,
        color
    );
}

void DrawStringAtRight(Fonts* fonts, FontTypes type, const char* text, int x, int y, int spacing, int fontSize, Color color) {
    if (!fonts) {
        return;
    }

    Font font = SelectFont(fonts, type);

    Vector2 measure = MeasureTextEx(
        font,
        text,
        (float) fontSize,
        (float) spacing
    );

    int rightX = x - (int) measure.x;

    DrawTextEx(
        font,
        text,
        (Vector2){
            (float) rightX,
            (float) y
        },
        (float) fontSize,
        (float) spacing,
        color
    );
}

void DrawOutline(Fonts* fonts, FontTypes type, const char* text, int x, int y, int outlineSize, int spacing, int fontSize, Color color) {
    if (!fonts) {
        return;
    }

    Font font = SelectFont(fonts, type);

    for (int i = -outlineSize; i <= outlineSize; i++) {
        for (int j = -outlineSize; j <= outlineSize; j++) {
            if (i == 0 && j == 0) continue;
            
            DrawTextEx(
                font,
                text,
                (Vector2){
                    (float) (x + i),
                    (float) (y + j)
                },
                (float) fontSize,
                (float) spacing,
                color
            );
        }
    }
}

void DrawOutlineAtCenter(Fonts* fonts, FontTypes type, const char* text, int x, int y, int outlineSize, int spacing, int fontSize, Color color) {
    if (!fonts) {
        return;
    }

    Font font = SelectFont(fonts, type);

    Vector2 measure = MeasureTextEx(
        font,
        text,
        (float) fontSize,
        (float) spacing
    );

    int centerX = x - (int)(measure.x / 2.0f);
    int centerY = y - (int)(measure.y / 2.0f);

    DrawOutline(
        fonts,
        type,
        text,
        centerX,
        centerY,
        outlineSize,
        spacing,
        fontSize,
        color
    );
}

void DrawOutlineAtRight(Fonts* fonts, FontTypes type, const char* text, int x, int y, int outlineSize, int spacing, int fontSize, Color color) {
    if (!fonts) {
        return;
    }

    Font font = SelectFont(fonts, type);

    Vector2 measure = MeasureTextEx(
        font,
        text,
        (float) fontSize,
        (float) spacing
    );

    int rightX = x - (int) measure.x;

    DrawOutline(
        fonts,
        type,
        text,
        rightX,
        y,
        outlineSize,
        spacing,
        fontSize,
        color
    );
}
