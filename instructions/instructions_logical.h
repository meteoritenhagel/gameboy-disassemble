#ifndef GAMEBOY_DISASSEMBLE_INSTRUCTIONS_LOGICAL_H
#define GAMEBOY_DISASSEMBLE_INSTRUCTIONS_LOGICAL_H

#include "interface.h"

class AndAAnd8BitRegister : public Instruction {
public:
    AndAAnd8BitRegister(const Register8Bit source)
            : Instruction("AND A, " + to_string(source),
                          determine_opcode(source)),
              _source(source) {}

private:
    Opcode determine_opcode(const Register8Bit source) const {
        switch (source) {
            case Register8Bit::B:          return opcodes::AND_A_AND_B;
            case Register8Bit::C:          return opcodes::AND_A_AND_C;
            case Register8Bit::D:          return opcodes::AND_A_AND_D;
            case Register8Bit::E:          return opcodes::AND_A_AND_E;
            case Register8Bit::H:          return opcodes::AND_A_AND_H;
            case Register8Bit::L:          return opcodes::AND_A_AND_L;
            case Register8Bit::ADDRESS_HL: return opcodes::AND_A_AND_ADDRESS_HL;
            case Register8Bit::A:          return opcodes::AND_A_AND_A;
            default:                       return opcodes::INVALID_OPCODE;
        }
    }

    const Register8Bit _source;
};

class OrAAnd8BitRegister : public Instruction {
public:
    OrAAnd8BitRegister(const Register8Bit source)
            : Instruction("OR A, " + to_string(source), determine_opcode(source)),
              _source(source) {}

private:
    Opcode determine_opcode(const Register8Bit source) const {
        switch (source) {
            case Register8Bit::B:          return opcodes::OR_A_AND_B;
            case Register8Bit::C:          return opcodes::OR_A_AND_C;
            case Register8Bit::D:          return opcodes::OR_A_AND_D;
            case Register8Bit::E:          return opcodes::OR_A_AND_E;
            case Register8Bit::H:          return opcodes::OR_A_AND_H;
            case Register8Bit::L:          return opcodes::OR_A_AND_L;
            case Register8Bit::ADDRESS_HL: return opcodes::OR_A_AND_ADDRESS_HL;
            case Register8Bit::A:          return opcodes::OR_A_AND_A;
            default:                       return opcodes::INVALID_OPCODE;
        }
    }

    const Register8Bit _source;
};

class XorAAnd8BitRegister : public Instruction {
public:
    XorAAnd8BitRegister(const Register8Bit source)
            : Instruction("XOR A, " + to_string(source),
                          determine_opcode(source)),
              _source(source) {}

private:
    Opcode determine_opcode(const Register8Bit source) const {
        switch (source) {
            case Register8Bit::B:          return opcodes::XOR_A_AND_B;
            case Register8Bit::C:          return opcodes::XOR_A_AND_C;
            case Register8Bit::D:          return opcodes::XOR_A_AND_D;
            case Register8Bit::E:          return opcodes::XOR_A_AND_E;
            case Register8Bit::H:          return opcodes::XOR_A_AND_H;
            case Register8Bit::L:          return opcodes::XOR_A_AND_L;
            case Register8Bit::ADDRESS_HL: return opcodes::XOR_A_AND_ADDRESS_HL;
            case Register8Bit::A:          return opcodes::XOR_A_AND_A;
            default:                       return opcodes::INVALID_OPCODE;
        }
    }

    const Register8Bit _source;
};

class CompareAAnd8BitRegister : public Instruction {
public:
    CompareAAnd8BitRegister(const Register8Bit source)
            : Instruction("CP A, " + to_string(source),
                          determine_opcode(source)),
              _source(source) {}

private:
    Opcode determine_opcode(const Register8Bit source) const {
        switch (source) {
            case Register8Bit::B:          return opcodes::COMPARE_A_AND_B;
            case Register8Bit::C:          return opcodes::COMPARE_A_AND_C;
            case Register8Bit::D:          return opcodes::COMPARE_A_AND_D;
            case Register8Bit::E:          return opcodes::COMPARE_A_AND_E;
            case Register8Bit::H:          return opcodes::COMPARE_A_AND_H;
            case Register8Bit::L:          return opcodes::COMPARE_A_AND_L;
            case Register8Bit::ADDRESS_HL: return opcodes::COMPARE_A_AND_ADDRESS_HL;
            case Register8Bit::A:          return opcodes::COMPARE_A_AND_A;
            default:                       return opcodes::INVALID_OPCODE;
        }
    }

    const Register8Bit _source;
};

class ComplementA : public Instruction {
public:
    ComplementA()
            : Instruction("CPL",
                          opcodes::COMPLEMENT_A) {}
};

class DecimalAdjustA : public Instruction {
public:
    DecimalAdjustA()
            : Instruction("DAA",
                          opcodes::DECIMAL_ADJUST_A) {}
};

class AndAAndImmediate : public Instruction {
public:
    AndAAndImmediate(const byte immediate)
            : Instruction("AND A, " + to_string_hex(immediate),
                          opcodes::AND_A_AND_IMMEDIATE),
              _immediate(immediate) {}

private:
    const byte _immediate;
};

class OrAAndImmediate : public Instruction {
public:
    OrAAndImmediate(const byte immediate)
            : Instruction("OR A, " + to_string_hex(immediate),
                          opcodes::OR_A_AND_IMMEDIATE),
              _immediate(immediate) {}

private:
    const byte _immediate;
};

class XorAAndImmediate : public Instruction {
public:
    XorAAndImmediate(const byte immediate)
            : Instruction("XOR A, " + to_string_hex(immediate),
                          opcodes::XOR_A_AND_IMMEDIATE),
              _immediate(immediate) {}

private:
    const byte _immediate;
};

class CompareAAndImmediate : public Instruction {
public:
    CompareAAndImmediate(const byte immediate)
            : Instruction("CP A, " + to_string_hex(immediate),
                          opcodes::COMPARE_A_AND_IMMEDIATE),
              _immediate(immediate) {}

private:
    const byte _immediate;
};
#endif //GAMEBOY_DISASSEMBLE_INSTRUCTIONS_LOGICAL_H
