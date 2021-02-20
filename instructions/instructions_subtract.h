#ifndef GAMEBOY_DISASSEMBLE_INSTRUCTIONS_SUBTRACT_H
#define GAMEBOY_DISASSEMBLE_INSTRUCTIONS_SUBTRACT_H

#include "instructions_interface.h"

class InstructionSubtractAAnd8BitRegister : public Instruction {
protected:
    InstructionSubtractAAnd8BitRegister(const Register8Bit source,
                                        const Opcode opc)
            : Instruction("SUB A, " + to_string(source),
                          opc),
              _source(source) {}

private:
    const Register8Bit _source;
};

class InstructionSubtractWithCarryAAnd8BitRegister : public Instruction {
protected:
    InstructionSubtractWithCarryAAnd8BitRegister(const Register8Bit source,
                                                 const Opcode opc)
            : Instruction("SBC A, " + to_string(source),
                          opc),
              _source(source) {}

private:
    const Register8Bit _source;
};

class SubtractAAndImmediate : public Instruction {
public:
    SubtractAAndImmediate(const byte immediate)
            : Instruction("SUB A, " + to_string_hex(immediate),
                          opcodes::SUBTRACT_A_AND_IMMEDIATE),
              _immediate(immediate) {}

private:
    const byte _immediate;
};

class SubtractWithCarryAAndImmediate : public Instruction {
public:
    SubtractWithCarryAAndImmediate(const byte immediate)
            : Instruction("SBC A, " + to_string_hex(immediate),
                          opcodes::SUBTRACT_WITH_CARRY_A_AND_IMMEDIATE),
              _immediate(immediate) {}

private:
    const byte _immediate;
};






// child classes

// Subtract 8 bit registers
class SubtractAAndB : public InstructionSubtractAAnd8BitRegister {
public:
    SubtractAAndB()
            : InstructionSubtractAAnd8BitRegister(Register8Bit::B,
                                                  opcodes::SUBTRACT_A_AND_B) {}
};

class SubtractAAndC : public InstructionSubtractAAnd8BitRegister {
public:
    SubtractAAndC()
            : InstructionSubtractAAnd8BitRegister(Register8Bit::C,
                                                  opcodes::SUBTRACT_A_AND_C) {}
};

class SubtractAAndD : public InstructionSubtractAAnd8BitRegister {
public:
    SubtractAAndD()
            : InstructionSubtractAAnd8BitRegister(Register8Bit::D,
                                                  opcodes::SUBTRACT_A_AND_D) {}
};

class SubtractAAndE : public InstructionSubtractAAnd8BitRegister {
public:
    SubtractAAndE()
            : InstructionSubtractAAnd8BitRegister(Register8Bit::E,
                                                  opcodes::SUBTRACT_A_AND_E) {}
};

class SubtractAAndH : public InstructionSubtractAAnd8BitRegister {
public:
    SubtractAAndH()
            : InstructionSubtractAAnd8BitRegister(Register8Bit::H,
                                                  opcodes::SUBTRACT_A_AND_H) {}
};

class SubtractAAndL : public InstructionSubtractAAnd8BitRegister {
public:
    SubtractAAndL()
            : InstructionSubtractAAnd8BitRegister(Register8Bit::L,
                                                  opcodes::SUBTRACT_A_AND_L) {}
};

class SubtractAAndAddressHL : public InstructionSubtractAAnd8BitRegister {
public:
    SubtractAAndAddressHL()
            : InstructionSubtractAAnd8BitRegister(Register8Bit::ADDRESS_HL,
                                                  opcodes::SUBTRACT_A_AND_ADDRESS_HL) {}
};

class SubtractAAndA : public InstructionSubtractAAnd8BitRegister {
public:
    SubtractAAndA()
            : InstructionSubtractAAnd8BitRegister(Register8Bit::A,
                                                  opcodes::SUBTRACT_A_AND_A) {}
};

// Subtract with carry 8 bit registers

class SubtractWithCarryAAndB : public InstructionSubtractWithCarryAAnd8BitRegister {
public:
    SubtractWithCarryAAndB()
            : InstructionSubtractWithCarryAAnd8BitRegister(Register8Bit::B,
                                                           opcodes::SUBTRACT_WITH_CARRY_A_AND_B) {}
};

class SubtractWithCarryAAndC : public InstructionSubtractWithCarryAAnd8BitRegister {
public:
    SubtractWithCarryAAndC()
            : InstructionSubtractWithCarryAAnd8BitRegister(Register8Bit::C,
                                                           opcodes::SUBTRACT_WITH_CARRY_A_AND_C) {}
};

class SubtractWithCarryAAndD : public InstructionSubtractWithCarryAAnd8BitRegister {
public:
    SubtractWithCarryAAndD()
            : InstructionSubtractWithCarryAAnd8BitRegister(Register8Bit::D,
                                                           opcodes::SUBTRACT_WITH_CARRY_A_AND_D) {}
};

class SubtractWithCarryAAndE : public InstructionSubtractWithCarryAAnd8BitRegister {
public:
    SubtractWithCarryAAndE()
            : InstructionSubtractWithCarryAAnd8BitRegister(Register8Bit::E,
                                                           opcodes::SUBTRACT_WITH_CARRY_A_AND_E) {}
};

class SubtractWithCarryAAndH : public InstructionSubtractWithCarryAAnd8BitRegister {
public:
    SubtractWithCarryAAndH()
            : InstructionSubtractWithCarryAAnd8BitRegister(Register8Bit::H,
                                                           opcodes::SUBTRACT_WITH_CARRY_A_AND_H) {}
};

class SubtractWithCarryAAndL : public InstructionSubtractWithCarryAAnd8BitRegister {
public:
    SubtractWithCarryAAndL()
            : InstructionSubtractWithCarryAAnd8BitRegister(Register8Bit::L,
                                                           opcodes::SUBTRACT_WITH_CARRY_A_AND_L) {}
};

class SubtractWithCarryAAndAddressHL : public InstructionSubtractWithCarryAAnd8BitRegister {
public:
    SubtractWithCarryAAndAddressHL()
            : InstructionSubtractWithCarryAAnd8BitRegister(Register8Bit::ADDRESS_HL,
                                                           opcodes::SUBTRACT_WITH_CARRY_A_AND_ADDRESS_HL) {}
};

class SubtractWithCarryAAndA : public InstructionSubtractWithCarryAAnd8BitRegister {
public:
    SubtractWithCarryAAndA()
            : InstructionSubtractWithCarryAAnd8BitRegister(Register8Bit::A,
                                                           opcodes::SUBTRACT_WITH_CARRY_A_AND_A) {}
};

#endif //GAMEBOY_DISASSEMBLE_INSTRUCTIONS_SUBTRACT_H
