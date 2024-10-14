#pragma once
#include "common.h"
#include "camera.h"

class LE_Selectable {
public:
    enum SelectState {
        Deselected,
        Hovered,
        Dragged,
        Selected,
    };

    LE_Selectable();
    ~LE_Selectable();

    void Draw(const Camera& camera, SDL_Renderer* renderer);
    void HandleDrag(const Camera& camera);
    void Update(const Camera& camera, SDL_Renderer* renderer);

    inline bool CheckHover(const Camera& camera) {
        Vec2f mousePos = ToVec2f(ImGui::GetMousePos());
        // camera.ToWorld(mousePos);

        return mousePos.x >= mCameraPosition.x && mousePos.x <= (mCameraPosition.x + mDimensions.x) &&
           mousePos.y >= mCameraPosition.y && mousePos.y <= (mCameraPosition.y + mDimensions.y);
    }


    inline bool CheckLeftClick(const Camera& camera) {
        return ImGui::IsMouseClicked(ImGuiMouseButton_Left) && CheckHover(camera);
    }

    inline bool CheckMouseDown(const Camera& camera) {
        return ImGui::IsMouseDown(ImGuiMouseButton_Left) && CheckHover(camera);
    }

    SelectState GetState() const {
        return mSelectState;
    }

    void SetState(SelectState state) {
        mSelectState = state;
    }

    inline RGBA GetColor() const {
        return mColor;
    }

    inline void SetColor(const RGBA color) {
        mColor = color;
    }

    inline Vec2f GetPosition() const {
        return mWorldPosition;
    }

    inline void SetPosition(const Vec2f pos) {
        mWorldPosition = pos;
    }

    inline void SetPosition(const float x, const float y) {
        mWorldPosition = Vec2f(x, y);
    }

    inline Vec2f GetDimensions() const {
        return mDimensions;
    }

    inline void SetDimensions(const Vec2f dim) {
        mDimensions = dim;
    }

    inline void SetDimensions(const float x, const float y) {
        mDimensions = Vec2f(x, y);
    }
    
private:
    SelectState mSelectState;
    Vec2f mCameraPosition;
    Vec2f mWorldPosition;
    Vec2f mDimensions;
    Vec2f mDragOffset;
    RGBA mColor;
};
