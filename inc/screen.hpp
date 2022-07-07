#pragma once

#include <SDL2/SDL.h>

#define FRAME_RATE              60

#define GAMEBOY_BG_WIDTH        256
#define GAMEBOY_BG_HEIGHT       256
#define GAMEBOY_WINDOW_WIDTH    160
#define GAMEBOY_WINDOW_HEIGHT   144

#define SCALING_FACTOR          4

#define SCREEN_WIDTH            GAMEBOY_WINDOW_WIDTH*SCALING_FACTOR
#define SCREEN_HEIGHT           GAMEBOY_WINDOW_HEIGHT*SCALING_FACTOR

struct RGB {
    uint8_t R;
    uint8_t G;
    uint8_t B;
};

class Screen {
    public:
        Screen();
        ~Screen();
        void init();

        void render_frame();
        void draw_tile(uint32_t x, uint32_t y, uint8_t tile[32]);

        void cleanup();

    public:
        uint8_t window_x;
        uint8_t window_y;

        RGB pixels[GAMEBOY_BG_WIDTH][GAMEBOY_BG_HEIGHT];

    private:
        RGB _palatte_to_rgb_lut[4];

    private:
        SDL_Event _event;
        SDL_Window* _window;
        SDL_Renderer* _renderer;

        uint32_t _prev_ticks;
        uint32_t _curr_ticks;
};

