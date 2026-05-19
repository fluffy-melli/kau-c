#include "video/player.h"

#include <raylib.h>
#include <opencv2/opencv.hpp>

struct VideoPlayer {
    float fps;

    int width;
    int height;

    int current_frame;

    Texture2D texture;

    cv::Mat frame_bgr;
    cv::Mat frame_rgb;

    cv::VideoCapture cap;
};

extern "C" {
    VideoPlayer* OpenVideo(const char* path) {
        VideoPlayer* player = new VideoPlayer;

        if (!player->cap.open(path)) {
            delete player;
            return nullptr;
        }

        player->width = (int) player->cap.get(cv::CAP_PROP_FRAME_WIDTH);

        player->height = (int) player->cap.get(cv::CAP_PROP_FRAME_HEIGHT);

        player->fps = (float) player->cap.get(cv::CAP_PROP_FPS);

        if (player->fps <= 0) {
            player->fps = 24.0f;
        }

        player->current_frame = -1;

        player->frame_rgb.create(
            player->height,
            player->width,
            CV_8UC3
        );

        unsigned char* pixels = new unsigned char[player->width * player->height * 3]();

        Image image = {
            .data = pixels,
            .width = player->width,
            .height = player->height,
            .mipmaps = 1,
            .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8
        };

        player->texture = LoadTextureFromImage(image);

        delete[] pixels;

        return player;
    }

    int RenderVideo(VideoPlayer* player, float elapsed) {
        if (!player || !player->cap.isOpened()) {
            return -1;
        }

        int target_frame = (int)(elapsed * player->fps);

        if (target_frame != player->current_frame) {

            if (target_frame < player->current_frame) {
                player->cap.set(
                    cv::CAP_PROP_POS_FRAMES,
                    target_frame
                );

                player->current_frame = target_frame - 1;
            }

            while (player->current_frame < target_frame) {
                if (!player->cap.read(player->frame_bgr)) {
                    return -1;
                }
                player->current_frame++;
            }

            if (player->frame_bgr.empty()) {
                return -1;
            }

            cv::cvtColor(
                player->frame_bgr,
                player->frame_rgb,
                cv::COLOR_BGR2RGB
            );

            UpdateTexture(
                player->texture,
                player->frame_rgb.data
            );
        }

        DrawTexturePro(
            player->texture,
            Rectangle{
                0.0f,
                0.0f,
                (float)player->width,
                (float)player->height
            },
            Rectangle{
                0.0f,
                0.0f,
                (float)GetScreenWidth(),
                (float)GetScreenHeight()
            },
            Vector2{0, 0},
            0.0f,
            WHITE
        );

        return 0;
    }

    void CloseVideo(VideoPlayer* player) {
        if (!player) return;

        UnloadTexture(player->texture);
        player->cap.release();

        delete player;
    }
}
