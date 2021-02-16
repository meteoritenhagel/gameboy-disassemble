//
// Created by tristan on 16.02.21.
//

#ifndef GAMEBOY_DISASSEMBLE_INSTRUCTIONS_LOAD_8BIT_H
#define GAMEBOY_DISASSEMBLE_INSTRUCTIONS_LOAD_8BIT_H

#include "instructions_constants.h"
#include "instructions_conversions.h"

class LoadImmediateIntoA : public Instruction
{
public:
    LoadImmediateIntoA(const uint8_t immediate);
    Opcode opcode() const;
    std::string str() const;
    bytestring bytestr() const;
private:
    static constexpr char NAME[]{"LD A"};
    uint8_t _immediate;
};

class LoadImmediateIntoB : public Instruction
{
public:
    LoadImmediateIntoB(const uint8_t immediate);
    Opcode opcode() const;
    std::string str() const;
    bytestring bytestr() const;
private:
    uint8_t _immediate;
    static constexpr char NAME[]{"LD B"};
};


class LoadImmediateIntoC : public Instruction
{
public:
    LoadImmediateIntoC(const uint8_t immediate);
    Opcode opcode() const;
    std::string str() const;
    bytestring bytestr() const;
private:
    uint8_t _immediate;
    static constexpr char NAME[]{"LD C"};
};

//

class LoadAIntoAddressBC : public Instruction
{
public:
    Opcode opcode() const;
    std::string str() const;
    bytestring bytestr() const;
private:
    static constexpr char NAME[]{"LD (BC), A"};
};

class LoadAddressBCIntoA : public Instruction
{
public:
    Opcode opcode() const;
    std::string str() const;
    bytestring bytestr() const;
private:
    static constexpr char NAME[]{"LD A, (BC)"};
};


#endif //GAMEBOY_DISASSEMBLE_INSTRUCTIONS_LOAD_8BIT_H
