#include <iostream>
#include <exception>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <string.h>
#include "screen.hpp"

Screen::Screen() {}

void Screen::init() {
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
    this->_renderer = SDL_CreateRenderer(this->_window, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderSetLogicalSize(this->_renderer, GAMEBOY_WINDOW_WIDTH, GAMEBOY_WINDOW_HEIGHT);

    RGB white       = {.R = 255, .G = 255, .B = 255};
    RGB light_grey  = {.R = 170, .G = 170, .B = 170};
    RGB grey        = {.R = 85, .G = 85, .B = 85};
    RGB black       = {.R = 0, .G = 0, .B = 0};

    this->_palatte_to_rgb_lut[0b00] = white;
    this->_palatte_to_rgb_lut[0b01] = light_grey;
    this->_palatte_to_rgb_lut[0b10] = grey;
    this->_palatte_to_rgb_lut[0b11] = black;

    // start with the whole screen white...
    for (uint32_t x = 0; x < GAMEBOY_BG_WIDTH; x++) {
        for (uint32_t y = 0; y < GAMEBOY_BG_HEIGHT; y++) {
            this->pixels[x][y] = white;
        }
    }

    this->window_x = 0;
    this->window_y = 0;

    this->_prev_ticks = 0;
    this->_curr_ticks = 0;
}
Screen::~Screen() { this->cleanup(); }

void Screen::cleanup() {
    SDL_DestroyWindow(this->_window);
    SDL_Quit();
}

void Screen::render_frame() {
    if (SDL_PollEvent(&this->_event)) {
        switch (this->_event.type) {
            case SDL_QUIT:
                exit(0);
        }
    }

    this->_curr_ticks = SDL_GetTicks();
    if ((this->_curr_ticks - this->_prev_ticks) > (1E3/FRAME_RATE)) {
        for (uint32_t y = 0; y < GAMEBOY_WINDOW_HEIGHT; y++) {
            for (uint32_t x = 0; x < GAMEBOY_WINDOW_WIDTH; x++) {
                uint8_t actual_x = (this->window_x + x) % GAMEBOY_BG_WIDTH;
                uint8_t actual_y = (this->window_y + y) % GAMEBOY_BG_HEIGHT;

                RGB p = this->pixels[actual_x][actual_y];
                SDL_SetRenderDrawColor(this->_renderer, p.R, p.G, p.B, 0xFF);
                SDL_RenderDrawPoint(this->_renderer, x, y);
            }
        }
        SDL_RenderPresent(this->_renderer);

        this->_prev_ticks = this->_curr_ticks;
    }

}


void Screen::draw_tile(uint32_t x, uint32_t y, uint8_t tile[32]) {
    uint32_t x_ = 8*x;
    uint32_t y_ = 8*y;

    for (uint8_t i = 0; i < 32; i+=2) {
        uint8_t lsb_byte = tile[i];
        uint8_t msb_byte = tile[i + 1];

        for (uint8_t j = 0; j < 8; j++) {
            uint8_t lsb = (lsb_byte >> j) & 1;
            uint8_t msb = (msb_byte >> j) & 1;
            uint8_t palette = (msb << 1) | lsb;

            // bit 7 is rightmost...
            this->pixels[x_ + (7 - j)][y_] = this->_palatte_to_rgb_lut[palette];
        }

        y_++;
    }
}



