//
// Created by tristan on 16.02.21.
//

#ifndef GAMEBOY_DISASSEMBLE_INSTRUCTIONS_LOAD_16BIT_H
#define GAMEBOY_DISASSEMBLE_INSTRUCTIONS_LOAD_16BIT_H

#include "instructions_constants.h"
#include "instructions_conversions.h"

class LoadImmediateIntoBC : public Instruction
{
public:
    LoadImmediateIntoBC(const uint16_t immediate);
    Opcode opcode() const;
    std::string str() const;
    bytestring bytestr() const;
private:
    static constexpr char NAME[]{"LD BC"};
    uint16_t _immediate;
};

class LoadSPIntoAddressImmediate : public Instruction
{
public:
    LoadSPIntoAddressImmediate(const uint16_t immediate);
    Opcode opcode() const;
    std::string str() const;
    bytestring bytestr() const;
private:
    uint16_t _immediate;
};


#endif //GAMEBOY_DISASSEMBLE_INSTRUCTIONS_LOAD_16BIT_H
