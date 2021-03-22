#ifndef GAMEBOY_DISASSEMBLE_INSTRUCTIONS_BIT_COMPLEMENT_H
#define GAMEBOY_DISASSEMBLE_INSTRUCTIONS_BIT_COMPLEMENT_H

#include "interface.h"

/**********************************************************+
 * Helper class ********************************************
 ***********************************************************/

class InstructionBitOf8BitRegisterComplementIntoZero : public Instruction {
protected:
    InstructionBitOf8BitRegisterComplementIntoZero(const uint8_t bitIndex, const Register8Bit reg, const Opcode opc)
            : Instruction("BIT " + to_string_dec(bitIndex) + ", " + to_string(reg), opc),
              _bitIndex(bitIndex),
              _register(reg) {}

private:
    const uint8_t _bitIndex;
    const Register8Bit _register;
};

/**********************************************************+
 * Public interface ****************************************
 ***********************************************************/

// Register B
class Bit0OfBComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit0OfBComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(0,
                                                             Register8Bit::B,
                                                             opcodes::BIT_0_OF_B_COMPLEMENT_INTO_ZERO) {}
};

class Bit1OfBComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit1OfBComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(1,
                                                             Register8Bit::B,
                                                             opcodes::BIT_1_OF_B_COMPLEMENT_INTO_ZERO) {}
};

class Bit2OfBComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit2OfBComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(2,
                                                             Register8Bit::B,
                                                             opcodes::BIT_2_OF_B_COMPLEMENT_INTO_ZERO) {}
};

class Bit3OfBComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit3OfBComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(3,
                                                             Register8Bit::B,
                                                             opcodes::BIT_3_OF_B_COMPLEMENT_INTO_ZERO) {}
};

class Bit4OfBComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit4OfBComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(4,
                                                             Register8Bit::B,
                                                             opcodes::BIT_4_OF_B_COMPLEMENT_INTO_ZERO) {}
};

class Bit5OfBComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit5OfBComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(5,
                                                             Register8Bit::B,
                                                             opcodes::BIT_5_OF_B_COMPLEMENT_INTO_ZERO) {}
};

class Bit6OfBComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit6OfBComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(6,
                                                             Register8Bit::B,
                                                             opcodes::BIT_6_OF_B_COMPLEMENT_INTO_ZERO) {}
};

class Bit7OfBComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit7OfBComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(7,
                                                             Register8Bit::B,
                                                             opcodes::BIT_7_OF_B_COMPLEMENT_INTO_ZERO) {}
};

// Register C
class Bit0OfCComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit0OfCComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(0,
                                                             Register8Bit::C,
                                                             opcodes::BIT_0_OF_C_COMPLEMENT_INTO_ZERO) {}
};

class Bit1OfCComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit1OfCComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(1,
                                                             Register8Bit::C,
                                                             opcodes::BIT_1_OF_C_COMPLEMENT_INTO_ZERO) {}
};

class Bit2OfCComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit2OfCComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(2,
                                                             Register8Bit::C,
                                                             opcodes::BIT_2_OF_C_COMPLEMENT_INTO_ZERO) {}
};

class Bit3OfCComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit3OfCComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(3,
                                                             Register8Bit::C,
                                                             opcodes::BIT_3_OF_C_COMPLEMENT_INTO_ZERO) {}
};

class Bit4OfCComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit4OfCComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(4,
                                                             Register8Bit::C,
                                                             opcodes::BIT_4_OF_C_COMPLEMENT_INTO_ZERO) {}
};

class Bit5OfCComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit5OfCComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(5,
                                                             Register8Bit::C,
                                                             opcodes::BIT_5_OF_C_COMPLEMENT_INTO_ZERO) {}
};

class Bit6OfCComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit6OfCComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(6,
                                                             Register8Bit::C,
                                                             opcodes::BIT_6_OF_C_COMPLEMENT_INTO_ZERO) {}
};

class Bit7OfCComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit7OfCComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(7,
                                                             Register8Bit::C,
                                                             opcodes::BIT_7_OF_C_COMPLEMENT_INTO_ZERO) {}
};

// Register D
class Bit0OfDComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit0OfDComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(0,
                                                             Register8Bit::D,
                                                             opcodes::BIT_0_OF_D_COMPLEMENT_INTO_ZERO) {}
};

class Bit1OfDComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit1OfDComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(1,
                                                             Register8Bit::D,
                                                             opcodes::BIT_1_OF_D_COMPLEMENT_INTO_ZERO) {}
};

class Bit2OfDComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit2OfDComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(2,
                                                             Register8Bit::D,
                                                             opcodes::BIT_2_OF_D_COMPLEMENT_INTO_ZERO) {}
};

class Bit3OfDComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit3OfDComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(3,
                                                             Register8Bit::D,
                                                             opcodes::BIT_3_OF_D_COMPLEMENT_INTO_ZERO) {}
};

class Bit4OfDComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit4OfDComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(4,
                                                             Register8Bit::D,
                                                             opcodes::BIT_4_OF_D_COMPLEMENT_INTO_ZERO) {}
};

class Bit5OfDComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit5OfDComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(5,
                                                             Register8Bit::D,
                                                             opcodes::BIT_5_OF_D_COMPLEMENT_INTO_ZERO) {}
};

class Bit6OfDComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit6OfDComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(6,
                                                             Register8Bit::D,
                                                             opcodes::BIT_6_OF_D_COMPLEMENT_INTO_ZERO) {}
};

class Bit7OfDComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit7OfDComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(7,
                                                             Register8Bit::D,
                                                             opcodes::BIT_7_OF_D_COMPLEMENT_INTO_ZERO) {}
};

// Register E
class Bit0OfEComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit0OfEComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(0,
                                                             Register8Bit::E,
                                                             opcodes::BIT_0_OF_E_COMPLEMENT_INTO_ZERO) {}
};

class Bit1OfEComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit1OfEComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(1,
                                                             Register8Bit::E,
                                                             opcodes::BIT_1_OF_E_COMPLEMENT_INTO_ZERO) {}
};

class Bit2OfEComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit2OfEComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(2,
                                                             Register8Bit::E,
                                                             opcodes::BIT_2_OF_E_COMPLEMENT_INTO_ZERO) {}
};

class Bit3OfEComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit3OfEComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(3,
                                                             Register8Bit::E,
                                                             opcodes::BIT_3_OF_E_COMPLEMENT_INTO_ZERO) {}
};

class Bit4OfEComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit4OfEComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(4,
                                                             Register8Bit::E,
                                                             opcodes::BIT_4_OF_E_COMPLEMENT_INTO_ZERO) {}
};

class Bit5OfEComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit5OfEComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(5,
                                                             Register8Bit::E,
                                                             opcodes::BIT_5_OF_E_COMPLEMENT_INTO_ZERO) {}
};

class Bit6OfEComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit6OfEComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(6,
                                                             Register8Bit::E,
                                                             opcodes::BIT_6_OF_E_COMPLEMENT_INTO_ZERO) {}
};

class Bit7OfEComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit7OfEComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(7,
                                                             Register8Bit::E,
                                                             opcodes::BIT_7_OF_E_COMPLEMENT_INTO_ZERO) {}
};

// Register H
class Bit0OfHComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit0OfHComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(0,
                                                             Register8Bit::H,
                                                             opcodes::BIT_0_OF_H_COMPLEMENT_INTO_ZERO) {}
};

class Bit1OfHComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit1OfHComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(1,
                                                             Register8Bit::H,
                                                             opcodes::BIT_1_OF_H_COMPLEMENT_INTO_ZERO) {}
};

class Bit2OfHComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit2OfHComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(2,
                                                             Register8Bit::H,
                                                             opcodes::BIT_2_OF_H_COMPLEMENT_INTO_ZERO) {}
};

class Bit3OfHComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit3OfHComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(3,
                                                             Register8Bit::H,
                                                             opcodes::BIT_3_OF_H_COMPLEMENT_INTO_ZERO) {}
};

class Bit4OfHComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit4OfHComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(4,
                                                             Register8Bit::H,
                                                             opcodes::BIT_4_OF_H_COMPLEMENT_INTO_ZERO) {}
};

class Bit5OfHComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit5OfHComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(5,
                                                             Register8Bit::H,
                                                             opcodes::BIT_5_OF_H_COMPLEMENT_INTO_ZERO) {}
};

class Bit6OfHComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit6OfHComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(6,
                                                             Register8Bit::H,
                                                             opcodes::BIT_6_OF_H_COMPLEMENT_INTO_ZERO) {}
};

class Bit7OfHComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit7OfHComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(7,
                                                             Register8Bit::H,
                                                             opcodes::BIT_7_OF_H_COMPLEMENT_INTO_ZERO) {}
};

// Register L
class Bit0OfLComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit0OfLComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(0,
                                                             Register8Bit::L,
                                                             opcodes::BIT_0_OF_L_COMPLEMENT_INTO_ZERO) {}
};

class Bit1OfLComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit1OfLComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(1,
                                                             Register8Bit::L,
                                                             opcodes::BIT_1_OF_L_COMPLEMENT_INTO_ZERO) {}
};

class Bit2OfLComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit2OfLComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(2,
                                                             Register8Bit::L,
                                                             opcodes::BIT_2_OF_L_COMPLEMENT_INTO_ZERO) {}
};

class Bit3OfLComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit3OfLComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(3,
                                                             Register8Bit::L,
                                                             opcodes::BIT_3_OF_L_COMPLEMENT_INTO_ZERO) {}
};

class Bit4OfLComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit4OfLComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(4,
                                                             Register8Bit::L,
                                                             opcodes::BIT_4_OF_L_COMPLEMENT_INTO_ZERO) {}
};

class Bit5OfLComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit5OfLComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(5,
                                                             Register8Bit::L,
                                                             opcodes::BIT_5_OF_L_COMPLEMENT_INTO_ZERO) {}
};

class Bit6OfLComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit6OfLComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(6,
                                                             Register8Bit::L,
                                                             opcodes::BIT_6_OF_L_COMPLEMENT_INTO_ZERO) {}
};

class Bit7OfLComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit7OfLComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(7,
                                                             Register8Bit::L,
                                                             opcodes::BIT_7_OF_L_COMPLEMENT_INTO_ZERO) {}
};

// Register ADDRESS_HL
class Bit0OfAddressHLComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit0OfAddressHLComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(0,
                                                             Register8Bit::ADDRESS_HL,
                                                             opcodes::BIT_0_OF_ADDRESS_HL_COMPLEMENT_INTO_ZERO) {}
};

class Bit1OfAddressHLComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit1OfAddressHLComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(1,
                                                             Register8Bit::ADDRESS_HL,
                                                             opcodes::BIT_1_OF_ADDRESS_HL_COMPLEMENT_INTO_ZERO) {}
};

class Bit2OfAddressHLComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit2OfAddressHLComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(2,
                                                             Register8Bit::ADDRESS_HL,
                                                             opcodes::BIT_2_OF_ADDRESS_HL_COMPLEMENT_INTO_ZERO) {}
};

class Bit3OfAddressHLComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit3OfAddressHLComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(3,
                                                             Register8Bit::ADDRESS_HL,
                                                             opcodes::BIT_3_OF_ADDRESS_HL_COMPLEMENT_INTO_ZERO) {}
};

class Bit4OfAddressHLComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit4OfAddressHLComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(4,
                                                             Register8Bit::ADDRESS_HL,
                                                             opcodes::BIT_4_OF_ADDRESS_HL_COMPLEMENT_INTO_ZERO) {}
};

class Bit5OfAddressHLComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit5OfAddressHLComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(5,
                                                             Register8Bit::ADDRESS_HL,
                                                             opcodes::BIT_5_OF_ADDRESS_HL_COMPLEMENT_INTO_ZERO) {}
};

class Bit6OfAddressHLComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit6OfAddressHLComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(6,
                                                             Register8Bit::ADDRESS_HL,
                                                             opcodes::BIT_6_OF_ADDRESS_HL_COMPLEMENT_INTO_ZERO) {}
};

class Bit7OfAddressHLComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit7OfAddressHLComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(7,
                                                             Register8Bit::ADDRESS_HL,
                                                             opcodes::BIT_7_OF_ADDRESS_HL_COMPLEMENT_INTO_ZERO) {}
};

// Register A
class Bit0OfAComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit0OfAComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(0,
                                                             Register8Bit::A,
                                                             opcodes::BIT_0_OF_A_COMPLEMENT_INTO_ZERO) {}
};

class Bit1OfAComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit1OfAComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(1,
                                                             Register8Bit::A,
                                                             opcodes::BIT_1_OF_A_COMPLEMENT_INTO_ZERO) {}
};

class Bit2OfAComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit2OfAComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(2,
                                                             Register8Bit::A,
                                                             opcodes::BIT_2_OF_A_COMPLEMENT_INTO_ZERO) {}
};

class Bit3OfAComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit3OfAComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(3,
                                                             Register8Bit::A,
                                                             opcodes::BIT_3_OF_A_COMPLEMENT_INTO_ZERO) {}
};

class Bit4OfAComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit4OfAComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(4,
                                                             Register8Bit::A,
                                                             opcodes::BIT_4_OF_A_COMPLEMENT_INTO_ZERO) {}
};

class Bit5OfAComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit5OfAComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(5,
                                                             Register8Bit::A,
                                                             opcodes::BIT_5_OF_A_COMPLEMENT_INTO_ZERO) {}
};

class Bit6OfAComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit6OfAComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(6,
                                                             Register8Bit::A,
                                                             opcodes::BIT_6_OF_A_COMPLEMENT_INTO_ZERO) {}
};

class Bit7OfAComplementIntoZero : public InstructionBitOf8BitRegisterComplementIntoZero {
public:
    Bit7OfAComplementIntoZero()
            : InstructionBitOf8BitRegisterComplementIntoZero(7,
                                                             Register8Bit::A,
                                                             opcodes::BIT_7_OF_A_COMPLEMENT_INTO_ZERO) {}
};


#endif //GAMEBOY_DISASSEMBLE_INSTRUCTIONS_BIT_COMPLEMENT_H
