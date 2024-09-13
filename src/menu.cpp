#include "application.h"

void Application::MenuBar() {
    ImGui::BeginMainMenuBar();

    if (ImGui::BeginMenu("Quilt")) {
        if (ImGui::MenuItem("Settings")) {
            mIsSettingsOpen = !mIsSettingsOpen;
        }

        if (ImGui::MenuItem("Colbin editor")) {
            // will be implemented soon...
        }


        if (ImGui::MenuItem("Level editor")) {
            // will be implemented soon...
        }


        if (ImGui::MenuItem("GfArch utility")) {
            // will be implemented soon...
        }


        // if (ImGui::MenuItem("MNEB Editor")) {
        //     // planned, but format is not known
        // }


        // if (ImGui::MenuItem("BGST Editor")) {
        //     // planned, but format is not known
        // }
        
        ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
}

void Application::SettingsMenu() {
    ImGui::Begin("Settings", &mIsSettingsOpen);

    if (ImGui::Button("Select game root path")) {
        std::string path = pfd::select_folder("Select game root path").result();

        if (!path.empty() && Settings::Instance()->GetGameRoot() != path) {
            Settings::Instance()->SetGameRoot(path);
        }
    }
    ImGui::Text(Settings::Instance()->GetGameRoot().empty() ? "none" : Settings::Instance()->GetGameRoot().c_str());

    
    if (ImGui::Button("Save settings")) {
        Settings::Instance()->SaveToDisk();
    }

    ImGui::End();
}