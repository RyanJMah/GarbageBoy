#pragma once

#include "cpu.hpp"
#include "abstract_peripheral.hpp"

#define IE      0xffff
#define IF      0xff0f

class InterruptController: public AbstractPeripheral {
    public:
        InterruptController(CPU* cpu_ptr);
        virtual void update();
};
