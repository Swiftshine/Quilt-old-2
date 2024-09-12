#pragma once

#include "common.h"

#define WINDOW_WIDTH   1280
#define WINDOW_HEIGHT  720

class Application {
public:
    /**
     * @note Returns the application instance.
     */
    static Application* Instance() {
        static Application inst;
        return &inst;
    }

    /**
     * @note Sets up the application.
     * @return Boolean indicating if the application was setup successfully.
     */
    bool Setup();

    /**
     * @note Runs the application main loop.
     */
    void Run();
private:
    Application();
    ~Application();

    /**
     * @note Cleans up all resources. Called upon class destruction.
     */
    void Cleanup();

    /**
     * @note Processes SDL2 events.
     * @return Boolean indicating if the application should continue running.
     */
    bool ProcessEvents();


    /* GUI functions */

    /**
     * @note Draws the menu.
     */
    void Menu();
private:
    SDL_Window* mMainWindow;
    SDL_Renderer* mMainRenderer;
    bool mIsSetup;
    bool mIsRunning;
    std::string mRomFSPath;
    bool mHasValidRomFSPath;
};
