#include <iostream>
#include <SDL2/SDL.h>

int main(int argc, char* argv[]) {
    SDL_Window* window = nullptr;
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        // failed
        return 1;
    }

    window = SDL_CreateWindow("Quilt", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);

    if (nullptr == window) {
        // failed
        SDL_Quit();
        return 1;
    }

    bool running = true;

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            if (SDL_QUIT == event.type) {
                running = false;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}