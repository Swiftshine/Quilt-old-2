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
    static bool b; // scratch boolean for many things
    ImGui::Begin("Settings", &mIsSettingsOpen);
    
    ImGui::SeparatorText("Quilt settings");
    b = Settings::Instance()->GetAutoSaveSettings();
    ImGui::Checkbox("Automatically save settings on change", &b);

    if (b != Settings::Instance()->GetAutoSaveSettings()) {
        Settings::Instance()->SetAutoSaveSettings(b);
    }


    if (ImGui::Button("Select game root path")) {
        std::string path = pfd::select_folder("Select game root path").result();

        if (!path.empty() && Settings::Instance()->GetGameRoot() != path) {
            Settings::Instance()->SetGameRoot(path);
        }
    }

    ImGui::Text(Settings::Instance()->GetGameRoot().empty() ? "none" : Settings::Instance()->GetGameRoot().c_str());

    ImGui::SeparatorText("Other");
    if (ImGui::Button("Save settings")) {
        Settings::Instance()->SaveToDisk();
    }

    ImGui::End();
}
