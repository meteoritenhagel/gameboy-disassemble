//
// Created by tristan on 16.02.21.
//

#include "baseinstruction.h"

BaseInstruction::BaseInstruction(const std::string &string, const Opcode opcode, const Bytestring &arguments)
        : _opcode(opcode),
          _string(string),
          _arguments(arguments) {}


bool BaseInstruction::operator==(const BaseInstruction &other) const {
    return (_opcode == other._opcode) && (_arguments == other._arguments);
}

Opcode BaseInstruction::opcode() const {
    return _opcode;
}

std::string BaseInstruction::str() const {
    return _string;
}

Bytestring BaseInstruction::bytestr() const {
    return merge_to_bytestring(opcode(), _arguments);
}

size_t BaseInstruction::length() const {
    return bytestr().size();
}

bool BaseInstruction::is_valid() const {
    return (opcode() != opcodes::INVALID_OPCODE);
}
