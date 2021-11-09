#include "peripheral.hpp"

void Peripheral::init(CPU* cpu_ptr) {
    this->_cpu = cpu_ptr;
}

Peripheral::~Peripheral() {}
