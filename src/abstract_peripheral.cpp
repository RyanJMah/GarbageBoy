#include "abstract_peripheral.hpp"

void AbstractPeripheral::init(CPU* cpu_ptr) {
    this->_cpu = cpu_ptr;
}

AbstractPeripheral::~AbstractPeripheral() {}
