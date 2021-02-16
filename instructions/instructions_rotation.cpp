#include "instructions_rotation.h"

Opcode RotateLeftContentsA::opcode() const {
    return opcodes::ROTATE_LEFT_CONTENTS_A;
}
std::string RotateLeftContentsA::str() const {
    return NAME;
}
bytestring RotateLeftContentsA::bytestr() const {
    return opcode_to_bytestring(opcode());
}

Opcode RotateRightContentsA::opcode() const {
    return opcodes::ROTATE_RIGHT_CONTENTS_A;
}
std::string RotateRightContentsA::str() const {
    return NAME;
}
bytestring RotateRightContentsA::bytestr() const {
    return opcode_to_bytestring(opcode());
}
