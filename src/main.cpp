#include <cstdio>
#include <string>

#include <raylib.h>
#include <opencv2/opencv.hpp>

int main() {
    InitWindow(1280, 720, "raylib");
    InitAudioDevice();

    Font font = LoadFont("resources/NotoSansKR-Bold.ttf");
    Music music = LoadMusicStream("resources/audio.mp3");
    
    PlayMusicStream(music);

    cv::VideoCapture cap("resources/video.mp4");

    if (!cap.isOpened()) {
        printf("failed to open video\n");
        return -1;
    }

    double video_fps = cap.get(cv::CAP_PROP_FPS);
    if (video_fps <= 0) video_fps = 24.0;

    int total_frames = (int)cap.get(cv::CAP_PROP_FRAME_COUNT);

    cv::Mat frame;

    if (!cap.read(frame) || frame.empty()) {
        printf("empty frame\n");
        return -1;
    }

    cv::resize(frame, frame, cv::Size(1280, 720));
    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);

    Texture2D texture = LoadTextureFromImage(Image{
        .data = frame.data,
        .width = frame.cols,
        .height = frame.rows,
        .mipmaps = 1,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8
    });

    int current_frame = 1;

    while (!WindowShouldClose()) {
        UpdateMusicStream(music);
        double elapsed = GetMusicTimePlayed(music);
        int expected_frame = (int)(elapsed * video_fps);

        bool new_frame_read = false;
        
        if (expected_frame < current_frame) {
            cap.set(cv::CAP_PROP_POS_FRAMES, 0);
            if (cap.read(frame) && !frame.empty()) {
                current_frame = 1;
                new_frame_read = true;
            } else {
                current_frame = 0;
            }
        }

        while (current_frame < expected_frame) {
            if (!cap.read(frame) || frame.empty()) {
                break;
            }

            new_frame_read = true;
            current_frame++;
        }

        if (new_frame_read && !frame.empty()) {
            cv::resize(frame, frame, cv::Size(1280, 720));
            cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);

            if (!frame.isContinuous()) {
                frame = frame.clone();
            }

            static std::vector<unsigned char> buffer;

            size_t size = frame.total() * frame.elemSize();

            if (buffer.size() != size) {
                buffer.resize(size);
            }

            memcpy(buffer.data(), frame.data, size);

            UpdateTexture(texture, buffer.data());
        }

        BeginDrawing();
        ClearBackground(BLACK);

        DrawTexture(texture, 0, 0, WHITE);

        char info_text[256];
        snprintf(info_text, sizeof(info_text), "FPS: %d\nRaylib: v%s\nOpenCV: v%s", 
                 GetFPS(), RAYLIB_VERSION, CV_VERSION);
        DrawTextEx(font, info_text, Vector2{20, 20}, 30, 1, GREEN);

        EndDrawing();
    }

    UnloadTexture(texture);
    UnloadFont(font);
    UnloadMusicStream(music);
    CloseAudioDevice();

    cap.release();
    CloseWindow();

    return 0;
}
