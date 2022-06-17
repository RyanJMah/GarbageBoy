/*
Emulates the CPU

reference:
    - https://gbdev.io/pandocs/CPU_Registers_and_Flags.html
*/

#include <iostream>
#include <stdexcept>
#include <vector>
#include <fstream>

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
    this->cycles = 0;

    this->_OP_CODE_LUT_init();
    // this->_OP_CODE_LUT_init_CB();


    this->_peripherals.push_back( new Serial(this) );

    this->_peripherals.push_back( new InterruptController(this) );
}
CPU::~CPU() {
    for (size_t i = 0; i < this->_peripherals.size(); i++) {
        delete this->_peripherals[i];
    }
}

void CPU::load_rom(std::string rom_path) {
    this->_init_state();

    std::vector<uint8_t> rom_bytes = this->_read_rom_file(rom_path);
    for (size_t i = 0; i < rom_bytes.size(); i++) {
        this->mem_write_byte(i, rom_bytes[i]);
    }
}

void CPU::run() {
    // idk how much this will really improve performance, but eh...
    size_t peripheral_vect_size = this->_peripherals.size();
    uint8_t curr_opcode;
    void (CPU::*curr_instruction)();

    while (1) {
        curr_opcode = this->mem_read_byte(this->_PC.raw);
        curr_instruction = this->_OP_CODE_LUT[curr_opcode];
        (this->*curr_instruction)();

        for (size_t i = 0; i < peripheral_vect_size; i++) {
            this->_peripherals[i]->respond();
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
}
void CPU::call(size_t addr) {
    this->_push_stack(this->_PC.bytes[1]);
    this->_push_stack(this->_PC.bytes[0]);
    this->_PC.raw = addr;
}

/*
Bypasses the boot rom by setting the state to what
it needs to be to handoff the rom to a cartridge.

reference:
    - https://gbdev.io/pandocs/Power_Up_Sequence.html
    - using the DMG boot rom
*/
void CPU::_init_state() {
    this->_AF.bytes[1] = 0x01;

    this->_set_flag(ZERO_FLAG);
    this->_clear_flag(SUB_FLAG);
    this->_set_flag(HALF_CARRY_FLAG);
    this->_set_flag(CARRY_FLAG);

    this->_BC.raw = (0x00U << 8) | (0x13U);
    this->_DE.raw = (0x00U << 8) | (0xd8U);
    this->_HL.raw = (0x01U << 8) | (0x4dU);
    this->_PC.raw = 0x0100U;
    this->_SP.raw = 0xfffeU;

    this->mem_write_byte(0xff00U, 0xcfU);
    this->mem_write_byte(0xff01U, 0x00U);
    this->mem_write_byte(0xff02U, 0x7eU);
    this->mem_write_byte(0xff04U, 0xabU);
    this->mem_write_byte(0xff05U, 0x00U);
    this->mem_write_byte(0xff06U, 0x00U);
    this->mem_write_byte(0xff07U, 0xf8U);
    this->mem_write_byte(0xff0fU, 0xe1U);
    this->mem_write_byte(0xff10U, 0x80U);
    this->mem_write_byte(0xff11U, 0xbfU);
    this->mem_write_byte(0xff12U, 0xf3U);
    this->mem_write_byte(0xff13U, 0xffU);
    this->mem_write_byte(0xff14U, 0xbfU);
    this->mem_write_byte(0xff16U, 0x3fU);
    this->mem_write_byte(0xff17U, 0x00U);
    this->mem_write_byte(0xff18U, 0xffU);
    this->mem_write_byte(0xff19U, 0xbfU);
    this->mem_write_byte(0xff1aU, 0x7fU);
    this->mem_write_byte(0xff1bU, 0xffU);
    this->mem_write_byte(0xff1cU, 0x9fU);
    this->mem_write_byte(0xff1dU, 0xffU);
    this->mem_write_byte(0xff1eU, 0xbfU);
    this->mem_write_byte(0xff20U, 0xffU);
    this->mem_write_byte(0xff21U, 0x00U);
    this->mem_write_byte(0xff22U, 0x00U);
    this->mem_write_byte(0xff23U, 0xbfU);
    this->mem_write_byte(0xff24U, 0x77U);
    this->mem_write_byte(0xff25U, 0xf3U);
    this->mem_write_byte(0xff26U, 0xf1U);
    this->mem_write_byte(0xff40U, 0x91U);
    this->mem_write_byte(0xff41U, 0x85U);
    this->mem_write_byte(0xff42U, 0x00U);
    this->mem_write_byte(0xff43U, 0x00U);
    this->mem_write_byte(0xff44U, 0x00U);
    this->mem_write_byte(0xff45U, 0x00U);
    this->mem_write_byte(0xff46U, 0xffU);
    this->mem_write_byte(0xff47U, 0xfcU);
    this->mem_write_byte(0xff48U, 0x00U);
    this->mem_write_byte(0xff49U, 0x00U);
    this->mem_write_byte(0xff4aU, 0x00U);
    this->mem_write_byte(0xff4bU, 0x00U);
    this->mem_write_byte(0xff4dU, 0xffU);
    this->mem_write_byte(0xff4fU, 0xffU);
    this->mem_write_byte(0xff51U, 0xffU);
    this->mem_write_byte(0xff52U, 0xffU);
    this->mem_write_byte(0xff53U, 0xffU);
    this->mem_write_byte(0xff54U, 0xffU);
    this->mem_write_byte(0xff55U, 0xffU);
    this->mem_write_byte(0xff56U, 0xffU);
    this->mem_write_byte(0xff68U, 0xffU);
    this->mem_write_byte(0xff69U, 0xffU);
    this->mem_write_byte(0xff6aU, 0xffU);
    this->mem_write_byte(0xff6bU, 0xffU);
    this->mem_write_byte(0xff70U, 0xffU);
    this->mem_write_byte(0xffffU, 0x00U);
}

std::vector<uint8_t> CPU::_read_rom_file(std::string rom_path) {
    std::ifstream f(rom_path, std::ios::binary);

    f.seekg(0, std::ios::end);
    std::streampos f_size = f.tellg();
    f.seekg(0, std::ios::beg);

    std::vector<uint8_t> rom_data(f_size);
    f.read((char*)(&rom_data[0]), f_size);

    return rom_data;
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
            ret = &(this->_AF.bytes[0]);
            break;
        case (0b111):
            ret = &(this->_AF.bytes[1]);
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
        default:
            throw std::range_error("received invalid bitcode...");

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

