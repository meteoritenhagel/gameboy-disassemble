#ifndef GAMEBOY_DISASSEMBLE_BASEINSTRUCTION_H
#define GAMEBOY_DISASSEMBLE_BASEINSTRUCTION_H

#include "constants.h"
#include "auxiliary_and_conversions.h"

#include <functional>
#include <ostream>
#include <string>

class BaseInstruction;

using InstructionPtr = std::unique_ptr<const BaseInstruction>;
using InstructionVector = std::vector<InstructionPtr>;

template<typename InstructionType, typename... Args>
InstructionPtr create_instruction(Args... args) {
    return std::make_unique<InstructionType>(args...);
}

/**
 * Ostream overloaded operator << for class BaseInstruction
 * @param os output stream
 * @param instruction instruction
 * @return stream containing @param instruction's string part.
 */
std::ostream& operator<<(std::ostream& os, const BaseInstruction& instruction);

/**
 * Ostream overloaded operator << for class InstructionPtr
 * @param os output stream
 * @param instructionPtr instructionPtr
 * @return stream containing @param instructionPtr's string part.
 */
std::ostream& operator<<(std::ostream& os, const InstructionPtr& instructionPtr);

/**
 * Class BaseInstruction. All GameBoy instructions are supposed to be derived from this class.
 * Note that all possible realizations of the same child class must have the same bytecode length each,
 * and they must be default constructible.
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
