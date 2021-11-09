/*
Abstract base class for a CPU peripheral
*/

#include "abstract_peripheral.hpp"

void AbstractPeripheral::init(CPU* cpu_ptr) {
    this->_cpu = cpu_ptr;
}

AbstractPeripheral::~AbstractPeripheral() {}

/*
gosh I really hate C++ sometimes
*/

///////////////////////////////////////////////////////////////////////////////////
/* INTERRUPT REGISTERS AND FLAGS */
bool* AbstractPeripheral::IME() { return &this->_cpu->IME; }
uint8_t* AbstractPeripheral::IE() { return this->_cpu->mem_get(0xffffU); }
uint8_t* AbstractPeripheral::IF() { return this->_cpu->mem_get(0xff0fU); }

///////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////
/* SERIAL REGISTERS */
uint8_t* AbstractPeripheral::SB() { return this->_cpu->mem_get(0xff01U); }
uint8_t* AbstractPeripheral::SC() { return this->_cpu->mem_get(0xff02U); }
///////////////////////////////////////////////////////////////////////////////////
