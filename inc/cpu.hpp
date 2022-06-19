#pragma once

#include <string>
#include <vector>
#include <boost/format.hpp>

#include <stdint.h>
#include <stddef.h>

#include "abstract_peripheral.hpp"

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

#define ENABLE_TRACE        true
#define TRACE_FPATH         "./garbage-boy-trace.log"

// lowercase
#define PRINT_UINT8_LC(x)      (boost::format("%02x") % (int)(x))
#define PRINT_UINT16_LC(x)     (boost::format("%04x") % (int)(x))

// uppercase
#define PRINT_UINT8_UC(x)      (boost::format("%02X") % (int)(x))
#define PRINT_UINT16_UC(x)     (boost::format("%04X") % (int)(x))

#define MACHINE_CYCLE       4

// I saw this method of checking on stackoverflow, I think mine is a bit more intiuitive tho...
// #define CHECK_8_BIT_HALF_CARRY(a, b) ( (((a & 0xf) + (b & 0xf)) & 0x10) == 0x10 )

#define CHECK_8_BIT_HALF_CARRY(a, b) ( ((a & 0xf) + (b & 0xf)) > 0xf )
#define CHECK_16_BIT_HALF_CARRY(a, b) ( ((a & 0xfff) + (b & 0xfff)) > 0xfff )
#define CHECK_8_BIT_HALF_CARRY_SUB(a, b) ( (a & 0xf) < (b & 0xf) )
// #define CHECK_16_BIT_HALF_CARRY_SUB(a, b) ( (a & 0xff) < (b & 0xff) )

#define CHECK_8_BIT_CARRY(a, b) ( ((a & 0xff) + (b & 0xff)) > 0xff )
#define CHECK_16_BIT_CARRY(a, b) ( ((a & 0xffff) + (b & 0xffff)) > 0xffff )
#define CHECK_SUB_CARRY(a, b) ( (a & 0xff) < (b & 0xff) )

enum Flags {
    CARRY_FLAG = 4,
    HALF_CARRY_FLAG = 5,
    SUB_FLAG = 6,
    ZERO_FLAG = 7
};

union Reg {
    uint8_t bytes[2];
    uint16_t raw;
};

class AbstractPeripheral;
class CPU {
    friend class AbstractPeripheral;

    private:
        void _log_trace(std::ofstream &tf);

    public:
        CPU();
        ~CPU();

        uint8_t mem_read_byte(size_t addr);
        void mem_write_byte(size_t addr, uint8_t val);
        uint8_t* mem_get(size_t addr);

        void jump(size_t addr);
        void call(size_t addr);

        void load_rom(std::string rom_path, size_t offset);
        void run();

    public:
        bool IME;  // Interrupt Master Enable Flag
        uint32_t cycles;

    private:
        // registers
        Reg _AF;    // Accumulator and Flags
        Reg _BC;    // General Purpose
        Reg _DE;    // General Purpose
        Reg _HL;    // General Purpose
        Reg _SP;    // Stack Pointer
        Reg _PC;    // Program Counter

        uint8_t _memory[0xFFFF + 1];
        bool _is_halted;

        void (CPU::*_OP_CODE_LUT[0xFF + 1])();
        void (CPU::*_OP_CODE_LUT_CB[0xFF + 1])();

        std::vector<AbstractPeripheral*> _peripherals;

    private:
        void _OP_CODE_LUT_init();
        void _OP_CODE_LUT_init_CB();

        void _init_state();
        std::vector<uint8_t> _read_rom_file(std::string rom_path);

        uint8_t _read_and_increment_PC();

        uint8_t* _get_8_bit_reg(uint8_t bitcode);
        Reg* _get_16_bit_reg(uint8_t bitcode);

        bool _eval_cond_code(uint8_t bitcode);

        void _push_stack(uint8_t byte);
        uint8_t _pop_stack();

        void _set_flag(uint8_t flag);
        void _clear_flag(uint8_t flag);
        bool _get_flag(uint8_t flag);

        uint8_t _add_bytes(uint8_t a, uint8_t b);
        uint8_t _sub_bytes(uint8_t a, uint8_t b);

    private:
        ///////////////////////////////////////////////////////////////////////////////////////
        /*
        CPU instructions, these functions will do the following:
            1 - execute whatever the instruction is supposed to do
            2 - increment the number of cycles appropriately
            3 - place the program pointer and the stack pointer in the appropriate locations
        */
        ///////////////////////////////////////////////////////////////////////////////////////

        ///////////////////////////////////////////////////////////////////////////////////////
        /* CPU CONTROL INSTRUCTIONS */
        void _ccf();
        void _scf();
        void _nop();
        void _halt();
        void _di();
        void _ei();
        ///////////////////////////////////////////////////////////////////////////////////////

        ///////////////////////////////////////////////////////////////////////////////////////
        /* JUMP INSTRUCTIONS */
        void _jp_nn();
        void _jp_HL();
        void _jp_cc_nn();
        void _jr_dd();
        void _jr_cc_dd();
        void _call_nn();
        void _call_cc_nn();
        void _ret();
        void _ret_cc();
        void _reti();
        void _rst_n();
        ///////////////////////////////////////////////////////////////////////////////////////

        ///////////////////////////////////////////////////////////////////////////////////////
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
        ///////////////////////////////////////////////////////////////////////////////////////

        ///////////////////////////////////////////////////////////////////////////////////////
        /* 16-BIT LOAD INSTRUCTIONS */
        void _ld_rr_nn();
        void _ld_nn_SP();
        void _ld_SP_HL();
        void _push_rr();
        void _pop_rr();
        void _ld_HL_SP_dd();
        ///////////////////////////////////////////////////////////////////////////////////////

        ///////////////////////////////////////////////////////////////////////////////////////
        /* 8-BIT ARITHMETIC/LOGIC INSTRUCTIONS */
        void _add_A_r();
        void _add_A_n();
        void _add_A_HL();
        void _adc_A_r();
        void _adc_A_n();
        void _adc_A_HL();
        void _sub_r();
        void _sub_n();
        void _sub_HL();
        void _sbc_A_r();
        void _sbc_A_n();
        void _sbc_A_HL();
        void _and_r();
        void _and_n();
        void _and_HL();
        void _xor_r();
        void _xor_n();
        void _xor_HL();
        void _or_r();
        void _or_n();
        void _or_HL();
        void _cp_r();
        void _cp_n();
        void _cp_HL();
        void _inc_r();
        void _inc_HL();
        void _dec_r();
        void _dec_HL();
        void _daa();
        void _cpl();
        ///////////////////////////////////////////////////////////////////////////////////////

        ///////////////////////////////////////////////////////////////////////////////////////
        /* 16-BIT ARITHMETIC/LOGIC INSTRUCTIONS */
        void _add_HL_rr();
        void _inc_rr();
        void _dec_rr();
        void _add_SP_dd();
        ///////////////////////////////////////////////////////////////////////////////////////

        ///////////////////////////////////////////////////////////////////////////////////////
        /* SINGLE BIT INSTRUCTIONS */
        void _bit_n_r();
        void _bit_n_HL();
        void _set_n_r();
        void _set_n_HL();
        // void _res_n_r();
        // void _res_n_HL();

        ///////////////////////////////////////////////////////////////////////////////////////

        ///////////////////////////////////////////////////////////////////////////////////////
        /* ROTATE AND SHIFT INSTRUCTIONS */
        void _rlca();
        void _rla();
        void _rrca();
        void _rra();
        // void _rlc_r();
        // void _rlc_HL();
        // void _rl_r();
        // void _rl_HL();
        // void _rrc_r();
        // void _rrc_HL();
        // void _rr_r();
        // void _rr_HL();
        // void _sla_r();
        // void _sla_HL();
        // void _swap_r();
        // void _swap_HL();
        // void _sra_r();
        // void _sra_HL();
        // void _srl_r();
        // void srl_HL();
        ///////////////////////////////////////////////////////////////////////////////////////

};
