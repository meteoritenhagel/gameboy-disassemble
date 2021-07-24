#ifndef GAMEBOY_DEBUG_UNRESOLVEDINSTRUCTION_H
#define GAMEBOY_DEBUG_UNRESOLVEDINSTRUCTION_H

#include "../instructions/baseinstruction.h"

#include <memory>

class UnresolvedInstructionInterface;

using UnresolvedInstructionPtr = std::unique_ptr<UnresolvedInstructionInterface>;

class UnresolvedInstructionInterface {
public:
    virtual InstructionPtr resolve() const = 0;
    virtual size_t length() const = 0;
};

template<typename F>
class UnresolvedInstructionImpl : public UnresolvedInstructionInterface {
public:
    UnresolvedInstructionImpl(const F &unresolvedInstruction)
    : _unresolvedInstruction(unresolvedInstruction) {}

    InstructionPtr resolve() const {
        auto x = _unresolvedInstruction();
        return create_instruction<decltype(_unresolvedInstruction())>(_unresolvedInstruction());
    }

    size_t length() const {
        decltype(_unresolvedInstruction()) instruction{}; // default-construct instruction of the right type
        return instruction.length();
    }

private:
    F _unresolvedInstruction;
};

template<typename F>
UnresolvedInstructionPtr create_unresolved_instruction(F f) {
    return std::make_unique<UnresolvedInstructionImpl<F>>(f);
}

#endif //GAMEBOY_DEBUG_UNRESOLVEDINSTRUCTION_H
