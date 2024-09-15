#include "level_editor.h"
#include "application.h"
#include "gfarch_utility.h"

const std::string LevelResourceIDListPath = "res/quiltdata/level_resource_ids.json";

LevelEditor::LevelEditor() {
    mIsActive = false;
    mTryOpenByName = false;
    mLevelOpen = false;
    mCurrentFileIndex.mEnbinIndex = -1;
    mCurrentFileIndex.mMapbinIndex = -1;

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
    
    ShowFiles();

}

void LevelEditor::Menu() {
    ImGui::Begin("Level editor viewport", &mIsActive, ImGuiWindowFlags_MenuBar);
    
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
            mCurrentFileIndex.mEnbinIndex = -1;
            mCurrentFileIndex.mMapbinIndex = -1;
        }
        ImGui::EndMenu();
    }

    ImGui::EndMenuBar();

    Render();


    if (!mCurrentLevelPath.empty() && -1 != mCurrentFileIndex.mEnbinIndex && -1 != mCurrentFileIndex.mMapbinIndex) {
        ImGui::Text(mCurrentLevelPath.c_str());
        std::string text = "Editing files " + mCurrentLevelContents[mCurrentFileIndex.mEnbinIndex].GetFilename() + " and " + mCurrentLevelContents[mCurrentFileIndex.mMapbinIndex].GetFilename();
        ImGui::Text(text.c_str());
    }

    ImGui::End();
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
            ProcessLevelContents();
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
        filters).result();
    
    if (pathVector.empty()) {
        return;
    }

    std::string path = pathVector[0];
    mCurrentLevelPath = path;
    mCurrentLevelContents = GfArchUtility::Extract(path);
    mLevelOpen = true;
    ProcessLevelContents();
}

void LevelEditor::Render() {
    if (!mLevelOpen && -1 != mCurrentFileIndex.mEnbinIndex && -1 != mCurrentFileIndex.mMapbinIndex) {
        return;
    }

    SDL_Renderer* renderer = Application::Instance()->GetMainRenderer();
    SDL_SetRenderTarget(renderer, mTexture);
    
    // start drawing
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    SDL_Point start = {600, 600};
    SDL_Point end = {700, 800};

    SDL_RenderDrawLine(renderer, start.x, start.y, end.x, end.y);

    // end drawing
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
            mCurrentFileIndex.mEnbinIndex = i;
            mCurrentFileIndex.mMapbinIndex = i + 1;
            break;
        }
    }

    ImGui::End();
}
