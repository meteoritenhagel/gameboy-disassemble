//
// Created by tristan on 16.02.21.
//

#ifndef GAMEBOY_DISASSEMBLE_INSTRUCTIONS_CONSTANTS_H
#define GAMEBOY_DISASSEMBLE_INSTRUCTIONS_CONSTANTS_H

#include <cstdint>
#include <memory>
#include <vector>

using bytestring = std::vector<uint8_t>;
using Opcode = uint16_t; // must be literal type, so that it can be used with switch statements

namespace opcodes
{
    constexpr Opcode NOP{0x00};
    constexpr Opcode LOAD_IMMEDIATE_INTO_BC{0x01};
    constexpr Opcode LOAD_A_INTO_ADDRESS_BC{0x02};
    constexpr Opcode INCREMENT_BC{0x03};
    constexpr Opcode INCREMENT_B{0x04};
    constexpr Opcode DECREMENT_B{0x05};
    constexpr Opcode LOAD_IMMEDIATE_INTO_B{0x06};
    constexpr Opcode ROTATE_LEFT_CONTENTS_A{0x07};
    constexpr Opcode LOAD_SP_INTO_ADDRESS_IMMEDIATE{0x08};
    constexpr Opcode ADD_HL_AND_BC{0x09};
    constexpr Opcode LOAD_ADDRESS_BC_INTO_A{0x0A};
    constexpr Opcode DECREMENT_BC{0x0B};
    constexpr Opcode INCREMENT_C{0x0C};
    constexpr Opcode DECREMENT_C{0x0D};
    constexpr Opcode LOAD_IMMEDIATE_INTO_C{0x0E};
    constexpr Opcode ROTATE_RIGHT_CONTENTS_A{0x0F};
    //
    /*
    constexpr Opcode STOP{0x10};
    constexpr Opcode LOAD_IMMEDIATE_INTO_DE{0x11};
    constexpr Opcode LOAD_A_INTO_ADDRESS_DE{0x12};
    constexpr Opcode INCREMENT_DE{0x13};
    constexpr Opcode INCREMENT_D{0x14};
    constexpr Opcode DECREMENT_D{0x15};
    constexpr Opcode LOAD_IMMEDIATE_INTO_D{0x16};
    constexpr Opcode ROTATE_LEFT_A{0x17};
    constexpr Opcode JUMP_RELATIVE{0x18};
    constexpr Opcode ADD_HL_AND_DE{0x19};
    constexpr Opcode LOAD_ADDRESS_DE_INTO_A{0x1A};
    constexpr Opcode DECREMENT_DE{0x1B};
    constexpr Opcode INCREMENT_E{0x1C};
    constexpr Opcode DECREMENT_E{0x1D};
    constexpr Opcode LOAD_IMMEDIATE_INTO_E{0x1E};
    constexpr Opcode ROTATE_RIGHT_A{0x1F};
     */
    //constexpr Opcode LOAD_IMMEDIATE_INTO_BC{0x01};
    //constexpr Opcode LOAD_IMMEDIATE_INTO_BC{0x01};
    //constexpr Opcode LOAD_IMMEDIATE_INTO_BC{0x01};
    //constexpr Opcode LOAD_IMMEDIATE_INTO_BC{0x01};
    //constexpr Opcode LOAD_IMMEDIATE_INTO_BC{0x01};

    constexpr Opcode LOAD_IMMEDIATE_A{0x3E};
}

enum class Register_8_bit {
    A,
    B,
    C,
    D,
    E,
    H,
    L
};

enum class Register_16_bit {
    AF,
    BC,
    DE,
    HL,
    SP
};

class Instruction;
using InstructionPtr = std::unique_ptr<const Instruction>;

class Instruction
{
public:
    Instruction() = default;
    virtual ~Instruction() = default;

    virtual Opcode opcode() const = 0;
    virtual std::string str() const = 0;
    virtual bytestring bytestr() const = 0;

    //virtual void emulate(VirtualGameboy& gameboy) = 0;
    //virtual std::string additional_info() = 0;
};

#endif //GAMEBOY_DISASSEMBLE_INSTRUCTIONS_CONSTANTS_H
