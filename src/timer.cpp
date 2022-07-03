/*
Emulates timers

reference:
    - https://gbdev.io/pandocs/Timer_and_Divider_Registers.html#timer-and-divider-registers
*/

#include <exception>
#include <stdint.h>
#include "helpers.hpp"
#include "abstract_peripheral.hpp"
#include "timer.hpp"

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
    uint32_t curr_cycles = this->_cpu->cycles;
    uint32_t elapsed_cycles = curr_cycles - this->_prev_cycles;

    // increment DIV register
    this->_div_elapsed_cycles += elapsed_cycles;
    uint32_t div_inc = elapsed_cycles/256;
    if (div_inc > 0) {
        *this->DIV() += div_inc;
        this->_div_elapsed_cycles = 0;
    }

    if (BIT_IS_SET(*this->TAC(), 2)) {
        this->_tima_elapsed_cycles += elapsed_cycles;

        // get TIMA increment
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
            default:
                throw std::logic_error("this should not happen ever, please report a bug...");
        }

        uint32_t tima_inc = this->_tima_elapsed_cycles/clk_div;
        if (tima_inc > 0) {
            if ((*this->TIMA() + tima_inc) > 0xff) {
                // if overflow will happen...
                uint8_t wrap_around = (*this->TIMA() + tima_inc) % 0xff;
                *this->TIMA() = *this->TMA();
                *this->TIMA() += wrap_around;

                // generate an interrupt on overflow
                this->generate_interrupt(TIMER_IRQ);
            }
            else {
                // if no overflow, increment as usual
                (*this->TIMA()) += tima_inc;
            }
            this->_tima_elapsed_cycles = 0;
        }
    }

    this->_prev_cycles = curr_cycles;
}
