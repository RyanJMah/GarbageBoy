/*
Emulates timers

reference:
    - https://gbdev.io/pandocs/Timer_and_Divider_Registers.html#timer-and-divider-registers
*/

#include <stdint.h>
#include "helpers.hpp"
#include "abstract_peripheral.hpp"
#include "timers.hpp"

TimerController::TimerController(CPU* cpu_ptr) {
    AbstractPeripheral::init(cpu_ptr);
    this->_prev_cycles = 0;
}

/*
NOTE:
    - CPU clock freq = 4194304Hz

    - DIV register increments at 16384Hz (cpu_clock/256)
    - TAC:
        - bit2: timer enable
        - bits 1-0:
            - 00: TIMA = CPU_CLOCK/1024
            - 01: TIMA = CPU_CLOCK/16
            - 10: TIMA = CPU_CLOCK/64
            - 11: TIMA = CPU_CLOCK/256
*/

void TimerController::respond() {
    uint32_t elapsed_cycles = this->_cpu->cycles - this->_prev_cycles;

    uint32_t div_inc = elapsed_cycles/256;
    (*this->DIV()) += div_inc;

    if (BIT_IS_SET(*this->TAC(), 2)) {
        uint32_t clk_div;
        switch (*this->TAC() & 0b11) {
            case 0b00:
                clk_div = 1024;
                break;
            case 0b01:
                clk_div = 16;
                break;
            case 0b10:
                clk_div = 64;
                break;
            case 0b11:
                clk_div = 256;
                break;
            default;
                clk_div = 0;
        }

        (*this->TIMA()) += elapsed_cycles/clk_div;
    }
}
