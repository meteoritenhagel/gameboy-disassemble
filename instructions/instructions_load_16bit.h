//
// Created by tristan on 16.02.21.
//

#ifndef GAMEBOY_DISASSEMBLE_INSTRUCTIONS_LOAD_16BIT_H
#define GAMEBOY_DISASSEMBLE_INSTRUCTIONS_LOAD_16BIT_H

#include "instructions_interface.h"

class LoadImmediateIntoBC : public Instruction
{
public:
    LoadImmediateIntoBC(const uint16_t immediate)
    : Instruction(opcodes::LOAD_IMMEDIATE_INTO_BC,
                  "LD BC, " + to_string_hex_prefixed(immediate),
                  to_bytestring_little_endian(immediate)),
      _immediate(immediate)
    {}
private:
    uint16_t _immediate;
};

class LoadImmediateIntoDE : public Instruction
{
public:
    LoadImmediateIntoDE(const uint16_t immediate)
            : Instruction(opcodes::LOAD_IMMEDIATE_INTO_DE,
                          "LD DE, " + to_string_hex_prefixed(immediate),
                          to_bytestring_little_endian(immediate)),
              _immediate(immediate)
    {}
private:
    uint16_t _immediate;
};

class LoadImmediateIntoHL : public Instruction
{
public:
    LoadImmediateIntoHL(const uint16_t immediate)
            : Instruction(opcodes::LOAD_IMMEDIATE_INTO_HL,
                          "LD HL, " + to_string_hex_prefixed(immediate),
                          to_bytestring_little_endian(immediate)),
              _immediate(immediate)
    {}
private:
    uint16_t _immediate;
};

class LoadImmediateIntoSP : public Instruction
{
public:
    LoadImmediateIntoSP(const uint16_t immediate)
            : Instruction(opcodes::LOAD_IMMEDIATE_INTO_SP,
                          "LD SP, " + to_string_hex_prefixed(immediate),
                          to_bytestring_little_endian(immediate)),
              _immediate(immediate)
    {}
private:
    uint16_t _immediate;
};

class LoadSPIntoAddressImmediate : public Instruction
{
public:
    LoadSPIntoAddressImmediate(const uint16_t immediate)
    : Instruction(opcodes::LOAD_SP_INTO_ADDRESS_IMMEDIATE,
                  "LD (" + to_string_hex_prefixed(immediate) + "), SP",
                  to_bytestring_little_endian(immediate)),
      _immediate(immediate)
    {}
private:
    uint16_t _immediate;
};


#endif //GAMEBOY_DISASSEMBLE_INSTRUCTIONS_LOAD_16BIT_H
