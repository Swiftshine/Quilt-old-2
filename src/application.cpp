#include "application.h"
#include "level_editor.h"

Application::Application() {
    mMainWindow = nullptr;
    mMainRenderer = nullptr;
    mIsSetup = false;
    mIsRunning = false;
    mIsSettingsOpen = false;
    mGameRoot = "";
    mHasValidRomFSPath = false;
}

Application::~Application() { 
    Cleanup();
}

bool Application::Setup() {
    // setup SDL2

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        // failed
        return false;
    }

    mMainWindow = SDL_CreateWindow(
        "Quilt", 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        WINDOW_WIDTH, 
        WINDOW_HEIGHT, 
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED
    );

    if (PTR_INVALID(mMainWindow)) {
        // failed
        return false;
    }

    mMainRenderer = SDL_CreateRenderer(mMainWindow, -1, SDL_RENDERER_ACCELERATED);

    if (PTR_INVALID(mMainRenderer)) {
        // failed
        return false;
    }

    // setup ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForSDLRenderer(mMainWindow, mMainRenderer);
    ImGui_ImplSDLRenderer2_Init(mMainRenderer);

    mIsSetup = true;
    return true;
}


void Application::Cleanup() {
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();


    if (PTR_VALID(mMainRenderer)) {
        SDL_DestroyRenderer(mMainRenderer);
    }

    if (PTR_VALID(mMainWindow)) {
        SDL_DestroyWindow(mMainWindow);
    }

    SDL_Quit();
}

void Application::Run() {
    mIsRunning = true;

    SDL_Texture* texture = nullptr;
    
    while (mIsRunning) {
        // processing
        if (!ProcessEvents()) {
            break;
        }

        // rendering
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        ImGui::DockSpaceOverViewport();
        
        // menu
        MenuBar();
        LevelEditor::Instance()->Run();

        if (mIsSettingsOpen) {
            SettingsMenu();
        }

        ImGui::Render();

        // clear renderer before drawing ImGui
        SDL_SetRenderDrawColor(mMainRenderer, 0, 0, 0, 255);
        SDL_RenderClear(mMainRenderer);


        // render ImGui data after clearing
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), mMainRenderer);
        SDL_RenderPresent(mMainRenderer);
    }
}


bool Application::ProcessEvents() {
    static SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (SDL_QUIT == event.type) {
            mIsRunning = false;
            return false;
        } else if (SDL_KEYDOWN == event.type || SDL_MOUSEWHEEL == event.type) {
            LevelEditor::Instance()->UpdateCamera(event);
        }

        ImGui_ImplSDL2_ProcessEvent(&event);
    }

    return true;
}
