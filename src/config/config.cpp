#include "config/config.h"

#include <stdlib.h>
#include <raylib.h>
#include <glaze/glaze.hpp>

struct ConfigInfoJSON4K {
    int key1;
    int key2;
    int key3;
    int key4;
};

struct ConfigInfoJSON5K {
    int key1;
    int key2;
    int key3;
    int key4;
    int key5;
    int key6;
};

struct ConfigInfoJSON6K {
    int key1;
    int key2;
    int key3;
    int key4;
    int key5;
    int key6;
};

struct ConfigInfoJSONKeybind {
    ConfigInfoJSON4K k4;
    ConfigInfoJSON5K k5;
    ConfigInfoJSON6K k6;
};

struct ConfigInfoJSON {
    ConfigInfoJSONKeybind keybind;
    float dropSpeed;
};

template <>
struct glz::meta<ConfigInfoJSON4K> {
    using T = ConfigInfoJSON4K;
    static constexpr auto value = glz::object(
        "key1", &T::key1,
        "key2", &T::key2,
        "key3", &T::key3,
        "key4", &T::key4
    );
};

template <>
struct glz::meta<ConfigInfoJSON5K> {
    using T = ConfigInfoJSON5K;
    static constexpr auto value = glz::object(
        "key1", &T::key1,
        "key2", &T::key2,
        "key3", &T::key3,
        "key4", &T::key4,
        "key5", &T::key5,
        "key6", &T::key6
    );
};

template <>
struct glz::meta<ConfigInfoJSON6K> {
    using T = ConfigInfoJSON6K;
    static constexpr auto value = glz::object(
        "key1", &T::key1,
        "key2", &T::key2,
        "key3", &T::key3,
        "key4", &T::key4,
        "key5", &T::key5,
        "key6", &T::key6
    );
};

template <>
struct glz::meta<ConfigInfoJSONKeybind> {
    using T = ConfigInfoJSONKeybind;
    static constexpr auto value = glz::object(
        "4k", &T::k4,
        "5k", &T::k5,
        "6k", &T::k6
    );
};

template <>
struct glz::meta<ConfigInfoJSON> {
    using T = ConfigInfoJSON;
    static constexpr auto value = glz::object(
        "keybind", &T::keybind,
        "note-drop-speed", &T::dropSpeed
    );
};

ConfigInfoJSON* OpenConfigInfo(const char* config_json_path) {
    auto* config = new ConfigInfoJSON();

    static std::vector<std::byte> buffer;
    auto ec = glz::read_file_json(*config, config_json_path, buffer);

    if (ec) {
        delete config;
        return nullptr;
    }

    return config;
}

void CloseConfigInfo(ConfigInfoJSON* config) {
    delete config;
}

int ConfigInfoIsDown(ConfigInfoJSON* config, int laneCount, int lane) {
    if (!config) {
        return 0;
    }

    int pressKey;
        
    switch (laneCount) {
        case 4:
            if (lane == 0) {
                pressKey = IsKeyDown(config->keybind.k4.key1);
            } else if (lane == 1) {
                pressKey = IsKeyDown(config->keybind.k4.key2);
            } else if (lane == 2) {
                pressKey = IsKeyDown(config->keybind.k4.key3);
            } else if (lane == 3) {
                pressKey = IsKeyDown(config->keybind.k4.key4);
            } else {
                pressKey = 0;
            }
            break;
        case 5:
            if (lane == 0) {
                pressKey = IsKeyDown(config->keybind.k5.key1);
            } else if (lane == 1) {
                pressKey = IsKeyDown(config->keybind.k5.key2);
            } else if (lane == 2) {
                pressKey = IsKeyDown(config->keybind.k5.key3) || IsKeyDown(config->keybind.k5.key4);
            } else if (lane == 3) {
                pressKey = IsKeyDown(config->keybind.k5.key5);
            } else if (lane == 4) {
                pressKey = IsKeyDown(config->keybind.k5.key6);
            } else {
                pressKey = 0;
            }
            break;
        case 6:
            if (lane == 0) {
                pressKey = IsKeyDown(config->keybind.k6.key1);
            } else if (lane == 1) {
                pressKey = IsKeyDown(config->keybind.k6.key2);
            } else if (lane == 2) {
                pressKey = IsKeyDown(config->keybind.k6.key3);
            } else if (lane == 3) {
                pressKey = IsKeyDown(config->keybind.k6.key4);
            } else if (lane == 4) {
                pressKey = IsKeyDown(config->keybind.k6.key5);
            } else if (lane == 5) {
                pressKey = IsKeyDown(config->keybind.k6.key6);
            } else {
                pressKey = 0;
            }
            break;
        default:
            pressKey = 0;
            break;
    }

    return pressKey;
}

int ConfigInfoIsPressed(ConfigInfoJSON* config, int laneCount, int lane) {
    if (!config) {
        return 0;
    }

    int pressKey;
        
    switch (laneCount) {
        case 4:
            if (lane == 0) {
                pressKey = IsKeyPressed(config->keybind.k4.key1);
            } else if (lane == 1) {
                pressKey = IsKeyPressed(config->keybind.k4.key2);
            } else if (lane == 2) {
                pressKey = IsKeyPressed(config->keybind.k4.key3);
            } else if (lane == 3) {
                pressKey = IsKeyPressed(config->keybind.k4.key4);
            } else {
                pressKey = 0;
            }
            break;
        case 5:
            if (lane == 0) {
                pressKey = IsKeyPressed(config->keybind.k5.key1);
            } else if (lane == 1) {
                pressKey = IsKeyPressed(config->keybind.k5.key2);
            } else if (lane == 2) {
                pressKey = IsKeyPressed(config->keybind.k5.key3) || IsKeyPressed(config->keybind.k5.key4);
            } else if (lane == 3) {
                pressKey = IsKeyPressed(config->keybind.k5.key5);
            } else if (lane == 4) {
                pressKey = IsKeyPressed(config->keybind.k5.key6);
            } else {
                pressKey = 0;
            }
            break;
        case 6:
            if (lane == 0) {
                pressKey = IsKeyPressed(config->keybind.k6.key1);
            } else if (lane == 1) {
                pressKey = IsKeyPressed(config->keybind.k6.key2);
            } else if (lane == 2) {
                pressKey = IsKeyPressed(config->keybind.k6.key3);
            } else if (lane == 3) {
                pressKey = IsKeyPressed(config->keybind.k6.key4);
            } else if (lane == 4) {
                pressKey = IsKeyPressed(config->keybind.k6.key5);
            } else if (lane == 5) {
                pressKey = IsKeyPressed(config->keybind.k6.key6);
            } else {
                pressKey = 0;
            }
            break;
        default:
            pressKey = 0;
            break;
    }

    return pressKey;
}

int ConfigInfoIsReleased(ConfigInfoJSON* config, int laneCount, int lane) {
    if (!config) {
        return 0;
    }

    int pressKey;
        
    switch (laneCount) {
        case 4:
            if (lane == 0) {
                pressKey = IsKeyReleased(config->keybind.k4.key1);
            } else if (lane == 1) {
                pressKey = IsKeyReleased(config->keybind.k4.key2);
            } else if (lane == 2) {
                pressKey = IsKeyReleased(config->keybind.k4.key3);
            } else if (lane == 3) {
                pressKey = IsKeyReleased(config->keybind.k4.key4);
            } else {
                pressKey = 0;
            }
            break;
        case 5:
            if (lane == 0) {
                pressKey = IsKeyReleased(config->keybind.k5.key1);
            } else if (lane == 1) {
                pressKey = IsKeyReleased(config->keybind.k5.key2);
            } else if (lane == 2) {
                pressKey = IsKeyReleased(config->keybind.k5.key3) || IsKeyReleased(config->keybind.k5.key4);
            } else if (lane == 3) {
                pressKey = IsKeyReleased(config->keybind.k5.key5);
            } else if (lane == 4) {
                pressKey = IsKeyReleased(config->keybind.k5.key6);
            } else {
                pressKey = 0;
            }
            break;
        case 6:
            if (lane == 0) {
                pressKey = IsKeyReleased(config->keybind.k6.key1);
            } else if (lane == 1) {
                pressKey = IsKeyReleased(config->keybind.k6.key2);
            } else if (lane == 2) {
                pressKey = IsKeyReleased(config->keybind.k6.key3);
            } else if (lane == 3) {
                pressKey = IsKeyReleased(config->keybind.k6.key4);
            } else if (lane == 4) {
                pressKey = IsKeyReleased(config->keybind.k6.key5);
            } else if (lane == 5) {
                pressKey = IsKeyReleased(config->keybind.k6.key6);
            } else {
                pressKey = 0;
            }
            break;
        default:
            pressKey = 0;
            break;
    }

    return pressKey;
}


float ConfigInfoGetDropSpeed(ConfigInfoJSON* config) {
    if (!config) {
        return 0.5f;
    }

    return config->dropSpeed;
}
