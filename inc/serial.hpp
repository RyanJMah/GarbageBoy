#pragma once

#include <stdint.h>
#include "cpu.hpp"
#include "abstract_peripheral.hpp"

#define SERIAL_ISR_ADDR     0x0058

#define SB_ADDR             0xff01
#define SC_ADDR             0xff02

#define TRANSFER_START      7
#define CLOCK_SPEED         1
#define SHIFT_CLOCK         0

class Serial: public AbstractPeripheral {
    public:
        Serial(CPU* cpu_ptr);
        virtual void update();
    
    private:
        uint8_t* _SB;
        uint8_t* _SC;
};
