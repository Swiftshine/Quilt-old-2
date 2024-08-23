#include "selectable.h"

Selectable::Selectable(Camera& camera)
    : mSelectState(SelectState::Deselected)
    , mColorSelect(0xFF'FF'FF'FF)
    , mColorDeselect(0x77'77'77'77)
    , mColorHover(0xFF'FF'FF'FF)
    , mPosition(ImVec2(100, 100))
    , mDimensions(ImVec2(50, 50))
    , mCamera(&camera)
{ }

Selectable::~Selectable() { }
void Selectable::HandleDrag() {

    // check if clicked

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
        
        mPosition = mousePos + mDragOffset * 0.5f;
    }

    if (ImGui::IsMouseReleased(ImGuiMouseButton_Left) && IsStateDragged()) {
        SetStateSelected();
    }
}

void Selectable::Draw() {
    u32 drawCol;

    switch (mSelectState) {
        case SelectState::Deselected:
            drawCol = mColorDeselect;
            break;
        
        case SelectState::Selected:
        case SelectState::Hovered:
            drawCol = mColorSelect;
            break; 
        default:
            drawCol = 0xFF'FF'FF'FF;
            break;
    }

    ImGui::GetWindowDrawList()->AddRect(mPosition, ImVec2(mPosition.x + mDimensions.x, mPosition.y + mDimensions.y), drawCol);
}


void Selectable::OnDeselect() { }

void Selectable::Update() {
    HandleDrag();
    Draw();
}

void Selectable::OnClick() {
    AppLog::Print("i was clicked");
}

void Selectable::DuringHover() {
    ImGui::BeginTooltip();
    ImGui::Text("i am hovered");
    ImGui::EndTooltip();
}