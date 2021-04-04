#ifndef GAMEBOY_DISASSEMBLE_BASEINSTRUCTION_H
#define GAMEBOY_DISASSEMBLE_BASEINSTRUCTION_H

#include "constants.h"
#include "auxiliary_and_conversions.h"

#include <string>

class BaseInstruction;

using InstructionPtr = std::unique_ptr<const BaseInstruction>;
using InstructionVector = std::vector<InstructionPtr>;

/**
 * Class BaseInstruction. All GameBoy instructions are supposed to be derived from this class.
 * Note that all possible realizations of the same child class must have the same bytecode length.
 * Otherwise, when assembling, label resolution cannot work properly.
 */
class BaseInstruction {
public:
    BaseInstruction(const std::string &string, const Opcode opcode, const Bytestring &arguments = {});
    virtual ~BaseInstruction() = default;

    bool operator==(const BaseInstruction &other) const;

    Opcode opcode() const;

    std::string str() const;

    Bytestring bytestr() const;

    size_t length() const;

    bool is_valid() const;

    //virtual void emulate(VirtualGameboy& gameboy) = 0;
    //virtual std::string additional_info() = 0;

private:
    const Opcode _opcode;
    const std::string _string;
    const Bytestring _arguments{};
};


#endif //GAMEBOY_DISASSEMBLE_BASEINSTRUCTION_H
