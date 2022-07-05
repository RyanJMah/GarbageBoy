#pragma once

#include <SDL2/SDL.h>

#define GAMEBOY_SCREEN_WIDTH    160
#define GAMEBOY_SCREEN_HEIGHT   144

#define SCALING_FACTOR          4

#define SCREEN_WIDTH            GAMEBOY_SCREEN_WIDTH*SCALING_FACTOR
#define SCREEN_HEIGHT           GAMEBOY_SCREEN_HEIGHT*SCALING_FACTOR

struct RGB {
    uint8_t R;
    uint8_t G;
    uint8_t B;
};

class Screen {
    public:
        Screen();
        ~Screen();

        void draw_pixels();
        void cleanup();

    public:
        RGB pixels[GAMEBOY_SCREEN_WIDTH][GAMEBOY_SCREEN_HEIGHT];

    private:
        SDL_Event _event;
        SDL_Window* _window;
        SDL_Renderer* _renderer;
};

