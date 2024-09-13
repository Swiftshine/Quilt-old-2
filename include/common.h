#pragma once

// C/C++ standard library
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace fs = std::filesystem;

// dependency headers
#include "imgui/imgui_impl_sdl2.h"
#include "imgui/imgui_impl_sdlrenderer2.h"
#include "SDL2/SDL.h"
#include "json.hpp"
#include "portable-file-dialogs.h"

using json = nlohmann::json;

// Quilt utility headers
#include "applog.h"
#include "types.h"
#include "quilt_util.h"

namespace Quilt {
    static std::string QuiltRoot = fs::current_path().string();
    static std::string SettingsPath = QuiltRoot + "/quilt-settings.json";
}
