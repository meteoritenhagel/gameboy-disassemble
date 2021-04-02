#ifndef GAMEBOY_DISASSEMBLE_INSTRUCTIONS_ADD_H
#define GAMEBOY_DISASSEMBLE_INSTRUCTIONS_ADD_H

#include "baseinstruction.h"

class AddAAndImmediate : public BaseInstruction {
public:
    AddAAndImmediate(const byte immediate)
            : BaseInstruction("ADD A, " + to_string_hex_prefixed(immediate),
                              opcodes::ADD_A_AND_IMMEDIATE,
                              Bytestring{immediate}),
              _immediate(immediate) {}

private:
    const byte _immediate;
};

class AddWithCarryAAndImmediate : public BaseInstruction {
public:
    AddWithCarryAAndImmediate(const byte immediate)
            : BaseInstruction("ADC A, " + to_string_hex_prefixed(immediate),
                              opcodes::ADD_WITH_CARRY_A_AND_IMMEDIATE,
                              Bytestring{immediate}),
              _immediate(immediate) {}

private:
    const byte _immediate;
};

class AddAAnd8BitRegister : public BaseInstruction {
public:
    AddAAnd8BitRegister(const Register8Bit source)
            : BaseInstruction("ADD A, " + to_string(source),
                              determine_opcode(source)),
              _source(source) {}

private:
    Opcode determine_opcode(const Register8Bit source) const {
        switch (source) {
            case Register8Bit::B:          return opcodes::ADD_A_AND_B;
            case Register8Bit::C:          return opcodes::ADD_A_AND_C;
            case Register8Bit::D:          return opcodes::ADD_A_AND_D;
            case Register8Bit::E:          return opcodes::ADD_A_AND_E;
            case Register8Bit::H:          return opcodes::ADD_A_AND_H;
            case Register8Bit::L:          return opcodes::ADD_A_AND_L;
            case Register8Bit::ADDRESS_HL: return opcodes::ADD_A_AND_ADDRESS_HL;
            case Register8Bit::A:          return opcodes::ADD_A_AND_A;
            default:                       return opcodes::INVALID_OPCODE;
        }
    }

    const Register8Bit _source;
};

class AddWithCarryAAnd8BitRegister : public BaseInstruction {
public:
    AddWithCarryAAnd8BitRegister(const Register8Bit source)
            : BaseInstruction("ADC A, " + to_string(source),
                              determine_opcode(source)),
              _source(source) {}

private:
    Opcode determine_opcode(const Register8Bit source) const {
        switch (source) {
            case Register8Bit::B:          return opcodes::ADD_WITH_CARRY_A_AND_B;
            case Register8Bit::C:          return opcodes::ADD_WITH_CARRY_A_AND_C;
            case Register8Bit::D:          return opcodes::ADD_WITH_CARRY_A_AND_D;
            case Register8Bit::E:          return opcodes::ADD_WITH_CARRY_A_AND_E;
            case Register8Bit::H:          return opcodes::ADD_WITH_CARRY_A_AND_H;
            case Register8Bit::L:          return opcodes::ADD_WITH_CARRY_A_AND_L;
            case Register8Bit::ADDRESS_HL: return opcodes::ADD_WITH_CARRY_A_AND_ADDRESS_HL;
            case Register8Bit::A:          return opcodes::ADD_WITH_CARRY_A_AND_A;
            default:                       return opcodes::INVALID_OPCODE;
        }
    }

    const Register8Bit _source;
};

class AddHLAnd16BitRegister : public BaseInstruction {
public:
    AddHLAnd16BitRegister(const Register16Bit source)
            : BaseInstruction("ADD HL, " + to_string(source),
                              determine_opcode(source)),
              _source(source) {}

private:
    Opcode determine_opcode(const Register16Bit source) const {
        switch(source) {
            case Register16Bit::BC: return opcodes::ADD_HL_AND_BC;
            case Register16Bit::DE: return opcodes::ADD_HL_AND_DE;
            case Register16Bit::HL: return opcodes::ADD_HL_AND_HL;
            case Register16Bit::SP: return opcodes::ADD_HL_AND_SP;
            default:                return opcodes::INVALID_OPCODE;
        }
    }
    const Register16Bit _source;
};

class AddSPAndImmediate : public BaseInstruction {
public:
    AddSPAndImmediate(const byte immediate)
            : BaseInstruction("ADD SP, " + to_string_hex_signed_prefixed(immediate, 2),
                              opcodes::ADD_SP_AND_IMMEDIATE,
                              Bytestring{immediate}),
              _immediate(immediate) {}

private:
    const byte _immediate;
};

#endif //GAMEBOY_DISASSEMBLE_INSTRUCTIONS_ADD_H
