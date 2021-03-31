#ifndef GAMEBOY_DEBUG_INSTRUCTIONS_PARSER_H
#define GAMEBOY_DEBUG_INSTRUCTIONS_PARSER_H

#include "interface.h"

class SymbolResolutionFailed : public Instruction {
public:
    using TokenVectorPosition = size_t;

    SymbolResolutionFailed(const TokenVectorPosition tokenVectorPosition)
            : Instruction("[SYMBOL RESOLUTION FAILED]",
                          opcodes::INVALID_OPCODE),
              _tokenVectorPosition(tokenVectorPosition) {}

    TokenVectorPosition get_tokenvector_position() const {
        return _tokenVectorPosition;
    }

private:
    TokenVectorPosition _tokenVectorPosition{0};
};

#endif //GAMEBOY_DEBUG_INSTRUCTIONS_PARSER_H
