#include "application.h"

void Application::Menu() {
    ImGui::BeginMainMenuBar();

    if (ImGui::BeginMenu("Quilt")) {
        if (ImGui::MenuItem("Select RomFS Path")) {
            // will be implemented soon...
        }

        if (ImGui::MenuItem("Colbin Editor")) {
            // will be implemented soon...
        }


        if (ImGui::MenuItem("Level Editor")) {
            // will be implemented soon...
        }


        if (ImGui::MenuItem("GfArch Utility")) {
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
