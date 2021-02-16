#include "instructions_load_16bit.h"

LoadImmediateIntoBC::LoadImmediateIntoBC(const uint16_t immediate)
        : _immediate(immediate)
{}
Opcode LoadImmediateIntoBC::opcode() const {
    return opcodes::LOAD_IMMEDIATE_INTO_BC;
}
std::string LoadImmediateIntoBC::str() const {
    return NAME + (", " + to_string_hex_prefixed(_immediate));
}
bytestring LoadImmediateIntoBC::bytestr() const {
    return to_bytestring(opcode(), opcode_to_bytestring(_immediate));
}

LoadSPIntoAddressImmediate::LoadSPIntoAddressImmediate(const uint16_t immediate)
        : _immediate(immediate)
{}
Opcode LoadSPIntoAddressImmediate::opcode() const {
    return opcodes::LOAD_SP_INTO_ADDRESS_IMMEDIATE;
}
std::string LoadSPIntoAddressImmediate::str() const {
    return "LD (" + to_string_hex_prefixed(_immediate) + "), SP";
}
bytestring LoadSPIntoAddressImmediate::bytestr() const {
    return to_bytestring(opcode(), opcode_to_bytestring(_immediate));
}
