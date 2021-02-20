#ifndef GAMEBOY_DISASSEMBLE_INSTRUCTIONS_SET_H
#define GAMEBOY_DISASSEMBLE_INSTRUCTIONS_SET_H

class InstructionSetBitOf8BitRegister : public Instruction {
protected:
    InstructionSetBitOf8BitRegister(const uint8_t bitIndex, const Register8Bit reg, const Opcode opc)
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
class SetBit0OfB : public InstructionSetBitOf8BitRegister {
public:
    SetBit0OfB()
            : InstructionSetBitOf8BitRegister(0,
                                              Register8Bit::B,
                                              opcodes::SET_BIT_0_OF_B) {}
};

class SetBit1OfB : public InstructionSetBitOf8BitRegister {
public:
    SetBit1OfB()
            : InstructionSetBitOf8BitRegister(1,
                                              Register8Bit::B,
                                              opcodes::SET_BIT_1_OF_B) {}
};

class SetBit2OfB : public InstructionSetBitOf8BitRegister {
public:
    SetBit2OfB()
            : InstructionSetBitOf8BitRegister(2,
                                              Register8Bit::B,
                                              opcodes::SET_BIT_2_OF_B) {}
};

class SetBit3OfB : public InstructionSetBitOf8BitRegister {
public:
    SetBit3OfB()
            : InstructionSetBitOf8BitRegister(3,
                                              Register8Bit::B,
                                              opcodes::SET_BIT_3_OF_B) {}
};

class SetBit4OfB : public InstructionSetBitOf8BitRegister {
public:
    SetBit4OfB()
            : InstructionSetBitOf8BitRegister(4,
                                              Register8Bit::B,
                                              opcodes::SET_BIT_4_OF_B) {}
};

class SetBit5OfB : public InstructionSetBitOf8BitRegister {
public:
    SetBit5OfB()
            : InstructionSetBitOf8BitRegister(5,
                                              Register8Bit::B,
                                              opcodes::SET_BIT_5_OF_B) {}
};

class SetBit6OfB : public InstructionSetBitOf8BitRegister {
public:
    SetBit6OfB()
            : InstructionSetBitOf8BitRegister(6,
                                              Register8Bit::B,
                                              opcodes::SET_BIT_6_OF_B) {}
};

class SetBit7OfB : public InstructionSetBitOf8BitRegister {
public:
    SetBit7OfB()
            : InstructionSetBitOf8BitRegister(7,
                                              Register8Bit::B,
                                              opcodes::SET_BIT_7_OF_B) {}
};

// Register C
class SetBit0OfC : public InstructionSetBitOf8BitRegister {
public:
    SetBit0OfC()
            : InstructionSetBitOf8BitRegister(0,
                                              Register8Bit::C,
                                              opcodes::SET_BIT_0_OF_C) {}
};

class SetBit1OfC : public InstructionSetBitOf8BitRegister {
public:
    SetBit1OfC()
            : InstructionSetBitOf8BitRegister(1,
                                              Register8Bit::C,
                                              opcodes::SET_BIT_1_OF_C) {}
};

class SetBit2OfC : public InstructionSetBitOf8BitRegister {
public:
    SetBit2OfC()
            : InstructionSetBitOf8BitRegister(2,
                                              Register8Bit::C,
                                              opcodes::SET_BIT_2_OF_C) {}
};

class SetBit3OfC : public InstructionSetBitOf8BitRegister {
public:
    SetBit3OfC()
            : InstructionSetBitOf8BitRegister(3,
                                              Register8Bit::C,
                                              opcodes::SET_BIT_3_OF_C) {}
};

class SetBit4OfC : public InstructionSetBitOf8BitRegister {
public:
    SetBit4OfC()
            : InstructionSetBitOf8BitRegister(4,
                                              Register8Bit::C,
                                              opcodes::SET_BIT_4_OF_C) {}
};

class SetBit5OfC : public InstructionSetBitOf8BitRegister {
public:
    SetBit5OfC()
            : InstructionSetBitOf8BitRegister(5,
                                              Register8Bit::C,
                                              opcodes::SET_BIT_5_OF_C) {}
};

class SetBit6OfC : public InstructionSetBitOf8BitRegister {
public:
    SetBit6OfC()
            : InstructionSetBitOf8BitRegister(6,
                                              Register8Bit::C,
                                              opcodes::SET_BIT_6_OF_C) {}
};

class SetBit7OfC : public InstructionSetBitOf8BitRegister {
public:
    SetBit7OfC()
            : InstructionSetBitOf8BitRegister(7,
                                              Register8Bit::C,
                                              opcodes::SET_BIT_7_OF_C) {}
};

// Register D
class SetBit0OfD : public InstructionSetBitOf8BitRegister {
public:
    SetBit0OfD()
            : InstructionSetBitOf8BitRegister(0,
                                              Register8Bit::D,
                                              opcodes::SET_BIT_0_OF_D) {}
};

class SetBit1OfD : public InstructionSetBitOf8BitRegister {
public:
    SetBit1OfD()
            : InstructionSetBitOf8BitRegister(1,
                                              Register8Bit::D,
                                              opcodes::SET_BIT_1_OF_D) {}
};

class SetBit2OfD : public InstructionSetBitOf8BitRegister {
public:
    SetBit2OfD()
            : InstructionSetBitOf8BitRegister(2,
                                              Register8Bit::D,
                                              opcodes::SET_BIT_2_OF_D) {}
};

class SetBit3OfD : public InstructionSetBitOf8BitRegister {
public:
    SetBit3OfD()
            : InstructionSetBitOf8BitRegister(3,
                                              Register8Bit::D,
                                              opcodes::SET_BIT_3_OF_D) {}
};

class SetBit4OfD : public InstructionSetBitOf8BitRegister {
public:
    SetBit4OfD()
            : InstructionSetBitOf8BitRegister(4,
                                              Register8Bit::D,
                                              opcodes::SET_BIT_4_OF_D) {}
};

class SetBit5OfD : public InstructionSetBitOf8BitRegister {
public:
    SetBit5OfD()
            : InstructionSetBitOf8BitRegister(5,
                                              Register8Bit::D,
                                              opcodes::SET_BIT_5_OF_D) {}
};

class SetBit6OfD : public InstructionSetBitOf8BitRegister {
public:
    SetBit6OfD()
            : InstructionSetBitOf8BitRegister(6,
                                              Register8Bit::D,
                                              opcodes::SET_BIT_6_OF_D) {}
};

class SetBit7OfD : public InstructionSetBitOf8BitRegister {
public:
    SetBit7OfD()
            : InstructionSetBitOf8BitRegister(7,
                                              Register8Bit::D,
                                              opcodes::SET_BIT_7_OF_D) {}
};

// Register E
class SetBit0OfE : public InstructionSetBitOf8BitRegister {
public:
    SetBit0OfE()
            : InstructionSetBitOf8BitRegister(0,
                                              Register8Bit::E,
                                              opcodes::SET_BIT_0_OF_E) {}
};

class SetBit1OfE : public InstructionSetBitOf8BitRegister {
public:
    SetBit1OfE()
            : InstructionSetBitOf8BitRegister(1,
                                              Register8Bit::E,
                                              opcodes::SET_BIT_1_OF_E) {}
};

class SetBit2OfE : public InstructionSetBitOf8BitRegister {
public:
    SetBit2OfE()
            : InstructionSetBitOf8BitRegister(2,
                                              Register8Bit::E,
                                              opcodes::SET_BIT_2_OF_E) {}
};

class SetBit3OfE : public InstructionSetBitOf8BitRegister {
public:
    SetBit3OfE()
            : InstructionSetBitOf8BitRegister(3,
                                              Register8Bit::E,
                                              opcodes::SET_BIT_3_OF_E) {}
};

class SetBit4OfE : public InstructionSetBitOf8BitRegister {
public:
    SetBit4OfE()
            : InstructionSetBitOf8BitRegister(4,
                                              Register8Bit::E,
                                              opcodes::SET_BIT_4_OF_E) {}
};

class SetBit5OfE : public InstructionSetBitOf8BitRegister {
public:
    SetBit5OfE()
            : InstructionSetBitOf8BitRegister(5,
                                              Register8Bit::E,
                                              opcodes::SET_BIT_5_OF_E) {}
};

class SetBit6OfE : public InstructionSetBitOf8BitRegister {
public:
    SetBit6OfE()
            : InstructionSetBitOf8BitRegister(6,
                                              Register8Bit::E,
                                              opcodes::SET_BIT_6_OF_E) {}
};

class SetBit7OfE : public InstructionSetBitOf8BitRegister {
public:
    SetBit7OfE()
            : InstructionSetBitOf8BitRegister(7,
                                              Register8Bit::E,
                                              opcodes::SET_BIT_7_OF_E) {}
};

// Register H
class SetBit0OfH : public InstructionSetBitOf8BitRegister {
public:
    SetBit0OfH()
            : InstructionSetBitOf8BitRegister(0,
                                              Register8Bit::H,
                                              opcodes::SET_BIT_0_OF_H) {}
};

class SetBit1OfH : public InstructionSetBitOf8BitRegister {
public:
    SetBit1OfH()
            : InstructionSetBitOf8BitRegister(1,
                                              Register8Bit::H,
                                              opcodes::SET_BIT_1_OF_H) {}
};

class SetBit2OfH : public InstructionSetBitOf8BitRegister {
public:
    SetBit2OfH()
            : InstructionSetBitOf8BitRegister(2,
                                              Register8Bit::H,
                                              opcodes::SET_BIT_2_OF_H) {}
};

class SetBit3OfH : public InstructionSetBitOf8BitRegister {
public:
    SetBit3OfH()
            : InstructionSetBitOf8BitRegister(3,
                                              Register8Bit::H,
                                              opcodes::SET_BIT_3_OF_H) {}
};

class SetBit4OfH : public InstructionSetBitOf8BitRegister {
public:
    SetBit4OfH()
            : InstructionSetBitOf8BitRegister(4,
                                              Register8Bit::H,
                                              opcodes::SET_BIT_4_OF_H) {}
};

class SetBit5OfH : public InstructionSetBitOf8BitRegister {
public:
    SetBit5OfH()
            : InstructionSetBitOf8BitRegister(5,
                                              Register8Bit::H,
                                              opcodes::SET_BIT_5_OF_H) {}
};

class SetBit6OfH : public InstructionSetBitOf8BitRegister {
public:
    SetBit6OfH()
            : InstructionSetBitOf8BitRegister(6,
                                              Register8Bit::H,
                                              opcodes::SET_BIT_6_OF_H) {}
};

class SetBit7OfH : public InstructionSetBitOf8BitRegister {
public:
    SetBit7OfH()
            : InstructionSetBitOf8BitRegister(7,
                                              Register8Bit::H,
                                              opcodes::SET_BIT_7_OF_H) {}
};

// Register L
class SetBit0OfL : public InstructionSetBitOf8BitRegister {
public:
    SetBit0OfL()
            : InstructionSetBitOf8BitRegister(0,
                                              Register8Bit::L,
                                              opcodes::SET_BIT_0_OF_L) {}
};

class SetBit1OfL : public InstructionSetBitOf8BitRegister {
public:
    SetBit1OfL()
            : InstructionSetBitOf8BitRegister(1,
                                              Register8Bit::L,
                                              opcodes::SET_BIT_1_OF_L) {}
};

class SetBit2OfL : public InstructionSetBitOf8BitRegister {
public:
    SetBit2OfL()
            : InstructionSetBitOf8BitRegister(2,
                                              Register8Bit::L,
                                              opcodes::SET_BIT_2_OF_L) {}
};

class SetBit3OfL : public InstructionSetBitOf8BitRegister {
public:
    SetBit3OfL()
            : InstructionSetBitOf8BitRegister(3,
                                              Register8Bit::L,
                                              opcodes::SET_BIT_3_OF_L) {}
};

class SetBit4OfL : public InstructionSetBitOf8BitRegister {
public:
    SetBit4OfL()
            : InstructionSetBitOf8BitRegister(4,
                                              Register8Bit::L,
                                              opcodes::SET_BIT_4_OF_L) {}
};

class SetBit5OfL : public InstructionSetBitOf8BitRegister {
public:
    SetBit5OfL()
            : InstructionSetBitOf8BitRegister(5,
                                              Register8Bit::L,
                                              opcodes::SET_BIT_5_OF_L) {}
};

class SetBit6OfL : public InstructionSetBitOf8BitRegister {
public:
    SetBit6OfL()
            : InstructionSetBitOf8BitRegister(6,
                                              Register8Bit::L,
                                              opcodes::SET_BIT_6_OF_L) {}
};

class SetBit7OfL : public InstructionSetBitOf8BitRegister {
public:
    SetBit7OfL()
            : InstructionSetBitOf8BitRegister(7,
                                              Register8Bit::L,
                                              opcodes::SET_BIT_7_OF_L) {}
};

// Register ADDRESS_HL
class SetBit0OfAddressHL : public InstructionSetBitOf8BitRegister {
public:
    SetBit0OfAddressHL()
            : InstructionSetBitOf8BitRegister(0,
                                              Register8Bit::ADDRESS_HL,
                                              opcodes::SET_BIT_0_OF_ADDRESS_HL) {}
};

class SetBit1OfAddressHL : public InstructionSetBitOf8BitRegister {
public:
    SetBit1OfAddressHL()
            : InstructionSetBitOf8BitRegister(1,
                                              Register8Bit::ADDRESS_HL,
                                              opcodes::SET_BIT_1_OF_ADDRESS_HL) {}
};

class SetBit2OfAddressHL : public InstructionSetBitOf8BitRegister {
public:
    SetBit2OfAddressHL()
            : InstructionSetBitOf8BitRegister(2,
                                              Register8Bit::ADDRESS_HL,
                                              opcodes::SET_BIT_2_OF_ADDRESS_HL) {}
};

class SetBit3OfAddressHL : public InstructionSetBitOf8BitRegister {
public:
    SetBit3OfAddressHL()
            : InstructionSetBitOf8BitRegister(3,
                                              Register8Bit::ADDRESS_HL,
                                              opcodes::SET_BIT_3_OF_ADDRESS_HL) {}
};

class SetBit4OfAddressHL : public InstructionSetBitOf8BitRegister {
public:
    SetBit4OfAddressHL()
            : InstructionSetBitOf8BitRegister(4,
                                              Register8Bit::ADDRESS_HL,
                                              opcodes::SET_BIT_4_OF_ADDRESS_HL) {}
};

class SetBit5OfAddressHL : public InstructionSetBitOf8BitRegister {
public:
    SetBit5OfAddressHL()
            : InstructionSetBitOf8BitRegister(5,
                                              Register8Bit::ADDRESS_HL,
                                              opcodes::SET_BIT_5_OF_ADDRESS_HL) {}
};

class SetBit6OfAddressHL : public InstructionSetBitOf8BitRegister {
public:
    SetBit6OfAddressHL()
            : InstructionSetBitOf8BitRegister(6,
                                              Register8Bit::ADDRESS_HL,
                                              opcodes::SET_BIT_6_OF_ADDRESS_HL) {}
};

class SetBit7OfAddressHL : public InstructionSetBitOf8BitRegister {
public:
    SetBit7OfAddressHL()
            : InstructionSetBitOf8BitRegister(7,
                                              Register8Bit::ADDRESS_HL,
                                              opcodes::SET_BIT_7_OF_ADDRESS_HL) {}
};

// Register A
class SetBit0OfA : public InstructionSetBitOf8BitRegister {
public:
    SetBit0OfA()
            : InstructionSetBitOf8BitRegister(0,
                                              Register8Bit::A,
                                              opcodes::SET_BIT_0_OF_A) {}
};

class SetBit1OfA : public InstructionSetBitOf8BitRegister {
public:
    SetBit1OfA()
            : InstructionSetBitOf8BitRegister(1,
                                              Register8Bit::A,
                                              opcodes::SET_BIT_1_OF_A) {}
};

class SetBit2OfA : public InstructionSetBitOf8BitRegister {
public:
    SetBit2OfA()
            : InstructionSetBitOf8BitRegister(2,
                                              Register8Bit::A,
                                              opcodes::SET_BIT_2_OF_A) {}
};

class SetBit3OfA : public InstructionSetBitOf8BitRegister {
public:
    SetBit3OfA()
            : InstructionSetBitOf8BitRegister(3,
                                              Register8Bit::A,
                                              opcodes::SET_BIT_3_OF_A) {}
};

class SetBit4OfA : public InstructionSetBitOf8BitRegister {
public:
    SetBit4OfA()
            : InstructionSetBitOf8BitRegister(4,
                                              Register8Bit::A,
                                              opcodes::SET_BIT_4_OF_A) {}
};

class SetBit5OfA : public InstructionSetBitOf8BitRegister {
public:
    SetBit5OfA()
            : InstructionSetBitOf8BitRegister(5,
                                              Register8Bit::A,
                                              opcodes::SET_BIT_5_OF_A) {}
};

class SetBit6OfA : public InstructionSetBitOf8BitRegister {
public:
    SetBit6OfA()
            : InstructionSetBitOf8BitRegister(6,
                                              Register8Bit::A,
                                              opcodes::SET_BIT_6_OF_A) {}
};

class SetBit7OfA : public InstructionSetBitOf8BitRegister {
public:
    SetBit7OfA()
            : InstructionSetBitOf8BitRegister(7,
                                              Register8Bit::A,
                                              opcodes::SET_BIT_7_OF_A) {}
};

#endif //GAMEBOY_DISASSEMBLE_INSTRUCTIONS_SET_H
