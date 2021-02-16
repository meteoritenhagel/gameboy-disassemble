#include "instructions_increment_decrement.h"

Opcode IncrementB::opcode() const {
    return opcodes::INCREMENT_B;
}

std::string IncrementB::str() const {
    return NAME;
}

bytestring IncrementB::bytestr() const {
    return opcode_to_bytestring(opcode());
}

Opcode DecrementB::opcode() const {
    return opcodes::DECREMENT_B;
}

std::string DecrementB::str() const {
    return NAME;
}

bytestring DecrementB::bytestr() const {
    return opcode_to_bytestring(opcode());
}

Opcode IncrementC::opcode() const {
    return opcodes::INCREMENT_C;
}

std::string IncrementC::str() const {
    return NAME;
}

bytestring IncrementC::bytestr() const {
    return opcode_to_bytestring(opcode());
}

Opcode DecrementC::opcode() const {
    return opcodes::DECREMENT_C;
}

std::string DecrementC::str() const {
    return NAME;
}

bytestring DecrementC::bytestr() const {
    return opcode_to_bytestring(opcode());
}

Opcode IncrementBC::opcode() const {
    return opcodes::INCREMENT_BC;
}

std::string IncrementBC::str() const {
    return NAME;
}

bytestring IncrementBC::bytestr() const {
    return opcode_to_bytestring(opcode());
}

Opcode DecrementBC::opcode() const {
    return opcodes::DECREMENT_BC;
}

std::string DecrementBC::str() const {
    return NAME;
}

bytestring DecrementBC::bytestr() const {
    return opcode_to_bytestring(opcode());
}
