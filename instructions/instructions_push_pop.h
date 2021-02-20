#ifndef GAMEBOY_DISASSEMBLE_INSTRUCTIONS_PUSH_POP_H
#define GAMEBOY_DISASSEMBLE_INSTRUCTIONS_PUSH_POP_H

#include "instructions_interface.h"

class InstructionPush16BitRegister : public Instruction {
protected:
    InstructionPush16BitRegister(const Register16Bit reg, const Opcode opc)
            : Instruction("PUSH " + to_string(reg), opc),
              _register(reg) {}

private:
    const Register16Bit _register;
};

class InstructionPop16BitRegister : public Instruction {
protected:
    InstructionPop16BitRegister(const Register16Bit reg, const Opcode opc)
            : Instruction("POP " + to_string(reg), opc),
              _register(reg) {}

private:
    const Register16Bit _register;
};




// child classes

// Push
class PushBC : public InstructionPush16BitRegister {
public:
    PushBC()
            : InstructionPush16BitRegister(Register16Bit::BC, opcodes::PUSH_BC) {}
};

class PushDE : public InstructionPush16BitRegister {
public:
    PushDE()
            : InstructionPush16BitRegister(Register16Bit::DE, opcodes::PUSH_DE) {}
};

class PushHL : public InstructionPush16BitRegister {
public:
    PushHL()
            : InstructionPush16BitRegister(Register16Bit::HL, opcodes::PUSH_HL) {}
};

class PushAF : public InstructionPush16BitRegister {
public:
    PushAF()
            : InstructionPush16BitRegister(Register16Bit::AF, opcodes::PUSH_AF) {}
};

// Pop
class PopBC : public InstructionPop16BitRegister {
public:
    PopBC()
            : InstructionPop16BitRegister(Register16Bit::BC, opcodes::POP_BC) {}
};

class PopDE : public InstructionPop16BitRegister {
public:
    PopDE()
            : InstructionPop16BitRegister(Register16Bit::DE, opcodes::POP_DE) {}
};

class PopHL : public InstructionPop16BitRegister {
public:
    PopHL()
            : InstructionPop16BitRegister(Register16Bit::HL, opcodes::POP_HL) {}
};

class PopAF : public InstructionPop16BitRegister {
public:
    PopAF()
            : InstructionPop16BitRegister(Register16Bit::AF, opcodes::POP_AF) {}
};

#endif //GAMEBOY_DISASSEMBLE_INSTRUCTIONS_PUSH_POP_H
