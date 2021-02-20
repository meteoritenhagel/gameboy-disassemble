#ifndef GAMEBOY_DISASSEMBLE_INSTRUCTIONS_LOGICAL_H
#define GAMEBOY_DISASSEMBLE_INSTRUCTIONS_LOGICAL_H

#include "instructions_interface.h"

class InstructionAndAAnd8BitRegister : public Instruction {
protected:
    InstructionAndAAnd8BitRegister(const Register8Bit source,
                                   const Opcode opc)
            : Instruction("AND A, " + to_string(source),
                          opc),
              _source(source) {}

private:
    const Register8Bit _source;
};

class InstructionOrAAnd8BitRegister : public Instruction {
protected:
    InstructionOrAAnd8BitRegister(const Register8Bit source,
                                  const Opcode opc)
            : Instruction("OR A, " + to_string(source),
                          opc),
              _source(source) {}

private:
    const Register8Bit _source;
};

class InstructionXorAAnd8BitRegister : public Instruction {
protected:
    InstructionXorAAnd8BitRegister(const Register8Bit source,
                                   const Opcode opc)
            : Instruction("XOR A, " + to_string(source),
                          opc),
              _source(source) {}

private:
    const Register8Bit _source;
};

class InstructionCompareAAnd8BitRegister : public Instruction {
protected:
    InstructionCompareAAnd8BitRegister(const Register8Bit source,
                                       const Opcode opc)
            : Instruction("CP A, " + to_string(source),
                          opc),
              _source(source) {}

private:
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




// child classes

// And 8 bit registers
class AndAAndB : public InstructionAndAAnd8BitRegister {
public:
    AndAAndB()
            : InstructionAndAAnd8BitRegister(Register8Bit::B,
                                             opcodes::AND_A_AND_B) {}
};

class AndAAndC : public InstructionAndAAnd8BitRegister {
public:
    AndAAndC()
            : InstructionAndAAnd8BitRegister(Register8Bit::C,
                                             opcodes::AND_A_AND_C) {}
};

class AndAAndD : public InstructionAndAAnd8BitRegister {
public:
    AndAAndD()
            : InstructionAndAAnd8BitRegister(Register8Bit::D,
                                             opcodes::AND_A_AND_D) {}
};

class AndAAndE : public InstructionAndAAnd8BitRegister {
public:
    AndAAndE()
            : InstructionAndAAnd8BitRegister(Register8Bit::E,
                                             opcodes::AND_A_AND_E) {}
};

class AndAAndH : public InstructionAndAAnd8BitRegister {
public:
    AndAAndH()
            : InstructionAndAAnd8BitRegister(Register8Bit::H,
                                             opcodes::AND_A_AND_H) {}
};

class AndAAndL : public InstructionAndAAnd8BitRegister {
public:
    AndAAndL()
            : InstructionAndAAnd8BitRegister(Register8Bit::L,
                                             opcodes::AND_A_AND_L) {}
};

class AndAAndAddressHL : public InstructionAndAAnd8BitRegister {
public:
    AndAAndAddressHL()
            : InstructionAndAAnd8BitRegister(Register8Bit::ADDRESS_HL,
                                             opcodes::AND_A_AND_ADDRESS_HL) {}
};

class AndAAndA : public InstructionAndAAnd8BitRegister {
public:
    AndAAndA()
            : InstructionAndAAnd8BitRegister(Register8Bit::A,
                                             opcodes::AND_A_AND_A) {}
};


// Or 8 bit registers
class OrAAndB : public InstructionOrAAnd8BitRegister {
public:
    OrAAndB()
            : InstructionOrAAnd8BitRegister(Register8Bit::B,
                                            opcodes::OR_A_AND_B) {}
};

class OrAAndC : public InstructionOrAAnd8BitRegister {
public:
    OrAAndC()
            : InstructionOrAAnd8BitRegister(Register8Bit::C,
                                            opcodes::OR_A_AND_C) {}
};

class OrAAndD : public InstructionOrAAnd8BitRegister {
public:
    OrAAndD()
            : InstructionOrAAnd8BitRegister(Register8Bit::D,
                                            opcodes::OR_A_AND_D) {}
};

class OrAAndE : public InstructionOrAAnd8BitRegister {
public:
    OrAAndE()
            : InstructionOrAAnd8BitRegister(Register8Bit::E,
                                            opcodes::OR_A_AND_E) {}
};

class OrAAndH : public InstructionOrAAnd8BitRegister {
public:
    OrAAndH()
            : InstructionOrAAnd8BitRegister(Register8Bit::H,
                                            opcodes::OR_A_AND_H) {}
};

class OrAAndL : public InstructionOrAAnd8BitRegister {
public:
    OrAAndL()
            : InstructionOrAAnd8BitRegister(Register8Bit::L,
                                            opcodes::OR_A_AND_L) {}
};

class OrAAndAddressHL : public InstructionOrAAnd8BitRegister {
public:
    OrAAndAddressHL()
            : InstructionOrAAnd8BitRegister(Register8Bit::ADDRESS_HL,
                                            opcodes::OR_A_AND_ADDRESS_HL) {}
};

class OrAAndA : public InstructionOrAAnd8BitRegister {
public:
    OrAAndA()
            : InstructionOrAAnd8BitRegister(Register8Bit::A,
                                            opcodes::OR_A_AND_A) {}
};

// Xor 8 bit registers
class XorAAndB : public InstructionXorAAnd8BitRegister {
public:
    XorAAndB()
            : InstructionXorAAnd8BitRegister(Register8Bit::B,
                                             opcodes::XOR_A_AND_B) {}
};

class XorAAndC : public InstructionXorAAnd8BitRegister {
public:
    XorAAndC()
            : InstructionXorAAnd8BitRegister(Register8Bit::C,
                                             opcodes::XOR_A_AND_C) {}
};

class XorAAndD : public InstructionXorAAnd8BitRegister {
public:
    XorAAndD()
            : InstructionXorAAnd8BitRegister(Register8Bit::D,
                                             opcodes::XOR_A_AND_D) {}
};

class XorAAndE : public InstructionXorAAnd8BitRegister {
public:
    XorAAndE()
            : InstructionXorAAnd8BitRegister(Register8Bit::E,
                                             opcodes::XOR_A_AND_E) {}
};

class XorAAndH : public InstructionXorAAnd8BitRegister {
public:
    XorAAndH()
            : InstructionXorAAnd8BitRegister(Register8Bit::H,
                                             opcodes::XOR_A_AND_H) {}
};

class XorAAndL : public InstructionXorAAnd8BitRegister {
public:
    XorAAndL()
            : InstructionXorAAnd8BitRegister(Register8Bit::L,
                                             opcodes::XOR_A_AND_L) {}
};

class XorAAndAddressHL : public InstructionXorAAnd8BitRegister {
public:
    XorAAndAddressHL()
            : InstructionXorAAnd8BitRegister(Register8Bit::ADDRESS_HL,
                                             opcodes::XOR_A_AND_ADDRESS_HL) {}
};

class XorAAndA : public InstructionXorAAnd8BitRegister {
public:
    XorAAndA()
            : InstructionXorAAnd8BitRegister(Register8Bit::A,
                                             opcodes::XOR_A_AND_A) {}
};

// Compare 8 bit registers
class CompareAAndB : public InstructionCompareAAnd8BitRegister {
public:
    CompareAAndB()
            : InstructionCompareAAnd8BitRegister(Register8Bit::B,
                                                 opcodes::COMPARE_A_AND_B) {}
};

class CompareAAndC : public InstructionCompareAAnd8BitRegister {
public:
    CompareAAndC()
            : InstructionCompareAAnd8BitRegister(Register8Bit::C,
                                                 opcodes::COMPARE_A_AND_C) {}
};

class CompareAAndD : public InstructionCompareAAnd8BitRegister {
public:
    CompareAAndD()
            : InstructionCompareAAnd8BitRegister(Register8Bit::D,
                                                 opcodes::COMPARE_A_AND_D) {}
};

class CompareAAndE : public InstructionCompareAAnd8BitRegister {
public:
    CompareAAndE()
            : InstructionCompareAAnd8BitRegister(Register8Bit::E,
                                                 opcodes::COMPARE_A_AND_E) {}
};

class CompareAAndH : public InstructionCompareAAnd8BitRegister {
public:
    CompareAAndH()
            : InstructionCompareAAnd8BitRegister(Register8Bit::H,
                                                 opcodes::COMPARE_A_AND_H) {}
};

class CompareAAndL : public InstructionCompareAAnd8BitRegister {
public:
    CompareAAndL()
            : InstructionCompareAAnd8BitRegister(Register8Bit::L,
                                                 opcodes::COMPARE_A_AND_L) {}
};

class CompareAAndAddressHL : public InstructionCompareAAnd8BitRegister {
public:
    CompareAAndAddressHL()
            : InstructionCompareAAnd8BitRegister(Register8Bit::ADDRESS_HL,
                                                 opcodes::COMPARE_A_AND_ADDRESS_HL) {}
};

class CompareAAndA : public InstructionCompareAAnd8BitRegister {
public:
    CompareAAndA()
            : InstructionCompareAAnd8BitRegister(Register8Bit::A,
                                                 opcodes::COMPARE_A_AND_A) {}
};


#endif //GAMEBOY_DISASSEMBLE_INSTRUCTIONS_LOGICAL_H
