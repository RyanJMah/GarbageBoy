#pragma once

#include <stdint.h>
#include "cpu.hpp"
#include "abstract_peripheral.hpp"

class TimerController: public AbstractPeripheral {
    public:
        TimerController(CPU* cpu_ptr);
        virtual void respond();

    private:
        uint32_t _div_elapsed_cycles;
        uint32_t _tima_elapsed_cycles;

        uint32_t _prev_cycles;
};


