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

#include "types.h"
#include "applog.h"

namespace fs = std::filesystem;

const f32 SCALE_FACTOR = 100.0f;

namespace quilt {
    // This function assumes the input point has not been properly scaled and flipped.
    static ImVec2 ToWindowCenter(Vec2f& original, bool flip = false) {
        ImVec2 windowPos = ImGui::GetWindowPos();
        ImVec2 windowSize = ImGui::GetWindowSize();

        ImVec2 windowCenter = ImVec2(windowPos.x + windowSize.x * 0.5f, windowPos.y + windowSize.y * 0.5f);

        float s = flip ? -1.0f : 1.0f;
        
        ImVec2 point = ImVec2((SCALE_FACTOR * original.x * s) + windowCenter.x, (SCALE_FACTOR * original.y * s) + windowCenter.y);

        return point;
    }

    static ImVec2 ToWindowCenter(ImVec2& original, bool flip = false) {
        ImVec2 windowPos = ImGui::GetWindowPos();
        ImVec2 windowSize = ImGui::GetWindowSize();

        ImVec2 windowCenter = ImVec2(windowPos.x + windowSize.x * 0.5f, windowPos.y + windowSize.y * 0.5f);

        float s = flip ? -1.0f : 1.0f;
        
        ImVec2 point = ImVec2((SCALE_FACTOR * original.x * s) + windowCenter.x, (SCALE_FACTOR * original.y * s) + windowCenter.y);

        return point;
    }
}