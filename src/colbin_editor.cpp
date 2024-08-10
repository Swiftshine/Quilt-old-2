#include "colbin_editor.h"

bool ColbinEditor::IsRunning = false;

ColbinEditor::ColbinEditor()
    : mFileOpen(false)
    , mpColbinFile(nullptr)
    , mCamera(this)
{ }

ColbinEditor::~ColbinEditor() { }


void ColbinEditor::Run() {
    if (!IsRunning) {
        return;
    }
    
    ImGui::Begin("Colbin Editor", &IsRunning, ImGuiWindowFlags_MenuBar);

    mCamera.Update();


    Menu();

    ImGui::Text("Camera (X, Y, Zoom): %f, %f, %f", mCamera.x, mCamera.y, mCamera.zoom);

    FileProperties();
    RenderFile();


    ImGui::End();
}

void ColbinEditor::Menu() {
    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("Editor")) {
            if (ImGui::MenuItem("Open File")) {
                OpenFile();   
            }

            if (mFileOpen) {
                if (ImGui::MenuItem("Save File")) {
                    SaveFile(false);
                }

                if (ImGui::MenuItem("Save File As")) {
                    SaveFile(true);
                }

                if (ImGui::MenuItem("Close File")) {
                    mFileOpen = false;
                    mColbinFilepath = "";
                    mpColbinFile.reset();
                }
            }

            if (ImGui::MenuItem("Hide Editor")) {
                IsRunning = false;
            }

            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
}


/* file io */

void ColbinEditor::OpenFile() {
    nfdu8char_t* path;
    nfdu8filteritem_t filters[] = { {"Collision Files", "colbin"} };
    nfdopendialogu8args_t args = {0};
    args.filterList = filters;
    args.filterCount = 1;
    nfdresult_t result = NFD_OpenDialogU8_With(&path, &args);
    switch (result) {
        case NFD_CANCEL: return;
        case NFD_OKAY: {
            mColbinFilepath = path;
            NFD_FreePathU8(path);
            try {
                LoadFile();
            } catch (const std::runtime_error& e) {
                std::cerr << e.what();
            }
            return;
        }
        default: AppLog::Error(NFD_GetError());
    }
}

void ColbinEditor::SaveFile(bool saveAs) {
    if (!mFileOpen) { return; }

    std::string savePath = mColbinFilepath;

    if (saveAs) {
        nfdu8char_t* path;
        nfdu8filteritem_t filters[] = { {"Collision Files", "colbin"} };
        nfdsavedialogu8args_t args = {0};
        args.filterList = filters;
        args.filterCount = 1;
        nfdresult_t result = NFD_SaveDialogU8_With(&path, &args);

        switch (result) {
            case NFD_CANCEL: return;
            case NFD_OKAY: {
                savePath = path;
                NFD_FreePathU8(path);
                break;
            }
            default: AppLog::Error(NFD_GetError());
        }
    }

    std::ofstream file(savePath, std::ios::out | std::ios::binary);

    if (!file.is_open()) {
        AppLog::Error("Colbin Editor - unable to create file.");
    }

    mpColbinFile->Write(file);
    file.close();
}


void ColbinEditor::LoadFile() {
    if (!fs::is_regular_file(mColbinFilepath)) {
        AppLog::Error("Colbin Editor - File does not exist.");
    }

    std::ifstream file(mColbinFilepath, std::ios::in | std::ios::binary);

    if (!file.is_open()) {
        AppLog::Error("Colbin Editor - Could not open file.");
    }
    mpColbinFile.reset();
    mpColbinFile = std::make_unique<key::colbin::wrapper::Colbin>(file);
    file.close();

    mFileOpen = true;
}

void ColbinEditor::RenderFile() {
    if (!mFileOpen) {
        return;
    }

    static Vec2f origin;

    ImGui::GetWindowDrawList()->AddCircleFilled(quilt::ToImVec2(origin), 1.0f, 0xFFFFFFFF, 32);
    auto curPos = ImGui::GetCursorPos();
    ImGui::SetCursorPos(quilt::ToImVec2(origin));
    ImGui::Text("Origin");
    ImGui::SetCursorPos(curPos);

    for (auto i = 0; i < mpColbinFile->GetEntryCount(); i++) {
        ImVec2 p1 = quilt::ToImVec2(mpColbinFile->GetEntry(i)->GetPoint1());
        ImVec2 p2 = quilt::ToImVec2(mpColbinFile->GetEntry(i)->GetPoint2());


        p1 = quilt::ToWindow(mCamera, p1);
        p2 = quilt::ToWindow(mCamera, p2);

        ImGui::GetWindowDrawList()->AddLine(p1, p2, 0xFFFFFFFF, 1.0f);
    }
}

void ColbinEditor::FileProperties() {
    if (!mFileOpen) { return; }

    ImGui::Text("%s", fs::path(mColbinFilepath).filename().string().c_str());
    
    if (ImGui::CollapsingHeader("File Properties")) {
        float unk0 = mpColbinFile->GetUnk0();
        ImGui::InputFloat("unknown float at 0x0", &unk0);
        mpColbinFile->SetUnk0(unk0);

        ImGui::Text("Lines: %d", mpColbinFile->GetEntryCount());
        ImGui::Text("Collision types: %d", mpColbinFile->GetCollisionTypeCount());

        if (ImGui::CollapsingHeader("Collision Types")) {
            for (auto i = 0; i < mpColbinFile->GetCollisionTypeCount(); i++) {
                ImGui::Selectable(mpColbinFile->GetCollisionType(i).c_str());
            }
        }
    }

}