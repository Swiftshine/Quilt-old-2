#include "selectable.h"

Selectable::Selectable()
    : mSelectState(SelectState::Deselected)
    , mJustSelected(false)
    , mColorSelect(0xFF'FF'FF'FF)
    , mColorDeselect(0x77'77'77'77)
    , mColorHover(0xFF'FF'FF'FF)
    , mPosition(ImVec2(100, 100))
    , mDimensions(ImVec2(50, 50))
{ }

Selectable::~Selectable() { }
void Selectable::HandleDrag() {

    // // hover checks

    // if (CheckHover()) {
    //     if (IsDeselected() || IsHovered()) {
    //         if (CheckClick()) {
    //             SetClicked();
    //             OnClick();
    //             SetSelected();
    //         } else {
    //             SetHovered();
    //         }
    //     }
    // } else {
    //     if (IsSelected()) {
    //         if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
    //             SetDeselected();
    //         }
    //     }
    // }


    // // case 1 - hovered, not selected
    // if (CheckHover() && SelectState::Selected != mSelectState) {
    //     mSelectState = SelectState::Hovered;

    //     // check click
    //     if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
    //         mSelectState = SelectState::Clicked;
    //         OnClick();
    //         mSelectState = SelectState::Selected;
    //     }
    // }

    // // case 2 - not hovered, selected
    // else if (SelectState::Selected == mSelectState) {
    //     // check click elsewhere, deselect if clicked
    //     if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && !CheckHover()) {
    //         mSelectState = SelectState::Deselected;
    //     }
    // }


    // drag if selected
    if (IsSelected()) {
        if (ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
            mSelectState = SelectState::Deselected;
        } else {
            mPosition = ImGui::GetMousePos();
        }
    }
}

void Selectable::Draw() {
    u32 drawCol;

    switch (mSelectState) {
        case SelectState::Deselected:
            drawCol = mColorDeselect;
            break;
        
        case SelectState::Clicked:
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