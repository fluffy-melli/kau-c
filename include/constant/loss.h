#pragma once

#include <raylib.h>

#define LOSS_LENGTH 20

#define LOSS_GAP 0.05625f // 1280: 74px

#define LOSS_HEIGHT 0.0208f // 720: 15px

#define LOSS_CENTER_Y 0.64583f // 720: 465pxx

#define LOSS_EARLY_FONT_SIZE 0.01171f // 1280: 15px
#define LOSS_LATE_FONT_SIZE  0.01171f // 1280: 15px

#define LOSS_EARLY_SPACING 0.001562f // 1280: 2px
#define LOSS_LATE_SPACING 0.001562f // 1280: 2px

#define LOSS_LINE_SIZE     0.001562f // 1280: 2px
#define LOSS_ACC_LINE_SIZE 0.006250f // 1280: 8px

#define LOSS_EARLY_COLOR ((Color) {0, 0, 255, 255})
#define LOSS_LATE_COLOR  ((Color) {255, 0, 0, 255})

#define LOSS_LINE_NOW_COLOR   ((Color) {255, 255, 255, 255})
#define LOSS_LINE_OLD_COLOR   ((Color) {100, 100, 100, 255})
#define LOSS_LINE_ACC_COLOR   ((Color) {255, 0, 0, 255})

#define LOSS_BACKGROUND_COLOR       ((Color) {100, 100, 100, 100})
#define LOSS_COMBO_BACKGROUND_COLOR ((Color) {255, 125, 125, 100})
