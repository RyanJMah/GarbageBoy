/*
Emulates interrupts

reference:
    - https://gbdev.io/pandocs/Interrupts.html
*/

#include <stddef.h>
#include "helpers.hpp"
#include "abstract_peripheral.hpp"
#include "interrupt_controller.hpp"

InterruptController::InterruptController(CPU* cpu_ptr) {
    AbstractPeripheral::init(cpu_ptr);
}

void InterruptController::_call_isr(size_t addr) {
    this->_cpu->IME = 0;
    this->_cpu->call(addr);
    this->_cpu->cycles += MACHINE_CYCLE*5;
}

void InterruptController::respond() {
    if (*IME()) {
        // if a particular interrupt is enabled AND an
        // interrupt is requested, jump to the relevant ISR
        if (BIT_IS_SET(*IF(), IF_VBLANK) && BIT_IS_SET(*IE(), IE_VBLANK)) {
            this->_call_isr(VBLANK_ISR_ADDR);
            *IF() &= ~(1 << VBLANK_IRQ);
        }
        else if (BIT_IS_SET(*IF(), IF_LCD_STAT) && BIT_IS_SET(*IE(), IE_LCD_STAT)) {
            this->_call_isr(LCD_STAT_ISR_ADDR);
            *IF() &= ~(1 << LCD_STAT_IRQ);
        }
        else if (BIT_IS_SET(*IF(), IF_TIMER) && BIT_IS_SET(*IE(), IE_TIMER)) {
            this->_call_isr(TIMER_ISR_ADDR);
            *IF() &= ~(1 << TIMER_IRQ);
        }
        else if (BIT_IS_SET(*IF(), IF_SERIAL) && BIT_IS_SET(*IE(), IE_SERIAL)) {
            this->_call_isr(SERIAL_ISR_ADDR);
            *IF() &= ~(1 << SERIAL_IRQ);
        }
        else if (BIT_IS_SET(*IF(), IF_JOYPAD) && BIT_IS_SET(*IE(), IE_JOYPAD)) {
            this->_call_isr(JOYPAD_ISR_ADDR);
            *IF() &= ~(1 << JOYPAD_IRQ);
        }
    }
}
