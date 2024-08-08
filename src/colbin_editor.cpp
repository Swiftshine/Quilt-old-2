#include "colbin_editor.h"

bool ColbinEditor::IsRunning = false;

ColbinEditor::ColbinEditor()
    : mFileOpen(false)
    , mpColbinFile(nullptr)
{ }

ColbinEditor::~ColbinEditor() { }


void ColbinEditor::Run() {
    if (!IsRunning) {
        return;
    }
    
    ImGui::Begin("Colbin Editor", &IsRunning, ImGuiWindowFlags_MenuBar);
    
    Menu();

    RenderFile();

    ImGui::End();
}

void ColbinEditor::Menu() {
    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("Editor")) {
            if (ImGui::MenuItem("Open File")) {
                nfdu8char_t* path;
                nfdu8filteritem_t filters[] = { {"Collision Files", "colbin"} };

                nfdopendialogu8args_t args = {0};
                args.filterList = filters;
                args.filterCount = 1;
                nfdresult_t result = NFD_OpenDialogU8_With(&path, &args);

                switch (result) {
                    case NFD_CANCEL: break;

                    case NFD_OKAY: {
                        mColbinFilepath = path;
                        NFD_FreePathU8(path);

                        try {
                            LoadFile();
                        } catch (const std::runtime_error& e) {
                            std::cerr << e.what();
                        }

                        break;
                    }

                    default: AppLog::Error(NFD_GetError());
                }

                
            }

            // if (ImGui::MenuItem("Save")) {

            // }

            if (ImGui::MenuItem("Close")) {
                IsRunning = false;
            }

            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
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

    ImGui::GetWindowDrawList()->AddCircleFilled(quilt::ToWindowCenter(origin), 1.0f, 0xFFFFFFFF, 32);
    auto curPos = ImGui::GetCursorPos();
    ImGui::SetCursorPos(quilt::ToWindowCenter(origin));
    ImGui::Text("Origin");
    ImGui::SetCursorPos(curPos);

    for (auto i = 0; i < mpColbinFile->GetEntryCount(); i++) {
        ImVec2 p1 = quilt::ToWindowCenter(mpColbinFile->At(i)->GetPoint1(), true);
        ImVec2 p2 = quilt::ToWindowCenter(mpColbinFile->At(i)->GetPoint2(), true);

        ImGui::GetWindowDrawList()->AddLine(p1, p2, 0xFFFFFFFF, 1.0f);
    }
}
