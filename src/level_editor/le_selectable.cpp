#include "level_editor/le_selectable.h"
#include "level_editor/level_editor.h"

LE_Selectable::LE_Selectable() {
    mSelectState = SelectState::Deselected;
    mColor = 0xFF6666FF;
    mDimensions = 16.0f;
}

LE_Selectable::~LE_Selectable() { }

void LE_Selectable::HandleDrag(const Camera& camera) {
    //// dragging works, but the mouse is almost never actually
    //// aligned with the node itself.
    //! dragging no longer works, fix this

    mCameraPosition = camera.ToCamera(mWorldPosition);

    mWorldPosition = camera.ToWorld(mCameraPosition);

    Vec2f mousePos = ToVec2f(ImGui::GetMousePos());

    // check if we were clicked

    if (CheckLeftClick(camera) && SelectState::Dragged != mSelectState) {
        // we were clicked
        // check if we were being dragged as well

        mDragOffset = (mousePos - mWorldPosition) * -1.0f;

        mSelectState = SelectState::Selected;

        if (0.0f != mDragOffset.x || 0.0f != mDragOffset.y) {
            mSelectState = SelectState::Dragged;
        }
    } else if (CheckHover(camera) && SelectState::Dragged != mSelectState) {
        
        // we are being hovered
        mSelectState = SelectState::Hovered;

    } else if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) || SelectState::Hovered == mSelectState) {
        // the user either clicked off (selected/dragged)
        // or moved the mouse away (hovered)
        mSelectState = SelectState::Deselected; 
    }

    // adjust position while being dragged

    if (ImGui::IsMouseDown(ImGuiMouseButton_Left) && SelectState::Dragged == mSelectState) {
        mCameraPosition = mousePos + mDragOffset;
        // mWorldPosition.x = camera.ToWorld(mousePos).x + mDragOffset.x;
        // mWorldPosition.y = camera.ToWorld(mousePos).y + mDragOffset.y;
        // mWorldPosition = camera.ToWorld(mCameraPosition);
    }

    // check if we are finally in a "selected" state

    if (ImGui::IsMouseReleased(ImGuiMouseButton_Left) && SelectState::Dragged == mSelectState) {
        mSelectState = SelectState::Selected;
        // mWorldPosition = camera.ToWorld(mCameraPosition);
    }
}

void LE_Selectable::Draw(const Camera& camera, SDL_Renderer* renderer) {
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

    // mCameraPosition = camera.ToCamera(mWorldPosition);

    SDL_SetRenderDrawColor(renderer, drawCol.r, drawCol.g, drawCol.b, drawCol.a);

    SDL_Rect rect;
    Vec2f pos = camera.ToCamera(mWorldPosition);

    rect.x = static_cast<int>(pos.x);
    rect.y = static_cast<int>(pos.y);
    rect.w = static_cast<int>(mDimensions.x);
    rect.h = static_cast<int>(mDimensions.y * -1.0f);

    if (SelectState::Selected == mSelectState) {
        SDL_RenderFillRect(renderer, &rect);
    } else {
        SDL_RenderDrawRect(renderer, &rect);
    }
}

void LE_Selectable::Update(const Camera& camera, SDL_Renderer* renderer) {
    HandleDrag(camera);
    Draw(camera, renderer);
}
