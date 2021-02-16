
#include "instructions.h"

Opcode Nop::opcode() const {
    return opcodes::NOP;
}
std::string Nop::str() const {
    return NAME;
}
bytestring Nop::bytestr() const {
    return opcode_to_bytestring(opcode());
}

