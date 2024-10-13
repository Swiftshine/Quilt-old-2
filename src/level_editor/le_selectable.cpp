#include "level_editor/le_selectable.h"

LE_Selectable::LE_Selectable() {
    mSelectState = SelectState::Deselected;
    mColor = 0xFF6666FF;
    mDimensions = 20.0f;
}

LE_Selectable::~LE_Selectable() { }

void LE_Selectable::HandleDrag() {
    /// ISSUE: dragging works, but the mouse is almost never actually
    // aligned with the node itself.


    // check if we were clicked

    if (CheckLeftClick() && SelectState::Dragged != mSelectState) {
        // we were clicked
        // check if we were being dragged as well

        mDragOffset = (ToVec2f(ImGui::GetMousePos()) - mPosition) * -1.0f;
        
        if (0.0f != mDragOffset.x || 0.0f != mDragOffset.y) {
            mSelectState = SelectState::Dragged;
        }
    } else if (CheckHover() && SelectState::Dragged != mSelectState) {
        
        // we are being hovered
        mSelectState = SelectState::Hovered;

    } else if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) || SelectState::Hovered == mSelectState) {
        // the user either clicked off (selected/dragged)
        // or moved the mouse away (hovered)
        mSelectState = SelectState::Deselected; 
    }

    // adjust position while being dragged

    if (ImGui::IsMouseDown(ImGuiMouseButton_Left) && SelectState::Dragged == mSelectState) {
        mPosition = ToVec2f(ImGui::GetMousePos()) + mDragOffset;
    }

    // check if we are finally in a "selected" state

    if (ImGui::IsMouseReleased(ImGuiMouseButton_Left) && SelectState::Dragged == mSelectState) {
        mSelectState = SelectState::Selected;
    }
}

void LE_Selectable::Draw(SDL_Renderer* renderer) {
    // deselect color is pale
    // hover color is in the middle
    // select color is the main color

    RGBA drawCol;

    switch (mSelectState) {
        case SelectState::Selected:
            drawCol = mColor;
            break;
        case SelectState::Hovered:
            drawCol = RGBA(mColor.r * 0.8f, mColor.g * 0.8f, mColor.b * 0.8f, mColor.a);
            break;
        case SelectState::Deselected:
        default:
            drawCol = RGBA(mColor.r * 0.5f, mColor.g * 0.5f, mColor.b * 0.5f, mColor.a);
            break;
    }

    SDL_SetRenderDrawColor(renderer, drawCol.r, drawCol.g, drawCol.b, drawCol.a);

    SDL_Rect rect;
    rect.x = static_cast<int>(mPosition.x);
    rect.y = static_cast<int>(mPosition.y);
    rect.w = static_cast<int>(mDimensions.x);
    rect.h = static_cast<int>(mDimensions.y);


    if (SelectState::Selected == mSelectState) {
        SDL_RenderFillRect(renderer, &rect);
    } else {
        SDL_RenderDrawRect(renderer, &rect);
    }
}

void LE_Selectable::Update(SDL_Renderer* renderer) {
    HandleDrag();
    Draw(renderer);
}
