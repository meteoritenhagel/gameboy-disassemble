#ifndef GAMEBOY_DISASSEMBLE_INSTRUCTIONS_RESET_H
#define GAMEBOY_DISASSEMBLE_INSTRUCTIONS_RESET_H

#include "instructions_interface.h"

class InstructionResetBitOf8BitRegister : public Instruction {
protected:
    InstructionResetBitOf8BitRegister(const uint8_t bitIndex, const Register8Bit reg, const Opcode opc)
            : Instruction("BIT " + to_string_dec(bitIndex) + ", " + to_string(reg),
                          opc),
              _bitIndex(bitIndex),
              _register(reg) {}

private:
    const uint8_t _bitIndex;
    const Register8Bit _register;
};





// child classes


// Register B
class ResetBit0OfB : public InstructionResetBitOf8BitRegister {
public:
    ResetBit0OfB()
            : InstructionResetBitOf8BitRegister(0,
                                                Register8Bit::B,
                                                opcodes::RESET_BIT_0_OF_B) {}
};

class ResetBit1OfB : public InstructionResetBitOf8BitRegister {
public:
    ResetBit1OfB()
            : InstructionResetBitOf8BitRegister(1,
                                                Register8Bit::B,
                                                opcodes::RESET_BIT_1_OF_B) {}
};

class ResetBit2OfB : public InstructionResetBitOf8BitRegister {
public:
    ResetBit2OfB()
            : InstructionResetBitOf8BitRegister(2,
                                                Register8Bit::B,
                                                opcodes::RESET_BIT_2_OF_B) {}
};

class ResetBit3OfB : public InstructionResetBitOf8BitRegister {
public:
    ResetBit3OfB()
            : InstructionResetBitOf8BitRegister(3,
                                                Register8Bit::B,
                                                opcodes::RESET_BIT_3_OF_B) {}
};

class ResetBit4OfB : public InstructionResetBitOf8BitRegister {
public:
    ResetBit4OfB()
            : InstructionResetBitOf8BitRegister(4,
                                                Register8Bit::B,
                                                opcodes::RESET_BIT_4_OF_B) {}
};

class ResetBit5OfB : public InstructionResetBitOf8BitRegister {
public:
    ResetBit5OfB()
            : InstructionResetBitOf8BitRegister(5,
                                                Register8Bit::B,
                                                opcodes::RESET_BIT_5_OF_B) {}
};

class ResetBit6OfB : public InstructionResetBitOf8BitRegister {
public:
    ResetBit6OfB()
            : InstructionResetBitOf8BitRegister(6,
                                                Register8Bit::B,
                                                opcodes::RESET_BIT_6_OF_B) {}
};

class ResetBit7OfB : public InstructionResetBitOf8BitRegister {
public:
    ResetBit7OfB()
            : InstructionResetBitOf8BitRegister(7,
                                                Register8Bit::B,
                                                opcodes::RESET_BIT_7_OF_B) {}
};

// Register C
class ResetBit0OfC : public InstructionResetBitOf8BitRegister {
public:
    ResetBit0OfC()
            : InstructionResetBitOf8BitRegister(0,
                                                Register8Bit::C,
                                                opcodes::RESET_BIT_0_OF_C) {}
};

class ResetBit1OfC : public InstructionResetBitOf8BitRegister {
public:
    ResetBit1OfC()
            : InstructionResetBitOf8BitRegister(1,
                                                Register8Bit::C,
                                                opcodes::RESET_BIT_1_OF_C) {}
};

class ResetBit2OfC : public InstructionResetBitOf8BitRegister {
public:
    ResetBit2OfC()
            : InstructionResetBitOf8BitRegister(2,
                                                Register8Bit::C,
                                                opcodes::RESET_BIT_2_OF_C) {}
};

class ResetBit3OfC : public InstructionResetBitOf8BitRegister {
public:
    ResetBit3OfC()
            : InstructionResetBitOf8BitRegister(3,
                                                Register8Bit::C,
                                                opcodes::RESET_BIT_3_OF_C) {}
};

class ResetBit4OfC : public InstructionResetBitOf8BitRegister {
public:
    ResetBit4OfC()
            : InstructionResetBitOf8BitRegister(4,
                                                Register8Bit::C,
                                                opcodes::RESET_BIT_4_OF_C) {}
};

class ResetBit5OfC : public InstructionResetBitOf8BitRegister {
public:
    ResetBit5OfC()
            : InstructionResetBitOf8BitRegister(5,
                                                Register8Bit::C,
                                                opcodes::RESET_BIT_5_OF_C) {}
};

class ResetBit6OfC : public InstructionResetBitOf8BitRegister {
public:
    ResetBit6OfC()
            : InstructionResetBitOf8BitRegister(6,
                                                Register8Bit::C,
                                                opcodes::RESET_BIT_6_OF_C) {}
};

class ResetBit7OfC : public InstructionResetBitOf8BitRegister {
public:
    ResetBit7OfC()
            : InstructionResetBitOf8BitRegister(7,
                                                Register8Bit::C,
                                                opcodes::RESET_BIT_7_OF_C) {}
};

// Register D
class ResetBit0OfD : public InstructionResetBitOf8BitRegister {
public:
    ResetBit0OfD()
            : InstructionResetBitOf8BitRegister(0,
                                                Register8Bit::D,
                                                opcodes::RESET_BIT_0_OF_D) {}
};

class ResetBit1OfD : public InstructionResetBitOf8BitRegister {
public:
    ResetBit1OfD()
            : InstructionResetBitOf8BitRegister(1,
                                                Register8Bit::D,
                                                opcodes::RESET_BIT_1_OF_D) {}
};

class ResetBit2OfD : public InstructionResetBitOf8BitRegister {
public:
    ResetBit2OfD()
            : InstructionResetBitOf8BitRegister(2,
                                                Register8Bit::D,
                                                opcodes::RESET_BIT_2_OF_D) {}
};

class ResetBit3OfD : public InstructionResetBitOf8BitRegister {
public:
    ResetBit3OfD()
            : InstructionResetBitOf8BitRegister(3,
                                                Register8Bit::D,
                                                opcodes::RESET_BIT_3_OF_D) {}
};

class ResetBit4OfD : public InstructionResetBitOf8BitRegister {
public:
    ResetBit4OfD()
            : InstructionResetBitOf8BitRegister(4,
                                                Register8Bit::D,
                                                opcodes::RESET_BIT_4_OF_D) {}
};

class ResetBit5OfD : public InstructionResetBitOf8BitRegister {
public:
    ResetBit5OfD()
            : InstructionResetBitOf8BitRegister(5,
                                                Register8Bit::D,
                                                opcodes::RESET_BIT_5_OF_D) {}
};

class ResetBit6OfD : public InstructionResetBitOf8BitRegister {
public:
    ResetBit6OfD()
            : InstructionResetBitOf8BitRegister(6,
                                                Register8Bit::D,
                                                opcodes::RESET_BIT_6_OF_D) {}
};

class ResetBit7OfD : public InstructionResetBitOf8BitRegister {
public:
    ResetBit7OfD()
            : InstructionResetBitOf8BitRegister(7,
                                                Register8Bit::D,
                                                opcodes::RESET_BIT_7_OF_D) {}
};

// Register E
class ResetBit0OfE : public InstructionResetBitOf8BitRegister {
public:
    ResetBit0OfE()
            : InstructionResetBitOf8BitRegister(0,
                                                Register8Bit::E,
                                                opcodes::RESET_BIT_0_OF_E) {}
};

class ResetBit1OfE : public InstructionResetBitOf8BitRegister {
public:
    ResetBit1OfE()
            : InstructionResetBitOf8BitRegister(1,
                                                Register8Bit::E,
                                                opcodes::RESET_BIT_1_OF_E) {}
};

class ResetBit2OfE : public InstructionResetBitOf8BitRegister {
public:
    ResetBit2OfE()
            : InstructionResetBitOf8BitRegister(2,
                                                Register8Bit::E,
                                                opcodes::RESET_BIT_2_OF_E) {}
};

class ResetBit3OfE : public InstructionResetBitOf8BitRegister {
public:
    ResetBit3OfE()
            : InstructionResetBitOf8BitRegister(3,
                                                Register8Bit::E,
                                                opcodes::RESET_BIT_3_OF_E) {}
};

class ResetBit4OfE : public InstructionResetBitOf8BitRegister {
public:
    ResetBit4OfE()
            : InstructionResetBitOf8BitRegister(4,
                                                Register8Bit::E,
                                                opcodes::RESET_BIT_4_OF_E) {}
};

class ResetBit5OfE : public InstructionResetBitOf8BitRegister {
public:
    ResetBit5OfE()
            : InstructionResetBitOf8BitRegister(5,
                                                Register8Bit::E,
                                                opcodes::RESET_BIT_5_OF_E) {}
};

class ResetBit6OfE : public InstructionResetBitOf8BitRegister {
public:
    ResetBit6OfE()
            : InstructionResetBitOf8BitRegister(6,
                                                Register8Bit::E,
                                                opcodes::RESET_BIT_6_OF_E) {}
};

class ResetBit7OfE : public InstructionResetBitOf8BitRegister {
public:
    ResetBit7OfE()
            : InstructionResetBitOf8BitRegister(7,
                                                Register8Bit::E,
                                                opcodes::RESET_BIT_7_OF_E) {}
};

// Register H
class ResetBit0OfH : public InstructionResetBitOf8BitRegister {
public:
    ResetBit0OfH()
            : InstructionResetBitOf8BitRegister(0,
                                                Register8Bit::H,
                                                opcodes::RESET_BIT_0_OF_H) {}
};

class ResetBit1OfH : public InstructionResetBitOf8BitRegister {
public:
    ResetBit1OfH()
            : InstructionResetBitOf8BitRegister(1,
                                                Register8Bit::H,
                                                opcodes::RESET_BIT_1_OF_H) {}
};

class ResetBit2OfH : public InstructionResetBitOf8BitRegister {
public:
    ResetBit2OfH()
            : InstructionResetBitOf8BitRegister(2,
                                                Register8Bit::H,
                                                opcodes::RESET_BIT_2_OF_H) {}
};

class ResetBit3OfH : public InstructionResetBitOf8BitRegister {
public:
    ResetBit3OfH()
            : InstructionResetBitOf8BitRegister(3,
                                                Register8Bit::H,
                                                opcodes::RESET_BIT_3_OF_H) {}
};

class ResetBit4OfH : public InstructionResetBitOf8BitRegister {
public:
    ResetBit4OfH()
            : InstructionResetBitOf8BitRegister(4,
                                                Register8Bit::H,
                                                opcodes::RESET_BIT_4_OF_H) {}
};

class ResetBit5OfH : public InstructionResetBitOf8BitRegister {
public:
    ResetBit5OfH()
            : InstructionResetBitOf8BitRegister(5,
                                                Register8Bit::H,
                                                opcodes::RESET_BIT_5_OF_H) {}
};

class ResetBit6OfH : public InstructionResetBitOf8BitRegister {
public:
    ResetBit6OfH()
            : InstructionResetBitOf8BitRegister(6,
                                                Register8Bit::H,
                                                opcodes::RESET_BIT_6_OF_H) {}
};

class ResetBit7OfH : public InstructionResetBitOf8BitRegister {
public:
    ResetBit7OfH()
            : InstructionResetBitOf8BitRegister(7,
                                                Register8Bit::H,
                                                opcodes::RESET_BIT_7_OF_H) {}
};

// Register L
class ResetBit0OfL : public InstructionResetBitOf8BitRegister {
public:
    ResetBit0OfL()
            : InstructionResetBitOf8BitRegister(0,
                                                Register8Bit::L,
                                                opcodes::RESET_BIT_0_OF_L) {}
};

class ResetBit1OfL : public InstructionResetBitOf8BitRegister {
public:
    ResetBit1OfL()
            : InstructionResetBitOf8BitRegister(1,
                                                Register8Bit::L,
                                                opcodes::RESET_BIT_1_OF_L) {}
};

class ResetBit2OfL : public InstructionResetBitOf8BitRegister {
public:
    ResetBit2OfL()
            : InstructionResetBitOf8BitRegister(2,
                                                Register8Bit::L,
                                                opcodes::RESET_BIT_2_OF_L) {}
};

class ResetBit3OfL : public InstructionResetBitOf8BitRegister {
public:
    ResetBit3OfL()
            : InstructionResetBitOf8BitRegister(3,
                                                Register8Bit::L,
                                                opcodes::RESET_BIT_3_OF_L) {}
};

class ResetBit4OfL : public InstructionResetBitOf8BitRegister {
public:
    ResetBit4OfL()
            : InstructionResetBitOf8BitRegister(4,
                                                Register8Bit::L,
                                                opcodes::RESET_BIT_4_OF_L) {}
};

class ResetBit5OfL : public InstructionResetBitOf8BitRegister {
public:
    ResetBit5OfL()
            : InstructionResetBitOf8BitRegister(5,
                                                Register8Bit::L,
                                                opcodes::RESET_BIT_5_OF_L) {}
};

class ResetBit6OfL : public InstructionResetBitOf8BitRegister {
public:
    ResetBit6OfL()
            : InstructionResetBitOf8BitRegister(6,
                                                Register8Bit::L,
                                                opcodes::RESET_BIT_6_OF_L) {}
};

class ResetBit7OfL : public InstructionResetBitOf8BitRegister {
public:
    ResetBit7OfL()
            : InstructionResetBitOf8BitRegister(7,
                                                Register8Bit::L,
                                                opcodes::RESET_BIT_7_OF_L) {}
};

// Register ADDRESS_HL
class ResetBit0OfAddressHL : public InstructionResetBitOf8BitRegister {
public:
    ResetBit0OfAddressHL()
            : InstructionResetBitOf8BitRegister(0,
                                                Register8Bit::ADDRESS_HL,
                                                opcodes::RESET_BIT_0_OF_ADDRESS_HL) {}
};

class ResetBit1OfAddressHL : public InstructionResetBitOf8BitRegister {
public:
    ResetBit1OfAddressHL()
            : InstructionResetBitOf8BitRegister(1,
                                                Register8Bit::ADDRESS_HL,
                                                opcodes::RESET_BIT_1_OF_ADDRESS_HL) {}
};

class ResetBit2OfAddressHL : public InstructionResetBitOf8BitRegister {
public:
    ResetBit2OfAddressHL()
            : InstructionResetBitOf8BitRegister(2,
                                                Register8Bit::ADDRESS_HL,
                                                opcodes::RESET_BIT_2_OF_ADDRESS_HL) {}
};

class ResetBit3OfAddressHL : public InstructionResetBitOf8BitRegister {
public:
    ResetBit3OfAddressHL()
            : InstructionResetBitOf8BitRegister(3,
                                                Register8Bit::ADDRESS_HL,
                                                opcodes::RESET_BIT_3_OF_ADDRESS_HL) {}
};

class ResetBit4OfAddressHL : public InstructionResetBitOf8BitRegister {
public:
    ResetBit4OfAddressHL()
            : InstructionResetBitOf8BitRegister(4,
                                                Register8Bit::ADDRESS_HL,
                                                opcodes::RESET_BIT_4_OF_ADDRESS_HL) {}
};

class ResetBit5OfAddressHL : public InstructionResetBitOf8BitRegister {
public:
    ResetBit5OfAddressHL()
            : InstructionResetBitOf8BitRegister(5,
                                                Register8Bit::ADDRESS_HL,
                                                opcodes::RESET_BIT_5_OF_ADDRESS_HL) {}
};

class ResetBit6OfAddressHL : public InstructionResetBitOf8BitRegister {
public:
    ResetBit6OfAddressHL()
            : InstructionResetBitOf8BitRegister(6,
                                                Register8Bit::ADDRESS_HL,
                                                opcodes::RESET_BIT_6_OF_ADDRESS_HL) {}
};

class ResetBit7OfAddressHL : public InstructionResetBitOf8BitRegister {
public:
    ResetBit7OfAddressHL()
            : InstructionResetBitOf8BitRegister(7,
                                                Register8Bit::ADDRESS_HL,
                                                opcodes::RESET_BIT_7_OF_ADDRESS_HL) {}
};

// Register A
class ResetBit0OfA : public InstructionResetBitOf8BitRegister {
public:
    ResetBit0OfA()
            : InstructionResetBitOf8BitRegister(0,
                                                Register8Bit::A,
                                                opcodes::RESET_BIT_0_OF_A) {}
};

class ResetBit1OfA : public InstructionResetBitOf8BitRegister {
public:
    ResetBit1OfA()
            : InstructionResetBitOf8BitRegister(1,
                                                Register8Bit::A,
                                                opcodes::RESET_BIT_1_OF_A) {}
};

class ResetBit2OfA : public InstructionResetBitOf8BitRegister {
public:
    ResetBit2OfA()
            : InstructionResetBitOf8BitRegister(2,
                                                Register8Bit::A,
                                                opcodes::RESET_BIT_2_OF_A) {}
};

class ResetBit3OfA : public InstructionResetBitOf8BitRegister {
public:
    ResetBit3OfA()
            : InstructionResetBitOf8BitRegister(3,
                                                Register8Bit::A,
                                                opcodes::RESET_BIT_3_OF_A) {}
};

class ResetBit4OfA : public InstructionResetBitOf8BitRegister {
public:
    ResetBit4OfA()
            : InstructionResetBitOf8BitRegister(4,
                                                Register8Bit::A,
                                                opcodes::RESET_BIT_4_OF_A) {}
};

class ResetBit5OfA : public InstructionResetBitOf8BitRegister {
public:
    ResetBit5OfA()
            : InstructionResetBitOf8BitRegister(5,
                                                Register8Bit::A,
                                                opcodes::RESET_BIT_5_OF_A) {}
};

class ResetBit6OfA : public InstructionResetBitOf8BitRegister {
public:
    ResetBit6OfA()
            : InstructionResetBitOf8BitRegister(6,
                                                Register8Bit::A,
                                                opcodes::RESET_BIT_6_OF_A) {}
};

class ResetBit7OfA : public InstructionResetBitOf8BitRegister {
public:
    ResetBit7OfA()
            : InstructionResetBitOf8BitRegister(7,
                                                Register8Bit::A,
                                                opcodes::RESET_BIT_7_OF_A) {}
};

#endif //GAMEBOY_DISASSEMBLE_INSTRUCTIONS_RESET_H
