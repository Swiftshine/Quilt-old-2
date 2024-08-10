#include "camera.h"
#include <imgui.h>

Vec2f quilt::GetAppWindowDimensions() {
    if (!quilt::MainWindow) {
        return Vec2f();
    }
    int w, h;
    glfwGetFramebufferSize(quilt::MainWindow, &w, &h);
    return Vec2f(float(w), float(w));
}

Camera::Camera()
    : mpOwner(nullptr)
    , x(0)
    , y(0)
    , zoom(1.0f)
{ }

Camera::Camera(void* newOwner)
    : mpOwner(newOwner)
    , x(0)
    , y(0)
    , zoom(1.0f)
{ }

Camera::~Camera() {
    mpOwner = nullptr;
}

void Camera::Update() {
    if (!ImGui::IsWindowFocused()) return;


    if (ImGui::IsKeyDown(ImGuiKey_UpArrow)) {
        y -= 1.0f;
    }

    if (ImGui::IsKeyDown(ImGuiKey_DownArrow)) {
        y += 1.0f;
    }

    if (ImGui::IsKeyDown(ImGuiKey_LeftArrow)) {
        x += 1.0f;
    }

    if (ImGui::IsKeyDown(ImGuiKey_RightArrow)) {
        x -= 1.0f;
    }

    if (!ImGui::IsWindowHovered()) return;

    ImGuiIO& io = ImGui::GetIO();

    if (io.MouseWheel > 0.0f) {
        zoom += 0.2f;
    } else if (io.MouseWheel < 0.0f) {
        zoom -= 0.2f;
    }

    if (zoom < 1.0f) zoom = 1.0f;
}