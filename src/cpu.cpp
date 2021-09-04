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

	////////////////////////////////////////////////////////////////
	// load up the _OP_CODE_LUT with instructions
	////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////
	/* 0x00 */
	this->_OP_CODE_LUT[0x00] = &CPU::_nop;
	// this->_OP_CODE_LUT[0x01] =
	this->_OP_CODE_LUT[0x02] = &CPU::_ld_BC_A;
	// this->_OP_CODE_LUT[0x03] =
	// this->_OP_CODE_LUT[0x04] =
	// this->_OP_CODE_LUT[0x05] =
	this->_OP_CODE_LUT[0x06] = &CPU::_ld_r_n;
	// this->_OP_CODE_LUT[0x07] =
	// this->_OP_CODE_LUT[0x08] =
	// this->_OP_CODE_LUT[0x09] =
	this->_OP_CODE_LUT[0x0A] = &CPU::_ld_A_BC;
	// this->_OP_CODE_LUT[0x0B] =
	// this->_OP_CODE_LUT[0x0C] =
	// this->_OP_CODE_LUT[0x0D] =
	this->_OP_CODE_LUT[0x0E] = &CPU::_ld_r_n;
	// this->_OP_CODE_LUT[0x0F] =
	////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////
	/* 0x10 */
	// this->_OP_CODE_LUT[0x10] =
	// this->_OP_CODE_LUT[0x11] =
	this->_OP_CODE_LUT[0x12] = &CPU::_ld_DE_A;
	// this->_OP_CODE_LUT[0x13] =
	// this->_OP_CODE_LUT[0x14] =
	// this->_OP_CODE_LUT[0x15] =
	this->_OP_CODE_LUT[0x16] = &CPU::_ld_r_n;
	// this->_OP_CODE_LUT[0x17] =
	// this->_OP_CODE_LUT[0x18] =
	// this->_OP_CODE_LUT[0x19] =
	this->_OP_CODE_LUT[0x1A] = &CPU::_ld_A_DE;
	// this->_OP_CODE_LUT[0x1B] =
	// this->_OP_CODE_LUT[0x1C] =
	// this->_OP_CODE_LUT[0x1D] =
	this->_OP_CODE_LUT[0x1E] = &CPU::_ld_r_n;
	// this->_OP_CODE_LUT[0x1F] =
	////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////
	/* 0x20 */
	// this->_OP_CODE_LUT[0x20] =
	// this->_OP_CODE_LUT[0x21] =
	this->_OP_CODE_LUT[0x22] = &CPU::_ldi_HL_A ;
	// this->_OP_CODE_LUT[0x23] =
	// this->_OP_CODE_LUT[0x24] =
	// this->_OP_CODE_LUT[0x25] =
	this->_OP_CODE_LUT[0x26] = &CPU::_ld_r_n;
	// this->_OP_CODE_LUT[0x27] =
	// this->_OP_CODE_LUT[0x28] =
	// this->_OP_CODE_LUT[0x29] =
	this->_OP_CODE_LUT[0x2A] = &CPU::_ldi_A_HL;
	// this->_OP_CODE_LUT[0x2B] =
	// this->_OP_CODE_LUT[0x2C] =
	// this->_OP_CODE_LUT[0x2D] =
	this->_OP_CODE_LUT[0x2E] = &CPU::_ld_r_n;
	// this->_OP_CODE_LUT[0x2F] =
	////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////
	/* 0x30 */
	// this->_OP_CODE_LUT[0x30] =
	// this->_OP_CODE_LUT[0x31] =
	this->_OP_CODE_LUT[0x32] = &CPU::_ldd_HL_A ;
	// this->_OP_CODE_LUT[0x33] =
	// this->_OP_CODE_LUT[0x34] =
	// this->_OP_CODE_LUT[0x35] =
	this->_OP_CODE_LUT[0x36] = &CPU::_ld_r_n;
	// this->_OP_CODE_LUT[0x37] =
	// this->_OP_CODE_LUT[0x38] =
	// this->_OP_CODE_LUT[0x39] =
	this->_OP_CODE_LUT[0x3A] = &CPU::_ldd_A_HL;
	// this->_OP_CODE_LUT[0x3B] =
	// this->_OP_CODE_LUT[0x3C] =
	// this->_OP_CODE_LUT[0x3D] =
	this->_OP_CODE_LUT[0x3E] = &CPU::_ld_r_n;
	// this->_OP_CODE_LUT[0x3F] =
	////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////
	/* 0x40 */
	this->_OP_CODE_LUT[0x40] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x41] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x42] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x43] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x44] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x45] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x46] = &CPU::_ld_r_HL;
	this->_OP_CODE_LUT[0x47] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x48] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x49] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x4A] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x4B] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x4C] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x4D] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x4E] = &CPU::_ld_r_HL;
	this->_OP_CODE_LUT[0x4F] = &CPU::_ld_r_R;
	////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////
	/* 0x50 */
	this->_OP_CODE_LUT[0x50] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x51] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x52] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x53] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x54] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x55] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x56] = &CPU::_ld_r_HL;
	this->_OP_CODE_LUT[0x57] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x58] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x59] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x5A] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x5B] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x5C] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x5D] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x5E] = &CPU::_ld_r_HL;
	this->_OP_CODE_LUT[0x5F] = &CPU::_ld_r_R;
	////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////
	/* 0x60 */
	this->_OP_CODE_LUT[0x60] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x61] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x62] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x63] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x64] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x65] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x66] = &CPU::_ld_r_HL;
	this->_OP_CODE_LUT[0x67] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x68] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x69] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x6A] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x6B] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x6C] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x6D] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x6E] = &CPU::_ld_r_HL;
	this->_OP_CODE_LUT[0x6F] = &CPU::_ld_r_R;
	////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////
	/* 0x70 */
	this->_OP_CODE_LUT[0x70] = &CPU::_ld_HL_r;
	this->_OP_CODE_LUT[0x71] = &CPU::_ld_HL_r;
	this->_OP_CODE_LUT[0x72] = &CPU::_ld_HL_r;
	this->_OP_CODE_LUT[0x73] = &CPU::_ld_HL_r;
	this->_OP_CODE_LUT[0x74] = &CPU::_ld_HL_r;
	this->_OP_CODE_LUT[0x75] = &CPU::_ld_HL_r;
	// this->_OP_CODE_LUT[0x76] =
	this->_OP_CODE_LUT[0x77] = &CPU::_ld_HL_r;
	this->_OP_CODE_LUT[0x78] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x79] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x7A] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x7B] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x7C] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x7D] = &CPU::_ld_r_R;
	this->_OP_CODE_LUT[0x7E] = &CPU::_ld_r_HL;
	this->_OP_CODE_LUT[0x7F] = &CPU::_ld_r_R;
	////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////
	/* 0x80 */
	// this->_OP_CODE_LUT[0x80] =
	// this->_OP_CODE_LUT[0x81] =
	// this->_OP_CODE_LUT[0x82] =
	// this->_OP_CODE_LUT[0x83] =
	// this->_OP_CODE_LUT[0x84] =
	// this->_OP_CODE_LUT[0x85] =
	// this->_OP_CODE_LUT[0x86] =
	// this->_OP_CODE_LUT[0x87] =
	// this->_OP_CODE_LUT[0x88] =
	// this->_OP_CODE_LUT[0x89] =
	// this->_OP_CODE_LUT[0x8A] =
	// this->_OP_CODE_LUT[0x8B] =
	// this->_OP_CODE_LUT[0x8C] =
	// this->_OP_CODE_LUT[0x8D] =
	// this->_OP_CODE_LUT[0x8E] =
	// this->_OP_CODE_LUT[0x8F] =
	////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////
	/* 0x90 */
	// this->_OP_CODE_LUT[0x90] =
	// this->_OP_CODE_LUT[0x91] =
	// this->_OP_CODE_LUT[0x92] =
	// this->_OP_CODE_LUT[0x93] =
	// this->_OP_CODE_LUT[0x94] =
	// this->_OP_CODE_LUT[0x95] =
	// this->_OP_CODE_LUT[0x96] =
	// this->_OP_CODE_LUT[0x97] =
	// this->_OP_CODE_LUT[0x98] =
	// this->_OP_CODE_LUT[0x99] =
	// this->_OP_CODE_LUT[0x9A] =
	// this->_OP_CODE_LUT[0x9B] =
	// this->_OP_CODE_LUT[0x9C] =
	// this->_OP_CODE_LUT[0x9D] =
	// this->_OP_CODE_LUT[0x9E] =
	// this->_OP_CODE_LUT[0x9F] =
	////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////
	/* 0xA0 */
	// this->_OP_CODE_LUT[0xA0] =
	// this->_OP_CODE_LUT[0xA1] =
	// this->_OP_CODE_LUT[0xA2] =
	// this->_OP_CODE_LUT[0xA3] =
	// this->_OP_CODE_LUT[0xA4] =
	// this->_OP_CODE_LUT[0xA5] =
	// this->_OP_CODE_LUT[0xA6] =
	// this->_OP_CODE_LUT[0xA7] =
	// this->_OP_CODE_LUT[0xA8] =
	// this->_OP_CODE_LUT[0xA9] =
	// this->_OP_CODE_LUT[0xAA] =
	// this->_OP_CODE_LUT[0xAB] =
	// this->_OP_CODE_LUT[0xAC] =
	// this->_OP_CODE_LUT[0xAD] =
	// this->_OP_CODE_LUT[0xAE] =
	// this->_OP_CODE_LUT[0xAF] =
	////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////
	/* 0xB0 */
	// this->_OP_CODE_LUT[0xB0] =
	// this->_OP_CODE_LUT[0xB1] =
	// this->_OP_CODE_LUT[0xB2] =
	// this->_OP_CODE_LUT[0xB3] =
	// this->_OP_CODE_LUT[0xB4] =
	// this->_OP_CODE_LUT[0xB5] =
	// this->_OP_CODE_LUT[0xB6] =
	// this->_OP_CODE_LUT[0xB7] =
	// this->_OP_CODE_LUT[0xB8] =
	// this->_OP_CODE_LUT[0xB9] =
	// this->_OP_CODE_LUT[0xBA] =
	// this->_OP_CODE_LUT[0xBB] =
	// this->_OP_CODE_LUT[0xBC] =
	// this->_OP_CODE_LUT[0xBD] =
	// this->_OP_CODE_LUT[0xBE] =
	// this->_OP_CODE_LUT[0xBF] =
	////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////
	/* 0xC0 */
	// this->_OP_CODE_LUT[0xC0] =
	// this->_OP_CODE_LUT[0xC1] =
	// this->_OP_CODE_LUT[0xC2] =
	// this->_OP_CODE_LUT[0xC3] =
	// this->_OP_CODE_LUT[0xC4] =
	// this->_OP_CODE_LUT[0xC5] =
	// this->_OP_CODE_LUT[0xC6] =
	// this->_OP_CODE_LUT[0xC7] =
	// this->_OP_CODE_LUT[0xC8] =
	// this->_OP_CODE_LUT[0xC9] =
	// this->_OP_CODE_LUT[0xCA] =
	// this->_OP_CODE_LUT[0xCB] =
	// this->_OP_CODE_LUT[0xCC] =
	// this->_OP_CODE_LUT[0xCD] =
	// this->_OP_CODE_LUT[0xCE] =
	// this->_OP_CODE_LUT[0xCF] =
	////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////
	/* 0xD0 */
	// this->_OP_CODE_LUT[0xD0] =
	// this->_OP_CODE_LUT[0xD1] =
	// this->_OP_CODE_LUT[0xD2] =
	// this->_OP_CODE_LUT[0xD3] =
	// this->_OP_CODE_LUT[0xD4] =
	// this->_OP_CODE_LUT[0xD5] =
	// this->_OP_CODE_LUT[0xD6] =
	// this->_OP_CODE_LUT[0xD7] =
	// this->_OP_CODE_LUT[0xD8] =
	// this->_OP_CODE_LUT[0xD9] =
	// this->_OP_CODE_LUT[0xDA] =
	// this->_OP_CODE_LUT[0xDB] =
	// this->_OP_CODE_LUT[0xDC] =
	// this->_OP_CODE_LUT[0xDD] =
	// this->_OP_CODE_LUT[0xDE] =
	// this->_OP_CODE_LUT[0xDF] =
	////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////
	/* 0xE0 */
	this->_OP_CODE_LUT[0xE0] = &CPU::_ld_FF00_n_A;
	// this->_OP_CODE_LUT[0xE1] =
	this->_OP_CODE_LUT[0xE2] = &CPU::_ld_FF00_C_A;
	// this->_OP_CODE_LUT[0xE3] =
	// this->_OP_CODE_LUT[0xE4] =
	// this->_OP_CODE_LUT[0xE5] =
	// this->_OP_CODE_LUT[0xE6] =
	// this->_OP_CODE_LUT[0xE7] =
	// this->_OP_CODE_LUT[0xE8] =
	// this->_OP_CODE_LUT[0xE9] =
	this->_OP_CODE_LUT[0xEA] = &CPU::_ld_nn_A;
	// this->_OP_CODE_LUT[0xEB] =
	// this->_OP_CODE_LUT[0xEC] =
	// this->_OP_CODE_LUT[0xED] =
	// this->_OP_CODE_LUT[0xEE] =
	// this->_OP_CODE_LUT[0xEF] =
	////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////
	/* 0xF0 */
	this->_OP_CODE_LUT[0xF0] = &CPU::_ld_A_FF00_n;
	// this->_OP_CODE_LUT[0xF1] =
	this->_OP_CODE_LUT[0xF2] = &CPU::_ld_A_FF00_C;
	// this->_OP_CODE_LUT[0xF3] =
	// this->_OP_CODE_LUT[0xF4] =
	// this->_OP_CODE_LUT[0xF5] =
	// this->_OP_CODE_LUT[0xF6] =
	// this->_OP_CODE_LUT[0xF7] =
	// this->_OP_CODE_LUT[0xF8] =
	// this->_OP_CODE_LUT[0xF9] =
	this->_OP_CODE_LUT[0xFA] = &CPU::_ld_A_nn;
	// this->_OP_CODE_LUT[0xFB] =
	// this->_OP_CODE_LUT[0xFC] =
	// this->_OP_CODE_LUT[0xFD] =
	// this->_OP_CODE_LUT[0xFE] =
	// this->_OP_CODE_LUT[0xFF] =
	////////////////////////////////////////////////////////////////
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
			ret = &(this->_BC.bytes[1]);
		case (0b001):
			ret = &(this->_BC.bytes[0]);
		case (0b010):
			ret = &(this->_DE.bytes[1]);
		case (0b011):
			ret = &(this->_DE.bytes[0]);
		case (0b100):
			ret = &(this->_HL.bytes[1]);
		case (0b101):
			ret = &(this->_HL.bytes[0]);
		case (0b110):
			ret = &(this->_AF.bytes[1]);
		case (0b111):
			ret = &(this->_AF.bytes[0]);
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
	- load to the 8-bit register r, data from the 8-bit register r'
*/
void CPU::_ld_r_R() {
	uint8_t opcode = this->_read_and_increment_PC();

	uint8_t* r = this->_get_8_bit_reg( (opcode >> 3) & 0b111 );
	uint8_t* R = this->_get_8_bit_reg(opcode & 0b111);
	(*r) = (*R);

	this->_cycles += MACHINE_CYCLE;
}

/*
LD r, n
	- OpCode = 0b00xxx110 + n
	- load to the 8 bit register r, the immediate data n
*/
void CPU::_ld_r_n() {
	uint8_t opcode = this->_read_and_increment_PC();
	uint8_t n = this->_read_and_increment_PC();

	uint8_t* r = this->_get_8_bit_reg( (opcode >> 3) & 0b111 );
	(*r) = n;

	this->_cycles += MACHINE_CYCLE*2;
}

/*
LD r, (HL)
	- OpCode = 0b01xxx110
	- load to the 8-bit register r, data from the address specified by register HL
*/
void CPU::_ld_r_HL() {
	uint8_t opcode = this->_read_and_increment_PC();

	uint8_t* r = this->_get_8_bit_reg( (opcode >> 3) & 0b111 );
	(*r) = this->_mem_read_byte(this->_HL.raw);

	this->_cycles += MACHINE_CYCLE*2;
}

/*
LD (HL), r
	- OpCode = 0b01100xxx
	- load to the address specificed by register HL, data from the 8-bit register r
*/
void CPU::_ld_HL_r() {
	uint8_t opcode = this->_read_and_increment_PC();

	uint8_t* r = this->_get_8_bit_reg(opcode & 0b111);
	this->_HL.raw = *r;

	this->_cycles += MACHINE_CYCLE*2;
}

/*
LD (HL), n
	- OpCode = 0b00110110 + n
	- load to the address specified by register HL, the immediate data n
*/
void CPU::_ld_HL_n() {
	this->_read_and_increment_PC();
	uint8_t n = this->_read_and_increment_PC();
	this->_HL.raw = n;
	this->_cycles += MACHINE_CYCLE*3;
}

/*
LD A, (BC)
	- OpCode = 0b00001010
	- load to the register A, data from the address specified by register BC
*/
void CPU::_ld_A_BC() {
	this->_read_and_increment_PC();	
	this->_AF.bytes[1] = this->_mem_read_byte(this->_BC.raw);
	this->_cycles += MACHINE_CYCLE*2;
}

/*
LD A, (DE)
	- OpCode = 0b00011010
	- load to the 8-bit register A, data from the address specified by register DE
*/
void CPU::_ld_A_DE() {
	this->_read_and_increment_PC();
	this->_AF.bytes[1] = this->_mem_read_byte(this->_DE.raw);
	this->_cycles += MACHINE_CYCLE*2;
}

/*
LD (BC), A
	- OpCode = 0b00000010
	- load to the address specified by register BC, data from the 8-bit register A
*/
void CPU::_ld_BC_A() {
	this->_read_and_increment_PC();

	uint8_t addr = this->_BC.raw;
	this->_mem_write_byte(addr, this->_AF.bytes[1]);

	this->_cycles += MACHINE_CYCLE*2;
}

/*
LD (DE), A
	- OpCode = 0b00010010
	- load to the address specified by register DE, data from the 8-bit register A
*/
void CPU::_ld_DE_A() {
	this->_read_and_increment_PC();

	uint8_t addr = this->_DE.raw;
	this->_mem_write_byte(addr, this->_AF.bytes[1]);

	this->_cycles += MACHINE_CYCLE*2;
}

/*
LD A, (nn)
	- OpCode = 0b11111010 + n
	- load to the 8-bit register A, data from the address specified by the 16-bit operand n
*/
void CPU::_ld_A_nn() {
	this->_read_and_increment_PC();
	uint8_t lsb_n = this->_read_and_increment_PC();
	uint8_t msb_n = this->_read_and_increment_PC();

	uint16_t addr = (msb_n << 8) | lsb_n;
	this->_AF.bytes[1] = this->_mem_read_byte(addr);

	this->_cycles += MACHINE_CYCLE*4;
}

/*
LD (nn), A
	- OpCode = 0b11101010 + n
	- load to the address specified by the 16-bit operand n, data from the 8-bit register A
*/
void CPU::_ld_nn_A() {
	this->_read_and_increment_PC();
	uint8_t lsb_n = this->_read_and_increment_PC();
	uint8_t msb_n = this->_read_and_increment_PC();

	uint8_t addr = (msb_n << 8) | lsb_n;
	this->_mem_write_byte(addr, this->_AF.bytes[1]);

	this->_cycles += MACHINE_CYCLE*4;
}

/*
LD A, (FF00 + n)
	- OpCode = 0b11110000 + n
	- load to the 8-bit register A, data specifed by the 16-bit address (0xFF00 + n), where n is an 8-bit operand
*/
void CPU::_ld_A_FF00_n() {
	this->_read_and_increment_PC();
	uint8_t n = this->_read_and_increment_PC() & 0xff;
	this->_AF.bytes[1] = this->_mem_read_byte(0xFF00 + n);
	this->_cycles += MACHINE_CYCLE*3;
}

/*
LD (FF00 + n), A
	- OpCode = 0b11100000 + n
	- load to the 16-bit address (0xFF00 + n), the data in the 8-bit register A
*/
void CPU::_ld_FF00_n_A() {
	this->_read_and_increment_PC();
	uint8_t n = this->_read_and_increment_PC() & 0xff;
	this->_mem_write_byte(0xff00 + n, this->_AF.bytes[1]);
	this->_cycles += MACHINE_CYCLE*3;
}

/*
LD A, (FF00 + C)
	- OpCode = 0b11110010
	- load to the 8-bit register A, data from the 16-bit address specified by (0xFF00 + C)
*/
void CPU::_ld_A_FF00_C() {
	this->_read_and_increment_PC();
	this->_AF.bytes[1] = this->_mem_read_byte(0xff00 + this->_BC.bytes[0]);
	this->_cycles += MACHINE_CYCLE*2;
}

/*
LD (FF00 + C), A
	- OpCode = 0b11100010
	- load to the 16-bit address specified by (0xFF00 + C), the data in the 8-bit register A
*/
void CPU::_ld_FF00_C_A() {
	this->_read_and_increment_PC();
	uint8_t addr = 0xff00 + this->_BC.bytes[0];
	this->_mem_write_byte(addr, this->_AF.bytes[1]);
	this->_cycles += MACHINE_CYCLE*2;
}

/*
LDI (HL), A
	- OpCode = 0b00100010
	- load to the address specified by register HL, the data in register A, and increment HL by 1
*/
void CPU::_ldi_HL_A() {
	this->_read_and_increment_PC();
	this->_mem_write_byte(this->_HL.raw, this->_AF.bytes[1]);
	this->_HL.raw += 1;
	this->_cycles += MACHINE_CYCLE*2;
}

/*
LDI A, (HL)
	- OpCode = 0b00101010
	- load to register A, the data at the address specified by HL, and increment HL by 1
*/
void CPU::_ldi_A_HL() {
	this->_read_and_increment_PC();
	this->_AF.bytes[1] = this->_mem_read_byte(this->_HL.raw);
	this->_HL.raw += 1;
	this->_cycles += MACHINE_CYCLE*2;
}

/*
LDD (HL), A
	- OpCode = 0b00110010
	- load to address specified by register HL, the data in register A, and decrement HL by 1
*/
void CPU::_ldd_HL_A() {
	this->_read_and_increment_PC();
	this->_mem_write_byte(this->_HL.raw, this->_AF.bytes[1]);
	this->_HL.raw -= 1;
	this->_cycles += MACHINE_CYCLE*2;
}

/*
LDD A, (HL)
	- OpCode = 0b00111010
	- load to register A, the data in the address specified by register HL, and decrement HL by 1
*/
void CPU::_ldd_A_HL() {
	this->_read_and_increment_PC();
	this->_AF.bytes[1] = this->_mem_read_byte(this->_HL.raw);
	this->_HL.raw -= 1;
	this->_cycles += MACHINE_CYCLE*2;
}
