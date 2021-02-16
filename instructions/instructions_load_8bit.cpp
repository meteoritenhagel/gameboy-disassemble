#include "instructions_load_8bit.h"

LoadImmediateIntoA::LoadImmediateIntoA(const uint8_t immediate)
        : _immediate(immediate)
{}
Opcode LoadImmediateIntoA::opcode() const {
    return opcodes::LOAD_IMMEDIATE_A;
}
std::string LoadImmediateIntoA::str() const {
    return NAME + (", " + to_string_hex_prefixed(_immediate));
}
bytestring LoadImmediateIntoA::bytestr() const {
    return to_bytestring(opcode(), bytestring{_immediate});
}


LoadImmediateIntoB::LoadImmediateIntoB(const uint8_t immediate)
        : _immediate(immediate)
{}
Opcode LoadImmediateIntoB::opcode() const {
    return opcodes::LOAD_IMMEDIATE_INTO_B;
}
std::string LoadImmediateIntoB::str() const {
    return NAME + (", " + to_string_hex_prefixed(_immediate));
}
bytestring LoadImmediateIntoB::bytestr() const {
    return to_bytestring(opcode(), opcode_to_bytestring(_immediate));
}


LoadImmediateIntoC::LoadImmediateIntoC(const uint8_t immediate)
        : _immediate(immediate)
{}
Opcode LoadImmediateIntoC::opcode() const {
    return opcodes::LOAD_IMMEDIATE_INTO_C;
}
std::string LoadImmediateIntoC::str() const {
    return NAME + (", " + to_string_hex_prefixed(_immediate));
}
bytestring LoadImmediateIntoC::bytestr() const {
    return to_bytestring(opcode(), opcode_to_bytestring(_immediate));
}

//

Opcode LoadAIntoAddressBC::opcode() const {
    return opcodes::LOAD_A_INTO_ADDRESS_BC;
}
std::string LoadAIntoAddressBC::str() const {
    return NAME;
}
bytestring LoadAIntoAddressBC::bytestr() const {
    return opcode_to_bytestring(opcode());
}

Opcode LoadAddressBCIntoA::opcode() const {
    return opcodes::LOAD_ADDRESS_BC_INTO_A;
}
std::string LoadAddressBCIntoA::str() const {
    return NAME;
}
bytestring LoadAddressBCIntoA::bytestr() const {
    return opcode_to_bytestring(opcode());
}
