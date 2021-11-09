#pragma once

#include <stddef.h>
#include "cpu.hpp"
#include "abstract_peripheral.hpp"

class InterruptController: public AbstractPeripheral {
    public:
        InterruptController(CPU* cpu_ptr);
        virtual void respond();
    
    private:
        void _call_isr(size_t addr);
};
