/*
The "GPU" of the emulator, tries to emulate as much of the
Gameboy's PPU as possible, but ultimately still has to use a
frame buffer to draw pixels on the screen (it's just easier this way)

reference:
    - https://gbdev.io/pandocs/Rendering.html
*/

#include <stdint.h>
#include "abstract_peripheral.hpp"
#include "screen.hpp"
#include "gpu.hpp"

GPU::GPU(CPU* cpu_ptr) {
    AbstractPeripheral::init(cpu_ptr);
    this->_screen.init();

    uint8_t test_tile[32] = {
        0x3C, 0x7E,
        0x42, 0x42,
        0x42, 0x42,
        0x42, 0x42,
        0x7E, 0x5E,
        0x7E, 0x0A,
        0x7C, 0x56,
        0x38, 0x7C
    };
    for (uint8_t x = 0; x < (GAMEBOY_WINDOW_WIDTH/8); x++) {
        for (uint8_t y = 0; y < (GAMEBOY_WINDOW_HEIGHT/8); y++) {
            this->_screen.draw_tile(x, y, test_tile);
        }
    }
}

static uint32_t tmp = 0;
void GPU::respond() {
    this->_screen.render_frame();
    if ((tmp % 50000) == 0) {
        this->_screen.window_x += 8;
        // this->_screen.window_y += 8;
    }
    tmp++;
}

