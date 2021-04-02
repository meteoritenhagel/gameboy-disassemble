#ifndef GAMEBOY_DISASSEMBLE_INSTRUCTIONS_INCREMENT_DECREMENT_H
#define GAMEBOY_DISASSEMBLE_INSTRUCTIONS_INCREMENT_DECREMENT_H

#include "baseinstruction.h"

class IncrementRegister : public BaseInstruction {
public:
    IncrementRegister(const Register &reg)
            : BaseInstruction("INC " + to_string(reg),
                              determine_opcode(reg)),
              _register(reg) {}

private:
    Opcode determine_opcode(const Register &reg) const {
        if (is_register_8_bit(reg)) {
            switch(std::get<Register8Bit>(reg)) {
                case Register8Bit::B:          return opcodes::INCREMENT_B;
                case Register8Bit::C:          return opcodes::INCREMENT_C;
                case Register8Bit::D:          return opcodes::INCREMENT_D;
                case Register8Bit::E:          return opcodes::INCREMENT_E;
                case Register8Bit::H:          return opcodes::INCREMENT_H;
                case Register8Bit::L:          return opcodes::INCREMENT_L;
                case Register8Bit::ADDRESS_HL: return opcodes::INCREMENT_ADDRESS_HL;
                case Register8Bit::A:          return opcodes::INCREMENT_A;
                default: break;
            }
        } else if (is_register_16_bit(reg)) {
            switch(std::get<Register16Bit>(reg)) {
                case Register16Bit::BC: return opcodes::INCREMENT_BC;
                case Register16Bit::DE: return opcodes::INCREMENT_DE;
                case Register16Bit::HL: return opcodes::INCREMENT_HL;
                case Register16Bit::SP: return opcodes::INCREMENT_SP;
                default:                break;
            }
        }

        return opcodes::INVALID_OPCODE;
    }

    const Register _register;
};

class DecrementRegister : public BaseInstruction {
public:
    DecrementRegister(const Register &reg)
            : BaseInstruction("DEC " + to_string(reg),
                              determine_opcode(reg)),
              _register(reg) {}

private:
    Opcode determine_opcode(const Register &reg) const {
        if (is_register_8_bit(reg)) {
            switch(to_register_8_bit(reg)) {
                case Register8Bit::B:          return opcodes::DECREMENT_B;
                case Register8Bit::C:          return opcodes::DECREMENT_C;
                case Register8Bit::D:          return opcodes::DECREMENT_D;
                case Register8Bit::E:          return opcodes::DECREMENT_E;
                case Register8Bit::H:          return opcodes::DECREMENT_H;
                case Register8Bit::L:          return opcodes::DECREMENT_L;
                case Register8Bit::ADDRESS_HL: return opcodes::DECREMENT_ADDRESS_HL;
                case Register8Bit::A:          return opcodes::DECREMENT_A;
                default:                       break;
            }
        } else if (is_register_16_bit(reg)) {
            switch(to_register_16_bit(reg)) {
                case Register16Bit::BC: return opcodes::DECREMENT_BC;
                case Register16Bit::DE: return opcodes::DECREMENT_DE;
                case Register16Bit::HL: return opcodes::DECREMENT_HL;
                case Register16Bit::SP: return opcodes::DECREMENT_SP;
                default:                break;
            }
        }

        return opcodes::INVALID_OPCODE;
    }

    const Register _register;
};
#endif //GAMEBOY_DISASSEMBLE_INSTRUCTIONS_INCREMENT_DECREMENT_H
