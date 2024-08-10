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
public:
    void* mpOwner;
    float x, y, zoom;
};