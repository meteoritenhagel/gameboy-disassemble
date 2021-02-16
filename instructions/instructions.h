#ifndef GAMEBOY_DEBUG_INSTRUCTIONS_H
#define GAMEBOY_DEBUG_INSTRUCTIONS_H

#include "instructions_conversions.h"
#include "instructions_constants.h"

#include "instructions_increment_decrement.h"
#include "instructions_load_8bit.h"
#include "instructions_load_16bit.h"
#include "instructions_rotation.h"

#include <memory>
#include <vector>

class Nop : public Instruction
{
public:
    Opcode opcode() const override;
    std::string str() const override;
    bytestring bytestr() const override;

private:
    static constexpr char NAME[]{"NOP"};
};

//


class AddHLAndBC : public Instruction
{
public:
    Opcode opcode() const
    {
        return opcodes::ADD_HL_AND_BC;
    }

    std::string str() const
    {
        return NAME;
    }

    bytestring bytestr() const
    {
        return opcode_to_bytestring(opcode());
    }

private:
    static constexpr char NAME[]{"ADD HL, BC"};
};


class Unknown : public Instruction
{
public:
    Opcode opcode() const
    {
        return opcodes::NOP;
    }

    std::string str() const
    {
        return NAME;
    }

    bytestring bytestr() const
    {
        return opcode_to_bytestring(opcode());
    }

private:
    static constexpr char NAME[]{"???"};
};


#endif //GAMEBOY_DEBUG_INSTRUCTIONS_H
