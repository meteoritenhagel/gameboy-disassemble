#ifndef GAMEBOY_DISASSEMBLE_INSTRUCTIONS_UNUSED_H
#define GAMEBOY_DISASSEMBLE_INSTRUCTIONS_UNUSED_H

#include "instructions_interface.h"

class Unused0 : public Instruction
{
public:
    Unused0()
            : Instruction(opcodes::UNUSED_0,
                          "??0")
    {}
};

class Unused1 : public Instruction
{
public:
    Unused1()
            : Instruction(opcodes::UNUSED_1,
                          "??1")
    {}
};

class Unused2 : public Instruction
{
public:
    Unused2()
            : Instruction(opcodes::UNUSED_2),
                          "??2")
    {}
};

class Unused3 : public Instruction
{
public:
    Unused3()
            : Instruction(opcodes::UNUSED_3,
                          "??3")
    {}
};

class Unused4 : public Instruction
{
public:
    Unused4()
            : Instruction(opcodes::UNUSED_4,
                          "??4")
    {}
};

class Unused5 : public Instruction
{
public:
    Unused5()
            : Instruction(opcodes::UNUSED_5,
                          "??5")
    {}
};

class Unused6 : public Instruction
{
public:
    Unused6()
            : Instruction(opcodes::UNUSED_6,
                          "??6")
    {}
};

class Unused7 : public Instruction
{
public:
    Unused7()
            : Instruction(opcodes::UNUSED_7,
                          "??7")
    {}
};

class Unused8 : public Instruction
{
public:
    Unused8()
            : Instruction(opcodes::UNUSED_8,
                          "??8")
    {}
};

class Unused9 : public Instruction
{
public:
    Unused9()
            : Instruction(opcodes::UNUSED_9,
                          "??9")
    {}
};

class Unused10 : public Instruction
{
public:
    Unused10()
            : Instruction(opcodes::UNUSED_10,
                          "?10")
    {}
};

class Unused11 : public Instruction
{
public:
    Unused11()
            : Instruction(opcodes::UNUSED_11,
                          "?11")
    {}
};

// If not implemented yet

class Unknown : public Instruction
{
public:
    Unknown()
            : Instruction(opcodes::NOP,
                          "???")
    {}
};

#endif //GAMEBOY_DISASSEMBLE_INSTRUCTIONS_UNUSED_H
