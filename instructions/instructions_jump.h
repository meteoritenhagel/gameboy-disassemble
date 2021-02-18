#ifndef GAMEBOY_DISASSEMBLE_INSTRUCTIONS_JUMP_H
#define GAMEBOY_DISASSEMBLE_INSTRUCTIONS_JUMP_H

// Relative jumps

class JumpRelative : public Instruction
{
public:
    JumpRelative(const uint8_t relativePosition)
            : Instruction(opcodes::JUMP_RELATIVE,
                          "JR " + to_string_hex_signed_prefixed(relativePosition),
                          bytestring{relativePosition}),
              _relativePosition(relativePosition)
    {}
private:
    uint8_t _relativePosition;
};

class JumpRelativeIfNotZero : public Instruction
{
public:
    JumpRelativeIfNotZero(const uint8_t relativePosition)
            : Instruction(opcodes::JUMP_RELATIVE_IF_NOT_ZERO,
                          "JR NZ, " + to_string_hex_signed_prefixed(relativePosition),
                          bytestring{relativePosition}),
              _relativePosition(relativePosition)
    {}
private:
    uint8_t _relativePosition;
};

class JumpRelativeIfZero : public Instruction
{
public:
    JumpRelativeIfZero(const uint8_t relativePosition)
            : Instruction(opcodes::JUMP_RELATIVE_IF_ZERO,
                          "JR Z, " + to_string_hex_signed_prefixed(relativePosition),
                          bytestring{relativePosition}),
              _relativePosition(relativePosition)
    {}
private:
    uint8_t _relativePosition;
};

class JumpRelativeIfNotCarry : public Instruction
{
public:
    JumpRelativeIfNotCarry(const uint8_t relativePosition)
            : Instruction(opcodes::JUMP_RELATIVE_IF_NOT_CARRY,
                          "JR NC, " + to_string_hex_signed_prefixed(relativePosition),
                          bytestring{relativePosition}),
              _relativePosition(relativePosition)
    {}
private:
    uint8_t _relativePosition;
};

class JumpRelativeIfCarry : public Instruction
{
public:
    JumpRelativeIfCarry(const uint8_t relativePosition)
            : Instruction(opcodes::JUMP_RELATIVE_IF_CARRY,
                          "JR C, " + to_string_hex_signed_prefixed(relativePosition),
                          bytestring{relativePosition}),
              _relativePosition(relativePosition)
    {}
private:
    uint8_t _relativePosition;
};

// Restart instructions

class Restart0 : public Instruction
{
public:
    Restart0()
    : Instruction(opcodes::RESTART_0,
                  "RST 0")
    {}
};

class Restart1 : public Instruction
{
public:
    Restart1()
            : Instruction(opcodes::RESTART_1,
                          "RST 1")
    {}
};

class Restart2 : public Instruction
{
public:
    Restart2()
            : Instruction(opcodes::RESTART_2,
                          "RST 2")
    {}
};

class Restart3 : public Instruction
{
public:
    Restart3()
            : Instruction(opcodes::RESTART_3,
                          "RST 3")
    {}
};

class Restart4 : public Instruction
{
public:
    Restart4()
            : Instruction(opcodes::RESTART_4,
                          "RST 4")
    {}
};

class Restart5 : public Instruction
{
public:
    Restart5()
            : Instruction(opcodes::RESTART_5,
                          "RST 5")
    {}
};

class Restart6 : public Instruction
{
public:
    Restart6()
            : Instruction(opcodes::RESTART_6,
                          "RST 6")
    {}
};

class Restart7 : public Instruction
{
public:
    Restart7()
            : Instruction(opcodes::RESTART_7,
                          "RST 7")
    {}
};


#endif //GAMEBOY_DISASSEMBLE_INSTRUCTIONS_JUMP_H
