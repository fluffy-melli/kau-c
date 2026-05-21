#include "layout/video.h"

#include <raylib.h>
#include <opencv2/opencv.hpp>
#include "constant/video.h"

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
    VideoPlayer* OpenVideo(const char *video_path) {
        VideoPlayer* player = new VideoPlayer;

        if (!player->cap.open(video_path)) {
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

    void CloseVideo(VideoPlayer* player) {
        if (!player) {
            return;
        }

        UnloadTexture(player->texture);
        player->cap.release();

        delete player;
    }

    int VideoProgressRender(VideoPlayer* player, float elapsed) {
        if (!player || !player->cap.isOpened()) {
            return -1;
        }

        float length = VideoLength(player);

        int screenWidth = GetScreenWidth();
        int screenHeight = GetScreenHeight();

        float progressWidth = screenWidth / length * elapsed;
        float progressHeight = (float) screenHeight * VIDEO_PREGRESS_HEIGHT;

        DrawRectangle(
            0,
            0,
            screenWidth,
            (int) progressHeight,
            VIDEO_PREGRESS_BACKGROUND_COLOR
        );

        DrawRectangle(
            0,
            0,
            (int) progressWidth,
            (int) progressHeight,
            VIDEO_PREGRESS_COLOR
        );

        return 0;
    }

    int VideoImageRender(VideoPlayer* player, float elapsed) {
        if (!player || !player->cap.isOpened()) {
            return -1;
        }

        int target_frame = (int) (elapsed * player->fps);

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
            VIDEO_BACKGROUND_COLOR
        );

        return 0;
    }

    float VideoLength(VideoPlayer* player) {
        if (!player || !player->cap.isOpened()) {
            return -1;
        }

        double frame_count = player->cap.get(cv::CAP_PROP_FRAME_COUNT);
        double fps = player->cap.get(cv::CAP_PROP_FPS);

        float length = 0.0;
        if (fps > 0) {
            length = frame_count / fps;
        }

        return length;
    }
}
