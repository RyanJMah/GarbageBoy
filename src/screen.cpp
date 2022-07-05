#include <iostream>
#include <exception>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <string.h>
#include "screen.hpp"

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
    this->_renderer = SDL_CreateRenderer(this->_window, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderSetLogicalSize(this->_renderer, GAMEBOY_SCREEN_WIDTH, GAMEBOY_SCREEN_HEIGHT);

    RGB white = {
        .R = 0xFF,
        .G = 0xFF,
        .B = 0xFF
    };
    memset(
        (void*)(&this->pixels[0][0]),
        *(int*)(&white),
        GAMEBOY_SCREEN_WIDTH*GAMEBOY_SCREEN_HEIGHT*sizeof(RGB)
    );
}
Screen::~Screen() { this->cleanup(); }

void Screen::cleanup() {
    SDL_DestroyWindow(this->_window);
    SDL_Quit();
}

void Screen::draw_pixels() {
    while (SDL_PollEvent(&this->_event)) {
        switch (this->_event.type) {
            case SDL_QUIT:
                exit(0);
        }
    }

    for (uint32_t y = 0; y < GAMEBOY_SCREEN_HEIGHT; y++) {
        for (uint32_t x = 0; x < GAMEBOY_SCREEN_WIDTH; x++) {
            uint8_t r = this->pixels[x][y].R;
            uint8_t g = this->pixels[x][y].G;
            uint8_t b = this->pixels[x][y].B;

            SDL_SetRenderDrawColor(this->_renderer, r, g, b, 0xFF);
            SDL_RenderDrawPoint(this->_renderer, x, y);
        }
    }
    SDL_RenderPresent(this->_renderer);
}



