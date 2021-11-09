#include <iostream>
#include "cpu.hpp"

int main();

int main() {
    CPU cpu = CPU();

    cpu.load_rom("./tests/gb-test-roms/cpu_instrs/individual/06-ld r,r.gb");
    cpu.run();

    return 0;
}

