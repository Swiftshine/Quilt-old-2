#include "level_editor/level_editor.h"
#include "level_editor/le_selectable.h"
#include "application.h"
#include "gfarch_utility.h"

const std::string LevelResourceIDListPath = "res/quiltdata/level_resource_ids.json";

LevelEditor::LevelEditor() {
    mIsActive = false;
    mTryOpenByName = false;
    mLevelOpen = false;
    InvalidateFileIndices();

    ordered_json contents = ordered_json::parse(std::ifstream(LevelResourceIDListPath));
    for (auto& pair : contents.items()) {
        mLevelList.emplace_back(pair.key(), pair.value());
    }

    mTexture = SDL_CreateTexture(Application::Instance()->GetMainRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WINDOW_WIDTH, WINDOW_HEIGHT);

    if (PTR_INVALID(mTexture)) {
        // failed
        AppLog::Error("Failed to create level editor texture");
    }
}

LevelEditor::~LevelEditor() {
    mLevelList.clear();
    ClearSelectables();
}

void LevelEditor::Run() {
    if (!mIsActive) {
        return;
    }

    ImGui::Begin("Level editor viewport", &mIsActive, ImGuiWindowFlags_MenuBar);

    Menu();

    if (mTryOpenByName) {
        OpenByName();
    }
    
    ShowFiles();

    mCamera.mWindowPosition = {ImGui::GetWindowPos().x, ImGui::GetWindowPos().y};
    mCamera.mWindowDimensions = {ImGui::GetWindowSize().x, ImGui::GetWindowSize().y};
    mWindowHovered = ImGui::IsWindowHovered();
    mWindowFocused = ImGui::IsWindowFocused();

    UpdateLevel();


    if (!mCurrentLevelPath.empty() && FileIndicesValid()) {
        ImGui::SeparatorText("Level information");
        if (Settings::Instance()->GetLEDisplayLevelPath()) {
            ImGui::Text(mCurrentLevelPath.c_str());
        }
        std::string text = "Editing files " + mCurrentLevelContents[mCurrentFileIndex.mEnbinIndex].GetFilename() + " and " + mCurrentLevelContents[mCurrentFileIndex.mMapbinIndex].GetFilename();
        ImGui::Text(text.c_str());

        ImGui::SeparatorText("Camera information");
        ImGui::Text(std::string("Zoom: " + std::to_string(mCamera.mZoom)).c_str());
        ImGui::Text(std::string("Position: " + std::to_string(mCamera.mPosition.x) + ", " + std::to_string(mCamera.mPosition.y)).c_str());
    }

    ImGui::End();
}

void LevelEditor::Menu() {
    ImGui::BeginMenuBar();

    if (ImGui::BeginMenu("Menu")) {
        if (ImGui::MenuItem("Close editor")) {
            mIsActive = false;
        }

        if (ImGui::MenuItem("Open level by name")) {
            mTryOpenByName = true;
        }

        if (ImGui::MenuItem("Open level by archive")) {
            OpenByArchive();
        }
        
        if (ImGui::MenuItem("Close file")) {
            mLevelOpen = false;
            mCurrentLevelPath = "";
            mCurrentLevelContents.clear();
            InvalidateFileIndices();
        }
        ImGui::EndMenu();
    }

    ImGui::EndMenuBar();
}

void LevelEditor::OpenByName() {
    ImGui::Begin("Level list", &mTryOpenByName);

    std::string root = Settings::Instance()->GetGameRoot();
    if (root.empty()) {
        ImGui::Text("The current game root is empty!");
        ImGui::End();
        return;
    } else if (!fs::is_directory(root)) {
        ImGui::Text("The current game root does not exist!");
        ImGui::End();
        return;
    } else if (!Quilt::ValidateRoot(root)) {
        ImGui::Text("The current game root does not contain the required folders!");
        ImGui::End();
        return;
    }

    for (auto& pair : mLevelList) {
        if (ImGui::Selectable(pair.first.c_str())) {

            std::stringstream ss;
            ss << std::setw(3) << std::setfill('0') << pair.second;
            std::string filename = "stage" + ss.str() + ".gfa";
            std::string path = root + "mapdata/" + filename;
            mCurrentLevelContents = GfArchUtility::Extract(path);
            mCurrentLevelPath = path;
            mTryOpenByName = false;
            mLevelOpen = true;
            InvalidateFileIndices();
            break;
        }
    }
    ImGui::End();
}

void LevelEditor::OpenByArchive() {
    static const std::vector<std::string> filters = {
        "GfArch files (*.gfa)", "*.gfa",
    };

    std::vector<std::string> pathVector = pfd::open_file(
        "Select level archive",
        ".",
        filters
    ).result();
    
    if (pathVector.empty()) {
        return;
    }

    std::string path = pathVector[0];
    mCurrentLevelPath = path;
    mCurrentLevelContents = GfArchUtility::Extract(path);
    mLevelOpen = true;
}

void LevelEditor::ProcessLevelContents() {
    if (!mLevelOpen && FileIndicesValid()) {
        return;
    }
    
    
    const std::vector<char>& data = mCurrentLevelContents[mCurrentFileIndex.mMapbinIndex].GetData();
    mCurrentMapbin.Read(data);


    // add selectables
    ClearSelectables();

    for (auto i = 0; i < mCurrentMapbin.GetNumGimmicks(); i++) {
        auto& gmk = mCurrentMapbin.GetGimmick(i);
        LE_Selectable sel;
        sel.SetPosition(gmk.GetPosition());
        mGimmickSelectables.push_back(sel);
    }
}

void LevelEditor::ShowFiles() {
    if (!mLevelOpen) {
        return;
    }

    ImGui::Begin("File");
    ImGui::SeparatorText(strippath(mCurrentLevelPath).c_str());

    // each enbin will typically have a corresponding mapbin
    // since i want to render them both in the same window, i need to
    // do some trickery here
    
    for (auto i = 0; i < mCurrentLevelContents.size(); i += 2) {
        Quilt::File& f = mCurrentLevelContents[i];
        std::string name = fs::path(f.GetFilename()).stem().string();
        if (ImGui::Selectable(name.c_str(), i == mCurrentFileIndex.mEnbinIndex)) {
            if (i == mCurrentFileIndex.mEnbinIndex) {
                continue;
            }
            SetFileIndices(i, i + 1);
            ProcessLevelContents();
            break;
        }
    }

    ImGui::End();
}

void LevelEditor::UpdateCamera(SDL_Event& event) {
    if (!mLevelOpen) {
        return;
    }

    bool keyPressed = false;

    switch (event.key.keysym.sym) {
        case SDLK_a:
            keyPressed = true;
            mCamera.mPosition.x += mCamera.mSpeed;
            break;
        case SDLK_d:
            keyPressed = true;
            mCamera.mPosition.x -= mCamera.mSpeed;
            break;
        case SDLK_w:
            keyPressed = true;
            mCamera.mPosition.y += mCamera.mSpeed;
            break;
        case SDLK_s:
            keyPressed = true;
            mCamera.mPosition.y -= mCamera.mSpeed;
            break;
        case SDLK_r:
            keyPressed = true;
            mCamera.mPosition.x = 0.0f;
            mCamera.mPosition.y = 0.0f;
            break;
    }

    if (keyPressed) {
        mCamera.UpdateSpeed();
    } else {
        mCamera.Decelerate();
    }

    if (!(mWindowFocused && mWindowHovered)) {
        return;
    }

    if (SDL_MOUSEWHEEL == event.type) {
        if (event.wheel.y > 0) {
            mCamera.mZoom += 0.1f;
        } else if (event.wheel.y < 0) {
            mCamera.mZoom -= 0.1f;
        }
    }

    if (1.0f > mCamera.mZoom) {
        mCamera.mZoom = 1.0f;
    }
}

void LevelEditor::UpdateLevel() {
    if (!mLevelOpen && FileIndicesValid()) {
        return;
    }

    SDL_Renderer* renderer = Application::Instance()->GetMainRenderer();
    SDL_SetRenderTarget(renderer, mTexture);
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    // start drawing

    for (auto i = 0; i < mCurrentMapbin.GetNumWalls(); i++) {
        auto& wall = mCurrentMapbin.GetWall(i);
        SDL_FPoint start = {wall.GetStart(). x,wall.GetStart().y};
        SDL_FPoint end = {wall.GetEnd().x, wall.GetEnd().y};
        
        start = mCamera.ToCamera(start);
        end = mCamera.ToCamera(end);;

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLineF(renderer, start.x, start.y, end.x, end.y);
    }

    // for (auto i = 0; i < mCurrentMapbin.GetNumGimmicks(); i++) {
    //     auto& gmk = mCurrentMapbin.GetGimmick(i);
    //     auto& sel = mGimmickSelectables[i];

    //     sel.Update(mCamera, renderer);

    //     if (LE_Selectable::SelectState::Selected == sel.GetState()) {
    //         mSelectedGimmickSelectables.push_back(i);
    //     }
    // }


    if (0 != mCurrentMapbin.GetNumGimmicks()) {
        auto& gmk = mCurrentMapbin.GetGimmick(0);
        auto& sel = mGimmickSelectables[0];
        sel.Update(mCamera, renderer);
        if (LE_Selectable::SelectState::Selected == sel.GetState()) {
            mSelectedGimmickSelectables.push_back(0);
        }
    }
    DisplayEntityOptions();

    
    // for (auto& gmk : mGimmickSelectables) {
    //     gmk.Update(mCamera, renderer);
    // }
    // for (auto i = 0; i < mCurrentMapbin.GetNumGimmicks(); i++) {
    //     auto& gimmick = mCurrentMapbin.GetGimmick(i);
    //     SDL_FPoint points[5];

    //     // bottom left
    //     points[0] = {gimmick.GetPosition().x, gimmick.GetPosition().y};
    //     // top left
    //     points[1] = SDL_FPoint({points[0].x, points[0].y + 1.0f});
    //     // top right
    //     points[2] = SDL_FPoint({points[0].x + 1.0f, points[0].y + 1.0f});
    //     // bottom right
    //     points[3] = SDL_FPoint({points[0].x + 1.0f, points[0].y});
    //     // bottom left
    //     points[4] = points[0];

    //     for (auto& point : points) {
    //         mCamera.AdjustPosition(point);
    //     }

    //     SDL_SetRenderDrawColor(renderer, 0x78, 0xE3, 0xFD, 255);
    //     // SDL_RenderDrawRectF(renderer, &rect);
    //     SDL_RenderDrawLinesF(renderer, points, ARRAY_LENGTH(points));
    // }


    // end drawing

    ImGui::GetWindowDrawList()->AddImage(
        static_cast<void*>(mTexture),
        ImGui::GetWindowPos(),
        ImGui::GetWindowPos() + ImGui::GetWindowSize(),
        {0.0f, 0.0f}, {1.0f, 1.0f}
    );

    SDL_SetRenderTarget(renderer, nullptr);
}

void LevelEditor::DisplayEntityOptions() {

    // gimmicks   
    if (1 == mSelectedGimmickSelectables.size()) {
        // int index = mSelectedGimmickSelectables[0];

        // auto& sel = mGimmickSelectables[index];
        // auto& gmk = mCurrentMapbin.GetGimmick(index);

        // // draw settings

        // ImGui::Begin("Gimmick Settings");
        // ImGui::Text(std::string("Name: " + gmk.GetName()).c_str());
        
        // Vec2f pos = sel.GetPosition();

        // ImGui::InputFloat("X pos", &pos.x);
        // ImGui::InputFloat("Y pos", &pos.y);

        // gmk.SetPosition(pos);
        // sel.SetPosition(pos);


        // ImGui::End();

        // clear indices
        mSelectedGimmickSelectables.clear();
    }

}
