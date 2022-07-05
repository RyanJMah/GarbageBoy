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
}

void GPU::respond() {
    this->_screen.draw_pixels();
}

