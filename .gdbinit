source ~/.gdbinit

file build/main.elf
b main

b cpu.cpp:60

define hook-stop
    printf "\n"
    printf "AF = %x\n", this->_AF.raw
    printf "BC = %x\n", this->_BC.raw
    printf "DE = %x\n", this->_DE.raw
    printf "HL = %x\n", this->_HL.raw
    printf "SP = %x\n", this->_SP.raw
    printf "PC = %x\n", this->_PC.raw
    printf "is_halted = %x\n", this->_is_halted
    printf "current_opcode = %x\n", curr_opcode
    printf "\n"
end
