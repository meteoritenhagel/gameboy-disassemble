#ifndef GAMEBOY_DISASSEMBLE_INSTRUCTIONS_SUBTRACT_H
#define GAMEBOY_DISASSEMBLE_INSTRUCTIONS_SUBTRACT_H

#include "baseinstruction.h"

class SubtractAAnd8BitRegister : public BaseInstruction {
public:
    SubtractAAnd8BitRegister(const Register8Bit source = {})
            : BaseInstruction("SUB A, " + to_string(source),
                              determine_opcode(source)),
              _source(source) {}

private:
    Opcode determine_opcode(const Register8Bit reg) const {
        switch (reg) {
            case Register8Bit::B:          return opcodes::SUBTRACT_A_AND_B;
            case Register8Bit::C:          return opcodes::SUBTRACT_A_AND_C;
            case Register8Bit::D:          return opcodes::SUBTRACT_A_AND_D;
            case Register8Bit::E:          return opcodes::SUBTRACT_A_AND_E;
            case Register8Bit::H:          return opcodes::SUBTRACT_A_AND_H;
            case Register8Bit::L:          return opcodes::SUBTRACT_A_AND_L;
            case Register8Bit::ADDRESS_HL: return opcodes::SUBTRACT_A_AND_ADDRESS_HL;
            case Register8Bit::A:          return opcodes::SUBTRACT_A_AND_A;
            default:                       return opcodes::INVALID_OPCODE;
        }
    }

    const Register8Bit _source;
};

class SubtractWithCarryAAnd8BitRegister : public BaseInstruction {
public:
    SubtractWithCarryAAnd8BitRegister(const Register8Bit source = {})
            : BaseInstruction("SBC A, " + to_string(source),
                              determine_opcode(source)),
              _source(source) {}

private:
    Opcode determine_opcode(const Register8Bit reg) const {
        switch (reg) {
            case Register8Bit::B:          return opcodes::SUBTRACT_WITH_CARRY_A_AND_B;
            case Register8Bit::C:          return opcodes::SUBTRACT_WITH_CARRY_A_AND_C;
            case Register8Bit::D:          return opcodes::SUBTRACT_WITH_CARRY_A_AND_D;
            case Register8Bit::E:          return opcodes::SUBTRACT_WITH_CARRY_A_AND_E;
            case Register8Bit::H:          return opcodes::SUBTRACT_WITH_CARRY_A_AND_H;
            case Register8Bit::L:          return opcodes::SUBTRACT_WITH_CARRY_A_AND_L;
            case Register8Bit::ADDRESS_HL: return opcodes::SUBTRACT_WITH_CARRY_A_AND_ADDRESS_HL;
            case Register8Bit::A:          return opcodes::SUBTRACT_WITH_CARRY_A_AND_A;
            default:                       return opcodes::INVALID_OPCODE;
        }
    }

    const Register8Bit _source;
};

class SubtractAAndImmediate : public BaseInstruction {
public:
    SubtractAAndImmediate(const byte immediate = {})
            : BaseInstruction("SUB A, " + to_string_hex(immediate),
                              opcodes::SUBTRACT_A_AND_IMMEDIATE),
              _immediate(immediate) {}

private:
    const byte _immediate;
};

class SubtractWithCarryAAndImmediate : public BaseInstruction {
public:
    SubtractWithCarryAAndImmediate(const byte immediate = {})
            : BaseInstruction("SBC A, " + to_string_hex(immediate),
                              opcodes::SUBTRACT_WITH_CARRY_A_AND_IMMEDIATE),
              _immediate(immediate) {}

private:
    const byte _immediate;
};

#endif //GAMEBOY_DISASSEMBLE_INSTRUCTIONS_SUBTRACT_H
