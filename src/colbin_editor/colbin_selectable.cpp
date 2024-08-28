#include "colbin_editor/colbin_editor.h"

ColbinEntrySelectable::ColbinEntrySelectable(Camera* camera, Vec2f p1, Vec2f p2, key::colbin::wrapper::Entry& entry) 
    : Selectable()
    , mCamera(camera)
    , mEntry(entry)
{
    mEntry.SetPoint1(p1);
    mEntry.SetPoint2(p2);
}   

ColbinEntrySelectable::~ColbinEntrySelectable() { }

void ColbinEntrySelectable::HandleDrag() {
    if (CheckLeftClick() && !IsStateDragged()) {
        OnClick();
        ImVec2 mousePos = ImGui::GetMousePos();
        
        mDragOffset = mousePos - mPosition;
        mDragOffset = mDragOffset * -1.0f;

        if (0.0f != mDragOffset.x || 0.0f != mDragOffset.y) {
            SetStateDragged();
        }
    } else if (CheckHover() && !IsStateDragged()) {
        SetStateHovered();
        DuringHover();
    } else if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) || IsStateHovered()) {
        SetStateDeselected();
    }

    if (ImGui::IsMouseDown(ImGuiMouseButton_Left) && IsStateDragged()) {
        ImVec2 mousePos = ImGui::GetMousePos();
        mPosition = mousePos + mDragOffset;
    }

    if (ImGui::IsMouseReleased(ImGuiMouseButton_Left) && IsStateDragged()) {
        SetStateSelected();
    }
}