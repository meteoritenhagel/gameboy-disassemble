#ifndef GAMEBOY_DISASSEMBLE_INSTRUCTIONS_ROTATION_H
#define GAMEBOY_DISASSEMBLE_INSTRUCTIONS_ROTATION_H

#include "baseinstruction.h"

class RotateRight8BitRegister : public BaseInstruction {
public:
    RotateRight8BitRegister(const Register8Bit reg = {})
            : BaseInstruction("RR " + to_string(reg),
                              determine_opcode(reg)),
              _register(reg) {}

private:
    Opcode determine_opcode(const Register8Bit reg) const {
        switch (reg) {
            case Register8Bit::B:          return opcodes::ROTATE_RIGHT_B;
            case Register8Bit::C:          return opcodes::ROTATE_RIGHT_C;
            case Register8Bit::D:          return opcodes::ROTATE_RIGHT_D;
            case Register8Bit::E:          return opcodes::ROTATE_RIGHT_E;
            case Register8Bit::H:          return opcodes::ROTATE_RIGHT_H;
            case Register8Bit::L:          return opcodes::ROTATE_RIGHT_L;
            case Register8Bit::ADDRESS_HL: return opcodes::ROTATE_RIGHT_ADDRESS_HL;
            case Register8Bit::A:          return opcodes::ROTATE_RIGHT_A;
            default:                       return opcodes::INVALID_OPCODE;
        }
    }

    const Register8Bit _register;
};

class RotateLeft8BitRegister : public BaseInstruction {
public:
    RotateLeft8BitRegister(const Register8Bit reg = {})
            : BaseInstruction("RL " + to_string(reg),
                              determine_opcode(reg)),
              _register(reg) {}

private:
    Opcode determine_opcode(const Register8Bit reg) const {
        switch (reg) {
            case Register8Bit::B:          return opcodes::ROTATE_LEFT_B;
            case Register8Bit::C:          return opcodes::ROTATE_LEFT_C;
            case Register8Bit::D:          return opcodes::ROTATE_LEFT_D;
            case Register8Bit::E:          return opcodes::ROTATE_LEFT_E;
            case Register8Bit::H:          return opcodes::ROTATE_LEFT_H;
            case Register8Bit::L:          return opcodes::ROTATE_LEFT_L;
            case Register8Bit::ADDRESS_HL: return opcodes::ROTATE_LEFT_ADDRESS_HL;
            case Register8Bit::A:          return opcodes::ROTATE_LEFT_A;
            default:                       return opcodes::INVALID_OPCODE;
        }
    }

    const Register8Bit _register;
};

class RotateRightCircular8BitRegister : public BaseInstruction {
public:
    RotateRightCircular8BitRegister(const Register8Bit reg = {})
            : BaseInstruction("RRC " + to_string(reg),
                              determine_opcode(reg)),
              _register(reg) {}

private:
    Opcode determine_opcode(const Register8Bit reg) const {
        switch (reg) {
            case Register8Bit::B:          return opcodes::ROTATE_RIGHT_CIRCULAR_B;
            case Register8Bit::C:          return opcodes::ROTATE_RIGHT_CIRCULAR_C;
            case Register8Bit::D:          return opcodes::ROTATE_RIGHT_CIRCULAR_D;
            case Register8Bit::E:          return opcodes::ROTATE_RIGHT_CIRCULAR_E;
            case Register8Bit::H:          return opcodes::ROTATE_RIGHT_CIRCULAR_H;
            case Register8Bit::L:          return opcodes::ROTATE_RIGHT_CIRCULAR_L;
            case Register8Bit::ADDRESS_HL: return opcodes::ROTATE_RIGHT_CIRCULAR_ADDRESS_HL;
            case Register8Bit::A:          return opcodes::ROTATE_RIGHT_CIRCULAR_A;
            default:                       return opcodes::INVALID_OPCODE;
        }
    }

    const Register8Bit _register;
};

class RotateLeftCircular8BitRegister : public BaseInstruction {
public:
    RotateLeftCircular8BitRegister(const Register8Bit reg = {})
            : BaseInstruction("RLC " + to_string(reg),
                              determine_opcode(reg)),
              _register(reg) {}

private:
    Opcode determine_opcode(const Register8Bit reg) const {
        switch (reg) {
            case Register8Bit::B:          return opcodes::ROTATE_LEFT_CIRCULAR_B;
            case Register8Bit::C:          return opcodes::ROTATE_LEFT_CIRCULAR_C;
            case Register8Bit::D:          return opcodes::ROTATE_LEFT_CIRCULAR_D;
            case Register8Bit::E:          return opcodes::ROTATE_LEFT_CIRCULAR_E;
            case Register8Bit::H:          return opcodes::ROTATE_LEFT_CIRCULAR_H;
            case Register8Bit::L:          return opcodes::ROTATE_LEFT_CIRCULAR_L;
            case Register8Bit::ADDRESS_HL: return opcodes::ROTATE_LEFT_CIRCULAR_ADDRESS_HL;
            case Register8Bit::A:          return opcodes::ROTATE_LEFT_CIRCULAR_A;
            default:                       return opcodes::INVALID_OPCODE;
        }
    }

    const Register8Bit _register;
};

// Rotate A and clear Zero Flag
class RotateLeftAAndClearZero : public BaseInstruction {
public:
    RotateLeftAAndClearZero()
            : BaseInstruction("RLA",
                              opcodes::ROTATE_LEFT_A_AND_CLEAR_ZERO) {}
};

class RotateRightAAndClearZero : public BaseInstruction {
public:
    RotateRightAAndClearZero()
            : BaseInstruction("RRA",
                              opcodes::ROTATE_RIGHT_A_AND_CLEAR_ZERO) {}
};

class RotateLeftCircularAAndClearZero : public BaseInstruction {
public:
    RotateLeftCircularAAndClearZero()
            : BaseInstruction("RLCA",
                              opcodes::ROTATE_LEFT_CIRCULAR_A_AND_CLEAR_ZERO) {}
};

class RotateRightCircularAAndClearZero : public BaseInstruction {
public:
    RotateRightCircularAAndClearZero()
            : BaseInstruction("RRCA",
                              opcodes::ROTATE_RIGHT_CIRCULAR_A_AND_CLEAR_ZERO) {}
};

#endif //GAMEBOY_DISASSEMBLE_INSTRUCTIONS_ROTATION_H
