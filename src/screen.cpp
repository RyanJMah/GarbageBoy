#include <iostream>
#include <exception>
#include <SDL2/SDL.h>
#include <screen.hpp>

Screen::Screen() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error(SDL_GetError());
    }
    this->_window = SDL_CreateWindow(
        "garbageboy",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (this->_window == NULL) {
        throw std::runtime_error(SDL_GetError());
    }

    this->_surface = SDL_GetWindowSurface(this->_window);
}
Screen::~Screen() { this->cleanup(); }

void Screen::cleanup() {
    SDL_DestroyWindow(this->_window);
    SDL_Quit();
}

void Screen::mainloop() {
    SDL_Event e;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    quit = true;
            }
        }

    }

    this->cleanup();
}


