#pragma once

#include <raylib.h>
#include "layout/string.h"

typedef struct {
    const char* title;
    const char* artist;

    Texture2D texture;
} Info;

Info* LoadInfo(const char* image_path, const char* title, const char* artist);
void CloseInfo(Info* info);
int InfoRender(Info* info, Fonts* font, int laneCount);
