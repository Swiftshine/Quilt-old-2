#pragma once

#define DEBUG false

#if DEBUG
#include "debug_window.h"
#endif

#include "common.h"
#include "colbin_editor.h"

const int WINDOW_WIDTH  = 1280;
const int WINDOW_HEIGHT = 720;

class Application {

public:
    // returns the application instance
    static Application* Instance() {
        static Application inst;
        return &inst;
    }
    
    // seturns if application setup was successful
    bool Setup();

    // main application loop
    void Run();

private:
    Application();
    ~Application();

    // cleans up all resources
    void Cleanup();

    /* gui functions */

    void Menu();
private:
    std::string mRomFSPath;
    bool mHasValidRomFSPath;
};