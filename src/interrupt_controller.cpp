#include "interrupt_controller.hpp"

InterruptController::InterruptController(CPU* cpu_ptr) {
    AbstractPeripheral::init(cpu_ptr);
}

void InterruptController::update() {

}
