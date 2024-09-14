#pragma once

#include "common.h"
#include "settings.h"

#define WINDOW_WIDTH   1280
#define WINDOW_HEIGHT  720

class Application {
public:
    static Application* Instance() {
        static Application inst;
        return &inst;
    }

    // returns if setup was successful
    bool Setup();
    void Run();
    SDL_Window* GetMainWindow() {
        return mMainWindow;
    }

    SDL_Renderer* GetMainRenderer() {
        return mMainRenderer;
    }
private:
    Application();
    ~Application();

    // this is called upon class destruction
    void Cleanup();

    bool ProcessEvents();


    /* GUI functions */

    void MenuBar();
    void SettingsMenu();
private:
    SDL_Window* mMainWindow;
    SDL_Renderer* mMainRenderer;
    bool mIsSetup;
    bool mIsRunning;
    bool mIsSettingsOpen;
    std::string mGameRoot;
    bool mHasValidRomFSPath;
};
