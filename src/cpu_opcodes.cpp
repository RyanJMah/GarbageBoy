/*
Emulation for every CPU instruction...

references:
    - https://gbdev.io/pandocs/CPU_Instruction_Set.html
    - https://gbdev.io/gb-opcodes/optables/
    - http://www.zilog.com/docs/z80/um0080.pdf
    - https://gekkio.fi/files/gb-docs/gbctr.pdf
*/

#include <stdint.h>
#include <stddef.h>
#include "cpu.hpp"

void CPU::_OP_CODE_LUT_init() {
    ////////////////////////////////////////////////////////////////
    /* 0x00 */
    this->_OP_CODE_LUT[0x00] = &CPU::_nop;
    this->_OP_CODE_LUT[0x01] = &CPU::_ld_rr_nn;
    this->_OP_CODE_LUT[0x02] = &CPU::_ld_BC_A;
    this->_OP_CODE_LUT[0x03] = &CPU::_inc_rr;
    this->_OP_CODE_LUT[0x04] = &CPU::_inc_r;
    this->_OP_CODE_LUT[0x05] = &CPU::_dec_r;
    this->_OP_CODE_LUT[0x06] = &CPU::_ld_r_n;
    this->_OP_CODE_LUT[0x07] = &CPU::_rlca;
    this->_OP_CODE_LUT[0x08] = &CPU::_ld_nn_SP;
    this->_OP_CODE_LUT[0x09] = &CPU::_add_HL_rr;
    this->_OP_CODE_LUT[0x0A] = &CPU::_ld_A_BC;
    this->_OP_CODE_LUT[0x0B] = &CPU::_dec_rr;
    this->_OP_CODE_LUT[0x0C] = &CPU::_inc_r;
    this->_OP_CODE_LUT[0x0D] = &CPU::_dec_r;
    this->_OP_CODE_LUT[0x0E] = &CPU::_ld_r_n;
    this->_OP_CODE_LUT[0x0F] = &CPU::_rrca;
    ////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////
    /* 0x10 */
    this->_OP_CODE_LUT[0x10] = &CPU::_halt;
    this->_OP_CODE_LUT[0x11] = &CPU::_ld_rr_nn;
    this->_OP_CODE_LUT[0x12] = &CPU::_ld_DE_A;
    this->_OP_CODE_LUT[0x13] = &CPU::_inc_rr;
    this->_OP_CODE_LUT[0x14] = &CPU::_inc_r;
    this->_OP_CODE_LUT[0x15] = &CPU::_dec_r;
    this->_OP_CODE_LUT[0x16] = &CPU::_ld_r_n;
    this->_OP_CODE_LUT[0x17] = &CPU::_rla;
    this->_OP_CODE_LUT[0x18] = &CPU::_jr_dd;
    this->_OP_CODE_LUT[0x19] = &CPU::_add_HL_rr;
    this->_OP_CODE_LUT[0x1A] = &CPU::_ld_A_DE;
    this->_OP_CODE_LUT[0x1B] = &CPU::_dec_rr;
    this->_OP_CODE_LUT[0x1C] = &CPU::_inc_r;
    this->_OP_CODE_LUT[0x1D] = &CPU::_dec_r;
    this->_OP_CODE_LUT[0x1E] = &CPU::_ld_r_n;
    this->_OP_CODE_LUT[0x1F] = &CPU::_rra;
    ////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////
    /* 0x20 */
    this->_OP_CODE_LUT[0x20] = &CPU::_jr_cc_dd;
    this->_OP_CODE_LUT[0x21] = &CPU::_ld_rr_nn;
    this->_OP_CODE_LUT[0x22] = &CPU::_ldi_HL_A ;
    this->_OP_CODE_LUT[0x23] = &CPU::_inc_rr;
    this->_OP_CODE_LUT[0x24] = &CPU::_inc_r;
    this->_OP_CODE_LUT[0x25] = &CPU::_dec_r;
    this->_OP_CODE_LUT[0x26] = &CPU::_ld_r_n;
    this->_OP_CODE_LUT[0x27] = &CPU::_daa;
    this->_OP_CODE_LUT[0x28] = &CPU::_jr_cc_dd;
    this->_OP_CODE_LUT[0x29] = &CPU::_add_HL_rr;
    this->_OP_CODE_LUT[0x2A] = &CPU::_ldi_A_HL;
    this->_OP_CODE_LUT[0x2B] = &CPU::_dec_rr;
    this->_OP_CODE_LUT[0x2C] = &CPU::_inc_r;
    this->_OP_CODE_LUT[0x2D] = &CPU::_dec_r;
    this->_OP_CODE_LUT[0x2E] = &CPU::_ld_r_n;
    this->_OP_CODE_LUT[0x2F] = &CPU::_cpl;
    ////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////
    /* 0x30 */
    this->_OP_CODE_LUT[0x30] = &CPU::_jr_cc_dd;
    this->_OP_CODE_LUT[0x31] = &CPU::_ld_rr_nn;
    this->_OP_CODE_LUT[0x32] = &CPU::_ldd_HL_A ;
    this->_OP_CODE_LUT[0x33] = &CPU::_inc_rr;
    this->_OP_CODE_LUT[0x34] = &CPU::_inc_HL;
    this->_OP_CODE_LUT[0x35] = &CPU::_dec_HL;
    this->_OP_CODE_LUT[0x36] = &CPU::_ld_r_n;
    this->_OP_CODE_LUT[0x37] = &CPU::_scf;
    this->_OP_CODE_LUT[0x38] = &CPU::_jr_cc_dd;
    this->_OP_CODE_LUT[0x39] = &CPU::_add_HL_rr;
    this->_OP_CODE_LUT[0x3A] = &CPU::_ldd_A_HL;
    this->_OP_CODE_LUT[0x3B] = &CPU::_dec_rr;
    this->_OP_CODE_LUT[0x3C] = &CPU::_inc_r;
    this->_OP_CODE_LUT[0x3D] = &CPU::_dec_r;
    this->_OP_CODE_LUT[0x3E] = &CPU::_ld_r_n;
    this->_OP_CODE_LUT[0x3F] = &CPU::_ccf;
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
    this->_OP_CODE_LUT[0x76] = &CPU::_halt;
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
    this->_OP_CODE_LUT[0x80] = &CPU::_add_A_r;
    this->_OP_CODE_LUT[0x81] = &CPU::_add_A_r;
    this->_OP_CODE_LUT[0x82] = &CPU::_add_A_r;
    this->_OP_CODE_LUT[0x83] = &CPU::_add_A_r;
    this->_OP_CODE_LUT[0x84] = &CPU::_add_A_r;
    this->_OP_CODE_LUT[0x85] = &CPU::_add_A_r;
    this->_OP_CODE_LUT[0x86] = &CPU::_add_A_HL;
    this->_OP_CODE_LUT[0x87] = &CPU::_add_A_r;
    this->_OP_CODE_LUT[0x88] = &CPU::_adc_A_r;
    this->_OP_CODE_LUT[0x89] = &CPU::_adc_A_r;
    this->_OP_CODE_LUT[0x8A] = &CPU::_adc_A_r;
    this->_OP_CODE_LUT[0x8B] = &CPU::_adc_A_r;
    this->_OP_CODE_LUT[0x8C] = &CPU::_adc_A_r;
    this->_OP_CODE_LUT[0x8D] = &CPU::_adc_A_r;
    this->_OP_CODE_LUT[0x8E] = &CPU::_adc_A_HL;
    this->_OP_CODE_LUT[0x8F] = &CPU::_adc_A_r;
    ////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////
    /* 0x90 */
    this->_OP_CODE_LUT[0x90] = &CPU::_sub_r;
    this->_OP_CODE_LUT[0x91] = &CPU::_sub_r;
    this->_OP_CODE_LUT[0x92] = &CPU::_sub_r;
    this->_OP_CODE_LUT[0x93] = &CPU::_sub_r;
    this->_OP_CODE_LUT[0x94] = &CPU::_sub_r;
    this->_OP_CODE_LUT[0x95] = &CPU::_sub_r;
    this->_OP_CODE_LUT[0x96] = &CPU::_sub_HL;
    this->_OP_CODE_LUT[0x97] = &CPU::_sub_r;
    this->_OP_CODE_LUT[0x98] = &CPU::_sbc_A_r;
    this->_OP_CODE_LUT[0x99] = &CPU::_sbc_A_r;
    this->_OP_CODE_LUT[0x9A] = &CPU::_sbc_A_r;
    this->_OP_CODE_LUT[0x9B] = &CPU::_sbc_A_r;
    this->_OP_CODE_LUT[0x9C] = &CPU::_sbc_A_r;
    this->_OP_CODE_LUT[0x9D] = &CPU::_sbc_A_r;
    this->_OP_CODE_LUT[0x9E] = &CPU::_sbc_A_HL;
    this->_OP_CODE_LUT[0x9F] = &CPU::_sbc_A_r;
    ////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////
    /* 0xA0 */
    this->_OP_CODE_LUT[0xA0] = &CPU::_and_r;
    this->_OP_CODE_LUT[0xA1] = &CPU::_and_r;
    this->_OP_CODE_LUT[0xA2] = &CPU::_and_r;
    this->_OP_CODE_LUT[0xA3] = &CPU::_and_r;
    this->_OP_CODE_LUT[0xA4] = &CPU::_and_r;
    this->_OP_CODE_LUT[0xA5] = &CPU::_and_r;
    this->_OP_CODE_LUT[0xA6] = &CPU::_and_HL;
    this->_OP_CODE_LUT[0xA7] = &CPU::_and_r;
    this->_OP_CODE_LUT[0xA8] = &CPU::_xor_r;
    this->_OP_CODE_LUT[0xA9] = &CPU::_xor_r;
    this->_OP_CODE_LUT[0xAA] = &CPU::_xor_r;
    this->_OP_CODE_LUT[0xAB] = &CPU::_xor_r;
    this->_OP_CODE_LUT[0xAC] = &CPU::_xor_r;
    this->_OP_CODE_LUT[0xAD] = &CPU::_xor_r;
    this->_OP_CODE_LUT[0xAE] = &CPU::_xor_HL;
    this->_OP_CODE_LUT[0xAF] = &CPU::_xor_r;
    ////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////
    /* 0xB0 */
    this->_OP_CODE_LUT[0xB0] = &CPU::_or_r;
    this->_OP_CODE_LUT[0xB1] = &CPU::_or_r;
    this->_OP_CODE_LUT[0xB2] = &CPU::_or_r;
    this->_OP_CODE_LUT[0xB3] = &CPU::_or_r;
    this->_OP_CODE_LUT[0xB4] = &CPU::_or_r;
    this->_OP_CODE_LUT[0xB5] = &CPU::_or_r;
    this->_OP_CODE_LUT[0xB6] = &CPU::_or_HL;
    this->_OP_CODE_LUT[0xB7] = &CPU::_or_r;
    this->_OP_CODE_LUT[0xB8] = &CPU::_cp_r;
    this->_OP_CODE_LUT[0xB9] = &CPU::_cp_r;
    this->_OP_CODE_LUT[0xBA] = &CPU::_cp_r;
    this->_OP_CODE_LUT[0xBB] = &CPU::_cp_r;
    this->_OP_CODE_LUT[0xBC] = &CPU::_cp_r;
    this->_OP_CODE_LUT[0xBD] = &CPU::_cp_r;
    this->_OP_CODE_LUT[0xBE] = &CPU::_cp_HL;
    this->_OP_CODE_LUT[0xBF] = &CPU::_cp_r;
    ////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////
    /* 0xC0 */
    this->_OP_CODE_LUT[0xC0] = &CPU::_ret_cc;
    this->_OP_CODE_LUT[0xC1] = &CPU::_pop_rr;
    this->_OP_CODE_LUT[0xC2] = &CPU::_jp_cc_nn;
    this->_OP_CODE_LUT[0xC3] = &CPU::_jp_nn;
    this->_OP_CODE_LUT[0xC4] = &CPU::_call_cc_nn;
    this->_OP_CODE_LUT[0xC5] = &CPU::_push_rr;
    this->_OP_CODE_LUT[0xC6] = &CPU::_add_A_n;
    this->_OP_CODE_LUT[0xC7] = &CPU::_rst_n;
    this->_OP_CODE_LUT[0xC8] = &CPU::_ret_cc;
    this->_OP_CODE_LUT[0xC9] = &CPU::_ret;
    this->_OP_CODE_LUT[0xCA] = &CPU::_jp_cc_nn;
    // this->_OP_CODE_LUT[0xCB] = intentionally unassigned
    this->_OP_CODE_LUT[0xCC] = &CPU::_call_cc_nn;
    this->_OP_CODE_LUT[0xCD] = &CPU::_call_nn;
    this->_OP_CODE_LUT[0xCE] = &CPU::_adc_A_n;
    this->_OP_CODE_LUT[0xCF] = &CPU::_rst_n;
    ////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////
    /* 0xD0 */
    this->_OP_CODE_LUT[0xD0] = &CPU::_ret_cc;
    this->_OP_CODE_LUT[0xD1] = &CPU::_pop_rr;
    this->_OP_CODE_LUT[0xD2] = &CPU::_jp_cc_nn;
    // this->_OP_CODE_LUT[0xD3] = intentionally unassigned
    this->_OP_CODE_LUT[0xD4] = &CPU::_call_cc_nn;
    this->_OP_CODE_LUT[0xD5] = &CPU::_push_rr;
    this->_OP_CODE_LUT[0xD6] = &CPU::_sub_n;
    this->_OP_CODE_LUT[0xD7] = &CPU::_rst_n;
    this->_OP_CODE_LUT[0xD8] = &CPU::_ret_cc;
    this->_OP_CODE_LUT[0xD9] = &CPU::_reti;
    this->_OP_CODE_LUT[0xDA] = &CPU::_jp_cc_nn;
    // this->_OP_CODE_LUT[0xDB] = intentionally unassigned
    this->_OP_CODE_LUT[0xDC] = &CPU::_call_cc_nn;
    // this->_OP_CODE_LUT[0xDD] = intentionally unassigned
    this->_OP_CODE_LUT[0xDE] = &CPU::_sbc_A_n;
    this->_OP_CODE_LUT[0xDF] = &CPU::_rst_n;
    ////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////
    /* 0xE0 */
    this->_OP_CODE_LUT[0xE0] = &CPU::_ld_FF00_n_A;
    this->_OP_CODE_LUT[0xE1] = &CPU::_pop_rr;
    this->_OP_CODE_LUT[0xE2] = &CPU::_ld_FF00_C_A;
    // this->_OP_CODE_LUT[0xE3] = intentionally unassigned
    // this->_OP_CODE_LUT[0xE4] = intentionally unassigned
    this->_OP_CODE_LUT[0xE5] = &CPU::_push_rr;
    this->_OP_CODE_LUT[0xE6] = &CPU::_and_n;
    this->_OP_CODE_LUT[0xE7] = &CPU::_rst_n;
    this->_OP_CODE_LUT[0xE8] = &CPU::_add_SP_dd;
    this->_OP_CODE_LUT[0xE9] = &CPU::_jp_HL;
    this->_OP_CODE_LUT[0xEA] = &CPU::_ld_nn_A;
    // this->_OP_CODE_LUT[0xEB] = intentionally unassigned
    // this->_OP_CODE_LUT[0xEC] = intentionally unassigned
    // this->_OP_CODE_LUT[0xED] = intentionally unassigned
    this->_OP_CODE_LUT[0xEE] = &CPU::_xor_n;
    this->_OP_CODE_LUT[0xEF] = &CPU::_rst_n;
    ////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////
    /* 0xF0 */
    this->_OP_CODE_LUT[0xF0] = &CPU::_ld_A_FF00_n;
    this->_OP_CODE_LUT[0xF1] = &CPU::_pop_rr;
    this->_OP_CODE_LUT[0xF2] = &CPU::_ld_A_FF00_C;
    this->_OP_CODE_LUT[0xF3] = &CPU::_di;
    // this->_OP_CODE_LUT[0xF4] = intentionally unassigned
    this->_OP_CODE_LUT[0xF5] = &CPU::_push_rr;
    this->_OP_CODE_LUT[0xF6] = &CPU::_or_n;
    this->_OP_CODE_LUT[0xF7] = &CPU::_rst_n;
    this->_OP_CODE_LUT[0xF8] = &CPU::_ld_HL_SP_dd;
    this->_OP_CODE_LUT[0xF9] = &CPU::_ld_SP_HL;
    this->_OP_CODE_LUT[0xFA] = &CPU::_ld_A_nn;
    this->_OP_CODE_LUT[0xFB] = &CPU::_ei;
    // this->_OP_CODE_LUT[0xFC] = intentionally unassigned
    // this->_OP_CODE_LUT[0xFD] = intentionally unassigned
    this->_OP_CODE_LUT[0xFE] = &CPU::_cp_n;
    this->_OP_CODE_LUT[0xFF] = &CPU::_rst_n;
    ////////////////////////////////////////////////////////////////
}

// void CPU::_OP_CODE_LUT_init_CB() {
//     ////////////////////////////////////////////////////////////////
//     /* CB 0x00 */
//     // this->_OP_CODE_LUT[0xCB00] =
//     // this->_OP_CODE_LUT[0xCB01] =
//     // this->_OP_CODE_LUT[0xCB02] =
//     // this->_OP_CODE_LUT[0xCB03] =
//     // this->_OP_CODE_LUT[0xCB04] =
//     // this->_OP_CODE_LUT[0xCB05] =
//     // this->_OP_CODE_LUT[0xCB06] =
//     // this->_OP_CODE_LUT[0xCB07] =
//     // this->_OP_CODE_LUT[0xCB08] =
//     // this->_OP_CODE_LUT[0xCB09] =
//     // this->_OP_CODE_LUT[0xCB0A] =
//     // this->_OP_CODE_LUT[0xCB0B] =
//     // this->_OP_CODE_LUT[0xCB0C] =
//     // this->_OP_CODE_LUT[0xCB0D] =
//     // this->_OP_CODE_LUT[0xCB0E] =
//     // this->_OP_CODE_LUT[0xCB0F] =
//     ////////////////////////////////////////////////////////////////

//     ////////////////////////////////////////////////////////////////
//     /* CB 0x10 */
//     // this->_OP_CODE_LUT[0xCB10] =
//     // this->_OP_CODE_LUT[0xCB11] =
//     // this->_OP_CODE_LUT[0xCB12] =
//     // this->_OP_CODE_LUT[0xCB13] =
//     // this->_OP_CODE_LUT[0xCB14] =
//     // this->_OP_CODE_LUT[0xCB15] =
//     // this->_OP_CODE_LUT[0xCB16] =
//     // this->_OP_CODE_LUT[0xCB17] =
//     // this->_OP_CODE_LUT[0xCB18] =
//     // this->_OP_CODE_LUT[0xCB19] =
//     // this->_OP_CODE_LUT[0xCB1A] =
//     // this->_OP_CODE_LUT[0xCB1B] =
//     // this->_OP_CODE_LUT[0xCB1C] =
//     // this->_OP_CODE_LUT[0xCB1D] =
//     // this->_OP_CODE_LUT[0xCB1E] =
//     // this->_OP_CODE_LUT[0xCB1F] =
//     ////////////////////////////////////////////////////////////////

//     ////////////////////////////////////////////////////////////////
//     /* CB 0x20 */
//     // this->_OP_CODE_LUT[0xCB20] =
//     // this->_OP_CODE_LUT[0xCB21] =
//     // this->_OP_CODE_LUT[0xCB22] =
//     // this->_OP_CODE_LUT[0xCB23] =
//     // this->_OP_CODE_LUT[0xCB24] =
//     // this->_OP_CODE_LUT[0xCB25] =
//     // this->_OP_CODE_LUT[0xCB26] =
//     // this->_OP_CODE_LUT[0xCB27] =
//     // this->_OP_CODE_LUT[0xCB28] =
//     // this->_OP_CODE_LUT[0xCB29] =
//     // this->_OP_CODE_LUT[0xCB2A] =
//     // this->_OP_CODE_LUT[0xCB2B] =
//     // this->_OP_CODE_LUT[0xCB2C] =
//     // this->_OP_CODE_LUT[0xCB2D] =
//     // this->_OP_CODE_LUT[0xCB2E] =
//     // this->_OP_CODE_LUT[0xCB2F] =
//     ////////////////////////////////////////////////////////////////

//     ////////////////////////////////////////////////////////////////
//     /* CB 0x30 */
//     // this->_OP_CODE_LUT[0xCB30] =
//     // this->_OP_CODE_LUT[0xCB31] =
//     // this->_OP_CODE_LUT[0xCB32] =
//     // this->_OP_CODE_LUT[0xCB33] =
//     // this->_OP_CODE_LUT[0xCB34] =
//     // this->_OP_CODE_LUT[0xCB35] =
//     // this->_OP_CODE_LUT[0xCB36] =
//     // this->_OP_CODE_LUT[0xCB37] =
//     // this->_OP_CODE_LUT[0xCB38] =
//     // this->_OP_CODE_LUT[0xCB39] =
//     // this->_OP_CODE_LUT[0xCB3A] =
//     // this->_OP_CODE_LUT[0xCB3B] =
//     // this->_OP_CODE_LUT[0xCB3C] =
//     // this->_OP_CODE_LUT[0xCB3D] =
//     // this->_OP_CODE_LUT[0xCB3E] =
//     // this->_OP_CODE_LUT[0xCB3F] =
//     ////////////////////////////////////////////////////////////////

//     ////////////////////////////////////////////////////////////////
//     /* CB 0x40 */
//     this->_OP_CODE_LUT[0xCB40] = &CPU::_bit_n_r;
//     this->_OP_CODE_LUT[0xCB41] = &CPU::_bit_n_r;
//     this->_OP_CODE_LUT[0xCB42] = &CPU::_bit_n_r;
//     this->_OP_CODE_LUT[0xCB43] = &CPU::_bit_n_r;
//     this->_OP_CODE_LUT[0xCB44] = &CPU::_bit_n_r;
//     this->_OP_CODE_LUT[0xCB45] = &CPU::_bit_n_r;
//     // this->_OP_CODE_LUT[0xCB46] =
//     this->_OP_CODE_LUT[0xCB47] = &CPU::_bit_n_r;
//     this->_OP_CODE_LUT[0xCB48] = &CPU::_bit_n_r;
//     this->_OP_CODE_LUT[0xCB49] = &CPU::_bit_n_r;
//     this->_OP_CODE_LUT[0xCB4A] = &CPU::_bit_n_r;
//     this->_OP_CODE_LUT[0xCB4B] = &CPU::_bit_n_r;
//     this->_OP_CODE_LUT[0xCB4C] = &CPU::_bit_n_r;
//     this->_OP_CODE_LUT[0xCB4D] = &CPU::_bit_n_r;
//     // this->_OP_CODE_LUT[0xCB4E] =
//     this->_OP_CODE_LUT[0xCB4F] = &CPU::_bit_n_r;
//     ////////////////////////////////////////////////////////////////

//     ////////////////////////////////////////////////////////////////
//     /* CB 0x50 */
//     this->_OP_CODE_LUT[0xCB50] = &CPU::_bit_n_r;
//     this->_OP_CODE_LUT[0xCB51] = &CPU::_bit_n_r;
//     this->_OP_CODE_LUT[0xCB52] = &CPU::_bit_n_r;
//     this->_OP_CODE_LUT[0xCB53] = &CPU::_bit_n_r;
//     this->_OP_CODE_LUT[0xCB54] = &CPU::_bit_n_r;
//     this->_OP_CODE_LUT[0xCB55] = &CPU::_bit_n_r;
//     // this->_OP_CODE_LUT[0xCB56] =
//     this->_OP_CODE_LUT[0xCB57] = &CPU::_bit_n_r;
//     this->_OP_CODE_LUT[0xCB58] = &CPU::_bit_n_r;
//     this->_OP_CODE_LUT[0xCB59] = &CPU::_bit_n_r;
//     this->_OP_CODE_LUT[0xCB5A] = &CPU::_bit_n_r;
//     this->_OP_CODE_LUT[0xCB5B] = &CPU::_bit_n_r;
//     this->_OP_CODE_LUT[0xCB5C] = &CPU::_bit_n_r;
//     this->_OP_CODE_LUT[0xCB5D] = &CPU::_bit_n_r;
//     // this->_OP_CODE_LUT[0xCB5E] =
//     this->_OP_CODE_LUT[0xCB5F] = &CPU::_bit_n_r;
//     ////////////////////////////////////////////////////////////////

//     ////////////////////////////////////////////////////////////////
//     /* CB 0x60 */
//     this->_OP_CODE_LUT[0xCB60] = &CPU::_bit_n_r;
//     this->_OP_CODE_LUT[0xCB61] = &CPU::_bit_n_r;
//     this->_OP_CODE_LUT[0xCB62] = &CPU::_bit_n_r;
//     this->_OP_CODE_LUT[0xCB63] = &CPU::_bit_n_r;
//     this->_OP_CODE_LUT[0xCB64] = &CPU::_bit_n_r;
//     this->_OP_CODE_LUT[0xCB65] = &CPU::_bit_n_r;
//     // this->_OP_CODE_LUT[0xCB66] =
//     this->_OP_CODE_LUT[0xCB67] = &CPU::_bit_n_r;
//     this->_OP_CODE_LUT[0xCB68] = &CPU::_bit_n_r;
//     this->_OP_CODE_LUT[0xCB69] = &CPU::_bit_n_r;
//     this->_OP_CODE_LUT[0xCB6A] = &CPU::_bit_n_r;
//     this->_OP_CODE_LUT[0xCB6B] = &CPU::_bit_n_r;
//     this->_OP_CODE_LUT[0xCB6C] = &CPU::_bit_n_r;
//     this->_OP_CODE_LUT[0xCB6D] = &CPU::_bit_n_r;
//     // this->_OP_CODE_LUT[0xCB6E] =
//     this->_OP_CODE_LUT[0xCB6F] = &CPU::_bit_n_r;
//     ////////////////////////////////////////////////////////////////

//     ////////////////////////////////////////////////////////////////
//     /* CB 0x70 */
//     this->_OP_CODE_LUT[0xCB70] = &CPU::_bit_n_r;
//     this->_OP_CODE_LUT[0xCB71] = &CPU::_bit_n_r;
//     this->_OP_CODE_LUT[0xCB72] = &CPU::_bit_n_r;
//     this->_OP_CODE_LUT[0xCB73] = &CPU::_bit_n_r;
//     this->_OP_CODE_LUT[0xCB74] = &CPU::_bit_n_r;
//     this->_OP_CODE_LUT[0xCB75] = &CPU::_bit_n_r;
//     // this->_OP_CODE_LUT[0xCB76] =
//     this->_OP_CODE_LUT[0xCB77] = &CPU::_bit_n_r;
//     this->_OP_CODE_LUT[0xCB78] = &CPU::_bit_n_r;
//     this->_OP_CODE_LUT[0xCB79] = &CPU::_bit_n_r;
//     this->_OP_CODE_LUT[0xCB7A] = &CPU::_bit_n_r;
//     this->_OP_CODE_LUT[0xCB7B] = &CPU::_bit_n_r;
//     this->_OP_CODE_LUT[0xCB7C] = &CPU::_bit_n_r;
//     this->_OP_CODE_LUT[0xCB7D] = &CPU::_bit_n_r;
//     // this->_OP_CODE_LUT[0xCB7E] =
//     this->_OP_CODE_LUT[0xCB7F] = &CPU::_bit_n_r;
//     ////////////////////////////////////////////////////////////////

//     ////////////////////////////////////////////////////////////////
//     /* CB 0x80 */
//     // this->_OP_CODE_LUT[0xCB80] =
//     // this->_OP_CODE_LUT[0xCB81] =
//     // this->_OP_CODE_LUT[0xCB82] =
//     // this->_OP_CODE_LUT[0xCB83] =
//     // this->_OP_CODE_LUT[0xCB84] =
//     // this->_OP_CODE_LUT[0xCB85] =
//     // this->_OP_CODE_LUT[0xCB86] =
//     // this->_OP_CODE_LUT[0xCB87] =
//     // this->_OP_CODE_LUT[0xCB88] =
//     // this->_OP_CODE_LUT[0xCB89] =
//     // this->_OP_CODE_LUT[0xCB8A] =
//     // this->_OP_CODE_LUT[0xCB8B] =
//     // this->_OP_CODE_LUT[0xCB8C] =
//     // this->_OP_CODE_LUT[0xCB8D] =
//     // this->_OP_CODE_LUT[0xCB8E] =
//     // this->_OP_CODE_LUT[0xCB8F] =
//     ////////////////////////////////////////////////////////////////

//     ////////////////////////////////////////////////////////////////
//     /* CB 0x90 */
//     // this->_OP_CODE_LUT[0xCB90] =
//     // this->_OP_CODE_LUT[0xCB91] =
//     // this->_OP_CODE_LUT[0xCB92] =
//     // this->_OP_CODE_LUT[0xCB93] =
//     // this->_OP_CODE_LUT[0xCB94] =
//     // this->_OP_CODE_LUT[0xCB95] =
//     // this->_OP_CODE_LUT[0xCB96] =
//     // this->_OP_CODE_LUT[0xCB97] =
//     // this->_OP_CODE_LUT[0xCB98] =
//     // this->_OP_CODE_LUT[0xCB99] =
//     // this->_OP_CODE_LUT[0xCB9A] =
//     // this->_OP_CODE_LUT[0xCB9B] =
//     // this->_OP_CODE_LUT[0xCB9C] =
//     // this->_OP_CODE_LUT[0xCB9D] =
//     // this->_OP_CODE_LUT[0xCB9E] =
//     // this->_OP_CODE_LUT[0xCB9F] =
//     ////////////////////////////////////////////////////////////////

//     ////////////////////////////////////////////////////////////////
//     /* CB 0xA0 */
//     // this->_OP_CODE_LUT[0xCBA0] =
//     // this->_OP_CODE_LUT[0xCBA1] =
//     // this->_OP_CODE_LUT[0xCBA2] =
//     // this->_OP_CODE_LUT[0xCBA3] =
//     // this->_OP_CODE_LUT[0xCBA4] =
//     // this->_OP_CODE_LUT[0xCBA5] =
//     // this->_OP_CODE_LUT[0xCBA6] =
//     // this->_OP_CODE_LUT[0xCBA7] =
//     // this->_OP_CODE_LUT[0xCBA8] =
//     // this->_OP_CODE_LUT[0xCBA9] =
//     // this->_OP_CODE_LUT[0xCBAA] =
//     // this->_OP_CODE_LUT[0xCBAB] =
//     // this->_OP_CODE_LUT[0xCBAC] =
//     // this->_OP_CODE_LUT[0xCBAD] =
//     // this->_OP_CODE_LUT[0xCBAE] =
//     // this->_OP_CODE_LUT[0xCBAF] =
//     ////////////////////////////////////////////////////////////////

//     ////////////////////////////////////////////////////////////////
//     /* CB 0xB0 */
//     // this->_OP_CODE_LUT[0xCBB0] =
//     // this->_OP_CODE_LUT[0xCBB1] =
//     // this->_OP_CODE_LUT[0xCBB2] =
//     // this->_OP_CODE_LUT[0xCBB3] =
//     // this->_OP_CODE_LUT[0xCBB4] =
//     // this->_OP_CODE_LUT[0xCBB5] =
//     // this->_OP_CODE_LUT[0xCBB6] =
//     // this->_OP_CODE_LUT[0xCBB7] =
//     // this->_OP_CODE_LUT[0xCBB8] =
//     // this->_OP_CODE_LUT[0xCBB9] =
//     // this->_OP_CODE_LUT[0xCBBA] =
//     // this->_OP_CODE_LUT[0xCBBB] =
//     // this->_OP_CODE_LUT[0xCBBC] =
//     // this->_OP_CODE_LUT[0xCBBD] =
//     // this->_OP_CODE_LUT[0xCBBE] =
//     // this->_OP_CODE_LUT[0xCBBF] =
//     ////////////////////////////////////////////////////////////////

//     ////////////////////////////////////////////////////////////////
//     /* CB 0xC0 */
//     // this->_OP_CODE_LUT[0xCBC0] =
//     // this->_OP_CODE_LUT[0xCBC1] =
//     // this->_OP_CODE_LUT[0xCBC2] =
//     // this->_OP_CODE_LUT[0xCBC3] =
//     // this->_OP_CODE_LUT[0xCBC4] =
//     // this->_OP_CODE_LUT[0xCBC5] =
//     // this->_OP_CODE_LUT[0xCBC6] =
//     // this->_OP_CODE_LUT[0xCBC7] =
//     // this->_OP_CODE_LUT[0xCBC8] =
//     // this->_OP_CODE_LUT[0xCBC9] =
//     // this->_OP_CODE_LUT[0xCBCA] =
//     // this->_OP_CODE_LUT[0xCBCB] =
//     // this->_OP_CODE_LUT[0xCBCC] =
//     // this->_OP_CODE_LUT[0xCBCD] =
//     // this->_OP_CODE_LUT[0xCBCE] =
//     // this->_OP_CODE_LUT[0xCBCF] =
//     ////////////////////////////////////////////////////////////////

//     ////////////////////////////////////////////////////////////////
//     /* CB 0xD0 */
//     // this->_OP_CODE_LUT[0xCBD0] =
//     // this->_OP_CODE_LUT[0xCBD1] =
//     // this->_OP_CODE_LUT[0xCBD2] =
//     // this->_OP_CODE_LUT[0xCBD3] =
//     // this->_OP_CODE_LUT[0xCBD4] =
//     // this->_OP_CODE_LUT[0xCBD5] =
//     // this->_OP_CODE_LUT[0xCBD6] =
//     // this->_OP_CODE_LUT[0xCBD7] =
//     // this->_OP_CODE_LUT[0xCBD8] =
//     // this->_OP_CODE_LUT[0xCBD9] =
//     // this->_OP_CODE_LUT[0xCBDA] =
//     // this->_OP_CODE_LUT[0xCBDB] =
//     // this->_OP_CODE_LUT[0xCBDC] =
//     // this->_OP_CODE_LUT[0xCBDD] =
//     // this->_OP_CODE_LUT[0xCBDE] =
//     // this->_OP_CODE_LUT[0xCBDF] =
//     ////////////////////////////////////////////////////////////////

//     ////////////////////////////////////////////////////////////////
//     /* CB 0xE0 */
//     // this->_OP_CODE_LUT[0xCBE0] =
//     // this->_OP_CODE_LUT[0xCBE1] =
//     // this->_OP_CODE_LUT[0xCBE2] =
//     // this->_OP_CODE_LUT[0xCBE3] =
//     // this->_OP_CODE_LUT[0xCBE4] =
//     // this->_OP_CODE_LUT[0xCBE5] =
//     // this->_OP_CODE_LUT[0xCBE6] =
//     // this->_OP_CODE_LUT[0xCBE7] =
//     // this->_OP_CODE_LUT[0xCBE8] =
//     // this->_OP_CODE_LUT[0xCBE9] =
//     // this->_OP_CODE_LUT[0xCBEA] =
//     // this->_OP_CODE_LUT[0xCBEB] =
//     // this->_OP_CODE_LUT[0xCBEC] =
//     // this->_OP_CODE_LUT[0xCBED] =
//     // this->_OP_CODE_LUT[0xCBEE] =
//     // this->_OP_CODE_LUT[0xCBEF] =
//     ////////////////////////////////////////////////////////////////

//     ////////////////////////////////////////////////////////////////
//     /* CB 0xF0 */
//     // this->_OP_CODE_LUT[0xCBF0] =
//     // this->_OP_CODE_LUT[0xCBF1] =
//     // this->_OP_CODE_LUT[0xCBF2] =
//     // this->_OP_CODE_LUT[0xCBF3] =
//     // this->_OP_CODE_LUT[0xCBF4] =
//     // this->_OP_CODE_LUT[0xCBF5] =
//     // this->_OP_CODE_LUT[0xCBF6] =
//     // this->_OP_CODE_LUT[0xCBF7] =
//     // this->_OP_CODE_LUT[0xCBF8] =
//     // this->_OP_CODE_LUT[0xCBF9] =
//     // this->_OP_CODE_LUT[0xCBFA] =
//     // this->_OP_CODE_LUT[0xCBFB] =
//     // this->_OP_CODE_LUT[0xCBFC] =
//     // this->_OP_CODE_LUT[0xCBFD] =
//     // this->_OP_CODE_LUT[0xCBFE] =
//     // this->_OP_CODE_LUT[0xCBFF] =
//     ////////////////////////////////////////////////////////////////
// }

///////////////////////////////////////////////////////////////////////////////////////////
/* CPU CONTROL INSTRUCTIONS */

/*
CCF
    - OpCode = 0b00111111
    - flips the carry flag, clears the N and H flags
    - flags: -00c
*/
void CPU::_ccf() {
    this->_read_and_increment_PC();
    this->_clear_flag(SUB_FLAG);
    this->_clear_flag(HALF_CARRY_FLAG);

    if (this->_get_flag(CARRY_FLAG) == 1) { this->_clear_flag(CARRY_FLAG); }
    else { this->_set_flag(CARRY_FLAG); }

    this->cycles += MACHINE_CYCLE;
}

/*
SCF
    - OpCode = 0b00110111
    - sets the carry flag and clears the N and H flag
    - flags; -001
*/
void CPU::_scf() {
    this->_read_and_increment_PC();
    this->_clear_flag(SUB_FLAG);
    this->_clear_flag(HALF_CARRY_FLAG);
    this->_set_flag(CARRY_FLAG);
    this->cycles += MACHINE_CYCLE;
}

/*
NOP
    - OpCode = 0x00
    - do nothing for 4 clock cycles
*/
void CPU::_nop() {
    this->_read_and_increment_PC();
    this->cycles += MACHINE_CYCLE;
}

/*
HALT
    - OpCode = 0b01110110
    - halt until interrupt occurs
*/
void CPU::_halt() {
    this->_read_and_increment_PC();
    this->_is_halted = true;

    while (this->_is_halted) { this->cycles += MACHINE_CYCLE; }
}

/*
DI
    - OpCode = 0b01110110
    - disable all interrupts
*/
void CPU::_di() {
    this->_read_and_increment_PC();
    this->IME = 0;
    this->cycles += MACHINE_CYCLE;
}

/*
EI
    - OpCode = 0b01110110
    - enable all interrupts
*/
void CPU::_ei() {
    this->_read_and_increment_PC();
    this->IME = 1;
    this->cycles += MACHINE_CYCLE;
}
///////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////
/* JUMP INSTRUCTIONS */

/*
JP nn
    - OpCode = 0b11000011 nnnnnnnn nnnnnnnn
    - load the 16-bit address n into the program counter
*/
void CPU::_jp_nn() {
    this->_read_and_increment_PC();
    uint8_t n_lsb = this->_read_and_increment_PC();
    uint8_t n_msb = this->_read_and_increment_PC();

    this->jump( (n_msb << 8) | n_lsb );
    this->cycles += MACHINE_CYCLE*4;
}

/*
JP HL
    - OpCode = 0b11101001
    - load the address specified by HL into the program counter
*/
void CPU::_jp_HL() {
    this->_read_and_increment_PC();
    this->jump(this->_HL.raw);
    this->cycles += MACHINE_CYCLE;
}

/*
JP cc nn
    - OpCode = 0b11ccc010 nnnnnnnn nnnnnnnn
    - jump to the address n IF the condition specified by c is met
*/
void CPU::_jp_cc_nn() {
    uint8_t c = (this->_read_and_increment_PC() >> 3) & 0b11;
    uint8_t n_lsb = this->_read_and_increment_PC();
    uint8_t n_msb = this->_read_and_increment_PC();

    if (this->_eval_cond_code(c)) {
        this->jump( (n_msb << 8) | n_lsb );
        this->cycles += MACHINE_CYCLE*4;
    }
    else {
        this->cycles += MACHINE_CYCLE*3;
    }
}

/*
JR dd
    - OpCode = 0b00011000 dddddddd
    - PC += dd, where dd is a SIGNED 8-bit integer
*/
void CPU::_jr_dd() {
    this->_read_and_increment_PC();
    uint8_t d = static_cast<int8_t>(this->_read_and_increment_PC());
    this->_PC.raw += d;
    this->cycles += MACHINE_CYCLE*3;
}

/*
JR cc dd
    - OpCode = 0b001cc000 dddddddd
    - PC += dd, where dd is a SIGNED 8-bit integer, IF the conditions
      specified by c is met
*/
void CPU::_jr_cc_dd() {
    uint8_t c = (this->_read_and_increment_PC() >> 3) & 0b11;
    int8_t d = static_cast<int8_t>(this->_read_and_increment_PC());

    if (this->_eval_cond_code(c)) {
        this->_PC.raw += d;
        this->cycles += MACHINE_CYCLE*3;
    }
    else {
        this->cycles += MACHINE_CYCLE*2;
    }
}

/*
CALL nn
    - OpCode = 0b11001101 nnnnnnnn nnnnnnnn
    - make a call to a subroutine
        - push the address specified by PC to the stack
        - set PC to the address specified by n
        - at the end of the subroutine (RET instruction),
          pop and set PC back from stack
*/
void CPU::_call_nn() {
    this->_read_and_increment_PC();
    uint8_t n_lsb = this->_read_and_increment_PC();
    uint8_t n_msb = this->_read_and_increment_PC();

    this->call( (n_msb << 8) | n_lsb );

    this->cycles += MACHINE_CYCLE*6;
}

/*
CALL cc nn
    - OpCode = 0b110cc100 nnnnnnnn nnnnnnnn
    - call to subroutine at address n IF conditions specified by c are met
*/
void CPU::_call_cc_nn() {
    uint8_t c = (this->_read_and_increment_PC() >> 3) & 0b11;
    uint8_t n_lsb = this->_read_and_increment_PC();
    uint8_t n_msb = this->_read_and_increment_PC();

    if (this->_eval_cond_code(c)) {
        this->call( (n_msb << 8) | n_lsb );
        this->cycles += MACHINE_CYCLE*6;
    }
    else {
        this->cycles += MACHINE_CYCLE*3;
    }
}

/*
RET
    - OpCode = 0b11001001
    - return from subroutine:
        - pop PC from stack and set PC to the value which was popped
*/
void CPU::_ret() {
    this->_read_and_increment_PC();

    uint8_t pc_lsb = this->_pop_stack();
    uint8_t pc_msb = this->_pop_stack();
    this->_PC.raw = (pc_msb << 8) | pc_lsb;
    this->cycles += MACHINE_CYCLE*4;
}

/*
RET cc
    - OpCode = 0b110cc000
    - return from subroutine IF the condition specified by c is met
*/
void CPU::_ret_cc() {
    uint8_t c = (this->_read_and_increment_PC() >> 3) & 0b11;

    if (this->_eval_cond_code(c)) {
        uint8_t pc_lsb = this->_pop_stack();
        uint8_t pc_msb = this->_pop_stack();
        this->_PC.raw = (pc_msb << 8) | pc_lsb;
        this->cycles += MACHINE_CYCLE*5;
    }
    else {
        this->cycles += MACHINE_CYCLE*2;
    }
}

/*
RETI
    - OpCode = 0b11011001
    - return from subroutine and enable all interrupts
*/
void CPU::_reti() {
    this->_read_and_increment_PC();

    uint8_t pc_lsb = this->_pop_stack();
    uint8_t pc_msb = this->_pop_stack();
    this->_PC.raw = (pc_msb << 8) | pc_lsb;

    this->IME = 1;

    this->cycles += MACHINE_CYCLE*4;
}

/*
RST n
    - OpCode = 0b11nnn111
    - call to 0x00, 0x08, 0x10, 0x18, 0x20, 0x28, 0x30, or 0x38 depending on n
*/
void CPU::_rst_n() {
    uint8_t n = (this->_read_and_increment_PC() >> 3) & 0b111;

    uint8_t addr;
    switch (n) {
        case (0b000):
            addr = 0x00;
            break;
        case (0b001):
            addr = 0x08;
            break;
        case (0b010):
            addr = 0x10;
            break;
        case (0b011):
            addr = 0x18;
            break;
        case (0b100):
            addr = 0x20;
            break;
        case (0b101):
            addr = 0x28;
            break;
        case (0b110):
            addr = 0x30;
            break;
        case (0b111):
            addr = 0x38;
            break;
    }

    this->_push_stack(this->_PC.bytes[1]);
    this->_push_stack(this->_PC.bytes[0]);
    this->_PC.raw = addr;

    this->cycles += MACHINE_CYCLE*4;

}
///////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////
/* 8-BIT LOAD INSTRUCTIONS */
/*
LD r, R
    - OpCode = 0b01xxxyyy
    - load to the 8-bit register r, data from the 8-bit register R
*/
void CPU::_ld_r_R() {
    uint8_t opcode = this->_read_and_increment_PC();

    uint8_t* r = this->_get_8_bit_reg( (opcode >> 3) & 0b111 );
    uint8_t* R = this->_get_8_bit_reg(opcode & 0b111);
    (*r) = (*R);

    this->cycles += MACHINE_CYCLE;
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

    this->cycles += MACHINE_CYCLE*2;
}

/*
LD r, (HL)
    - OpCode = 0b01xxx110
    - load to the 8-bit register r, data from the address specified by register HL
*/
void CPU::_ld_r_HL() {
    uint8_t opcode = this->_read_and_increment_PC();

    uint8_t* r = this->_get_8_bit_reg( (opcode >> 3) & 0b111 );
    (*r) = this->mem_read_byte(this->_HL.raw);

    this->cycles += MACHINE_CYCLE*2;
}

/*
LD (HL), r
    - OpCode = 0b01100xxx
    - load to the address specificed by register HL, data from the 8-bit register r
*/
void CPU::_ld_HL_r() {
    uint8_t opcode = this->_read_and_increment_PC();

    uint8_t* r = this->_get_8_bit_reg(opcode & 0b111);
    this->mem_write_byte(this->_HL.raw, *r);

    this->cycles += MACHINE_CYCLE*2;
}

/*
LD (HL), n
    - OpCode = 0b00110110 + n
    - load to the address specified by register HL, the immediate data n
*/
void CPU::_ld_HL_n() {
    this->_read_and_increment_PC();

    uint8_t n = this->_read_and_increment_PC();
    this->mem_write_byte(this->_HL.raw, n);

    this->cycles += MACHINE_CYCLE*3;
}

/*
LD A, (BC)
    - OpCode = 0b00001010
    - load to the register A, data from the address specified by register BC
*/
void CPU::_ld_A_BC() {
    this->_read_and_increment_PC();    
    this->_AF.bytes[1] = this->mem_read_byte(this->_BC.raw);
    this->cycles += MACHINE_CYCLE*2;
}

/*
LD A, (DE)
    - OpCode = 0b00011010
    - load to the 8-bit register A, data from the address specified by register DE
*/
void CPU::_ld_A_DE() {
    this->_read_and_increment_PC();
    this->_AF.bytes[1] = this->mem_read_byte(this->_DE.raw);
    this->cycles += MACHINE_CYCLE*2;
}

/*
LD (BC), A
    - OpCode = 0b00000010
    - load to the address specified by register BC, data from the 8-bit register A
*/
void CPU::_ld_BC_A() {
    this->_read_and_increment_PC();

    uint16_t addr = this->_BC.raw;
    this->mem_write_byte(addr, this->_AF.bytes[1]);

    this->cycles += MACHINE_CYCLE*2;
}

/*
LD (DE), A
    - OpCode = 0b00010010
    - load to the address specified by register DE, data from the 8-bit register A
*/
void CPU::_ld_DE_A() {
    this->_read_and_increment_PC();

    uint16_t addr = this->_DE.raw;
    this->mem_write_byte(addr, this->_AF.bytes[1]);

    this->cycles += MACHINE_CYCLE*2;
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
    this->_AF.bytes[1] = this->mem_read_byte(addr);

    this->cycles += MACHINE_CYCLE*4;
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

    uint16_t addr = (msb_n << 8) | lsb_n;
    this->mem_write_byte(addr, this->_AF.bytes[1]);

    this->cycles += MACHINE_CYCLE*4;
}

/*
LD A, (FF00 + n)
    - OpCode = 0b11110000 + n
    - load to the 8-bit register A, data specifed by the 16-bit address (0xFF00 + n), where n is an 8-bit operand
*/
void CPU::_ld_A_FF00_n() {
    this->_read_and_increment_PC();
    uint8_t n = this->_read_and_increment_PC() & 0xff;
    this->_AF.bytes[1] = this->mem_read_byte(0xff00 + n);
    this->cycles += MACHINE_CYCLE*3;
}

/*
LD (FF00 + n), A
    - OpCode = 0b11100000 + n
    - load to the 16-bit address (0xFF00 + n), the data in the 8-bit register A
*/
void CPU::_ld_FF00_n_A() {
    this->_read_and_increment_PC();
    uint8_t n = this->_read_and_increment_PC() & 0xff;
    this->mem_write_byte(0xff00 + n, this->_AF.bytes[1]);
    this->cycles += MACHINE_CYCLE*3;
}

/*
LD A, (FF00 + C)
    - OpCode = 0b11110010
    - load to the 8-bit register A, data from the 16-bit address specified by (0xFF00 + C)
*/
void CPU::_ld_A_FF00_C() {
    this->_read_and_increment_PC();
    this->_AF.bytes[1] = this->mem_read_byte(0xff00 + this->_BC.bytes[0]);
    this->cycles += MACHINE_CYCLE*2;
}

/*
LD (FF00 + C), A
    - OpCode = 0b11100010
    - load to the 16-bit address specified by (0xFF00 + C), the data in the 8-bit register A
*/
void CPU::_ld_FF00_C_A() {
    this->_read_and_increment_PC();
    uint16_t addr = 0xff00 + this->_BC.bytes[0];
    this->mem_write_byte(addr, this->_AF.bytes[1]);
    this->cycles += MACHINE_CYCLE*2;
}

/*
LDI (HL), A
    - OpCode = 0b00100010
    - load to the address specified by register HL, the data in register A, and increment HL by 1
*/
void CPU::_ldi_HL_A() {
    this->_read_and_increment_PC();
    this->mem_write_byte(this->_HL.raw, this->_AF.bytes[1]);
    this->_HL.raw += 1;
    this->cycles += MACHINE_CYCLE*2;
}

/*
LDI A, (HL)
    - OpCode = 0b00101010
    - load to register A, the data at the address specified by HL, and increment HL by 1
*/
void CPU::_ldi_A_HL() {
    this->_read_and_increment_PC();
    this->_AF.bytes[1] = this->mem_read_byte(this->_HL.raw);
    this->_HL.raw += 1;
    this->cycles += MACHINE_CYCLE*2;
}

/*
LDD (HL), A
    - OpCode = 0b00110010
    - load to address specified by register HL, the data in register A, and decrement HL by 1
*/
void CPU::_ldd_HL_A() {
    this->_read_and_increment_PC();
    this->mem_write_byte(this->_HL.raw, this->_AF.bytes[1]);
    this->_HL.raw -= 1;
    this->cycles += MACHINE_CYCLE*2;
}

/*
LDD A, (HL)
    - OpCode = 0b00111010
    - load to register A, the data in the address specified by register HL, and decrement HL by 1
*/
void CPU::_ldd_A_HL() {
    this->_read_and_increment_PC();
    this->_AF.bytes[1] = this->mem_read_byte(this->_HL.raw);
    this->_HL.raw -= 1;
    this->cycles += MACHINE_CYCLE*2;
}
///////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////
/* 16-BIT LOAD INSTRUCTIONS */
/*
LD rr, nn
    - OpCode = 0b00xx0001 + n
    - load to the 16-bit register rr, the 16-bit immediate data n
*/
void CPU::_ld_rr_nn() {
    uint8_t opcode = this->_read_and_increment_PC();
    uint8_t lsb_n = this->_read_and_increment_PC();
    uint8_t msb_n = this->_read_and_increment_PC();

    Reg* reg = this->_get_16_bit_reg( (opcode >> 4) & 0b11 );
    reg->raw = (msb_n << 8) | lsb_n;

    this->cycles += MACHINE_CYCLE*3;
}

/*
LD (nn), SP
    - OpCode = 0b00001000 + n
    - load to the address specified by the 16-bit operand n, data from the SP register
*/
void CPU::_ld_nn_SP() {
    this->_read_and_increment_PC();
    uint8_t lsb_n = this->_read_and_increment_PC();
    uint8_t msb_n = this->_read_and_increment_PC();

    uint16_t addr = (msb_n << 8) | lsb_n;
    this->mem_write_byte(addr, this->_SP.raw);

    this->cycles += MACHINE_CYCLE*5;
}

/*
LD SP, HL
    - OpCode = 0b11111001
    - load to the SP register, data from the HL register
*/
void CPU::_ld_SP_HL() {
    this->_read_and_increment_PC();
    this->_SP.raw = this->_HL.raw;
    this->cycles += MACHINE_CYCLE*2;
}

/*
PUSH rr
    - OpCode = 0b11xx0101
    - push to the stack memory, data from the 16-bit register rr
*/
void CPU::_push_rr() {
    uint8_t opcode = this->_read_and_increment_PC();
    Reg* reg = this->_get_16_bit_reg( (opcode >> 4) & 0b11 );

    this->_push_stack(reg->bytes[1]);
    this->_push_stack(reg->bytes[0]);

    this->cycles += MACHINE_CYCLE*4;
}

/*
POP rr
    - OpCode = 0b11xx0001
    - pop to the 16-bit register rr, data from the stack
*/
void CPU::_pop_rr() {
    uint8_t opcode = this->_read_and_increment_PC();
    Reg* reg = this->_get_16_bit_reg( (opcode >> 4) & 0b11 );

    uint8_t lsb = this->_pop_stack();
    uint8_t msb = this->_pop_stack();

    reg->raw = (msb << 8) | lsb;

    this->cycles += MACHINE_CYCLE*3;    
}

/*
LD HL, SP + dd
    - OpCode = 0b11111000 + dd
    - Add the SIGNED 8-bit operand dd to the stack pointer SP, and store the result in HL
    - flags: 00hc
*/
void CPU::_ld_HL_SP_dd() {
    this->_read_and_increment_PC();
    int8_t d = static_cast<int8_t>(this->_read_and_increment_PC());
    this->_HL.raw = this->_SP.raw + d;

    this->_clear_flag(ZERO_FLAG);
    this->_clear_flag(SUB_FLAG);

    if (CHECK_8_BIT_HALF_CARRY(this->_SP.raw, d)) { this->_set_flag(HALF_CARRY_FLAG); }
    else { this->_clear_flag(HALF_CARRY_FLAG); }

    if (CHECK_8_BIT_CARRY(this->_SP.raw, d)) { this->_set_flag(CARRY_FLAG); }
    else { this->_clear_flag(CARRY_FLAG); }

    this->cycles += MACHINE_CYCLE*3;
}
///////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////
/* 8-BIT ARITHMETIC/LOGIC INSTRUCTIONS */

/*
ADD A, r
    - OpCode = 0b10000xxx
    - the contents of register r are added to the accumulator (A)
    - flags: z0hc
*/
void CPU::_add_A_r() {
    uint8_t opcode = this->_read_and_increment_PC();
    uint8_t* r = this->_get_8_bit_reg(opcode & 0b111);
    this->_AF.bytes[1] = this->_add_bytes(this->_AF.bytes[1], *r);
    this->cycles += MACHINE_CYCLE;
}

/*
ADD A, n
    - OpCode = 0b11000110 + n
    - the integer n is added to the contents of A
    - flags: z0hc
*/
void CPU::_add_A_n() {
    this->_read_and_increment_PC();
    uint8_t n = this->_read_and_increment_PC();
    this->_AF.bytes[1] = this->_add_bytes(this->_AF.bytes[1], n);
    this->cycles += MACHINE_CYCLE*2;
}

/*
ADD A, (HL)
    - OpCode = 0b10000110
    - the byte at the memory address specified by HL is added to A
    - flags: z0hc
*/
void CPU::_add_A_HL() {
    this->_read_and_increment_PC();
    uint8_t data = this->mem_read_byte(this->_HL.raw);
    this->_AF.bytes[1] = this->_add_bytes(data, this->_AF.bytes[1]);
    this->cycles += MACHINE_CYCLE*2;
}

/*
ADC A, r
    - OpCode = 0b10001xxx
    - the data in register r is added to A, plus the carry flag
    - flags: z0hc
*/
void CPU::_adc_A_r() {
    uint8_t opcode = this->_read_and_increment_PC();
    uint8_t* r = this->_get_8_bit_reg(opcode & 0b111);
    uint8_t c = this->_get_flag(CARRY_FLAG);
    this->_AF.bytes[1] = this->_add_bytes(this->_AF.bytes[1], *r + c);
    this->cycles += MACHINE_CYCLE;
}

/*
ADC A, n
    - OpCode = 0b11001110 + n
    - the 8-bit integer n is added to A, plus the carry flag
    - flags: z0hc
*/
void CPU::_adc_A_n() {
    this->_read_and_increment_PC();
    uint8_t n = this->_read_and_increment_PC();
    uint8_t c = this->_get_flag(CARRY_FLAG);
    this->_AF.bytes[1] = this->_add_bytes(this->_AF.bytes[1], n + c);
    this->cycles += MACHINE_CYCLE*2;
}

/*
ADC A, (HL)
    - OpCode = 0b10001110
    - the data from the address specified by HL is added to A
    - flags: z0hc
*/
void CPU::_adc_A_HL() {
    this->_read_and_increment_PC();
    uint8_t data = this->mem_read_byte(this->_HL.raw);
    uint8_t c = this->_get_flag(CARRY_FLAG);
    this->_AF.bytes[1] = this->_add_bytes(this->_AF.bytes[1], data + c);
    this->cycles += MACHINE_CYCLE*2;
}

/*
SUB r
    - OpCode = 0b10010xxx
    - the data from register r is subtracted from A
    - flags: z1hc
*/
void CPU::_sub_r() {
    uint8_t opcode = this->_read_and_increment_PC();
    uint8_t* r = this->_get_8_bit_reg(opcode & 0b111);
    this->_AF.bytes[1] = this->_sub_bytes(this->_AF.bytes[1], *r);
    this->cycles += MACHINE_CYCLE;
}

/*
SUB n
    - OpCode = 0b11010110 + n
    - the data from the 8-bit operand n is subtracted from A
    - flags: z1hc
*/
void CPU::_sub_n() {
    this->_read_and_increment_PC();
    uint8_t n = this->_read_and_increment_PC();
    this->_AF.bytes[1] = this->_sub_bytes(this->_AF.bytes[1], n);
    this->cycles += MACHINE_CYCLE*2;
}

/*
SUB (HL)
    - OpCode = 0b10010110
    - the data from the address specified by HL is subtracted from A
    - flags: z1hc
*/
void CPU::_sub_HL() {
    this->_read_and_increment_PC();
    uint8_t data = this->mem_read_byte(this->_HL.raw);
    this->_AF.bytes[1] = this->_sub_bytes(this->_AF.bytes[1], data);
    this->cycles += MACHINE_CYCLE*2;
}

/*
SBC A, r
    - OpCode = 0b10011xxx
    - the data from register r is subtracted from A, plus the carry flag
    - flags: z1hc
*/
void CPU::_sbc_A_r() {
    uint8_t opcode = this->_read_and_increment_PC();
    uint8_t* r = this->_get_8_bit_reg(opcode & 0b111);
    uint8_t c = this->_get_flag(CARRY_FLAG);
    this->_AF.bytes[1] = this->_sub_bytes(this->_AF.bytes[1], *r + c);
    this->cycles += MACHINE_CYCLE;
}

/*
SBC A, n
    - OpCode = 0b11011110 + n
    - the 8-bit integer n is subtracted from A, plus the carry flag
    - flags: z1hc
*/
void CPU::_sbc_A_n() {
    this->_read_and_increment_PC();
    uint8_t n = this->_read_and_increment_PC();
    uint8_t c = this->_get_flag(CARRY_FLAG);
    this->_AF.bytes[1] = this->_sub_bytes(this->_AF.bytes[1], n + c);
    this->cycles += MACHINE_CYCLE*2;
}

/*
SBC A, (HL)
    - OpCode = 0b10011110
    - the data from the address specified by HL is subtracted from A, plus the carry flag
    - flags: z1hc
*/
void CPU::_sbc_A_HL() {
    this->_read_and_increment_PC();
    uint8_t data = this->mem_read_byte(this->_HL.raw);
    uint8_t c = this->_get_flag(CARRY_FLAG);
    this->_AF.bytes[1] = this->_sub_bytes(this->_AF.bytes[1], data + c);
    this->cycles += MACHINE_CYCLE*2;
}

/*
AND r
    - OpCode = 0b10100xxx
    - logical AND data from A with the data from register r
    - flags: z010
*/
void CPU::_and_r() {
    uint8_t opcode = this->_read_and_increment_PC();
    uint8_t* r = this->_get_8_bit_reg(opcode & 0b111);
    this->_AF.bytes[1] &= (*r);

    if (this->_AF.raw == 0) { this->_set_flag(ZERO_FLAG); }
    else { this->_clear_flag(ZERO_FLAG); }

    this->_clear_flag(SUB_FLAG);
    this->_set_flag(HALF_CARRY_FLAG);
    this->_clear_flag(CARRY_FLAG);

    this->cycles += MACHINE_CYCLE;
}

/*
AND n
    - OpCode = 0b111100110 + n
    - logical AND data from A with data from the operand n
    - flags: z010
*/
void CPU::_and_n() {
    this->_read_and_increment_PC();
    uint8_t n = this->_read_and_increment_PC();
    this->_AF.bytes[1] &= n;

    if (this->_AF.raw == 0) { this->_set_flag(ZERO_FLAG); }
    else { this->_clear_flag(ZERO_FLAG); }

    this->_clear_flag(SUB_FLAG);
    this->_set_flag(HALF_CARRY_FLAG);
    this->_clear_flag(CARRY_FLAG);

    this->cycles += MACHINE_CYCLE*2;
}

/*
AND (HL)
    - OpCode = 0b10100110
    - logical AND data from A with the data from the address specified by HL
    - flags: z010
*/
void CPU::_and_HL() {
    this->_read_and_increment_PC();
    uint8_t data = this->mem_read_byte(this->_HL.raw);
    this->_AF.bytes[1] &= data;

    if (this->_AF.raw == 0) { this->_set_flag(ZERO_FLAG); }
    else { this->_clear_flag(ZERO_FLAG); }

    this->_clear_flag(SUB_FLAG);
    this->_set_flag(HALF_CARRY_FLAG);
    this->_clear_flag(CARRY_FLAG);

    this->cycles += MACHINE_CYCLE*2;
}

/*
XOR r
    - OpCode = 0b10110xxx
    - logical XOR data from A with data from the register r
    - flags: z000
*/
void CPU::_xor_r() {
    uint8_t opcode = this->_read_and_increment_PC();
    uint8_t* r = this->_get_8_bit_reg(opcode & 0b111);
    this->_AF.bytes[1] ^= (*r);

    if (this->_AF.raw == 0) { this->_set_flag(ZERO_FLAG); }
    else { this->_clear_flag(ZERO_FLAG); }

    this->_clear_flag(SUB_FLAG);
    this->_clear_flag(HALF_CARRY_FLAG);
    this->_clear_flag(CARRY_FLAG);

    this->cycles += MACHINE_CYCLE;
}

/*
XOR n
    - OpCode = 0b11110110 + n
    - logical XOR data from A with data from the operand n
    - flags: z000
*/
void CPU::_xor_n() {
    this->_read_and_increment_PC();
    uint8_t n = this->_read_and_increment_PC();
    this->_AF.bytes[1] ^= n;

    if (this->_AF.raw == 0) { this->_set_flag(ZERO_FLAG); }
    else { this->_clear_flag(ZERO_FLAG); }

    this->_clear_flag(SUB_FLAG);
    this->_clear_flag(HALF_CARRY_FLAG);
    this->_clear_flag(CARRY_FLAG);

    this->cycles += MACHINE_CYCLE*2;
}

/*
XOR (HL)
    - OpCode = 
    - logical XOR data from A with data from the adddress specified by HL
    - flags: z000
*/
void CPU::_xor_HL() {
    this->_read_and_increment_PC();
    uint8_t data = this->mem_read_byte(this->_HL.raw);
    this->_AF.bytes[1] ^= data;

    if (this->_AF.raw == 0) { this->_set_flag(ZERO_FLAG); }
    else { this->_clear_flag(ZERO_FLAG); }

    this->_clear_flag(SUB_FLAG);
    this->_clear_flag(HALF_CARRY_FLAG);
    this->_clear_flag(CARRY_FLAG);

    this->cycles += MACHINE_CYCLE*2;
}

/*
OR r
    - OpCode = 0b10110xxx
    - logical OR the data from A with the data from register r
    - flags: z000
*/
void CPU::_or_r() {
    uint8_t opcode = this->_read_and_increment_PC();
    uint8_t* r = this->_get_8_bit_reg(opcode & 0b111);
    this->_AF.bytes[1] |= (*r);

    if (this->_AF.raw == 0) { this->_set_flag(ZERO_FLAG); }
    else { this->_clear_flag(ZERO_FLAG); }

    this->_clear_flag(SUB_FLAG);
    this->_clear_flag(HALF_CARRY_FLAG);
    this->_clear_flag(CARRY_FLAG);

    this->cycles += MACHINE_CYCLE;
}

/*
OR n
    - OpCode = 0b11110110 + n
    - logical OR the data from A with the data from the operand n
    - flags: z000
*/
void CPU::_or_n() {
    this->_read_and_increment_PC();
    uint8_t n = this->_read_and_increment_PC();
    this->_AF.bytes[1] |= n;

    if (this->_AF.raw == 0) { this->_set_flag(ZERO_FLAG); }
    else { this->_clear_flag(ZERO_FLAG); }

    this->_clear_flag(SUB_FLAG);
    this->_clear_flag(HALF_CARRY_FLAG);
    this->_clear_flag(CARRY_FLAG);

    this->cycles += MACHINE_CYCLE*2;
}

/*
OR (HL)
    - OpCode = 0b101100110
    - logical OR data from r with the data at the address specified by HL
    - flags: z000
*/
void CPU::_or_HL() {
    this->_read_and_increment_PC();
    uint8_t data = this->mem_read_byte(this->_HL.raw);
    this->_AF.bytes[1] |= data;

    if (this->_AF.raw == 0) { this->_set_flag(ZERO_FLAG); }
    else { this->_clear_flag(ZERO_FLAG); }

    this->_clear_flag(SUB_FLAG);
    this->_clear_flag(HALF_CARRY_FLAG);
    this->_clear_flag(CARRY_FLAG);

    this->cycles += MACHINE_CYCLE*2;
}

/*
CP r
    - OpCode = 0b10111xxx
    - the contents of register r is compared with the contents of the accumulator (A)
    - flags: z1hc
*/
void CPU::_cp_r() {
    uint8_t opcode = this->_read_and_increment_PC();
    uint8_t* r = this->_get_8_bit_reg(opcode & 0b111);
    this->_sub_bytes(this->_AF.bytes[1], *r);
    this->cycles += MACHINE_CYCLE;
}

/*
CP n
    - OpCode = 0b11111110 + n
    - compare the contents of A with the operand n
    - flags: z1hc
*/
void CPU::_cp_n() {
    this->_read_and_increment_PC();
    uint8_t n = this->_read_and_increment_PC();
    this->_sub_bytes(this->_AF.bytes[1], n);
    this->cycles += MACHINE_CYCLE*2;
}

/*
CP (HL)
    - OpCode = 0b10111110
    - compare the contents of A with the data at the address specified by HL
    - flags: z1hc
*/
void CPU::_cp_HL() {
    this->_read_and_increment_PC();
    uint8_t data = this->mem_read_byte(this->_HL.raw);
    this->_sub_bytes(this->_AF.bytes[1], data);
    this->cycles += MACHINE_CYCLE*2;
}

/*
INC r
    - OpCode = 0b00xxx100
    - the contents of register r is incremented by 1
    - flags: z0h-
*/
void CPU::_inc_r() {
    uint8_t opcode = this->_read_and_increment_PC();
    uint8_t* r = this->_get_8_bit_reg( (opcode >> 3) & 0b111 );

    if (*r == 0) { this->_set_flag(ZERO_FLAG); }
    else { this->_clear_flag(ZERO_FLAG); }

    this->_clear_flag(SUB_FLAG);

    if (CHECK_8_BIT_HALF_CARRY(*r, 1)) { this->_set_flag(HALF_CARRY_FLAG); }
    else { this->_clear_flag(HALF_CARRY_FLAG); }

    (*r) += 1;
    this->cycles += MACHINE_CYCLE;
}

/*
INC (HL)
    - OpCode = 0b00110100
    - increment the data located at the address specified by HL
    - flags: z0h-
*/
void CPU::_inc_HL() {
    this->_read_and_increment_PC();
    uint8_t data = this->mem_read_byte(this->_HL.raw);

    if (data == 0) { this->_set_flag(ZERO_FLAG); }
    else { this->_clear_flag(ZERO_FLAG); }

    this->_clear_flag(SUB_FLAG);

    if (CHECK_8_BIT_HALF_CARRY(data, 1)) { this->_set_flag(HALF_CARRY_FLAG); }
    else { this->_clear_flag(HALF_CARRY_FLAG); }

    this->mem_write_byte(this->_HL.raw, data + 1);
    this->cycles += MACHINE_CYCLE*3;
}

/*
DEC r
    - OpCode = 0b00xxx101
    - decrement the data in register r
    - flags: z1h-
*/
void CPU::_dec_r() {
    uint8_t opcode = this->_read_and_increment_PC();
    uint8_t* r = this->_get_8_bit_reg( (opcode >> 3) & 0b111 );

    if (*r == 0) { this->_set_flag(ZERO_FLAG); }
    else { this->_clear_flag(ZERO_FLAG); }

    this->_clear_flag(SUB_FLAG);

    if (CHECK_8_BIT_HALF_CARRY(*r, 1)) { this->_set_flag(HALF_CARRY_FLAG); }
    else { this->_clear_flag(HALF_CARRY_FLAG); }

    (*r) -= 1;
    this->cycles += MACHINE_CYCLE;
}

/*
DEC (HL)
    - OpCode = 0b00110101
    - decrement the data at the address specified by HL
    - flags: z1h-
*/
void CPU::_dec_HL() {
    this->_read_and_increment_PC();
    uint8_t data = this->mem_read_byte(this->_HL.raw);

    if (data == 0) { this->_set_flag(ZERO_FLAG); }
    else { this->_clear_flag(ZERO_FLAG); }

    this->_clear_flag(SUB_FLAG);

    if (CHECK_8_BIT_HALF_CARRY(data, 1)) { this->_set_flag(HALF_CARRY_FLAG); }
    else { this->_clear_flag(HALF_CARRY_FLAG); }

    this->mem_write_byte(this->_HL.raw, data + 1);
    this->cycles += MACHINE_CYCLE*3;
}

/*
DAA
    - OpCode = 0b00100111
    - conditionally adjust the accumulator for BCD addition and subtraction operations
    - flags: z-0c
*/
void CPU::_daa() {
    this->_read_and_increment_PC();

    bool s = this->_get_flag(SUB_FLAG);
    bool h = this->_get_flag(HALF_CARRY_FLAG);
    bool c = this->_get_flag(CARRY_FLAG);    
    uint32_t A = this->_AF.bytes[1];

    if (s) {
        if (h || (A & 0xf) > 0x09) { A += 0x06; }
        if (c || (A > 0x9F)) { A += 0x60; }
    }
    else {
        if (h) { A = (A - 0x06) & 0xff; }
        if (c) { A -= 0x60; }
    }

    if (A == 0) { this->_set_flag(ZERO_FLAG); }
    else { this->_clear_flag(ZERO_FLAG); }

    this->_clear_flag(HALF_CARRY_FLAG);

    if (A > 0xff) { this->_set_flag(CARRY_FLAG); }
    else { this->_clear_flag(CARRY_FLAG); }

    this->_AF.bytes[1] = A & 0xff;

    this->cycles += MACHINE_CYCLE;
}

/*
CPL
    - OpCode = 0b00101111
    - the data in the accumulator are inverted
    - flags: -11-
*/
void CPU::_cpl() {
    this->_read_and_increment_PC();
    this->_AF.bytes[1] ^= 0xff;
    this->_set_flag(SUB_FLAG);
    this->_set_flag(HALF_CARRY_FLAG);
    this->cycles += MACHINE_CYCLE;
}
///////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////
/* 16-BIT ARITHMETIC/LOGIC INSTRUCTIONS */

/*
ADD HL, rr
    - OpCode = 0b00xx1001
    - the data in the 16-bit register rr is added to HL
    - flags: -0hc
*/
void CPU::_add_HL_rr() {
    uint8_t opcode = this->_read_and_increment_PC();
    Reg* r = this->_get_16_bit_reg( (opcode >> 4) & 0b11 );

    this->_clear_flag(SUB_FLAG);
    if (CHECK_16_BIT_HALF_CARRY(this->_HL.raw, r->raw)) { this->_set_flag(HALF_CARRY_FLAG); }
    else { this->_clear_flag(HALF_CARRY_FLAG); }
    if (CHECK_16_BIT_CARRY(this->_HL.raw, r->raw)) { this->_set_flag(CARRY_FLAG); }
    else { this->_clear_flag(CARRY_FLAG); }

    this->_HL.raw += r->raw;
    this->cycles += MACHINE_CYCLE*2;
}

/*
INC rr
    - OpCode = 0b00xx0011
    - the data in the 16-bit register rr is incremented by 1
*/
void CPU::_inc_rr() {
    uint8_t opcode = this->_read_and_increment_PC();
    Reg* r = this->_get_16_bit_reg( (opcode >> 4) & 0b11 );
    r->raw += 1;

    this->cycles += MACHINE_CYCLE*2;
}

/*
DEC rr
    - OpCode = 0b00xx1011
    - the data in the 16-bit register rr is decremented by 1
*/
void CPU::_dec_rr() {
    uint8_t opcode = this->_read_and_increment_PC();
    Reg* r = this->_get_16_bit_reg( (opcode >> 4) & 0b11 );
    r->raw -= 1;

    this->cycles += MACHINE_CYCLE*2;
}

/*
ADD SP, dd
    - OpCode = 0b11101000
    - the 8-bit immediate operand dd is added to the stack pointer
    - flags: 00hc
*/
void CPU::_add_SP_dd() {
    this->_read_and_increment_PC();
    uint8_t dd = this->_read_and_increment_PC();

    this->_clear_flag(ZERO_FLAG);
    this->_clear_flag(SUB_FLAG);
    
    if (CHECK_8_BIT_HALF_CARRY(this->_SP.raw, dd)) { this->_set_flag(HALF_CARRY_FLAG); }
    else { this->_clear_flag(HALF_CARRY_FLAG); }
    
    if (CHECK_8_BIT_CARRY(this->_SP.raw, dd)) { this->_set_flag(CARRY_FLAG); }
    else { this->_clear_flag(CARRY_FLAG); }

    this->_SP.raw += dd;
    this->cycles += MACHINE_CYCLE*4;
}
///////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////
/* SINGLE BIT INSTRUCTIONS */

/*
BIT n, r
    - OpCode = 0b11001011 0b01nnnrrr
    - tests bit n of register r and sets the Z flag accordingly
    - flags: z01-
*/
void CPU::_bit_n_r() {
    this->_read_and_increment_PC();
    uint8_t arg = this->_read_and_increment_PC();

    uint8_t* r = this->_get_8_bit_reg(arg & 0b111);
    uint8_t n = (arg >> 3) & 0b111;

    if ( ((*r >> n) & 1) == 0 ) { this->_set_flag(ZERO_FLAG); }
    else { this->_clear_flag(ZERO_FLAG); }

    this->_clear_flag(SUB_FLAG);
    this->_set_flag(HALF_CARRY_FLAG);

    this->cycles += MACHINE_CYCLE*2;
}

/*
BIT n, HL
    - OpCode = 0b11001011 0b01nnnrrr
    - tests bit n of register r and sets the Z flag accordingly
    - flags: z01-
*/

///////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////
/* ROTATE AND SHIFT INSTRUCTIONS */

/*
RLCA:  
    - OpCode = 0b00000111
    - rotate the A register left and store the 7th bit in the Carry Flag
    - flags: 000c
*/
void CPU::_rlca() {
    this->_read_and_increment_PC();

    uint8_t temp = this->_AF.bytes[1];
    this->_AF.bytes[1] = (temp << 1) & 0xff;
    this->_AF.bytes[1] |= (temp >> 7) & 1;

    this->_clear_flag(ZERO_FLAG);
    this->_clear_flag(SUB_FLAG);
    this->_clear_flag(HALF_CARRY_FLAG);

    if ((temp >> 7) & 1) { this->_set_flag(CARRY_FLAG); }
    else { this->_clear_flag(CARRY_FLAG); }

    this->cycles += MACHINE_CYCLE;
}

/*
RLA:  
    - OpCode = 0b00010111
    - rotate the A register, carry flag is copied to 0th bit, C is the 7th bit before rotate
    - flags: 000c
*/
void CPU::_rla() {
    this->_read_and_increment_PC();

    uint8_t temp = this->_AF.bytes[1];
    this->_AF.bytes[1] = (temp << 1) & 0xff;
    this->_AF.bytes[1] |= this->_get_flag(CARRY_FLAG) & 1;

    this->_clear_flag(ZERO_FLAG);
    this->_clear_flag(SUB_FLAG);
    this->_clear_flag(HALF_CARRY_FLAG);

    if ((temp >> 7) & 1) { this->_set_flag(CARRY_FLAG); }
    else { this->_clear_flag(CARRY_FLAG); }

    this->cycles += MACHINE_CYCLE;
}

/*
RRCA:  
    - OpCode = 0b00001111
    - rotate the A register right and store the 0th bit in the Carry Flag
    - flags: 000c
*/
void CPU::_rrca() {
    this->_read_and_increment_PC();

    uint8_t temp = this->_AF.bytes[1];
    this->_AF.bytes[1] = (temp >> 1) & 0xff;
    this->_AF.bytes[1] |= (temp & 1) << 7;

    this->_clear_flag(ZERO_FLAG);
    this->_clear_flag(SUB_FLAG);
    this->_clear_flag(HALF_CARRY_FLAG);

    if (temp & 1) { this->_set_flag(CARRY_FLAG); }
    else { this->_clear_flag(CARRY_FLAG); }

    this->cycles += MACHINE_CYCLE;
}

/*
RRA:  
    - OpCode = 0b00011111
    - rotate the A register, carry flag is copied to 0th bit, C is the 7th bit before rotate
    - flags: 000c
*/
void CPU::_rra() {
    this->_read_and_increment_PC();

    uint8_t temp = this->_AF.bytes[1];
    this->_AF.bytes[1] = (temp >> 1) & 0xff;
    this->_AF.bytes[1] |= (this->_get_flag(CARRY_FLAG) & 1) << 7;

    this->_clear_flag(ZERO_FLAG);
    this->_clear_flag(SUB_FLAG);
    this->_clear_flag(HALF_CARRY_FLAG);

    if (temp & 1) { this->_set_flag(CARRY_FLAG); }
    else { this->_clear_flag(CARRY_FLAG); }

    this->cycles += MACHINE_CYCLE;
}

///////////////////////////////////////////////////////////////////////////////////////////