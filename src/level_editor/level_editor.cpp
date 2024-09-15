#include "level_editor.h"
#include "application.h"
#include "gfarch_utility.h"

const std::string LevelResourceIDListPath = "res/quiltdata/level_resource_ids.json";

LevelEditor::LevelEditor() {
    mIsActive = false;
    mTryOpenByName = false;
    mLevelOpen = false;

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
}

void LevelEditor::Run() {
    if (!mIsActive) {
        return;
    }

    Menu();
    if (mTryOpenByName) {
        OpenByName();
    }
    

}

void LevelEditor::Menu() {
    ImGui::Begin("Level editor viewport", &mIsActive, ImGuiWindowFlags_MenuBar);
    
    ImGui::BeginMenuBar();

    if (ImGui::BeginMenu("Menu")) {
        if (ImGui::MenuItem("Close")) {
            mIsActive = false;
        }

        if (ImGui::MenuItem("Open level by name")) {
            mTryOpenByName = true;
        }

        if (ImGui::MenuItem("Open level by archive")) {

        }
        
        ImGui::EndMenu();
    }

    ImGui::EndMenuBar();

    Render();


    if (!mCurrentLevelPath.empty()) {
        ImGui::Text(mCurrentLevelPath.c_str());
    }

    ImGui::End();
}

void LevelEditor::OpenByName() {
    AppLog::Assert(!Settings::Instance()->GetGameRoot().empty(), "Game root must not be empty!");

    ImGui::Begin("Level list", &mTryOpenByName);

    for (auto& pair : mLevelList) {
        if (ImGui::Selectable(pair.first.c_str())) {

            std::stringstream ss;
            ss << std::setw(3) << std::setfill('0') << pair.second;
            std::string filename = "stage" + ss.str() + ".gfa";
            std::string path = Settings::Instance()->GetGameRoot() + "mapdata/" + filename;
            mCurrentLevelContents = GfArchUtility::Extract(path);
            mCurrentLevelPath = path;
            mTryOpenByName = false;
            mLevelOpen = true;
            ImGui::End();
            ProcessLevelContents();
            return;
        }
    }
    ImGui::End();
}

void LevelEditor::Render() {
    SDL_Renderer* renderer = Application::Instance()->GetMainRenderer();
    SDL_SetRenderTarget(renderer, mTexture);
    
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    SDL_Point start = {600, 600};
    SDL_Point end = {700, 800};

    SDL_RenderDrawLine(renderer, start.x, start.y, end.x, end.y);


    ImGui::GetWindowDrawList()->AddImage(
        (void*)mTexture,
        ImGui::GetWindowPos(),
        ImGui::GetWindowPos() + ImGui::GetWindowSize(),
        {0.0f, 0.0f}, {1.0f, 1.0f}
    );

    SDL_SetRenderTarget(renderer, nullptr);
}

void LevelEditor::ProcessLevelContents() {
    if (!mLevelOpen) {
        return;
    }

    
}
