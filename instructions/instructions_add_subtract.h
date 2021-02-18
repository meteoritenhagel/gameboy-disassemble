//
// Created by tristan on 18.02.21.
//

#ifndef GAMEBOY_DISASSEMBLE_INSTRUCTIONS_ADD_SUBTRACT_H
#define GAMEBOY_DISASSEMBLE_INSTRUCTIONS_ADD_SUBTRACT_H

#include "instructions_interface.h"

class AddHLAndBC : public Instruction
{
public:
    AddHLAndBC()
            : Instruction(opcodes::ADD_HL_AND_BC,
                          "ADD HL, BC")
    {}
};

class AddHLAndDE : public Instruction
{
public:
    AddHLAndDE()
            : Instruction(opcodes::ADD_HL_AND_DE,
                          "ADD HL, DE")
    {}
};

class AddHLAndHL : public Instruction
{
public:
    AddHLAndHL()
            : Instruction(opcodes::ADD_HL_AND_HL,
                          "ADD HL, HL")
    {}
};

class AddHLAndSP : public Instruction
{
public:
    AddHLAndSP()
            : Instruction(opcodes::ADD_HL_AND_SP,
                          "ADD HL, SP")
    {}
};

#endif //GAMEBOY_DISASSEMBLE_INSTRUCTIONS_ADD_SUBTRACT_H
