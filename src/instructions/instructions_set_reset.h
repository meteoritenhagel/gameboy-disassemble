#ifndef GAMEBOY_DISASSEMBLE_INSTRUCTIONS_SET_RESET_H
#define GAMEBOY_DISASSEMBLE_INSTRUCTIONS_SET_RESET_H

#include "interface.h"

class SetBitOf8BitRegister : public Instruction {
public:
    SetBitOf8BitRegister(const uint8_t bitIndex, const Register8Bit reg)
            : Instruction("SET " + to_string_dec(bitIndex) + ", " + to_string(reg),
                          determine_opcode(bitIndex, reg)),
              _bitIndex(bitIndex),
              _register(reg) {}

private:
    Opcode determine_opcode(const uint8_t bitIndex, const Register8Bit reg) const {
        switch (reg) {
            case Register8Bit::B: switch (bitIndex) {
                    case 0: return opcodes::SET_BIT_0_OF_B;
                    case 1: return opcodes::SET_BIT_1_OF_B;
                    case 2: return opcodes::SET_BIT_2_OF_B;
                    case 3: return opcodes::SET_BIT_3_OF_B;
                    case 4: return opcodes::SET_BIT_4_OF_B;
                    case 5: return opcodes::SET_BIT_5_OF_B;
                    case 6: return opcodes::SET_BIT_6_OF_B;
                    case 7: return opcodes::SET_BIT_7_OF_B;
                    default: break;
                }
            case Register8Bit::C: switch (bitIndex) {
                    case 0: return opcodes::SET_BIT_0_OF_C;
                    case 1: return opcodes::SET_BIT_1_OF_C;
                    case 2: return opcodes::SET_BIT_2_OF_C;
                    case 3: return opcodes::SET_BIT_3_OF_C;
                    case 4: return opcodes::SET_BIT_4_OF_C;
                    case 5: return opcodes::SET_BIT_5_OF_C;
                    case 6: return opcodes::SET_BIT_6_OF_C;
                    case 7: return opcodes::SET_BIT_7_OF_C;
                    default: break;
                }
            case Register8Bit::D: switch (bitIndex) {
                    case 0: return opcodes::SET_BIT_0_OF_D;
                    case 1: return opcodes::SET_BIT_1_OF_D;
                    case 2: return opcodes::SET_BIT_2_OF_D;
                    case 3: return opcodes::SET_BIT_3_OF_D;
                    case 4: return opcodes::SET_BIT_4_OF_D;
                    case 5: return opcodes::SET_BIT_5_OF_D;
                    case 6: return opcodes::SET_BIT_6_OF_D;
                    case 7: return opcodes::SET_BIT_7_OF_D;
                    default: break;
                }
            case Register8Bit::E: switch (bitIndex) {
                    case 0: return opcodes::SET_BIT_0_OF_E;
                    case 1: return opcodes::SET_BIT_1_OF_E;
                    case 2: return opcodes::SET_BIT_2_OF_E;
                    case 3: return opcodes::SET_BIT_3_OF_E;
                    case 4: return opcodes::SET_BIT_4_OF_E;
                    case 5: return opcodes::SET_BIT_5_OF_E;
                    case 6: return opcodes::SET_BIT_6_OF_E;
                    case 7: return opcodes::SET_BIT_7_OF_E;
                    default: break;
                }
            case Register8Bit::H: switch (bitIndex) {
                    case 0: return opcodes::SET_BIT_0_OF_H;
                    case 1: return opcodes::SET_BIT_1_OF_H;
                    case 2: return opcodes::SET_BIT_2_OF_H;
                    case 3: return opcodes::SET_BIT_3_OF_H;
                    case 4: return opcodes::SET_BIT_4_OF_H;
                    case 5: return opcodes::SET_BIT_5_OF_H;
                    case 6: return opcodes::SET_BIT_6_OF_H;
                    case 7: return opcodes::SET_BIT_7_OF_H;
                    default: break;
                }
            case Register8Bit::L: switch (bitIndex) {
                    case 0: return opcodes::SET_BIT_0_OF_L;
                    case 1: return opcodes::SET_BIT_1_OF_L;
                    case 2: return opcodes::SET_BIT_2_OF_L;
                    case 3: return opcodes::SET_BIT_3_OF_L;
                    case 4: return opcodes::SET_BIT_4_OF_L;
                    case 5: return opcodes::SET_BIT_5_OF_L;
                    case 6: return opcodes::SET_BIT_6_OF_L;
                    case 7: return opcodes::SET_BIT_7_OF_L;
                    default: break;
                }
            case Register8Bit::ADDRESS_HL: switch (bitIndex) {
                    case 0: return opcodes::SET_BIT_0_OF_ADDRESS_HL;
                    case 1: return opcodes::SET_BIT_1_OF_ADDRESS_HL;
                    case 2: return opcodes::SET_BIT_2_OF_ADDRESS_HL;
                    case 3: return opcodes::SET_BIT_3_OF_ADDRESS_HL;
                    case 4: return opcodes::SET_BIT_4_OF_ADDRESS_HL;
                    case 5: return opcodes::SET_BIT_5_OF_ADDRESS_HL;
                    case 6: return opcodes::SET_BIT_6_OF_ADDRESS_HL;
                    case 7: return opcodes::SET_BIT_7_OF_ADDRESS_HL;
                    default: break;
                }
            case Register8Bit::A: switch (bitIndex) {
                    case 0: return opcodes::SET_BIT_0_OF_A;
                    case 1: return opcodes::SET_BIT_1_OF_A;
                    case 2: return opcodes::SET_BIT_2_OF_A;
                    case 3: return opcodes::SET_BIT_3_OF_A;
                    case 4: return opcodes::SET_BIT_4_OF_A;
                    case 5: return opcodes::SET_BIT_5_OF_A;
                    case 6: return opcodes::SET_BIT_6_OF_A;
                    case 7: return opcodes::SET_BIT_7_OF_A;
                    default: break;
                }
            default: break;
        }
        return opcodes::INVALID_OPCODE;
    }

    const uint8_t _bitIndex;
    const Register8Bit _register;
};


class ResetBitOf8BitRegister : public Instruction {
public:
    ResetBitOf8BitRegister(const uint8_t bitIndex, const Register8Bit reg)
            : Instruction("RES " + to_string_dec(bitIndex) + ", " + to_string(reg),
                          determine_opcode(bitIndex, reg)),
              _bitIndex(bitIndex),
              _register(reg) {}

private:
    Opcode determine_opcode(const uint8_t bitIndex, const Register8Bit reg) const {
        switch (reg) {
                case Register8Bit::B: switch (bitIndex) {
                    case 0: return opcodes::RESET_BIT_0_OF_B;
                    case 1: return opcodes::RESET_BIT_1_OF_B;
                    case 2: return opcodes::RESET_BIT_2_OF_B;
                    case 3: return opcodes::RESET_BIT_3_OF_B;
                    case 4: return opcodes::RESET_BIT_4_OF_B;
                    case 5: return opcodes::RESET_BIT_5_OF_B;
                    case 6: return opcodes::RESET_BIT_6_OF_B;
                    case 7: return opcodes::RESET_BIT_7_OF_B;
                    default: break;
                }
            case Register8Bit::C: switch (bitIndex) {
                    case 0: return opcodes::RESET_BIT_0_OF_C;
                    case 1: return opcodes::RESET_BIT_1_OF_C;
                    case 2: return opcodes::RESET_BIT_2_OF_C;
                    case 3: return opcodes::RESET_BIT_3_OF_C;
                    case 4: return opcodes::RESET_BIT_4_OF_C;
                    case 5: return opcodes::RESET_BIT_5_OF_C;
                    case 6: return opcodes::RESET_BIT_6_OF_C;
                    case 7: return opcodes::RESET_BIT_7_OF_C;
                    default: break;
                }
            case Register8Bit::D: switch (bitIndex) {
                    case 0: return opcodes::RESET_BIT_0_OF_D;
                    case 1: return opcodes::RESET_BIT_1_OF_D;
                    case 2: return opcodes::RESET_BIT_2_OF_D;
                    case 3: return opcodes::RESET_BIT_3_OF_D;
                    case 4: return opcodes::RESET_BIT_4_OF_D;
                    case 5: return opcodes::RESET_BIT_5_OF_D;
                    case 6: return opcodes::RESET_BIT_6_OF_D;
                    case 7: return opcodes::RESET_BIT_7_OF_D;
                    default: break;
                }
            case Register8Bit::E: switch (bitIndex) {
                    case 0: return opcodes::RESET_BIT_0_OF_E;
                    case 1: return opcodes::RESET_BIT_1_OF_E;
                    case 2: return opcodes::RESET_BIT_2_OF_E;
                    case 3: return opcodes::RESET_BIT_3_OF_E;
                    case 4: return opcodes::RESET_BIT_4_OF_E;
                    case 5: return opcodes::RESET_BIT_5_OF_E;
                    case 6: return opcodes::RESET_BIT_6_OF_E;
                    case 7: return opcodes::RESET_BIT_7_OF_E;
                    default: break;
                }
            case Register8Bit::H: switch (bitIndex) {
                    case 0: return opcodes::RESET_BIT_0_OF_H;
                    case 1: return opcodes::RESET_BIT_1_OF_H;
                    case 2: return opcodes::RESET_BIT_2_OF_H;
                    case 3: return opcodes::RESET_BIT_3_OF_H;
                    case 4: return opcodes::RESET_BIT_4_OF_H;
                    case 5: return opcodes::RESET_BIT_5_OF_H;
                    case 6: return opcodes::RESET_BIT_6_OF_H;
                    case 7: return opcodes::RESET_BIT_7_OF_H;
                    default: break;
                }
            case Register8Bit::L: switch (bitIndex) {
                    case 0: return opcodes::RESET_BIT_0_OF_L;
                    case 1: return opcodes::RESET_BIT_1_OF_L;
                    case 2: return opcodes::RESET_BIT_2_OF_L;
                    case 3: return opcodes::RESET_BIT_3_OF_L;
                    case 4: return opcodes::RESET_BIT_4_OF_L;
                    case 5: return opcodes::RESET_BIT_5_OF_L;
                    case 6: return opcodes::RESET_BIT_6_OF_L;
                    case 7: return opcodes::RESET_BIT_7_OF_L;
                    default: break;
                }
            case Register8Bit::ADDRESS_HL: switch (bitIndex) {
                    case 0: return opcodes::RESET_BIT_0_OF_ADDRESS_HL;
                    case 1: return opcodes::RESET_BIT_1_OF_ADDRESS_HL;
                    case 2: return opcodes::RESET_BIT_2_OF_ADDRESS_HL;
                    case 3: return opcodes::RESET_BIT_3_OF_ADDRESS_HL;
                    case 4: return opcodes::RESET_BIT_4_OF_ADDRESS_HL;
                    case 5: return opcodes::RESET_BIT_5_OF_ADDRESS_HL;
                    case 6: return opcodes::RESET_BIT_6_OF_ADDRESS_HL;
                    case 7: return opcodes::RESET_BIT_7_OF_ADDRESS_HL;
                    default: break;
                }
            case Register8Bit::A: switch (bitIndex) {
                    case 0: return opcodes::RESET_BIT_0_OF_A;
                    case 1: return opcodes::RESET_BIT_1_OF_A;
                    case 2: return opcodes::RESET_BIT_2_OF_A;
                    case 3: return opcodes::RESET_BIT_3_OF_A;
                    case 4: return opcodes::RESET_BIT_4_OF_A;
                    case 5: return opcodes::RESET_BIT_5_OF_A;
                    case 6: return opcodes::RESET_BIT_6_OF_A;
                    case 7: return opcodes::RESET_BIT_7_OF_A;
                    default: break;
                }
            default: break;
        }
        return opcodes::INVALID_OPCODE;
    }

    const uint8_t _bitIndex;
    const Register8Bit _register;
};

#endif //GAMEBOY_DISASSEMBLE_INSTRUCTIONS_SET_RESET_H
