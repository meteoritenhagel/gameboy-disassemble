#ifndef GAMEBOY_DISASSEMBLE_INSTRUCTIONS_ROTATION_H
#define GAMEBOY_DISASSEMBLE_INSTRUCTIONS_ROTATION_H

#include "instructions_constants.h"
#include "instructions_conversions.h"

class RotateLeftContentsA : public Instruction
{
public:
    Opcode opcode() const;
    std::string str() const;
    bytestring bytestr() const;
private:
    static constexpr char NAME[]{"RLC A"};
};

class RotateRightContentsA : public Instruction
{
public:
    Opcode opcode() const;
    std::string str() const;
    bytestring bytestr() const;
private:
    static constexpr char NAME[]{"RRC A"};
};

#endif //GAMEBOY_DISASSEMBLE_INSTRUCTIONS_ROTATION_H
