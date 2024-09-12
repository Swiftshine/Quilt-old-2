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

// Quilt utility headers
#include "applog.h"
#include "types.h"
#include "quilt_util.h"
