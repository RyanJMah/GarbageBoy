#pragma once

#include "cpu.hpp"

class CPU;

class AbstractPeripheral {
    friend class CPU;

    public:
        void init(CPU* cpu_ptr);
        virtual ~AbstractPeripheral() = 0;

        virtual void update() = 0;

    protected:
        CPU* _cpu;

};
