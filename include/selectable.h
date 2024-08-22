#pragma once
#include "common.h"
class Selectable {
public:
    enum SelectState {
        Deselected,
        Hovered,
        Dragged,
        Selected,
    };
public:
    Selectable(Camera& camera);
    ~Selectable();

    virtual void Draw();
    virtual void HandleDrag();
    virtual void OnClick();
    virtual void DuringHover();
    virtual void OnDeselect();
    virtual void Update();

    SelectState GetSelectState() const { return mSelectState; }
    void SetSelectState(SelectState state) { mSelectState = state; }
    ImVec2 GetPosition() const { return mPosition; }
    void SetPosition(ImVec2 position) { mPosition = position; }
    ImVec2 GetDimensions() const { return mDimensions; }
    void SetDimensions(ImVec2 dimensions) { mDimensions = dimensions; }
    u32 GetColorSelect() const { return mColorSelect; }
    void SetColorSelect(u32 color) { mColorSelect = color; }
    u32 GetColorDeselect() const { return mColorDeselect; }
    void SetColorDeselect(u32 color) { mColorDeselect = color; }
private:
    // utility funcs

    inline bool CheckHover() {
        return ImGui::IsMouseHoveringRect(mPosition, mPosition + mDimensions);
    }

    inline bool CheckLeftClick() {
        return ImGui::IsMouseClicked(ImGuiMouseButton_Left) && CheckHover();
    }


    inline bool CheckMouseDown() {
        return ImGui::IsMouseDown(ImGuiMouseButton_Left) && CheckHover();
    }

    inline bool IsStateSelected()    { return SelectState::Selected == mSelectState; }
    inline bool IsStateHovered()     { return SelectState::Hovered == mSelectState; }
    inline bool IsStateDeselected()  { return SelectState::Deselected == mSelectState; }
    inline bool IsStateDragged()    { return SelectState::Dragged == mSelectState; }
    inline void SetStateSelected() { mSelectState = SelectState::Selected; }
    inline void SetStateHovered() { mSelectState = SelectState::Hovered; }
    inline void SetStateDeselected() { mSelectState = SelectState::Deselected; }
    inline void SetStateDragged() { mSelectState = SelectState::Dragged; }
private:
    Camera* mCamera;
    ImVec2 mPosition;
    ImVec2 mDimensions;
    ImVec2 mDragOffset;
    SelectState mSelectState;
    u32    mColorSelect;
    u32    mColorDeselect;
    u32    mColorHover;
};