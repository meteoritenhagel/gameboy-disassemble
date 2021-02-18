#ifndef GAMEBOY_DISASSEMBLE_INSTRUCTIONS_ROTATION_H
#define GAMEBOY_DISASSEMBLE_INSTRUCTIONS_ROTATION_H

#include "instructions_interface.h"

// Rotate A and clear Zero Flag

class RotateLeftAAndClearZero : public Instruction
{
public:
    RotateLeftAAndClearZero()
            : Instruction(opcodes::ROTATE_LEFT_A_AND_CLEAR_ZERO,
                          "RLA")
    {}
};

class RotateRightAAndClearZero : public Instruction
{
public:
    RotateRightAAndClearZero()
            : Instruction(opcodes::ROTATE_RIGHT_A_AND_CLEAR_ZERO,
                          "RRA")
    {}
};

class RotateLeftContentsAAndClearZero : public Instruction
{
public:
    RotateLeftContentsAAndClearZero()
    : Instruction(opcodes::ROTATE_LEFT_CONTENTS_A_AND_CLEAR_ZERO,
                  "RLCA")
    {}
};

class RotateRightContentsAAndClearZero : public Instruction
{
public:
    RotateRightContentsAAndClearZero()
    : Instruction(opcodes::ROTATE_RIGHT_CONTENTS_A_AND_CLEAR_ZERO,
                  "RRCA")
    {}
};

#endif //GAMEBOY_DISASSEMBLE_INSTRUCTIONS_ROTATION_H
