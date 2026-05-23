#pragma once

#include <raylib.h>

typedef enum {
    FONT_LIGHT,
    FONT_REGULAR,
    FONT_BOLD,
    FONT_EXTRA_BOLD
} FontTypes;

typedef struct {
    Font Light;
    Font Regular;
    Font Bold;
    Font ExtraBold;
} Fonts;

Fonts* OpenFonts(const char* light_path, const char* regular_path, const char* bold_path, const char* extra_bold_path);
void CloseFonts(Fonts* fonts);

Font SelectFont(Fonts* fonts, FontTypes type);

void DrawString(Fonts* fonts, FontTypes type, const char* text, int x, int y, int spacing, int fontSize, Color color);
void DrawStringAtCenter(Fonts* fonts, FontTypes type, const char* text, int x, int y, int spacing, int fontSize, Color color);

void DrawOutline(Fonts* fonts, FontTypes type, const char* text, int x, int y, int outlineSize, int spacing, int fontSize, Color color);
void DrawOutlineAtCenter(Fonts* fonts, FontTypes type, const char* text, int x, int y, int outlineSize, int spacing, int fontSize, Color color);
