#ifndef GAMEBOY_DISASSEMBLE_INSTRUCTIONS_JUMP_H
#define GAMEBOY_DISASSEMBLE_INSTRUCTIONS_JUMP_H

#include "interface.h"

/**********************************************************+
 * Helper classes ******************************************
 ***********************************************************/

class InstructionJumpRelativeConditional : public Instruction {
protected:
    InstructionJumpRelativeConditional(const FlagCondition flagCondition, const byte relativePosition, const Opcode opc)
            : Instruction("JR " + to_string(flagCondition) + ", " + to_string_hex_signed_prefixed(relativePosition),
                          opc,
                          bytestring{relativePosition}),
              _flagCondition(flagCondition),
              _relativePosition(relativePosition) {}

private:
    const FlagCondition _flagCondition;
    const byte _relativePosition;
};


class InstructionCallConditional : public Instruction {
protected:
    InstructionCallConditional(const FlagCondition flagCondition, const word address, const Opcode opc)
            : Instruction("CALL " + to_string(flagCondition) + ", " + to_string_hex_prefixed(address),
                          opc,
                          to_bytestring_little_endian(address)),
              _flagCondition(flagCondition),
              _address(address) {}

private:
    const FlagCondition _flagCondition;
    const word _address;
};

class InstructionReturnConditional : public Instruction {
protected:
    InstructionReturnConditional(const FlagCondition flagCondition, const Opcode opc)
            : Instruction("RET " + to_string(flagCondition), opc),
              _flagCondition(flagCondition) {}

private:
    const FlagCondition _flagCondition;
};

class InstructionRestart : public Instruction {
protected:
    InstructionRestart(const uint8_t jumpIndex, const Opcode opc)
            : Instruction("RST " + to_string_dec(jumpIndex),
                          opc),
              _jumpIndex(jumpIndex) {}

private:
    const uint8_t _jumpIndex;
};

/**********************************************************+
 * Public interface ****************************************
 ***********************************************************/

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

class Return : public Instruction {
public:
    Return()
            : Instruction("RET", opcodes::RETURN) {}
};

class ReturnFromInterrupt : public Instruction {
public:
    ReturnFromInterrupt()
            : Instruction("RETI", opcodes::RETURN_FROM_INTERRUPT) {}
};

class InstructionJumpConditional : public Instruction {
protected:
    InstructionJumpConditional(const FlagCondition flagCondition, const word address, const Opcode opc)
            : Instruction("JP " + to_string(flagCondition) + ", " + to_string_hex_prefixed(address),
                          opc,
                          to_bytestring_little_endian(address)),
              _flagCondition(flagCondition),
              _address(address) {}

private:
    const FlagCondition _flagCondition;
    const word _address;
};

/** Doubly derived classes ***********************************/

// conditional absolute jumps
class JumpIfNotZero : public InstructionJumpConditional {
public:
    JumpIfNotZero(const word address)
            : InstructionJumpConditional(FlagCondition::NOT_ZERO,
                                         address,
                                         opcodes::JUMP_IF_NOT_ZERO) {}
};

class JumpIfZero : public InstructionJumpConditional {
public:
    JumpIfZero(const word address)
            : InstructionJumpConditional(FlagCondition::ZERO,
                                         address,
                                         opcodes::JUMP_IF_ZERO) {}
};

class JumpIfNotCarry : public InstructionJumpConditional {
public:
    JumpIfNotCarry(const word address)
            : InstructionJumpConditional(FlagCondition::NOT_CARRY,
                                         address,
                                         opcodes::JUMP_IF_NOT_CARRY) {}
};

class JumpIfCarry : public InstructionJumpConditional {
public:
    JumpIfCarry(const word address)
            : InstructionJumpConditional(FlagCondition::CARRY,
                                         address,
                                         opcodes::JUMP_IF_CARRY) {}
};

// Conditional relative jumps
class JumpRelativeIfNotZero : public InstructionJumpRelativeConditional {
public:
    JumpRelativeIfNotZero(const byte address)
            : InstructionJumpRelativeConditional(FlagCondition::NOT_ZERO,
                                                 address,
                                                 opcodes::JUMP_RELATIVE_IF_NOT_ZERO) {}
};

class JumpRelativeIfZero : public InstructionJumpRelativeConditional {
public:
    JumpRelativeIfZero(const byte address)
            : InstructionJumpRelativeConditional(FlagCondition::ZERO,
                                                 address,
                                                 opcodes::JUMP_RELATIVE_IF_ZERO) {}
};

class JumpRelativeIfNotCarry : public InstructionJumpRelativeConditional {
public:
    JumpRelativeIfNotCarry(const byte address)
            : InstructionJumpRelativeConditional(FlagCondition::NOT_CARRY,
                                                 address,
                                                 opcodes::JUMP_RELATIVE_IF_NOT_CARRY) {}
};

class JumpRelativeIfCarry : public InstructionJumpRelativeConditional {
public:
    JumpRelativeIfCarry(const byte address)
            : InstructionJumpRelativeConditional(FlagCondition::CARRY,
                                                 address,
                                                 opcodes::JUMP_RELATIVE_IF_CARRY) {}
};

// conditional calls
class CallIfNotZero : public InstructionCallConditional {
public:
    CallIfNotZero(const word address)
            : InstructionCallConditional(FlagCondition::NOT_ZERO,
                                         address,
                                         opcodes::CALL_IF_NOT_ZERO) {}
};

class CallIfZero : public InstructionCallConditional {
public:
    CallIfZero(const word address)
            : InstructionCallConditional(FlagCondition::ZERO,
                                         address,
                                         opcodes::CALL_IF_ZERO) {}
};

class CallIfNotCarry : public InstructionCallConditional {
public:
    CallIfNotCarry(const word address)
            : InstructionCallConditional(FlagCondition::NOT_CARRY,
                                         address,
                                         opcodes::CALL_IF_NOT_CARRY) {}
};

class CallIfCarry : public InstructionCallConditional {
public:
    CallIfCarry(const word address)
            : InstructionCallConditional(FlagCondition::CARRY,
                                         address,
                                         opcodes::CALL_IF_CARRY) {}
};

// conditional returns
class ReturnIfNotZero : public InstructionReturnConditional {
public:
    ReturnIfNotZero()
            : InstructionReturnConditional(FlagCondition::NOT_ZERO,
                                           opcodes::RETURN_IF_NOT_ZERO) {}
};

class ReturnIfZero : public InstructionReturnConditional {
public:
    ReturnIfZero()
            : InstructionReturnConditional(FlagCondition::ZERO,
                                           opcodes::RETURN_IF_ZERO) {}
};

class ReturnIfNotCarry : public InstructionReturnConditional {
public:
    ReturnIfNotCarry()
            : InstructionReturnConditional(FlagCondition::NOT_CARRY,
                                           opcodes::RETURN_IF_NOT_CARRY) {}
};

class ReturnIfCarry : public InstructionReturnConditional {
public:
    ReturnIfCarry()
            : InstructionReturnConditional(FlagCondition::CARRY,
                                           opcodes::RETURN_IF_CARRY) {}
};

// Restart instructions
class Restart0 : public InstructionRestart {
public:
    Restart0()
            : InstructionRestart(0, opcodes::RESTART_0) {}
};

class Restart1 : public InstructionRestart {
public:
    Restart1()
            : InstructionRestart(1, opcodes::RESTART_1) {}
};

class Restart2 : public InstructionRestart {
public:
    Restart2()
            : InstructionRestart(2, opcodes::RESTART_2) {}
};

class Restart3 : public InstructionRestart {
public:
    Restart3()
            : InstructionRestart(3, opcodes::RESTART_3) {}
};

class Restart4 : public InstructionRestart {
public:
    Restart4()
            : InstructionRestart(4, opcodes::RESTART_4) {}
};

class Restart5 : public InstructionRestart {
public:
    Restart5()
            : InstructionRestart(5, opcodes::RESTART_5) {}
};

class Restart6 : public InstructionRestart {
public:
    Restart6()
            : InstructionRestart(6, opcodes::RESTART_6) {}
};

class Restart7 : public InstructionRestart {
public:
    Restart7()
            : InstructionRestart(7, opcodes::RESTART_7) {}
};

#endif //GAMEBOY_DISASSEMBLE_INSTRUCTIONS_JUMP_H
