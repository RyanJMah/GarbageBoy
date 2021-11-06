#include <stdint.h>
#include <stddef.h>
#include "serial.hpp"
#include "interrupt_controller.hpp"
#include "cpu.hpp"

CPU::CPU() {
    this->_AF.raw = 0x0000;
    this->_BC.raw = 0x0000;
    this->_DE.raw = 0x0000;
    this->_HL.raw = 0x0000;
    this->_SP.raw = 0x0000;
    this->_PC.raw = 0x0000;

    for (size_t i = 0; i < 0xffff; i++) { this->_memory[i] = 0; }
    this->_cycles = 0;

    this->_OP_CODE_LUT_init();
	this->_OP_CODE_LUT_init_CB();

    this->_peripherals.push_back( new Serial(this) );
    this->_peripherals.push_back( new InterruptController(this) );
}
CPU::~CPU() {
    for (size_t i = 0; i < this->_peripherals.size(); i++) {
        delete this->_peripherals[i];
    }
}

void CPU::run() {
    // idk how much this will really improve performance, but eh...
    size_t peripheral_vect_size = this->_peripherals.size();
    void (CPU::*curr_instruction)();

    while (1) {
        curr_instruction = this->_OP_CODE_LUT[ this->mem_read_byte(this->_PC.raw) ];
        (this->*curr_instruction)();

        for (size_t i = 0; i < peripheral_vect_size; i++) {
            this->_peripherals[i]->update();
        }
    }
}

uint8_t CPU::mem_read_byte(size_t addr) {
    return this->_memory[addr];
}
void CPU::mem_write_byte(size_t addr, uint8_t val) {
    this->_memory[addr] = val;
}
uint8_t* CPU::mem_get(size_t addr) {
    return &this->_memory[addr];
}

void CPU::jump(size_t addr) {
    this->_PC.raw = addr;
    this->_cycles += MACHINE_CYCLE*4;
}

uint8_t CPU::_read_and_increment_PC() {
    uint8_t ret = this->_memory[this->_PC.raw];
    this->_PC.raw += 1;
    return ret;
}

/*
Bitcodes:
    000 -> B
    001 -> C
    010 -> D
    011 -> E
    100 -> H
    101 -> L
    110 -> F
    111 -> A
*/
uint8_t* CPU::_get_8_bit_reg(uint8_t bitcode) {
    uint8_t* ret = nullptr;
    switch (bitcode) {
        case (0b000):
            ret = &(this->_BC.bytes[1]);
            break;
        case (0b001):
            ret = &(this->_BC.bytes[0]);
            break;
        case (0b010):
            ret = &(this->_DE.bytes[1]);
            break;
        case (0b011):
            ret = &(this->_DE.bytes[0]);
            break;
        case (0b100):
            ret = &(this->_HL.bytes[1]);
            break;
        case (0b101):
            ret = &(this->_HL.bytes[0]);
            break;
        case (0b110):
            ret = &(this->_AF.bytes[1]);
            break;
        case (0b111):
            ret = &(this->_AF.bytes[0]);
            break;
    }
    return ret;
}

/*
Bitcodes:
    00 -> BC
    01 -> DE
    10 -> HL
    11 -> SP
*/
Reg* CPU::_get_16_bit_reg(uint8_t bitcode) {
    Reg* ret = nullptr;
    switch (bitcode) {
        case (0b00):
            ret = &(this->_BC);
            break;
        case (0b01):
            ret = &(this->_DE);
            break;
        case (0b10):
            ret = &(this->_HL);
            break;
        case (0b11):
            ret = &(this->_SP);
            break;
    }
    return ret;
}

/*
Bitcodes:
    00 -> NZ
    01 -> Z
    10 -> NC
    11 -> C
*/
bool CPU::_eval_cond_code(uint8_t bitcode) {
    bool ret;
    switch (bitcode) {
        case (0b00):
            ret = (this->_get_flag(ZERO_FLAG) != 0);
            break;
        case (0b01):
            ret = (this->_get_flag(ZERO_FLAG) == 0);
            break;
        case (0b10):
            ret = (this->_get_flag(CARRY_FLAG) != 0);
            break;
        case (0b11):
            ret = (this->_get_flag(CARRY_FLAG) == 0);
            break;
    }
    return ret;
}

void CPU::_push_stack(uint8_t byte) {
    this->_SP.raw -= 1;
    this->mem_write_byte(this->_SP.raw, byte);
}
uint8_t CPU::_pop_stack() {
    uint8_t ret = this->mem_read_byte(this->_SP.raw);
    this->_SP.raw += 1;
    return ret;
}

void CPU::_set_flag(uint8_t flag) {
    this->_AF.bytes[0] |= (1 << flag);
}
void CPU::_clear_flag(uint8_t flag) {
    this->_AF.bytes[0] &= ~(1 << flag);
}
bool CPU::_get_flag(uint8_t flag) {
    return (this->_AF.bytes[0] >> flag) & 1;
}

uint8_t CPU::_add_bytes(uint8_t a, uint8_t b) {
    uint8_t ret = a + b;

    if (ret == 0) { this->_set_flag(ZERO_FLAG); }
    else { this->_clear_flag(ZERO_FLAG); }

    this->_clear_flag(SUB_FLAG);

    if (CHECK_8_BIT_HALF_CARRY(a, b)) { this->_set_flag(HALF_CARRY_FLAG); }
    else { this->_clear_flag(HALF_CARRY_FLAG); }

    if (CHECK_8_BIT_CARRY(a, b)) { this->_set_flag(CARRY_FLAG); }
    else { this->_clear_flag(HALF_CARRY_FLAG); }

    return ret;
}
uint8_t CPU::_sub_bytes(uint8_t a, uint8_t b) {
    uint8_t ret = a - b;

    if (ret == 0) { this->_set_flag(ZERO_FLAG); }
    else { this->_clear_flag(ZERO_FLAG); }

    this->_set_flag(SUB_FLAG);

    if (CHECK_SUB_HALF_CARRY(a, b)) { this->_set_flag(HALF_CARRY_FLAG); }
    else { this->_clear_flag(HALF_CARRY_FLAG); }

    if (CHECK_SUB_CARRY(a, b)) { this->_set_flag(CARRY_FLAG); }
    else { this->_clear_flag(CARRY_FLAG); }

    return ret;
}

