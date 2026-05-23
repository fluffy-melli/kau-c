#include "stage/info.h"

#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include <glaze/glaze.hpp>

struct StageInfoJSONInfo {
    std::string title;
    std::string artist;
    int lane_count;
};

struct StageInfoJSONPath {
    std::string audio;
    std::string video;
    std::string preview;
};

struct StageInfoJSON {
    StageInfoJSONInfo info;
    StageInfoJSONPath path;
};

template <>
struct glz::meta<StageInfoJSONInfo> {
    using T = StageInfoJSONInfo;
    static constexpr auto value = glz::object(
        "title", &T::title,
        "artist", &T::artist,
        "lane_count", &T::lane_count
    );
};

template <>
struct glz::meta<StageInfoJSONPath> {
    using T = StageInfoJSONPath;
    static constexpr auto value = glz::object(
        "audio", &T::audio,
        "video", &T::video,
        "preview", &T::preview
    );
};

template <>
struct glz::meta<StageInfoJSON> {
    using T = StageInfoJSON;
    static constexpr auto value = glz::object(
        "info", &T::info,
        "path", &T::path
    );
};

StageInfoJSON* OpenStageInfo(const char* stage_json_path) {
    auto* stage = new StageInfoJSON();

    static std::vector<std::byte> buffer;
    auto ec = glz::read_file_json(*stage, stage_json_path, buffer);

    if (ec) {
        delete stage;
        return nullptr;
    }

    return stage;
}

void CloseStageInfo(StageInfoJSON* stage_info) {
    delete stage_info;
}

const char* StageInfoGetTitle(StageInfoJSON* stage_info) {
    if (!stage_info) {
        return nullptr;
    }
    return stage_info->info.title.c_str();
}

const char* StageInfoGetArtist(StageInfoJSON* stage_info) {
    if (!stage_info) {
        return nullptr;
    }
    return stage_info->info.artist.c_str();
}

int StageInfoGetLaneCount(StageInfoJSON* stage_info) {
    if (!stage_info) {
        return -1;
    }
    return stage_info->info.lane_count;
}

const char* StageInfoGetAudioPath(StageInfoJSON* stage_info) {
    if (!stage_info) {
        return nullptr;
    }
    return stage_info->path.audio.c_str();
}

const char* StageInfoGetVideoPath(StageInfoJSON* stage_info) {
    if (!stage_info) {
        return nullptr;
    }
    return stage_info->path.video.c_str();
}

const char* StageInfoGetPreviewPath(StageInfoJSON* stage_info) {
    if (!stage_info) {
        return nullptr;
    }
    return stage_info->path.preview.c_str();
}
