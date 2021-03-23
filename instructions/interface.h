#ifndef GAMEBOY_DISASSEMBLE_INTERFACE_H
#define GAMEBOY_DISASSEMBLE_INTERFACE_H

#include "constants.h"
#include "conversions.h"

#include <string>

class Instruction;

using InstructionPtr = std::unique_ptr<const Instruction>;
using InstructionVector = std::vector<InstructionPtr>;

class Instruction {
public:
    Instruction(const std::string &string, const Opcode opcode, const Bytestring &arguments = {});

    virtual ~Instruction() = default;

    Opcode opcode() const;

    std::string str() const;

    Bytestring bytestr() const;

    bool is_valid() const;

    //virtual void emulate(VirtualGameboy& gameboy) = 0;
    //virtual std::string additional_info() = 0;

private:
    const Opcode _opcode;
    const std::string _string;
    const Bytestring _arguments{};
};


#endif //GAMEBOY_DISASSEMBLE_INTERFACE_H
