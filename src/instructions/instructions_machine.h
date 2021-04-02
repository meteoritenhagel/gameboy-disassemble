#ifndef GAMEBOY_DISASSEMBLE_INSTRUCTIONS_MACHINE_H
#define GAMEBOY_DISASSEMBLE_INSTRUCTIONS_MACHINE_H

#include "baseinstruction.h"

class Nop : public BaseInstruction {
public:
    Nop()
            : BaseInstruction("NOP", opcodes::NOP) {}
};

class Stop : public BaseInstruction {
public:
    Stop()
            : BaseInstruction("STOP", opcodes::STOP) {}
};

class Halt : public BaseInstruction {
public:
    Halt()
            : BaseInstruction("HALT", opcodes::HALT) {}
};

class SetCarry : public BaseInstruction {
public:
    SetCarry()
            : BaseInstruction("SCF", opcodes::SET_CARRY) {}
};

class FlipCarry : public BaseInstruction {
public:
    FlipCarry()
            : BaseInstruction("CCF", opcodes::FLIP_CARRY) {}
};

class EnableInterrupts : public BaseInstruction {
public:
    EnableInterrupts()
            : BaseInstruction("EI", opcodes::ENABLE_INTERRUPTS) {}
};

class DisableInterrupts : public BaseInstruction {
public:
    DisableInterrupts()
            : BaseInstruction("DI", opcodes::DISABLE_INTERRUPTS) {}
};

#endif //GAMEBOY_DISASSEMBLE_INSTRUCTIONS_MACHINE_H
