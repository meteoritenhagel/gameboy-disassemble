#ifndef GAMEBOY_DISASSEMBLE_INSTRUCTIONS_INCREMENT_DECREMENT_H
#define GAMEBOY_DISASSEMBLE_INSTRUCTIONS_INCREMENT_DECREMENT_H

#include "interface.h"

/**********************************************************+
 * Helper classes ******************************************
 ***********************************************************/

// 8 Bit Registers
class InstructionIncrement8BitRegister : public Instruction {
protected:
    InstructionIncrement8BitRegister(const Register8Bit reg,
                                     const Opcode opc)
            : Instruction("INC " + to_string(reg),
                          opc),
              _register(reg) {}

private:
    const Register8Bit _register;
};

class InstructionDecrement8BitRegister : public Instruction {
protected:
    InstructionDecrement8BitRegister(const Register8Bit reg,
                                     const Opcode opc)
            : Instruction("DEC " + to_string(reg),
                          opc),
              _register(reg) {}

private:
    const Register8Bit _register;
};

class InstructionIncrement16BitRegister : public Instruction {
protected:
    InstructionIncrement16BitRegister(const Register16Bit reg,
                                      const Opcode opc)
            : Instruction("INC " + to_string(reg),
                          opc),
              _register(reg) {}

private:
    const Register16Bit _register;
};

class InstructionDecrement16BitRegister : public Instruction {
protected:
    InstructionDecrement16BitRegister(const Register16Bit reg,
                                      const Opcode opc)
            : Instruction("DEC " + to_string(reg),
                          opc),
              _register(reg) {}

private:
    const Register16Bit _register;
};

/**********************************************************+
 * Public interface ****************************************
 ***********************************************************/

// Increment 8 bit register

class IncrementB : public InstructionIncrement8BitRegister {
public:
    IncrementB()
            : InstructionIncrement8BitRegister(Register8Bit::B,
                                               opcodes::INCREMENT_B) {}
};

class IncrementC : public InstructionIncrement8BitRegister {
public:
    IncrementC()
            : InstructionIncrement8BitRegister(Register8Bit::C,
                                               opcodes::INCREMENT_C) {}
};

class IncrementD : public InstructionIncrement8BitRegister {
public:
    IncrementD()
            : InstructionIncrement8BitRegister(Register8Bit::D,
                                               opcodes::INCREMENT_D) {}
};

class IncrementE : public InstructionIncrement8BitRegister {
public:
    IncrementE()
            : InstructionIncrement8BitRegister(Register8Bit::E,
                                               opcodes::INCREMENT_E) {}
};

class IncrementH : public InstructionIncrement8BitRegister {
public:
    IncrementH()
            : InstructionIncrement8BitRegister(Register8Bit::H,
                                               opcodes::INCREMENT_H) {}
};

class IncrementL : public InstructionIncrement8BitRegister {
public:
    IncrementL()
            : InstructionIncrement8BitRegister(Register8Bit::L,
                                               opcodes::INCREMENT_L) {}
};

class IncrementAddressHL : public InstructionIncrement8BitRegister {
public:
    IncrementAddressHL()
            : InstructionIncrement8BitRegister(Register8Bit::ADDRESS_HL,
                                               opcodes::INCREMENT_ADDRESS_HL) {}
};

class IncrementA : public InstructionIncrement8BitRegister {
public:
    IncrementA()
            : InstructionIncrement8BitRegister(Register8Bit::A,
                                               opcodes::INCREMENT_A) {}
};

// Decrement 8 bit register
class DecrementB : public InstructionDecrement8BitRegister {
public:
    DecrementB()
            : InstructionDecrement8BitRegister(Register8Bit::B,
                                               opcodes::DECREMENT_B) {}
};

class DecrementC : public InstructionDecrement8BitRegister {
public:
    DecrementC()
            : InstructionDecrement8BitRegister(Register8Bit::C,
                                               opcodes::DECREMENT_C) {}
};

class DecrementD : public InstructionDecrement8BitRegister {
public:
    DecrementD()
            : InstructionDecrement8BitRegister(Register8Bit::D,
                                               opcodes::DECREMENT_D) {}
};

class DecrementE : public InstructionDecrement8BitRegister {
public:
    DecrementE()
            : InstructionDecrement8BitRegister(Register8Bit::E,
                                               opcodes::DECREMENT_E) {}
};

class DecrementH : public InstructionDecrement8BitRegister {
public:
    DecrementH()
            : InstructionDecrement8BitRegister(Register8Bit::H,
                                               opcodes::DECREMENT_H) {}
};

class DecrementL : public InstructionDecrement8BitRegister {
public:
    DecrementL()
            : InstructionDecrement8BitRegister(Register8Bit::L,
                                               opcodes::DECREMENT_L) {}
};

class DecrementAddressHL : public InstructionDecrement8BitRegister {
public:
    DecrementAddressHL()
            : InstructionDecrement8BitRegister(Register8Bit::ADDRESS_HL,
                                               opcodes::DECREMENT_ADDRESS_HL) {}
};

class DecrementA : public InstructionDecrement8BitRegister {
public:
    DecrementA()
            : InstructionDecrement8BitRegister(Register8Bit::A,
                                               opcodes::DECREMENT_A) {}
};

// increment 16 Bit Registers
class IncrementBC : public InstructionIncrement16BitRegister {
public:
    IncrementBC()
            : InstructionIncrement16BitRegister(Register16Bit::BC,
                                                opcodes::INCREMENT_BC) {}
};

class IncrementDE : public InstructionIncrement16BitRegister {
public:
    IncrementDE()
            : InstructionIncrement16BitRegister(Register16Bit::DE,
                                                opcodes::INCREMENT_DE) {}
};

class IncrementHL : public InstructionIncrement16BitRegister {
public:
    IncrementHL()
            : InstructionIncrement16BitRegister(Register16Bit::HL,
                                                opcodes::INCREMENT_HL) {}
};

class IncrementSP : public InstructionIncrement16BitRegister {
public:
    IncrementSP()
            : InstructionIncrement16BitRegister(Register16Bit::SP,
                                                opcodes::INCREMENT_SP) {}
};

// decrement 16 Bit Registers
class DecrementBC : public InstructionDecrement16BitRegister {
public:
    DecrementBC()
            : InstructionDecrement16BitRegister(Register16Bit::BC,
                                                opcodes::DECREMENT_BC) {}
};

class DecrementDE : public InstructionDecrement16BitRegister {
public:
    DecrementDE()
            : InstructionDecrement16BitRegister(Register16Bit::DE,
                                                opcodes::DECREMENT_DE) {}
};

class DecrementHL : public InstructionDecrement16BitRegister {
public:
    DecrementHL()
            : InstructionDecrement16BitRegister(Register16Bit::HL,
                                                opcodes::DECREMENT_HL) {}
};

class DecrementSP : public InstructionDecrement16BitRegister {
public:
    DecrementSP()
            : InstructionDecrement16BitRegister(Register16Bit::SP,
                                                opcodes::DECREMENT_SP) {}
};

#endif //GAMEBOY_DISASSEMBLE_INSTRUCTIONS_INCREMENT_DECREMENT_H
