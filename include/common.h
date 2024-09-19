#pragma once

// C/C++ standard library
#include <array>
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <sstream>
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
using ordered_json = nlohmann::ordered_json;

// Quilt utility headers
#include "applog.h"
#include "types.h"
#include "quilt_util.h"

namespace Quilt {
    static std::string QuiltRoot = fs::current_path().string() + "/";
    static std::string SettingsPath = QuiltRoot + "quilt_settings.json";

    template <typename T>
    T ByteSwap(T value) {
        T swapped;

        char* src = reinterpret_cast<char*>(&value);
        char* dst = reinterpret_cast<char*>(&swapped);

        for (size_t i = 0; i < sizeof(T); i++) {
            dst[i] = src[sizeof(T) - 1 - i];
        }

        return swapped;
    }

    template <typename T>
    static inline void ByteSwapFromVector(const std::vector<char>& data, u32& offs, T& dest, bool offset = true) {
        T raw = *(T*)(&data[offs]);
        dest = ByteSwap(raw);

        if (offset) {
            offs += sizeof(T);
        }
    }

    template <typename T>
    static inline void GetFromVector(const std::vector<char>& data, u32& offs, T& dest, bool offset = true) {
        std::memcpy(&dest, &data[offs], sizeof(T));

        if (offset) {
            offs += sizeof(T);
        }
    }

    class File {
    public:
        File() = default;
        
        File(std::string filename, std::vector<char> data)
            : mFilename(filename)
            , mData(data)
        { }

        ~File() {
            mData.clear();
        }

        std::string& GetFilename() {
            return mFilename;
        }

        void SetFilename(std::string filename) {
            mFilename = filename;
        }

        std::vector<char>& GetData() {
            return mData;
        }

        void SetData(std::vector<char> data) {
            mData = data;
        }

    private:
        std::string mFilename;
        std::vector<char> mData;
    };
}

inline ImVec2 operator+(ImVec2 lhs, ImVec2 rhs) {
    return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y);
}

inline std::string strippath(std::string& path) {
    return path.substr(path.find_last_of("\\/") + 1);
}
