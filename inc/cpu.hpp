#pragma once

#include <map>
#include <stdint.h>
#include <stddef.h>

/*
	0000-3FFF   16KB ROM Bank 00     (in cartridge, fixed at bank 00)
	4000-7FFF   16KB ROM Bank 01..NN (in cartridge, switchable bank number)
	8000-9FFF   8KB Video RAM (VRAM) (switchable bank 0-1 in CGB Mode)
	A000-BFFF   8KB External RAM     (in cartridge, switchable bank, if any)
	C000-CFFF   4KB Work RAM Bank 0 (WRAM)
	D000-DFFF   4KB Work RAM Bank 1 (WRAM)  (switchable bank 1-7 in CGB Mode)
	E000-FDFF   Same as C000-DDFF (ECHO)    (typically not used)
	FE00-FE9F   Sprite Attribute Table (OAM)
	FEA0-FEFF   Not Usable
	FF00-FF7F   I/O Ports
	FF80-FFFE   High RAM (HRAM)
	FFFF        Interrupt Enable Register
*/

#define ZERO_FLAG			7
#define SUB_FLAG			6
#define HALF_CARRY_FLAG		5
#define CARRY_FLAG			4

#define MACHINE_CYCLE		4

union Reg {
	uint8_t bytes[2];
	uint16_t raw;
};

class CPU {
	private:
		// registers
		Reg _AF;	// Accumulator and Flags
		Reg _BC;	// General Purpose
		Reg _DE;	// General Purpose
		Reg _HL;	// General Purpose
		Reg _SP;	// Stack Pointer
		Reg _PC;	// Program Counter

		uint8_t _memory[0xffff];
		uint32_t _cycles;

		std::map<uint8_t, void (CPU::*)()> _OP_CODE_LUT;

	public:
		CPU();
		~CPU();
		void run();

	private:
		uint8_t _mem_read_byte(size_t addr);
		void _mem_write_byte(size_t addr, uint8_t val);
		uint8_t _read_and_increment_PC();

		uint8_t* _get_8_bit_reg(uint8_t bitcode);
		Reg* _get_16_bit_reg(uint8_t bitcode);

		/*
		CPU instructions, these functions will do the following:
			1 - execute whatever the instruction is supposed to do
			2 - increment the number of cycles appropriately
			3 - place the program pointer and the stack pointer in the appropriate location
		*/

		////////////////////////////////////////////////////////////////
		/* CPU CONTROL INSTRUCTIONS */
		void _nop();
		////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////
		/* 8-BIT LOAD INSTRUCTIONS */
		void _ld_r_R();
		void _ld_r_n();
		void _ld_r_HL();
		void _ld_HL_r();
		void _ld_HL_n();
		void _ld_A_BC();
		void _ld_A_DE();
		void _ld_A_nn();
		void _ld_BC_A();
		void _ld_DE_A();
		void _ld_nn_A();
		void _ld_A_FF00_n();
		void _ld_FF00_n_A();
		void _ld_A_FF00_C();
		void _ld_FF00_C_A();
		void _ldi_HL_A();
		void _ldi_A_HL();
		void _ldd_HL_A();
		void _ldd_A_HL();
		////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////
		/* 16-BIT LOAD INSTRUCTIONS */
		void _ld_rr_nn();
		////////////////////////////////////////////////////////////////

};

