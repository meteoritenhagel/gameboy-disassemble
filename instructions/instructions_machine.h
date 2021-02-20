#ifndef GAMEBOY_DISASSEMBLE_INSTRUCTIONS_MACHINE_H
#define GAMEBOY_DISASSEMBLE_INSTRUCTIONS_MACHINE_H

#include "instructions_interface.h"

class Nop : public Instruction {
public:
    Nop()
            : Instruction("NOP", opcodes::NOP) {}
};

class Stop : public Instruction {
public:
    Stop()
            : Instruction("STOP", opcodes::STOP) {}
};

class Halt : public Instruction {
public:
    Halt()
            : Instruction("HALT", opcodes::HALT) {}
};

class SetCarry : public Instruction {
public:
    SetCarry()
            : Instruction("SCF", opcodes::SET_CARRY) {}
};

class FlipCarry : public Instruction {
public:
    FlipCarry()
            : Instruction("CCF", opcodes::FLIP_CARRY) {}
};

class EnableInterrupts : public Instruction {
public:
    EnableInterrupts()
            : Instruction("EI", opcodes::ENABLE_INTERRUPTS) {}
};

class DisableInterrupts : public Instruction {
public:
    DisableInterrupts()
            : Instruction("DI", opcodes::DISABLE_INTERRUPTS) {}
};

#endif //GAMEBOY_DISASSEMBLE_INSTRUCTIONS_MACHINE_H
