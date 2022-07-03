#pragma once

#include "cpu.hpp"

#define VBLANK_ISR_ADDR         0x0040U
#define LCD_STAT_ISR_ADDR       0x0048U
#define TIMER_ISR_ADDR          0x0050U
#define SERIAL_ISR_ADDR         0x0058U
#define JOYPAD_ISR_ADDR         0x0060U

#define IE_VBLANK               0
#define IE_LCD_STAT             1
#define IE_TIMER                2
#define IE_SERIAL               3
#define IE_JOYPAD               4

#define IF_VBLANK               0
#define IF_LCD_STAT             1
#define IF_TIMER                2
#define IF_SERIAL               3
#define IF_JOYPAD               4

#define SC_SHIFT_CLOCK          0
#define SC_CLOCK_SPEED          1
#define SC_TRANSFER_START       7

class CPU;

class AbstractPeripheral {
    public:
        void init(CPU* cpu_ptr);
        virtual ~AbstractPeripheral() = 0;

        virtual void respond() = 0;

    protected:
        CPU* _cpu;

    protected:
        /*
        I'm really tempted to abuse the preprocessor here:

        e.x.,
            #define IE (this->_cpu->_mem_get(0xffffU))

        This would be SO nice to use, but alas, I will contain myself.

        Sidenote: Python's @property is exactly what I want here,
                  but C++... so this is the best I can do :(
        
        There is a good case that these guys should belong in their
        derieved classes, but there are cases where for example,
        the Serial class needs to set a bit in the InterruptController class,
        so this type of scope is needed sadly.
        */

        ///////////////////////////////////////////////////////////////////////////////////
        /* INTERRUPT REGISTERS AND FLAGS */
        bool* IME();
        uint8_t* IE();
        uint8_t* IF();
        ///////////////////////////////////////////////////////////////////////////////////

        ///////////////////////////////////////////////////////////////////////////////////
        /* TIMER REGISTERS */
        uint8_t* DIV();
        uint8_t* TIMA();
        uint8_t* TMA();
        uint8_t* TAC();
        ///////////////////////////////////////////////////////////////////////////////////

        ///////////////////////////////////////////////////////////////////////////////////
        /* SERIAL REGISTERS */
        uint8_t* SB();
        uint8_t* SC();
        ///////////////////////////////////////////////////////////////////////////////////
};

