#pragma once
#include "common.h"

class Camera {
public:
    Camera() {
        mPosition = Vec2f(0, 0);
        mZoom = 1.0f;
        mSpeed = 1.0f;
        mMinSpeed = 5.0f;
        mMaxSpeed = 25.0f;
        mAcceleration = 1.0f; 
        mDeceleration = 0.05f;
    }

    inline void UpdateSpeed() {
        if (mSpeed < mMaxSpeed) {
            mSpeed += mAcceleration;
            if (mSpeed > mMaxSpeed) {
                mSpeed = mMaxSpeed;
            }
        }
    }

    inline void Decelerate() {
        if (mSpeed > 1.0f) {
            mSpeed -= mDeceleration;
            if (mSpeed < mMinSpeed) {
                mSpeed = mMinSpeed;
            }
        }
    }
    
    ~Camera() = default;

public:
    Vec2f mPosition;
    float mZoom;
    float mSpeed;
    float mMinSpeed;
    float mMaxSpeed;
    float mAcceleration;
    float mDeceleration;
};
