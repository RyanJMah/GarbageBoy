#include <iostream>
#include "abstract_peripheral.hpp"
#include "serial.hpp"

Serial::Serial(CPU* cpu_ptr) {
    AbstractPeripheral::init(cpu_ptr);
    this->_SB = this->_cpu->mem_get(SB_ADDR);
    this->_SC = this->_cpu->mem_get(SC_ADDR);
}

void Serial::update() {
    // if transfer requested
    if ( ((*this->_SC) >> TRANSFER_START) & 1 ) {
        // send the character in SB to the terminal
        std::cout << (*this->_SB);

        // clear the TRANSFER_START bit
        *this->_SC &= ~(1 << TRANSFER_START);

        // call the serial interrupt handler
        this->_cpu->jump(SERIAL_ISR_ADDR);
    }
}
