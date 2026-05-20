#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct VideoPlayer VideoPlayer;
VideoPlayer* OpenVideo(int uid);
void CloseVideo(VideoPlayer* player);

int VideoProgressRender(VideoPlayer* player, float elapsed);
int VideoImageRender(VideoPlayer* player, float elapsed);

float VideoLength(VideoPlayer* player);

#ifdef __cplusplus
}
#endif
