#pragma once
#include "common.h"
class Selectable {
public:
    enum SelectState {
        Deselected,
        Clicked,
        Selected,
        Hovered,
    };
public:
    Selectable();
    ~Selectable();

    virtual void Draw();
    virtual void HandleDrag();
    virtual void OnClick();
    virtual void OnDeselect();
    virtual void Update();

    int GetSelectState() const { return mSelectState; }
    void SetSelectState(int state) { mSelectState = state; }
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

    inline bool CheckClick() {
        return ImGui::IsMouseClicked(ImGuiMouseButton_Left) && CheckHover();
    }

    inline bool IsClicked()     { return SelectState::Clicked == mSelectState; }
    inline bool IsSelected()    { return SelectState::Selected == mSelectState; }
    inline bool IsHovered()     { return SelectState::Hovered == mSelectState; }
    inline bool IsDeselected()  { return SelectState::Deselected == mSelectState; }
    inline void SetClicked() { mSelectState = SelectState::Clicked; }
    inline void SetSelected() { mSelectState = SelectState::Selected; }
    inline void SetHovered() { mSelectState = SelectState::Hovered; }
    inline void SetDeselected() { mSelectState = SelectState::Deselected; }
private:
    ImVec2 mPosition;
    int    mSelectState;
    ImVec2 mDimensions;
    u32    mColorSelect;
    u32    mColorDeselect;
    u32    mColorHover;
    bool   mJustSelected;
};