#include "level_editor/le_selectable.h"
#include "level_editor/level_editor.h"

LE_Selectable::LE_Selectable() {
    mSelectState = SelectState::Deselected;
    mColor = 0xFF0000FF;
    mDimensions = 16.0f;
}

LE_Selectable::~LE_Selectable() { }

void LE_Selectable::HandleDrag(const Camera& camera) {
    // take our world position and use the mouse position adjusted to the world to 
    // move our world position

    Vec2f mousePos = camera.MouseToWorld();

    // check if we were clicked
    if (CheckLeftClick(camera) && SelectState::Dragged != mSelectState) {
        AppLog::Print("Clicked X: " + std::to_string(mWorldPosition.x) + " Y: " + std::to_string(mWorldPosition.y));
        // we were clicked
        mSelectState = SelectState::Selected;

        // determine if we are being dragged

        mDragOffset = mousePos - mWorldPosition;

        if (0.0f != mDragOffset.x || 0.0f != mDragOffset.y) {
            mSelectState = SelectState::Dragged;
        }
    } else if (CheckHover(camera) && SelectState::Dragged != mSelectState) {
        // we are being hovered
        mSelectState = SelectState::Hovered;
    } else if (ImGui::IsMouseClicked(ImGuiMouseButton_Right) || SelectState::Hovered == mSelectState) {
        // the user either clicked off (selected/dragged)
        // or moved the mouse away (hovered)
        mSelectState = SelectState::Deselected; 
    }

    if (ImGui::IsMouseDown(ImGuiMouseButton_Left) && SelectState::Dragged == mSelectState) {
        // mWorldPosition = mWorldPosition + mDragOffset;
        // mWorldPosition = mousePos;

        mWorldPosition = mousePos - mDragOffset;
        AppLog::Print("Dragging X: " + std::to_string(mWorldPosition.x) + " Y: " + std::to_string(mWorldPosition.y));
    }
    
    if (ImGui::IsMouseReleased(ImGuiMouseButton_Left) && SelectState::Dragged == mSelectState) {
        mSelectState = SelectState::Selected;
        mDragOffset = 0.0f;
        AppLog::Print("Ending X: " + std::to_string(mWorldPosition.x) + " Y: " + std::to_string(mWorldPosition.y));
        // mWorldPosition = camera.ToWorld(mCameraPosition);
    }



    // mCameraPosition = camera.ToCamera(mWorldPosition);

    // Vec2f mousePos = ToVec2f(ImGui::GetMousePos());

    // // check if we were clicked

    // if (CheckLeftClick(camera) && SelectState::Dragged != mSelectState) {
    //     // we were clicked
    //     // check if we were being dragged as well

    //     mDragOffset = (mousePos - mCameraPosition);

    //     mSelectState = SelectState::Selected;

    //     if (0.0f != mDragOffset.x || 0.0f != mDragOffset.y) {
    //         mSelectState = SelectState::Dragged;
    //     }
    // } else if (CheckHover(camera) && SelectState::Dragged != mSelectState) {
        
    //     // we are being hovered
    //     mSelectState = SelectState::Hovered;

    // }
    // // else if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) || SelectState::Hovered == mSelectState) {
    // //     // the user either clicked off (selected/dragged)
    // //     // or moved the mouse away (hovered)
    // //     mSelectState = SelectState::Deselected; 
    // // }

    // else if (ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {
    //     mSelectState = SelectState::Deselected;
    // }

    // // adjust position while being dragged

    // if (ImGui::IsMouseDown(ImGuiMouseButton_Left) && SelectState::Dragged == mSelectState) {
    //     mCameraPosition = mousePos + mDragOffset;
    //     mWorldPosition = camera.ToWorld(mCameraPosition);
    //     // mWorldPosition.x = camera.ToWorld(mousePos).x + mDragOffset.x;
    //     // mWorldPosition.y = camera.ToWorld(mousePos).y + mDragOffset.y;
    //     // mWorldPosition = camera.ToWorld(mCameraPosition);
    // }

    // // check if we are finally in a "selected" state

    // if (ImGui::IsMouseReleased(ImGuiMouseButton_Left) && SelectState::Dragged == mSelectState) {
    //     mSelectState = SelectState::Selected;
    //     // mWorldPosition = camera.ToWorld(mCameraPosition);
    // }
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
        case SelectState::Dragged:
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

    SDL_FRect rect;
    Vec2f pos = camera.ToCamera(mWorldPosition);

    rect.x = pos.x + mDimensions.x;
    rect.y = pos.y;
    rect.w = mDimensions.x;
    rect.h = mDimensions.y;

    if (SelectState::Selected == mSelectState) {
        SDL_RenderFillRectF(renderer, &rect);
    } else {
        SDL_RenderDrawRectF(renderer, &rect);
    }
}

void LE_Selectable::Update(const Camera& camera, SDL_Renderer* renderer) {
    HandleDrag(camera);
    Draw(camera, renderer);
}
