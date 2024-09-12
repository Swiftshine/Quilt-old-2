#include "application.h"

Application::Application() {
    mMainWindow = nullptr;
    mMainRenderer = nullptr;
    mIsSetup = false;
    mIsRunning = false;
    mRomFSPath = "";
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

    mMainWindow = SDL_CreateWindow("Quilt", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    if (PTR_INVALID(mMainWindow)) {
        // failed
        return false;
    }

    mMainRenderer = SDL_CreateRenderer(mMainWindow, -1, SDL_RENDERER_ACCELERATED);

    if (PTR_INVALID(mMainRenderer)) {
        // failed
        return false;
    }

    mIsSetup = true;
    return true;
}


void Application::Cleanup() {
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

    while (mIsRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            if (SDL_QUIT == event.type) {
                mIsRunning = false;
            }
        }
    }
}
