//
// Created by tristan on 16.02.21.
//

#include "interface.h"

Instruction::Instruction(const std::string &string, const Opcode opcode, const Bytestring &arguments)
        : _opcode(opcode),
          _string(string),
          _arguments(arguments) {}

Opcode Instruction::opcode() const {
    return _opcode;
}

std::string Instruction::str() const {
    return _string;
}

Bytestring Instruction::bytestr() const {
    return merge_to_bytestring(opcode(), _arguments);
}

bool Instruction::is_valid() const {
    return (opcode() != opcodes::INVALID_OPCODE);
}
