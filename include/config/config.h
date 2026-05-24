#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ConfigInfoJSON ConfigInfoJSON;

ConfigInfoJSON* OpenConfigInfo(const char* config_json_path);
void CloseConfigInfo(ConfigInfoJSON* stage_info);

int ConfigInfoIsDown(ConfigInfoJSON* config, int laneCount, int lane);
int ConfigInfoIsPressed(ConfigInfoJSON* config, int laneCount, int lane);
int ConfigInfoIsReleased(ConfigInfoJSON* config, int laneCount, int lane);

float ConfigInfoGetDropSpeed(ConfigInfoJSON* config);
float ConfigInfoGetSpawnOffset(ConfigInfoJSON* config);

#ifdef __cplusplus
}
#endif
