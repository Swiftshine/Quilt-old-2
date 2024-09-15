#pragma once
#include "common.h"

class Camera {
public:
    Camera() {
        mPosition = Vec2f(0, 0);
        mZoom = 1.0f;
        mSpeed = 10.0f;
    }

    ~Camera() = default;

public:
    Vec2f mPosition;
    float mZoom;
    float mSpeed;
};
