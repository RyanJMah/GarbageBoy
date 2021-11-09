#pragma once

#include <stdint.h>
#include "cpu.hpp"
#include "abstract_peripheral.hpp"

class Serial: public AbstractPeripheral {
    public:
        Serial(CPU* cpu_ptr);
        virtual void respond();
};
