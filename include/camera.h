#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "types.h"

namespace quilt {
    static GLFWwindow* MainWindow = nullptr;
    static Vec2f GetAppWindowDimensions();
}

class Camera {
public:
    Camera();
    Camera(void*);
    ~Camera();

    void Update();
    void ToCamera(ImVec2*);
    void ToCamera(Vec2f*);
    void FromCamera(ImVec2*);
public:
    void* mOwner;
    float x, y, zoom, speed;
};