#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct StageInfoJSON StageInfoJSON;

StageInfoJSON* OpenStageInfo(const char* stage_json_path);
void CloseStageInfo(StageInfoJSON* stage_info);

const char* StageInfoGetTitle(StageInfoJSON* stage_info);
const char* StageInfoGetArtist(StageInfoJSON* stage_info);

const char* StageInfoGetAudioPath(StageInfoJSON* stage_info);
const char* StageInfoGetVideoPath(StageInfoJSON* stage_info);
const char* StageInfoGetPreviewPath(StageInfoJSON* stage_info);

#ifdef __cplusplus
}
#endif
