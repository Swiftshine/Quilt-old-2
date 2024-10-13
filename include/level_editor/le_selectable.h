#pragma once
#include "common.h"

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

    void Draw(SDL_Renderer* renderer);
    void HandleDrag();
    void Update(SDL_Renderer* renderer);

    inline bool CheckHover() {
        return ImGui::IsMouseHoveringRect(mPosition.ToImVec2(), (mPosition + mDimensions).ToImVec2());
    }

    inline bool CheckLeftClick() {
        return ImGui::IsMouseClicked(ImGuiMouseButton_Left) && CheckHover();
    }

    inline bool CheckMouseDown() {
        return ImGui::IsMouseDown(ImGuiMouseButton_Left) && CheckHover();
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
        return mPosition;
    }

    inline void SetPosition(const Vec2f pos) {
        mPosition = pos;
    }

    inline void SetPosition(const float x, const float y) {
        mPosition = Vec2f(x, y);
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
    Vec2f mPosition;
    Vec2f mDimensions;
    Vec2f mDragOffset;
    RGBA mColor;
};
