#ifndef GAMEBOY_DISASSEMBLE_INSTRUCTIONS_SHIFT_SWAP_H
#define GAMEBOY_DISASSEMBLE_INSTRUCTIONS_SHIFT_SWAP_H

#include "interface.h"

class ShiftLeftArithmetical8BitRegister : public Instruction {
public:
    ShiftLeftArithmetical8BitRegister(const Register8Bit reg)
            : Instruction("SLA " + to_string(reg),
                          determine_opcode(reg)),
              _register(reg) {}

private:
    Opcode determine_opcode(const Register8Bit reg) const {
        switch (reg) {
            case Register8Bit::B:          return opcodes::SHIFT_LEFT_ARITHMETICAL_B;
            case Register8Bit::C:          return opcodes::SHIFT_LEFT_ARITHMETICAL_C;
            case Register8Bit::D:          return opcodes::SHIFT_LEFT_ARITHMETICAL_D;
            case Register8Bit::E:          return opcodes::SHIFT_LEFT_ARITHMETICAL_E;
            case Register8Bit::H:          return opcodes::SHIFT_LEFT_ARITHMETICAL_H;
            case Register8Bit::L:          return opcodes::SHIFT_LEFT_ARITHMETICAL_L;
            case Register8Bit::ADDRESS_HL: return opcodes::SHIFT_LEFT_ARITHMETICAL_ADDRESS_HL;
            case Register8Bit::A:          return opcodes::SHIFT_LEFT_ARITHMETICAL_A;
            default:                       return opcodes::INVALID_OPCODE;
        }
    }

    const Register8Bit _register;
};

class ShiftRightArithmetical8BitRegister : public Instruction {
public:
    ShiftRightArithmetical8BitRegister(const Register8Bit reg)
            : Instruction("SRA " + to_string(reg),
                          determine_opcode(reg)),
              _register(reg) {}

private:
    Opcode determine_opcode(const Register8Bit reg) const {
        switch (reg) {
            case Register8Bit::B:          return opcodes::SHIFT_RIGHT_ARITHMETICAL_B;
            case Register8Bit::C:          return opcodes::SHIFT_RIGHT_ARITHMETICAL_C;
            case Register8Bit::D:          return opcodes::SHIFT_RIGHT_ARITHMETICAL_D;
            case Register8Bit::E:          return opcodes::SHIFT_RIGHT_ARITHMETICAL_E;
            case Register8Bit::H:          return opcodes::SHIFT_RIGHT_ARITHMETICAL_H;
            case Register8Bit::L:          return opcodes::SHIFT_RIGHT_ARITHMETICAL_L;
            case Register8Bit::ADDRESS_HL: return opcodes::SHIFT_RIGHT_ARITHMETICAL_ADDRESS_HL;
            case Register8Bit::A:          return opcodes::SHIFT_RIGHT_ARITHMETICAL_A;
            default:                       return opcodes::INVALID_OPCODE;
        }
    }

    const Register8Bit _register;
};

class ShiftRightLogical8BitRegister : public Instruction {
public:
    ShiftRightLogical8BitRegister(const Register8Bit reg)
            : Instruction("SRL " + to_string(reg),
                          determine_opcode(reg)),
              _register(reg) {}

private:
    Opcode determine_opcode(const Register8Bit reg) const {
        switch (reg) {
            case Register8Bit::B:          return opcodes::SHIFT_RIGHT_LOGICAL_B;
            case Register8Bit::C:          return opcodes::SHIFT_RIGHT_LOGICAL_C;
            case Register8Bit::D:          return opcodes::SHIFT_RIGHT_LOGICAL_D;
            case Register8Bit::E:          return opcodes::SHIFT_RIGHT_LOGICAL_E;
            case Register8Bit::H:          return opcodes::SHIFT_RIGHT_LOGICAL_H;
            case Register8Bit::L:          return opcodes::SHIFT_RIGHT_LOGICAL_L;
            case Register8Bit::ADDRESS_HL: return opcodes::SHIFT_RIGHT_LOGICAL_ADDRESS_HL;
            case Register8Bit::A:          return opcodes::SHIFT_RIGHT_LOGICAL_A;
            default:                       return opcodes::INVALID_OPCODE;
        }
    }

    const Register8Bit _register;
};

class Swap8BitRegister : public Instruction {
public:
    Swap8BitRegister(const Register8Bit reg)
            : Instruction("SWAP " + to_string(reg),
                          determine_opcode(reg)),
              _register(reg) {}

private:
    Opcode determine_opcode(const Register8Bit reg) const {
        switch (reg) {
            case Register8Bit::B:          return opcodes::SWAP_B;
            case Register8Bit::C:          return opcodes::SWAP_C;
            case Register8Bit::D:          return opcodes::SWAP_D;
            case Register8Bit::E:          return opcodes::SWAP_E;
            case Register8Bit::H:          return opcodes::SWAP_H;
            case Register8Bit::L:          return opcodes::SWAP_L;
            case Register8Bit::ADDRESS_HL: return opcodes::SWAP_ADDRESS_HL;
            case Register8Bit::A:          return opcodes::SWAP_A;
            default:                       return opcodes::INVALID_OPCODE;
        }
    }

    const Register8Bit _register;
};

#endif //GAMEBOY_DISASSEMBLE_INSTRUCTIONS_SHIFT_SWAP_H
