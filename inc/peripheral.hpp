#pragma once

#include "cpu.hpp"

class CPU;

class Peripheral {
    public:
        void init(CPU* cpu_ptr);
        virtual ~Peripheral() = 0;

        virtual void update() = 0;

    protected:
        CPU* _cpu;

};
