#include "application.h"

Application::Application()
    : mpMainWindow(nullptr)  
    , mHasValidRomFSPath(false)  
{ }

Application::~Application() {
    Cleanup();
}

bool Application::Setup() {
    // setup GLFW
    glfwInit();

    // OpenGL 3.3 Core

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    mpMainWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Quilt", nullptr, nullptr);

    if (!mpMainWindow) {
        glfwTerminate();
        AppLog::Error("Failed to create GLFW window.");
    }

    glfwMakeContextCurrent(mpMainWindow);
    gladLoadGL();
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(mpMainWindow, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    NFD_Init();

    return true;
}

void Application::Cleanup() {
    NFD_Quit();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(mpMainWindow);
    glfwTerminate();
}

void Application::Run() {
    while (!glfwWindowShouldClose(mpMainWindow)) {
        glClearColor(0, 0, 0, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::DockSpaceOverViewport();
        // ----

        Menu();

        // ----
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(mpMainWindow);
        glfwPollEvents();
    }
}

/* gui functions */

void Application::Menu() {
    ImGui::BeginMainMenuBar();

    if (ImGui::BeginMenu("Editor")) {
        if (ImGui::MenuItem("Select RomFS Path")) {
            nfdu8char_t* path;
            nfdresult_t result = NFD_PickFolderU8(&path, nullptr);

            switch (result) {
                case NFD_CANCEL:break;
                case NFD_OKAY: {
                    mRomFSPath = path;
                    NFD_FreePathU8(path);
                    break;
                }
                default: AppLog::Error(NFD_GetError());
            }
        }

        if (ImGui::MenuItem("Level Editor")) {
            // will be implemented soon...
        }

        if (ImGui::MenuItem("Colbin Editor")) {
            // will be implemented soon...
        }

        if (ImGui::MenuItem("GfArch Utility")) {
            // will be implemented soon...
        }
        
        /*
        if (ImGui::MenuItem("MNEB Editor")) {
            // planned, but format is not known
        }

        if (ImGui::MenuItem("BGST Editor")) {
            // planned, but format is not known
        }
        */

        ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
}