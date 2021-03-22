#ifndef GAMEBOY_DISASSEMBLE_INSTRUCTIONS_BIT_COMPLEMENT_H
#define GAMEBOY_DISASSEMBLE_INSTRUCTIONS_BIT_COMPLEMENT_H

#include "interface.h"

class BitOf8BitRegisterComplementIntoZero : public Instruction {
public:
    BitOf8BitRegisterComplementIntoZero(const uint8_t bitIndex, const Register8Bit reg)
            : Instruction("BIT " + to_string_dec(bitIndex) + ", " + to_string(reg), determine_opcode(bitIndex, reg)),
              _bitIndex(bitIndex),
              _register(reg) {}

private:
    Opcode determine_opcode(const uint8_t bitIndex, const Register8Bit reg) const {
        switch (reg) {
            case Register8Bit::B: switch (bitIndex) {
                case 0: return opcodes::BIT_0_OF_B_COMPLEMENT_INTO_ZERO;
                case 1: return opcodes::BIT_1_OF_B_COMPLEMENT_INTO_ZERO;
                case 2: return opcodes::BIT_2_OF_B_COMPLEMENT_INTO_ZERO;
                case 3: return opcodes::BIT_3_OF_B_COMPLEMENT_INTO_ZERO;
                case 4: return opcodes::BIT_4_OF_B_COMPLEMENT_INTO_ZERO;
                case 5: return opcodes::BIT_5_OF_B_COMPLEMENT_INTO_ZERO;
                case 6: return opcodes::BIT_6_OF_B_COMPLEMENT_INTO_ZERO;
                case 7: return opcodes::BIT_7_OF_B_COMPLEMENT_INTO_ZERO;
                default: break;
            }
            case Register8Bit::C: switch (bitIndex) {
                case 0: return opcodes::BIT_0_OF_C_COMPLEMENT_INTO_ZERO;
                case 1: return opcodes::BIT_1_OF_C_COMPLEMENT_INTO_ZERO;
                case 2: return opcodes::BIT_2_OF_C_COMPLEMENT_INTO_ZERO;
                case 3: return opcodes::BIT_3_OF_C_COMPLEMENT_INTO_ZERO;
                case 4: return opcodes::BIT_4_OF_C_COMPLEMENT_INTO_ZERO;
                case 5: return opcodes::BIT_5_OF_C_COMPLEMENT_INTO_ZERO;
                case 6: return opcodes::BIT_6_OF_C_COMPLEMENT_INTO_ZERO;
                case 7: return opcodes::BIT_7_OF_C_COMPLEMENT_INTO_ZERO;
                default: break;
            }
            case Register8Bit::D: switch (bitIndex) {
                case 0: return opcodes::BIT_0_OF_D_COMPLEMENT_INTO_ZERO;
                case 1: return opcodes::BIT_1_OF_D_COMPLEMENT_INTO_ZERO;
                case 2: return opcodes::BIT_2_OF_D_COMPLEMENT_INTO_ZERO;
                case 3: return opcodes::BIT_3_OF_D_COMPLEMENT_INTO_ZERO;
                case 4: return opcodes::BIT_4_OF_D_COMPLEMENT_INTO_ZERO;
                case 5: return opcodes::BIT_5_OF_D_COMPLEMENT_INTO_ZERO;
                case 6: return opcodes::BIT_6_OF_D_COMPLEMENT_INTO_ZERO;
                case 7: return opcodes::BIT_7_OF_D_COMPLEMENT_INTO_ZERO;
                default: break;
            }
            case Register8Bit::E: switch (bitIndex) {
                case 0: return opcodes::BIT_0_OF_E_COMPLEMENT_INTO_ZERO;
                case 1: return opcodes::BIT_1_OF_E_COMPLEMENT_INTO_ZERO;
                case 2: return opcodes::BIT_2_OF_E_COMPLEMENT_INTO_ZERO;
                case 3: return opcodes::BIT_3_OF_E_COMPLEMENT_INTO_ZERO;
                case 4: return opcodes::BIT_4_OF_E_COMPLEMENT_INTO_ZERO;
                case 5: return opcodes::BIT_5_OF_E_COMPLEMENT_INTO_ZERO;
                case 6: return opcodes::BIT_6_OF_E_COMPLEMENT_INTO_ZERO;
                case 7: return opcodes::BIT_7_OF_E_COMPLEMENT_INTO_ZERO;
                default: break;
            }
            case Register8Bit::H: switch (bitIndex) {
                case 0: return opcodes::BIT_0_OF_H_COMPLEMENT_INTO_ZERO;
                case 1: return opcodes::BIT_1_OF_H_COMPLEMENT_INTO_ZERO;
                case 2: return opcodes::BIT_2_OF_H_COMPLEMENT_INTO_ZERO;
                case 3: return opcodes::BIT_3_OF_H_COMPLEMENT_INTO_ZERO;
                case 4: return opcodes::BIT_4_OF_H_COMPLEMENT_INTO_ZERO;
                case 5: return opcodes::BIT_5_OF_H_COMPLEMENT_INTO_ZERO;
                case 6: return opcodes::BIT_6_OF_H_COMPLEMENT_INTO_ZERO;
                case 7: return opcodes::BIT_7_OF_H_COMPLEMENT_INTO_ZERO;
                default: break;
            }
            case Register8Bit::L: switch (bitIndex) {
                case 0: return opcodes::BIT_0_OF_L_COMPLEMENT_INTO_ZERO;
                case 1: return opcodes::BIT_1_OF_L_COMPLEMENT_INTO_ZERO;
                case 2: return opcodes::BIT_2_OF_L_COMPLEMENT_INTO_ZERO;
                case 3: return opcodes::BIT_3_OF_L_COMPLEMENT_INTO_ZERO;
                case 4: return opcodes::BIT_4_OF_L_COMPLEMENT_INTO_ZERO;
                case 5: return opcodes::BIT_5_OF_L_COMPLEMENT_INTO_ZERO;
                case 6: return opcodes::BIT_6_OF_L_COMPLEMENT_INTO_ZERO;
                case 7: return opcodes::BIT_7_OF_L_COMPLEMENT_INTO_ZERO;
                default: break;
            }
            case Register8Bit::ADDRESS_HL: switch (bitIndex) {
                case 0: return opcodes::BIT_0_OF_ADDRESS_HL_COMPLEMENT_INTO_ZERO;
                case 1: return opcodes::BIT_1_OF_ADDRESS_HL_COMPLEMENT_INTO_ZERO;
                case 2: return opcodes::BIT_2_OF_ADDRESS_HL_COMPLEMENT_INTO_ZERO;
                case 3: return opcodes::BIT_3_OF_ADDRESS_HL_COMPLEMENT_INTO_ZERO;
                case 4: return opcodes::BIT_4_OF_ADDRESS_HL_COMPLEMENT_INTO_ZERO;
                case 5: return opcodes::BIT_5_OF_ADDRESS_HL_COMPLEMENT_INTO_ZERO;
                case 6: return opcodes::BIT_6_OF_ADDRESS_HL_COMPLEMENT_INTO_ZERO;
                case 7: return opcodes::BIT_7_OF_ADDRESS_HL_COMPLEMENT_INTO_ZERO;
                default: break;
            }
            case Register8Bit::A: switch (bitIndex) {
                case 0: return opcodes::BIT_0_OF_A_COMPLEMENT_INTO_ZERO;
                case 1: return opcodes::BIT_1_OF_A_COMPLEMENT_INTO_ZERO;
                case 2: return opcodes::BIT_2_OF_A_COMPLEMENT_INTO_ZERO;
                case 3: return opcodes::BIT_3_OF_A_COMPLEMENT_INTO_ZERO;
                case 4: return opcodes::BIT_4_OF_A_COMPLEMENT_INTO_ZERO;
                case 5: return opcodes::BIT_5_OF_A_COMPLEMENT_INTO_ZERO;
                case 6: return opcodes::BIT_6_OF_A_COMPLEMENT_INTO_ZERO;
                case 7: return opcodes::BIT_7_OF_A_COMPLEMENT_INTO_ZERO;
                default: break;
            }
            default: break;
        }
        return opcodes::INVALID_OPCODE;
    }

    const uint8_t _bitIndex;
    const Register8Bit _register;
};

#endif //GAMEBOY_DISASSEMBLE_INSTRUCTIONS_BIT_COMPLEMENT_H
