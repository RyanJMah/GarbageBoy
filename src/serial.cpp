/*
Emulation for the serial port, prints bytes to console

reference:
    - https://gbdev.io/pandocs/Serial_Data_Transfer_(Link_Cable).html
*/

#include <iostream>
#include "helpers.hpp"
#include "abstract_peripheral.hpp"
#include "serial.hpp"

Serial::Serial(CPU* cpu_ptr) {
    AbstractPeripheral::init(cpu_ptr);
}

void Serial::respond() {
    // if transfer requested
    if (BIT_IS_SET(*SC(), SC_TRANSFER_START)) {
        // send the character in SB to the terminal
        std::cout << *SB();

        // clear the TRANSFER_START bit
        *SC() &= ~(1 << SC_TRANSFER_START);

        // make a request for a serial interrupt to the interrupt controller
        *IF() |= (1 << IF_SERIAL);
    }
}
