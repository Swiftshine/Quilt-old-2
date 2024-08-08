#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_internal.h>

#include <nfd.h>

#include <filesystem>
#include <string>
#include <iostream>

namespace fs = std::filesystem;

#include "applog.h"


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
    GLFWwindow* mpMainWindow;
    std::string mRomFSPath;
    bool mHasValidRomFSPath;
};