#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <iostream>
#include <string>
#include <boost/program_options.hpp>
#include "cpu.hpp"

namespace po = boost::program_options;

int main(int argc, char* argv[]);

int main(int argc, char* argv[]) {
    ///////////////////////////////////////////////////////////////////////////////////////
    // CLI arguments
    std::string rom_path;

    po::options_description desc{"Options"};
    desc.add_options()
        ("help", "Print this help message")
        ("rom_path", po::value<std::string>(&rom_path), "path of ROM to run");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return 0;
    }
    ///////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////////////////
    CPU cpu = CPU();

    cpu.load_rom(rom_path, 0);

    // PASSES
    // cpu.load_rom("./tests/gb-test-roms/cpu_instrs/individual/01-special.gb", 0);
    // cpu.load_rom("./tests/gb-test-roms/cpu_instrs/individual/03-op sp,hl.gb", 0);
    // cpu.load_rom("./tests/gb-test-roms/cpu_instrs/individual/04-op r,imm.gb", 0);
    // cpu.load_rom("./tests/gb-test-roms/cpu_instrs/individual/05-op rp.gb", 0);
    // cpu.load_rom("./tests/gb-test-roms/cpu_instrs/individual/06-ld r,r.gb", 0);
    // cpu.load_rom("./tests/gb-test-roms/cpu_instrs/individual/07-jr,jp,call,ret,rst.gb", 0);
    // cpu.load_rom("./tests/gb-test-roms/cpu_instrs/individual/08-misc instrs.gb", 0);
    // cpu.load_rom("./tests/gb-test-roms/cpu_instrs/individual/09-op r,r.gb", 0);
    // cpu.load_rom("./tests/gb-test-roms/cpu_instrs/individual/10-bit ops.gb", 0);
    // cpu.load_rom("./tests/gb-test-roms/cpu_instrs/individual/11-op a,(hl).gb", 0);

    // FAILS
    // cpu.load_rom("./tests/gb-test-roms/cpu_instrs/individual/02-interrupts.gb", 0);
    // cpu.load_rom("./tests/gb-test-roms/cpu_instrs/cpu_instrs.gb", 0);

    cpu.run();
    ///////////////////////////////////////////////////////////////////////////////////////

    return 0;
}

