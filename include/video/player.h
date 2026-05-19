#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct VideoPlayer VideoPlayer;
VideoPlayer* OpenVideo(const char* path);

int RenderVideo(VideoPlayer* player, float elapsed);
void CloseVideo(VideoPlayer* player);

#ifdef __cplusplus
}
#endif
