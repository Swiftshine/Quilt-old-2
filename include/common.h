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

constexpr f32 SCALE_FACTOR = 5.0f;

// additional operator overloads for ImVec2

static ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs) {
    return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y);
}

static ImVec2 operator-(const ImVec2& lhs, const ImVec2& rhs) {

    return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y);
}

static ImVec2 operator*(const ImVec2& lhs, float rhs) {

    return ImVec2(lhs.x * rhs, lhs.y * rhs);
}

static ImVec2 operator/(const ImVec2& lhs, float rhs) {
    return ImVec2(lhs.x / rhs, lhs.y / rhs);
}


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

    static ImVec2 ToWindow(const Camera& camera, Vec2f& worldPosition) {
        ImVec2 result;
        result.x = worldPosition.x * camera.zoom + camera.x;
        result.y = worldPosition.y * camera.zoom + camera.y;
        result.x *= SCALE_FACTOR;
        result.y *= SCALE_FACTOR;
        result.y *= -1.0;
        return result;
    }

    static ImVec2 ToWindow(const Camera& camera, ImVec2& worldPosition) {
        ImVec2 result;
        result.x = worldPosition.x * camera.zoom + camera.x;
        result.y = worldPosition.y * camera.zoom + camera.y;
        result.x *= SCALE_FACTOR;
        result.y *= SCALE_FACTOR;
        result.y *= -1.0;
        return result;
    }

    static Vec2f ToWorld(const Camera& camera, Vec2f& windowPosition) {
        Vec2f result;
        result.x = (windowPosition.x - camera.x) / camera.zoom;
        result.y = (windowPosition.y - camera.y) / camera.zoom;
        result.y *= -1.0;
        return result;
    }

    static Vec2f ToWorld(const Camera& camera, ImVec2& windowPosition) {
        Vec2f result;
        result.x = (windowPosition.x - camera.x) / camera.zoom;
        result.y = (windowPosition.y - camera.y) / camera.zoom;
        result.y *= -1.0;
        return result;
    }

    // Check if a rect is hovered relative to window
    // This assumes that center is already relative to window
    static bool RectHovered(const Camera& camera, ImVec2 center, float w, float h) {
        if (!ImGui::IsWindowHovered() || !ImGui::IsWindowFocused()) return false;

        const float zoom = camera.zoom;
        const float camx = camera.x;
        const float camy = camera.y;

        ImVec2 mousePos = ImGui::GetMousePos();
        mousePos = quilt::ToWindow(camera, mousePos);

        ImVec2 bottomLeft = ImVec2(center.x - camera.x, center.y + camera.y);
        ImVec2 topRight = ImVec2(center.x + camera.y, center.y - camera.y);

        // Positive Y is down

        // conditions to check if the mouse is...

        // to the left of my right wall
        bool a = mousePos.x < topRight.x;
        // to the right of my left wall
        bool b = mousePos.x > bottomLeft.x;
        // above my floor
        bool c = mousePos.y < bottomLeft.y;
        // below my ceiling
        bool d = mousePos.y > bottomLeft.y;

        return a && b && c && d;
    }
}
