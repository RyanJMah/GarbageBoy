#include <iostream>
#include "cpu.hpp"

int main();

int main() {
    CPU cpu = CPU();

    // PASSES
    // cpu.load_rom("./tests/gb-test-roms/cpu_instrs/individual/01-special.gb", 0);
    // cpu.load_rom("./tests/gb-test-roms/cpu_instrs/individual/05-op rp.gb", 0);
    // cpu.load_rom("./tests/gb-test-roms/cpu_instrs/individual/06-ld r,r.gb", 0);
    // cpu.load_rom("./tests/gb-test-roms/cpu_instrs/individual/09-op r,r.gb", 0);
    // cpu.load_rom("./tests/gb-test-roms/cpu_instrs/individual/11-op a,(hl).gb", 0);

    // FAILS
    // cpu.load_rom("./tests/gb-test-roms/cpu_instrs/individual/02-interrupts.gb", 0);
    // cpu.load_rom("./tests/gb-test-roms/cpu_instrs/individual/03-op sp,hl.gb", 0);
    cpu.load_rom("./tests/gb-test-roms/cpu_instrs/individual/04-op r,imm.gb", 0);
    // cpu.load_rom("./tests/gb-test-roms/cpu_instrs/individual/07-jr,jp,call,ret,rst.gb", 0);
    // cpu.load_rom("./tests/gb-test-roms/cpu_instrs/individual/08-misc instrs.gb", 0);
    // cpu.load_rom("./tests/gb-test-roms/cpu_instrs/individual/10-bit ops.gb", 0);
    // cpu.load_rom("./tests/gb-test-roms/cpu_instrs/cpu_instrs.gb", 0);

    cpu.run();

    return 0;
}

