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

    inline SDL_FPoint ToCamera(const SDL_FPoint& point) const {
        SDL_FPoint ret = point;

        ret.x *= mZoom;
        ret.x += mPosition.x;

        ret.y *= mZoom;
        ret.y = mWindowDimensions.y - ret.y + mPosition.y;

        return ret;
    }

    inline Vec2f ToCamera(const Vec2f& point) const {
        Vec2f ret = point;

        ret.x *= mZoom;
        ret.x += mPosition.x;

        ret.y *= mZoom;
        ret.y = mWindowDimensions.y - ret.y + mPosition.y;

        return ret;
    }

    inline Vec2f ToWorld(const Vec2f& point) const {
        Vec2f ret = point;
        ret.x -= mPosition.x;
        ret.x /= mZoom;

        ret.y = mWindowDimensions.y - ret.y;
        ret.y -= mPosition.y;
        ret.y /= mZoom;
        return ret;
    }
    
    ~Camera() = default;

public:
    Vec2f mPosition;
    Vec2f mWindowPosition;
    Vec2f mWindowDimensions;
    float mZoom;
    float mSpeed;
    float mMinSpeed;
    float mMaxSpeed;
    float mAcceleration;
    float mDeceleration;
};
