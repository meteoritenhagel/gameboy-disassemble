#ifndef GAMEBOY_DISASSEMBLE_INSTRUCTIONS_PUSH_POP_H
#define GAMEBOY_DISASSEMBLE_INSTRUCTIONS_PUSH_POP_H

#include "interface.h"

class Push16BitRegister : public Instruction {
public:
    Push16BitRegister(const Register16Bit reg)
            : Instruction("PUSH " + to_string(reg), determine_opcode(reg)),
              _register(reg) {}

private:
    Opcode determine_opcode(const Register16Bit reg) {
        switch(reg) {
            case Register16Bit::AF: return opcodes::PUSH_AF;
            case Register16Bit::BC: return opcodes::PUSH_BC;
            case Register16Bit::DE: return opcodes::PUSH_DE;
            case Register16Bit::HL: return opcodes::PUSH_HL;
            default:                return opcodes::INVALID_OPCODE;
        }
    }

    const Register16Bit _register;
};

class Pop16BitRegister : public Instruction {
public:
    Pop16BitRegister(const Register16Bit reg)
            : Instruction("POP " + to_string(reg), determine_opcode(reg)),
              _register(reg) {}

private:
    Opcode determine_opcode(const Register16Bit reg) {
        switch(reg) {
            case Register16Bit::AF: return opcodes::POP_AF;
            case Register16Bit::BC: return opcodes::POP_BC;
            case Register16Bit::DE: return opcodes::POP_DE;
            case Register16Bit::HL: return opcodes::POP_HL;
            default:                return opcodes::INVALID_OPCODE;
        }
    }

    const Register16Bit _register;
};

#endif //GAMEBOY_DISASSEMBLE_INSTRUCTIONS_PUSH_POP_H
