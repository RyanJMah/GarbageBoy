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
    Screen s = Screen();
    s.mainloop();

    CPU cpu = CPU();

    cpu.load_rom(rom_path, 0);
    cpu.run();
    ///////////////////////////////////////////////////////////////////////////////////////

    return 0;
}

