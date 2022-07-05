#pragma once

#include <stdint.h>
#include "cpu.hpp"
#include "screen.hpp"
#include "abstract_peripheral.hpp"

class GPU: public AbstractPeripheral {
    public:
        GPU(CPU* cpu_ptr);
        virtual void respond();

    private:
        Screen _screen;
};

