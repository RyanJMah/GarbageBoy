#include <iostream>
#include <string>
#include <boost/program_options.hpp>
#include "cpu.hpp"
#include "screen.hpp"

namespace po = boost::program_options;

int main(int argc, char* argv[]);

int main(int argc, char* argv[]) {
    ///////////////////////////////////////////////////////////////////////////////////////
    // CLI arguments
    std::string rom_path;
    bool headless = false;

    po::options_description desc{"Options"};
    desc.add_options()
        ("help", "Print this help message")
        ("rom_path", po::value<std::string>(&rom_path), "path of ROM to run")
        ("headless", po::bool_switch(&headless), "run without gui");

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

    if (!headless) {
        Screen screen = Screen();
        screen.mainloop();
    }

    cpu.run();
    ///////////////////////////////////////////////////////////////////////////////////////

    return 0;
}

