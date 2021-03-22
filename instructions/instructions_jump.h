#ifndef GAMEBOY_DISASSEMBLE_INSTRUCTIONS_JUMP_H
#define GAMEBOY_DISASSEMBLE_INSTRUCTIONS_JUMP_H

#include "interface.h"

class Jump : public Instruction {
public:
    Jump(const word address)
            : Instruction(
            "JP " + to_string_hex_prefixed(address), opcodes::JUMP,
            to_bytestring_little_endian(address)),
              _address(address) {}

private:
    const word _address;
};

class JumpConditional : public Instruction {
public:
    JumpConditional(const FlagCondition flagCondition, const word address)
            : Instruction("JP " + to_string(flagCondition) + ", " + to_string_hex_prefixed(address),
                          determine_opcode(flagCondition),
                          to_bytestring_little_endian(address)),
              _flagCondition(flagCondition),
              _address(address) {}

private:
    Opcode determine_opcode(const FlagCondition flagCondition) const {
        switch (flagCondition) {
            case FlagCondition::NOT_ZERO:  return opcodes::JUMP_IF_NOT_ZERO;
            case FlagCondition::ZERO:      return opcodes::JUMP_IF_ZERO;
            case FlagCondition::NOT_CARRY: return opcodes::JUMP_IF_NOT_CARRY;
            case FlagCondition::CARRY:     return opcodes::JUMP_IF_CARRY;
            default:                       return opcodes::INVALID_OPCODE;
        }
    }
    const FlagCondition _flagCondition;
    const word _address;
};

class JumpToHL : public Instruction {
public:
    JumpToHL()
            : Instruction("JP HL", opcodes::JUMP_TO_HL) {}
};

class JumpRelative : public Instruction {
public:
    JumpRelative(const byte relativePosition)
            : Instruction(
            "JR " + to_string_hex_signed_prefixed(relativePosition), opcodes::JUMP_RELATIVE,
            bytestring{relativePosition}),
              _relativePosition(relativePosition) {}

private:
    const byte _relativePosition;
};

class JumpRelativeConditional : public Instruction {
public:
    JumpRelativeConditional(const FlagCondition flagCondition, const byte relativePosition)
            : Instruction("JR " + to_string(flagCondition) + ", " + to_string_hex_signed_prefixed(relativePosition),
                          determine_opcode(flagCondition),
                          bytestring{relativePosition}),
              _flagCondition(flagCondition),
              _relativePosition(relativePosition) {}

private:
    Opcode determine_opcode(const FlagCondition flagCondition) const {
        switch (flagCondition) {
            case FlagCondition::NOT_ZERO:  return opcodes::JUMP_RELATIVE_IF_NOT_ZERO;
            case FlagCondition::ZERO:      return opcodes::JUMP_RELATIVE_IF_ZERO;
            case FlagCondition::NOT_CARRY: return opcodes::JUMP_RELATIVE_IF_NOT_CARRY;
            case FlagCondition::CARRY:     return opcodes::JUMP_RELATIVE_IF_CARRY;
            default:                       return opcodes::INVALID_OPCODE;
        }
    }

    const FlagCondition _flagCondition;
    const byte _relativePosition;
};

class Call : public Instruction {
public:
    Call(const word address)
            : Instruction(
            "CALL " + to_string_hex_prefixed(address), opcodes::CALL,
            to_bytestring_little_endian(address)),
              _address(address) {}

private:
    const word _address;
};


class CallConditional : public Instruction {
public:
    CallConditional(const FlagCondition flagCondition, const word address)
            : Instruction("CALL " + to_string(flagCondition) + ", " + to_string_hex_prefixed(address),
                          determine_opcode(flagCondition),
                          to_bytestring_little_endian(address)),
              _flagCondition(flagCondition),
              _address(address) {}

private:
    Opcode determine_opcode(const FlagCondition flagCondition) const {
        switch (flagCondition) {
            case FlagCondition::NOT_ZERO:  return opcodes::CALL_IF_NOT_ZERO;
            case FlagCondition::ZERO:      return opcodes::CALL_IF_ZERO;
            case FlagCondition::NOT_CARRY: return opcodes::CALL_IF_NOT_CARRY;
            case FlagCondition::CARRY:     return opcodes::CALL_IF_CARRY;
            default:                       return opcodes::INVALID_OPCODE;
        }
    }

    const FlagCondition _flagCondition;
    const word _address;
};

class Return : public Instruction {
public:
    Return()
            : Instruction("RET", opcodes::RETURN) {}
};

class ReturnConditional : public Instruction {
public:
    ReturnConditional(const FlagCondition flagCondition)
            : Instruction("RET " + to_string(flagCondition), determine_opcode(flagCondition)),
              _flagCondition(flagCondition) {}

private:
    Opcode determine_opcode(const FlagCondition flagCondition) const {
        switch (flagCondition) {
            case FlagCondition::NOT_ZERO:  return opcodes::RETURN_IF_NOT_ZERO;
            case FlagCondition::ZERO:      return opcodes::RETURN_IF_ZERO;
            case FlagCondition::NOT_CARRY: return opcodes::RETURN_IF_NOT_CARRY;
            case FlagCondition::CARRY:     return opcodes::RETURN_IF_CARRY;
            default:                       return opcodes::INVALID_OPCODE;
        }
    }

    const FlagCondition _flagCondition;
};

class ReturnFromInterrupt : public Instruction {
public:
    ReturnFromInterrupt()
            : Instruction("RETI", opcodes::RETURN_FROM_INTERRUPT) {}
};

class Restart : public Instruction {
public:
    Restart(const uint8_t jumpIndex)
            : Instruction("RST " + to_string_dec(jumpIndex),
                          determine_opcode(jumpIndex)),
              _jumpIndex(jumpIndex) {}

private:
    Opcode determine_opcode(const uint8_t jumpIndex) const {
        switch (jumpIndex) {
            case 0:  return opcodes::RESTART_0;
            case 1:  return opcodes::RESTART_1;
            case 2:  return opcodes::RESTART_2;
            case 3:  return opcodes::RESTART_3;
            case 4:  return opcodes::RESTART_4;
            case 5:  return opcodes::RESTART_5;
            case 6:  return opcodes::RESTART_6;
            case 7:  return opcodes::RESTART_7;
            default: return opcodes::INVALID_OPCODE;
        }
    }

    const uint8_t _jumpIndex;
};

#endif //GAMEBOY_DISASSEMBLE_INSTRUCTIONS_JUMP_H
