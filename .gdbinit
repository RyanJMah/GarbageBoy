source ~/.gdbinit

file build/garbageboy
set args --rom_path ./tests/gb-test-roms/cpu_instrs/individual/02-interrupts.gb
b main

define hook-stop
    printf "\n"
    printf "AF = %x\n", this->_AF.raw
    printf "BC = %x\n", this->_BC.raw
    printf "DE = %x\n", this->_DE.raw
    printf "HL = %x\n", this->_HL.raw
    printf "SP = %x\n", this->_SP.raw
    printf "PC = %x\n", this->_PC.raw
    printf "IME = %x\n", this->IME
    printf "is_halted = %x\n", this->is_halted
    # printf "current_opcode = %x\n", curr_opcode
    printf "\n"
end

source ./breakpoints.gdb

r

