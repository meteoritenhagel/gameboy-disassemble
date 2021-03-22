//
// Created by tristan on 18.02.21.
//

#ifndef GAMEBOY_DISASSEMBLE_INSTRUCTIONS_ADD_H
#define GAMEBOY_DISASSEMBLE_INSTRUCTIONS_ADD_H

#include "interface.h"

/**********************************************************+
 * Helper classes ******************************************
 ***********************************************************/

class InstructionAddAAnd8BitRegister : public Instruction {
protected:
    InstructionAddAAnd8BitRegister(const Register8Bit source,
                                   const Opcode opc)
            : Instruction("ADD A, " + to_string(source),
                          opc),
              _source(source) {}

private:
    const Register8Bit _source;
};

class InstructionAddWithCarryAAnd8BitRegister : public Instruction {
protected:
    InstructionAddWithCarryAAnd8BitRegister(const Register8Bit source,
                                            const Opcode opc)
            : Instruction("ADC A, " + to_string(source),
                          opc),
              _source(source) {}

private:
    const Register8Bit _source;
};

class InstructionAdd16BitRegisterAnd16BitRegister : public Instruction {
protected:
    InstructionAdd16BitRegisterAnd16BitRegister(const Register16Bit destination,
                                                const Register16Bit source,
                                                const Opcode opc)
            : Instruction("ADD " + to_string(destination) + ", " + to_string(source),
                          opc),
              _destination(destination),
              _source(source) {}

private:
    const Register16Bit _destination;
    const Register16Bit _source;
};

/**********************************************************+
 * Public interface ****************************************
 ***********************************************************/

class AddAAndImmediate : public Instruction {
public:
    AddAAndImmediate(const byte immediate)
            : Instruction("ADD A, " + to_string_hex_prefixed(immediate),
                          opcodes::ADD_A_AND_IMMEDIATE),
              _immediate(immediate) {}

private:
    const byte _immediate;
};

class AddWithCarryAAndImmediate : public Instruction {
public:
    AddWithCarryAAndImmediate(const byte immediate)
            : Instruction("ADC A, " + to_string_hex_prefixed(immediate),
                          opcodes::ADD_WITH_CARRY_A_AND_IMMEDIATE),
              _immediate(immediate) {}

private:
    const byte _immediate;
};

class AddSPAndImmediate : public Instruction {
public:
    AddSPAndImmediate(const word immediate)
            : Instruction("ADD SP, " + to_string_hex_signed_prefixed(immediate),
                          opcodes::ADD_SP_AND_IMMEDIATE),
              _immediate(immediate) {}

private:
    const byte _immediate;
};

/** Doubly derived classes ***********************************/

// Add 8 bit registers
class AddAAndB : public InstructionAddAAnd8BitRegister {
public:
    AddAAndB()
            : InstructionAddAAnd8BitRegister(Register8Bit::B,
                                             opcodes::ADD_A_AND_B) {}
};

class AddAAndC : public InstructionAddAAnd8BitRegister {
public:
    AddAAndC()
            : InstructionAddAAnd8BitRegister(Register8Bit::C,
                                             opcodes::ADD_A_AND_C) {}
};

class AddAAndD : public InstructionAddAAnd8BitRegister {
public:
    AddAAndD()
            : InstructionAddAAnd8BitRegister(Register8Bit::D,
                                             opcodes::ADD_A_AND_D) {}
};

class AddAAndE : public InstructionAddAAnd8BitRegister {
public:
    AddAAndE()
            : InstructionAddAAnd8BitRegister(Register8Bit::E,
                                             opcodes::ADD_A_AND_E) {}
};

class AddAAndH : public InstructionAddAAnd8BitRegister {
public:
    AddAAndH()
            : InstructionAddAAnd8BitRegister(Register8Bit::H,
                                             opcodes::ADD_A_AND_H) {}
};

class AddAAndL : public InstructionAddAAnd8BitRegister {
public:
    AddAAndL()
            : InstructionAddAAnd8BitRegister(Register8Bit::L,
                                             opcodes::ADD_A_AND_L) {}
};

class AddAAndAddressHL : public InstructionAddAAnd8BitRegister {
public:
    AddAAndAddressHL()
            : InstructionAddAAnd8BitRegister(Register8Bit::ADDRESS_HL,
                                             opcodes::ADD_A_AND_ADDRESS_HL) {}
};

class AddAAndA : public InstructionAddAAnd8BitRegister {
public:
    AddAAndA()
            : InstructionAddAAnd8BitRegister(Register8Bit::A,
                                             opcodes::ADD_A_AND_A) {}
};

// Add with carry 8 bit registers

class AddWithCarryAAndB : public InstructionAddWithCarryAAnd8BitRegister {
public:
    AddWithCarryAAndB()
            : InstructionAddWithCarryAAnd8BitRegister(Register8Bit::B,
                                                      opcodes::ADD_WITH_CARRY_A_AND_B) {}
};

class AddWithCarryAAndC : public InstructionAddWithCarryAAnd8BitRegister {
public:
    AddWithCarryAAndC()
            : InstructionAddWithCarryAAnd8BitRegister(Register8Bit::C,
                                                      opcodes::ADD_WITH_CARRY_A_AND_C) {}
};

class AddWithCarryAAndD : public InstructionAddWithCarryAAnd8BitRegister {
public:
    AddWithCarryAAndD()
            : InstructionAddWithCarryAAnd8BitRegister(Register8Bit::D,
                                                      opcodes::ADD_WITH_CARRY_A_AND_D) {}
};

class AddWithCarryAAndE : public InstructionAddWithCarryAAnd8BitRegister {
public:
    AddWithCarryAAndE()
            : InstructionAddWithCarryAAnd8BitRegister(Register8Bit::E,
                                                      opcodes::ADD_WITH_CARRY_A_AND_E) {}
};

class AddWithCarryAAndH : public InstructionAddWithCarryAAnd8BitRegister {
public:
    AddWithCarryAAndH()
            : InstructionAddWithCarryAAnd8BitRegister(Register8Bit::H,
                                                      opcodes::ADD_WITH_CARRY_A_AND_H) {}
};

class AddWithCarryAAndL : public InstructionAddWithCarryAAnd8BitRegister {
public:
    AddWithCarryAAndL()
            : InstructionAddWithCarryAAnd8BitRegister(Register8Bit::L,
                                                      opcodes::ADD_WITH_CARRY_A_AND_L) {}
};

class AddWithCarryAAndAddressHL : public InstructionAddWithCarryAAnd8BitRegister {
public:
    AddWithCarryAAndAddressHL()
            : InstructionAddWithCarryAAnd8BitRegister(Register8Bit::ADDRESS_HL,
                                                      opcodes::ADD_WITH_CARRY_A_AND_ADDRESS_HL) {}
};

class AddWithCarryAAndA : public InstructionAddWithCarryAAnd8BitRegister {
public:
    AddWithCarryAAndA()
            : InstructionAddWithCarryAAnd8BitRegister(Register8Bit::A,
                                                      opcodes::ADD_WITH_CARRY_A_AND_A) {}
};


// Add 16 bit registers
class AddHLAndBC : public InstructionAdd16BitRegisterAnd16BitRegister {
public:
    AddHLAndBC()
            : InstructionAdd16BitRegisterAnd16BitRegister(Register16Bit::HL,
                                                          Register16Bit::BC,
                                                          opcodes::ADD_HL_AND_BC) {}
};

class AddHLAndDE : public InstructionAdd16BitRegisterAnd16BitRegister {
public:
    AddHLAndDE()
            : InstructionAdd16BitRegisterAnd16BitRegister(Register16Bit::HL,
                                                          Register16Bit::DE,
                                                          opcodes::ADD_HL_AND_DE) {}
};

class AddHLAndHL : public InstructionAdd16BitRegisterAnd16BitRegister {
public:
    AddHLAndHL()
            : InstructionAdd16BitRegisterAnd16BitRegister(Register16Bit::HL,
                                                          Register16Bit::HL,
                                                          opcodes::ADD_HL_AND_HL) {}
};

class AddHLAndSP : public InstructionAdd16BitRegisterAnd16BitRegister {
public:
    AddHLAndSP()
            : InstructionAdd16BitRegisterAnd16BitRegister(Register16Bit::HL,
                                                          Register16Bit::SP,
                                                          opcodes::ADD_HL_AND_SP) {}
};

#endif //GAMEBOY_DISASSEMBLE_INSTRUCTIONS_ADD_H
