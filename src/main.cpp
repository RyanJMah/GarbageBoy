#include <iostream>
#include "cpu.hpp"

int main();

int main() {
    CPU cpu = CPU();

    cpu.load_rom("./tests/gb-test-roms/cpu_instrs/individual/01-special.gb", 0);
    cpu.run();

    return 0;
}

