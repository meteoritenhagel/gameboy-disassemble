//
// Created by tristan on 16.02.21.
//

#include "interface.h"

Instruction::Instruction(const std::string &string, const Opcode opcode, const bytestring &arguments)
        : _opcode(opcode),
          _string(string),
          _arguments(arguments) {}

Opcode Instruction::opcode() const {
    return _opcode;
}

std::string Instruction::str() const {
    return _string;
}

bytestring Instruction::bytestr() const {
    return to_bytestring(opcode(), _arguments);
}

bool Instruction::is_valid() const {
    return (opcode() != opcodes::INVALID_OPCODE);
}
