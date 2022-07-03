/*
Abstract base class for a CPU peripheral
*/

#include "abstract_peripheral.hpp"

void AbstractPeripheral::init(CPU* cpu_ptr) {
    this->_cpu = cpu_ptr;
}

AbstractPeripheral::~AbstractPeripheral() {}

void AbstractPeripheral::generate_interrupt(IRQ irq) {
    *this->IF() |= (1 << irq);
}

///////////////////////////////////////////////////////////////////////////////////
/* INTERRUPT REGISTERS AND FLAGS */
bool* AbstractPeripheral::IME() { return &this->_cpu->IME; }
uint8_t* AbstractPeripheral::IE() { return this->_cpu->mem_get(0xffffU); }
uint8_t* AbstractPeripheral::IF() { return this->_cpu->mem_get(0xff0fU); }
///////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////
/* TIMER REGISTERS */
uint8_t* AbstractPeripheral::DIV() { return this->_cpu->mem_get(0xff04U); }
uint8_t* AbstractPeripheral::TIMA() { return this->_cpu->mem_get(0xff05U); }
uint8_t* AbstractPeripheral::TMA() { return this->_cpu->mem_get(0xff06U); }
uint8_t* AbstractPeripheral::TAC() { return this->_cpu->mem_get(0xff07U); }
///////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////
/* SERIAL REGISTERS */
uint8_t* AbstractPeripheral::SB() { return this->_cpu->mem_get(0xff01U); }
uint8_t* AbstractPeripheral::SC() { return this->_cpu->mem_get(0xff02U); }
///////////////////////////////////////////////////////////////////////////////////
