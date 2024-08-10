#pragma once


// all the includes go here for ease of reading

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_internal.h>
#include <nfd.h>

#include <filesystem>
#include <string>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <fstream>

#include "camera.h"
#include "types.h"
#include "applog.h"

namespace fs = std::filesystem;

const f32 SCALE_FACTOR = 100.0f;

// a collection of utility functions

namespace quilt {


    static ImVec2 ToImVec2(Vec2f v) {
        return ImVec2(v.x, v.y);
    }

    static Vec2f ToVec2f(ImVec2 v) {
        return Vec2f(v.x, v.y);
    }

    static void AlignOutstream(std::ofstream& file, u32 alignment) {
        const char zero = 0;
        if (file.tellp() % alignment != 0) {
            for (auto i = 0; i < (file.tellp() % alignment); i++) {
                file.write(&zero, 1);
            }
        }
    }

    static ImVec2 ToWindow(Camera& camera, Vec2f& worldPosition) {
        ImVec2 result;
        result.x = worldPosition.x * camera.zoom + camera.x;
        result.y = worldPosition.y * camera.zoom + camera.y;
        result.y *= -1.0;
        return result;
    }

    static ImVec2 ToWindow(Camera& camera, ImVec2& worldPosition) {
        ImVec2 result;
        result.x = worldPosition.x * camera.zoom + camera.x;
        result.y = worldPosition.y * camera.zoom + camera.y;
        result.y *= -1.0;
        return result;
    }

    static Vec2f ToWorld(Camera& camera, Vec2f& windowPosition) {
        Vec2f result;
        result.x = (windowPosition.x - camera.x) / camera.zoom;
        result.y = (windowPosition.y - camera.y) / camera.zoom;
        result.y *= -1.0;
        return result;
    }

    static Vec2f ToWorld(Camera& camera, ImVec2& windowPosition) {
        Vec2f result;
        result.x = (windowPosition.x - camera.x) / camera.zoom;
        result.y = (windowPosition.y - camera.y) / camera.zoom;
        result.y *= -1.0;
        return result;
    }
}
