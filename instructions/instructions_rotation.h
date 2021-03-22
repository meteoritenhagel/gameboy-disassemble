#ifndef GAMEBOY_DISASSEMBLE_INSTRUCTIONS_ROTATION_H
#define GAMEBOY_DISASSEMBLE_INSTRUCTIONS_ROTATION_H

#include "interface.h"

/**********************************************************+
 * Helper classes ******************************************
 ***********************************************************/

class InstructionRotateRight8BitRegister : public Instruction {
protected:
    InstructionRotateRight8BitRegister(const Register8Bit reg, const Opcode opc)
            : Instruction("RR " + to_string(reg),
                          opc),
              _register(reg) {}

private:
    const Register8Bit _register;
};

class InstructionRotateLeft8BitRegister : public Instruction {
protected:
    InstructionRotateLeft8BitRegister(const Register8Bit reg, const Opcode opc)
            : Instruction("RL " + to_string(reg),
                          opc),
              _register(reg) {}

private:
    const Register8Bit _register;
};

class InstructionRotateRightContentsOf8BitRegister : public Instruction {
protected:
    InstructionRotateRightContentsOf8BitRegister(const Register8Bit reg, const Opcode opc)
            : Instruction("RRC " + to_string(reg),
                          opc),
              _register(reg) {}

private:
    const Register8Bit _register;
};

class InstructionRotateLeftContentsOf8BitRegister : public Instruction {
protected:
    InstructionRotateLeftContentsOf8BitRegister(const Register8Bit reg, const Opcode opc)
            : Instruction("RLC " + to_string(reg),
                          opc),
              _register(reg) {}

private:
    const Register8Bit _register;
};

/**********************************************************+
 * Public interface ****************************************
 ***********************************************************/

// Rotate A and clear Zero Flag
class RotateLeftAAndClearZero : public Instruction {
public:
    RotateLeftAAndClearZero()
            : Instruction("RLA",
                          opcodes::ROTATE_LEFT_A_AND_CLEAR_ZERO) {}
};

class RotateRightAAndClearZero : public Instruction {
public:
    RotateRightAAndClearZero()
            : Instruction("RRA",
                          opcodes::ROTATE_RIGHT_A_AND_CLEAR_ZERO) {}
};

class RotateLeftContentsOfAAndClearZero : public Instruction {
public:
    RotateLeftContentsOfAAndClearZero()
            : Instruction("RLCA",
                          opcodes::ROTATE_LEFT_CONTENTS_OF_A_AND_CLEAR_ZERO) {}
};

class RotateRightContentsOfAAndClearZero : public Instruction {
public:
    RotateRightContentsOfAAndClearZero()
            : Instruction("RRCA",
                          opcodes::ROTATE_RIGHT_CONTENTS_OF_A_AND_CLEAR_ZERO) {}
};


/** Doubly derived classes ***********************************/

// Rotate left
class RotateLeftB : public InstructionRotateLeft8BitRegister {
public:
    RotateLeftB()
            : InstructionRotateLeft8BitRegister(Register8Bit::B,
                                                opcodes::ROTATE_LEFT_B) {}
};

class RotateLeftC : public InstructionRotateLeft8BitRegister {
public:
    RotateLeftC()
            : InstructionRotateLeft8BitRegister(Register8Bit::C,
                                                opcodes::ROTATE_LEFT_C) {}
};

class RotateLeftD : public InstructionRotateLeft8BitRegister {
public:
    RotateLeftD()
            : InstructionRotateLeft8BitRegister(Register8Bit::D,
                                                opcodes::ROTATE_LEFT_D) {}
};

class RotateLeftE : public InstructionRotateLeft8BitRegister {
public:
    RotateLeftE()
            : InstructionRotateLeft8BitRegister(Register8Bit::E,
                                                opcodes::ROTATE_LEFT_E) {}
};

class RotateLeftH : public InstructionRotateLeft8BitRegister {
public:
    RotateLeftH()
            : InstructionRotateLeft8BitRegister(Register8Bit::H,
                                                opcodes::ROTATE_LEFT_H) {}
};

class RotateLeftL : public InstructionRotateLeft8BitRegister {
public:
    RotateLeftL()
            : InstructionRotateLeft8BitRegister(Register8Bit::L,
                                                opcodes::ROTATE_LEFT_L) {}
};

class RotateLeftAddressHL : public InstructionRotateLeft8BitRegister {
public:
    RotateLeftAddressHL()
            : InstructionRotateLeft8BitRegister(Register8Bit::B,
                                                opcodes::ROTATE_LEFT_ADDRESS_HL) {}
};

class RotateLeftA : public InstructionRotateLeft8BitRegister {
public:
    RotateLeftA()
            : InstructionRotateLeft8BitRegister(Register8Bit::A,
                                                opcodes::ROTATE_LEFT_A) {}
};

// Rotate right

class RotateRightB : public InstructionRotateRight8BitRegister {
public:
    RotateRightB()
            : InstructionRotateRight8BitRegister(Register8Bit::B,
                                                 opcodes::ROTATE_RIGHT_B) {}
};

class RotateRightC : public InstructionRotateRight8BitRegister {
public:
    RotateRightC()
            : InstructionRotateRight8BitRegister(Register8Bit::C,
                                                 opcodes::ROTATE_RIGHT_C) {}
};

class RotateRightD : public InstructionRotateRight8BitRegister {
public:
    RotateRightD()
            : InstructionRotateRight8BitRegister(Register8Bit::D,
                                                 opcodes::ROTATE_RIGHT_D) {}
};

class RotateRightE : public InstructionRotateRight8BitRegister {
public:
    RotateRightE()
            : InstructionRotateRight8BitRegister(Register8Bit::E,
                                                 opcodes::ROTATE_RIGHT_E) {}
};

class RotateRightH : public InstructionRotateRight8BitRegister {
public:
    RotateRightH()
            : InstructionRotateRight8BitRegister(Register8Bit::H,
                                                 opcodes::ROTATE_RIGHT_H) {}
};

class RotateRightL : public InstructionRotateRight8BitRegister {
public:
    RotateRightL()
            : InstructionRotateRight8BitRegister(Register8Bit::L,
                                                 opcodes::ROTATE_RIGHT_L) {}
};

class RotateRightAddressHL : public InstructionRotateRight8BitRegister {
public:
    RotateRightAddressHL()
            : InstructionRotateRight8BitRegister(Register8Bit::B,
                                                 opcodes::ROTATE_RIGHT_ADDRESS_HL) {}
};

class RotateRightA : public InstructionRotateRight8BitRegister {
public:
    RotateRightA()
            : InstructionRotateRight8BitRegister(Register8Bit::A,
                                                 opcodes::ROTATE_RIGHT_A) {}
};

// Rotate left contents

class RotateLeftContentsOfB : public InstructionRotateLeftContentsOf8BitRegister {
public:
    RotateLeftContentsOfB()
            : InstructionRotateLeftContentsOf8BitRegister(Register8Bit::B,
                                                          opcodes::ROTATE_LEFT_CONTENTS_OF_B) {}
};

class RotateLeftContentsOfC : public InstructionRotateLeftContentsOf8BitRegister {
public:
    RotateLeftContentsOfC()
            : InstructionRotateLeftContentsOf8BitRegister(Register8Bit::C,
                                                          opcodes::ROTATE_LEFT_CONTENTS_OF_C) {}
};

class RotateLeftContentsOfD : public InstructionRotateLeftContentsOf8BitRegister {
public:
    RotateLeftContentsOfD()
            : InstructionRotateLeftContentsOf8BitRegister(Register8Bit::D,
                                                          opcodes::ROTATE_LEFT_CONTENTS_OF_D) {}
};

class RotateLeftContentsOfE : public InstructionRotateLeftContentsOf8BitRegister {
public:
    RotateLeftContentsOfE()
            : InstructionRotateLeftContentsOf8BitRegister(Register8Bit::E,
                                                          opcodes::ROTATE_LEFT_CONTENTS_OF_E) {}
};

class RotateLeftContentsOfH : public InstructionRotateLeftContentsOf8BitRegister {
public:
    RotateLeftContentsOfH()
            : InstructionRotateLeftContentsOf8BitRegister(Register8Bit::H,
                                                          opcodes::ROTATE_LEFT_CONTENTS_OF_H) {}
};

class RotateLeftContentsOfL : public InstructionRotateLeftContentsOf8BitRegister {
public:
    RotateLeftContentsOfL()
            : InstructionRotateLeftContentsOf8BitRegister(Register8Bit::L,
                                                          opcodes::ROTATE_LEFT_CONTENTS_OF_L) {}
};

class RotateLeftContentsOfAddressHL : public InstructionRotateLeftContentsOf8BitRegister {
public:
    RotateLeftContentsOfAddressHL()
            : InstructionRotateLeftContentsOf8BitRegister(Register8Bit::B,
                                                          opcodes::ROTATE_LEFT_CONTENTS_OF_ADDRESS_HL) {}
};

class RotateLeftContentsOfA : public InstructionRotateLeftContentsOf8BitRegister {
public:
    RotateLeftContentsOfA()
            : InstructionRotateLeftContentsOf8BitRegister(Register8Bit::A,
                                                          opcodes::ROTATE_LEFT_CONTENTS_OF_A) {}
};

// Rotate right contents

class RotateRightContentsOfB : public InstructionRotateRightContentsOf8BitRegister {
public:
    RotateRightContentsOfB()
            : InstructionRotateRightContentsOf8BitRegister(Register8Bit::B,
                                                           opcodes::ROTATE_RIGHT_CONTENTS_OF_B) {}
};

class RotateRightContentsOfC : public InstructionRotateRightContentsOf8BitRegister {
public:
    RotateRightContentsOfC()
            : InstructionRotateRightContentsOf8BitRegister(Register8Bit::C,
                                                           opcodes::ROTATE_RIGHT_CONTENTS_OF_C) {}
};

class RotateRightContentsOfD : public InstructionRotateRightContentsOf8BitRegister {
public:
    RotateRightContentsOfD()
            : InstructionRotateRightContentsOf8BitRegister(Register8Bit::D,
                                                           opcodes::ROTATE_RIGHT_CONTENTS_OF_D) {}
};

class RotateRightContentsOfE : public InstructionRotateRightContentsOf8BitRegister {
public:
    RotateRightContentsOfE()
            : InstructionRotateRightContentsOf8BitRegister(Register8Bit::E,
                                                           opcodes::ROTATE_RIGHT_CONTENTS_OF_E) {}
};

class RotateRightContentsOfH : public InstructionRotateRightContentsOf8BitRegister {
public:
    RotateRightContentsOfH()
            : InstructionRotateRightContentsOf8BitRegister(Register8Bit::H,
                                                           opcodes::ROTATE_RIGHT_CONTENTS_OF_H) {}
};

class RotateRightContentsOfL : public InstructionRotateRightContentsOf8BitRegister {
public:
    RotateRightContentsOfL()
            : InstructionRotateRightContentsOf8BitRegister(Register8Bit::L,
                                                           opcodes::ROTATE_RIGHT_CONTENTS_OF_L) {}
};

class RotateRightContentsOfAddressHL : public InstructionRotateRightContentsOf8BitRegister {
public:
    RotateRightContentsOfAddressHL()
            : InstructionRotateRightContentsOf8BitRegister(Register8Bit::B,
                                                           opcodes::ROTATE_RIGHT_CONTENTS_OF_ADDRESS_HL) {}
};

class RotateRightContentsOfA : public InstructionRotateRightContentsOf8BitRegister {
public:
    RotateRightContentsOfA()
            : InstructionRotateRightContentsOf8BitRegister(Register8Bit::A,
                                                           opcodes::ROTATE_RIGHT_CONTENTS_OF_A) {}
};

#endif //GAMEBOY_DISASSEMBLE_INSTRUCTIONS_ROTATION_H
