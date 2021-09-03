#include <iostream>
#include <stdint.h>
#include <stddef.h>
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

	// load up the _OP_CODE_LUT with instructions
	this->_OP_CODE_LUT[0x00] = &CPU::_nop;

	this->_OP_CODE_LUT[0x40] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x41] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x42] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x43] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x44] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x45] = &CPU::_ld_r_R;
	// this->_OP_CODE_LUT[0x46] = &CPU::_ld_r_HL;
	this->_OP_CODE_LUT[0x47] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x48] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x49] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x4A] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x4B] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x4C] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x4D] = &CPU::_ld_r_R;
	// this->_OP_CODE_LUT[0x4E] = &CPU::_ld_r_HL;
	this->_OP_CODE_LUT[0x4F] = &CPU::_ld_r_R;
}
CPU::~CPU() {

}
void CPU::run() {
	while (1) {
		auto curr_instruction = this->_OP_CODE_LUT[ this->_mem_read_byte(this->_PC.raw) ];
		(this->*curr_instruction)();
	}
}

uint8_t CPU::_mem_read_byte(size_t addr) {
	return this->_memory[addr];
}
void CPU::_mem_write_byte(size_t addr, uint8_t val) {
	this->_memory[addr] = val;
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
			ret = &(this->_BC.bytes[0]);
		case (0b001):
			ret = &(this->_BC.bytes[1]);
		case (0b010):
			ret = &(this->_DE.bytes[0]);
		case (0b011):
			ret = &(this->_DE.bytes[1]);
		case (0b100):
			ret = &(this->_HL.bytes[0]);
		case (0b101):
			ret = &(this->_HL.bytes[1]);
		case (0b110):
			ret = &(this->_AF.bytes[0]);
		case (0b111):
			ret = &(this->_AF.bytes[1]);
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
		case (0b01):
			ret = &(this->_DE);
		case (0b10):
			ret = &(this->_HL);
		case (0b11):
			ret = &(this->_SP);
	}
	return ret;
}

/*
NOP
	- OpCode = 0x00
	- Do nothing for 4 clock cycles

*/
void CPU::_nop() {
	this->_read_and_increment_PC();
	this->_cycles += 4;
}

/*
LD r, r'
	- OpCode = 0b01xxxyyy
	- load to the 8 bit register r, data from the 8-bit register r'
*/
void CPU::_ld_r_R() {
	uint8_t opcode = this->_read_and_increment_PC();

	uint8_t* r = this->_get_8_bit_reg( (opcode >> 3) & 0b111 );
	uint8_t* R = this->_get_8_bit_reg(opcode & 0b111);
	(*r) = (*R);

	this->_cycles += 4;
}