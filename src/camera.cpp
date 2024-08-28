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
    : mOwner(nullptr)
    , x(0)
    , y(0)
    , zoom(1.0f)
    , speed(1.0f)
{ }

Camera::Camera(void* newOwner)
    : mOwner(newOwner)
    , x(0)
    , y(0)
    , zoom(1.0f)
    , speed(0.5f)
{ }

Camera::~Camera() {
    mOwner = nullptr;
}

void Camera::Update() {
    if (!ImGui::IsWindowFocused()) return;

    if (ImGui::IsKeyPressed(ImGuiKey_R)) {
        x = 0;
        y = 0;
        zoom = 1.0f;
        return;
    }

    if (ImGui::IsKeyDown(ImGuiKey_UpArrow)) {
        y -= speed;
    }

    if (ImGui::IsKeyDown(ImGuiKey_DownArrow)) {
        y += speed;
    }

    if (ImGui::IsKeyDown(ImGuiKey_LeftArrow)) {
        x += speed;
    }

    if (ImGui::IsKeyDown(ImGuiKey_RightArrow)) {
        x -= speed;
    }

    if (!ImGui::IsWindowHovered()) return;

    ImGuiIO& io = ImGui::GetIO();

    if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl)) {
        if (io.MouseWheel > 0.0f) {
            speed += 0.1f;
        } else if (io.MouseWheel < 0.0f) {
            speed -= 0.1f;
        }
    } else {
        if (io.MouseWheel > 0.0f) {
            zoom += 0.2f;
        } else if (io.MouseWheel < 0.0f) {
            zoom -= 0.2f;
        }
    }

    if (zoom < 1.0f) zoom = 1.0f;
    if (speed < 0.1f) speed = 0.1f;
}

void Camera::ToCamera(ImVec2* v) {
    v->x = (v->x - this->x) / zoom;
    v->y = (v->y - this->y) / zoom;
}

void Camera::ToCamera(Vec2f* v) {
    v->x = (v->x - this->x) / zoom;
    v->y = (v->y - this->y) / zoom;
}

void Camera::FromCamera(ImVec2* v) {
    v->x = v->x * zoom + this->x;
    v->y = v->y * zoom + this->y;
}