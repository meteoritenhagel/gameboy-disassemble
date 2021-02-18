#ifndef GAMEBOY_DISASSEMBLE_INSTRUCTIONS_INTERFACE_H
#define GAMEBOY_DISASSEMBLE_INSTRUCTIONS_INTERFACE_H

#include "instructions_constants.h"
#include "instructions_conversions.h"

#include <string>

class Instruction;
using InstructionPtr = std::unique_ptr<const Instruction>;

class Instruction
{
public:
    Instruction(const Opcode opcode, const std::string& string, const bytestring& arguments = {});

    virtual ~Instruction() = default;

    Opcode opcode() const;

    std::string str() const;

    bytestring bytestr() const;

    //virtual void emulate(VirtualGameboy& gameboy) = 0;
    //virtual std::string additional_info() = 0;

private:
    const Opcode _opcode;
    const std::string _string;
    const bytestring _arguments{};
};


#endif //GAMEBOY_DISASSEMBLE_INSTRUCTIONS_INTERFACE_H
