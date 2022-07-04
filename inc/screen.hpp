#pragma once

#include <SDL2/SDL.h>

#define SCREEN_WIDTH    160
#define SCREEN_HEIGHT   144

class Screen {
    public:
        Screen();
        ~Screen();

        void mainloop();
        void cleanup();

    private:
        SDL_Window* _window;
        SDL_Surface* _surface;
};

