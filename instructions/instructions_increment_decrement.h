#ifndef GAMEBOY_DISASSEMBLE_INSTRUCTIONS_INCREMENT_DECREMENT_H
#define GAMEBOY_DISASSEMBLE_INSTRUCTIONS_INCREMENT_DECREMENT_H

#include "instructions_interface.h"

// 8 Bit Registers

class IncrementA : public Instruction
{
public:
    IncrementA()
            : Instruction(opcodes::INCREMENT_A,
                          "INC A")
    {}
};

class DecrementA : public Instruction
{
public:
    DecrementA()
            : Instruction(opcodes::DECREMENT_A,
                          "DEC A")
    {}
};

class IncrementB : public Instruction
{
public:
    IncrementB()
    : Instruction(opcodes::INCREMENT_B,
                  "INC B")
    {}
};

class DecrementB : public Instruction
{
public:
    DecrementB()
    : Instruction(opcodes::DECREMENT_B,
                  "DEC B")
    {}
};

class IncrementC : public Instruction
{
public:
    IncrementC()
    : Instruction(opcodes::INCREMENT_C,
                  "INC B")
    {}
};

class DecrementC : public Instruction
{
public:
    DecrementC()
    : Instruction(opcodes::DECREMENT_C,
                  "DEC C")
    {}
};

class IncrementD : public Instruction
{
public:
    IncrementD()
            : Instruction(opcodes::INCREMENT_D,
                          "INC D")
    {}
};

class DecrementD : public Instruction
{
public:
    DecrementD()
            : Instruction(opcodes::DECREMENT_D,
                          "DEC D")
    {}
};

class IncrementE : public Instruction
{
public:
    IncrementE()
            : Instruction(opcodes::INCREMENT_E,
                          "INC E")
    {}
};

class DecrementE : public Instruction
{
public:
    DecrementE()
            : Instruction(opcodes::DECREMENT_E,
                          "DEC E")
    {}
};

class IncrementH : public Instruction
{
public:
    IncrementH()
            : Instruction(opcodes::INCREMENT_H,
                          "INC H")
    {}
};

class DecrementH : public Instruction
{
public:
    DecrementH()
            : Instruction(opcodes::DECREMENT_H,
                          "DEC H")
    {}
};

class IncrementL : public Instruction
{
public:
    IncrementL()
            : Instruction(opcodes::INCREMENT_L,
                          "INC L")
    {}
};

class DecrementL : public Instruction
{
public:
    DecrementL()
            : Instruction(opcodes::DECREMENT_L,
                          "DEC L")
    {}
};

// Increment contents of memory location

class IncrementAddressHL : public Instruction
{
public:
    IncrementAddressHL()
            : Instruction(opcodes::INCREMENT_ADDRESS_HL,
                          "INC (HL)")
    {}
};

class DecrementAddressHL : public Instruction
{
public:
    DecrementAddressHL()
            : Instruction(opcodes::DECREMENT_ADDRESS_HL,
                          "DEC (HL)")
    {}
};


// 16 Bit Registers

class IncrementBC : public Instruction
{
public:
    IncrementBC()
    : Instruction(opcodes::INCREMENT_BC,
                  "INC BC")
    {}
};

class DecrementBC : public Instruction
{
public:
    DecrementBC()
    : Instruction(opcodes::DECREMENT_BC,
                  "DEC BC")
    {}

};

class IncrementDE : public Instruction
{
public:
    IncrementDE()
            : Instruction(opcodes::INCREMENT_DE,
                          "INC DE")
    {}
};

class DecrementDE : public Instruction
{
public:
    DecrementDE()
            : Instruction(opcodes::DECREMENT_DE,
                          "DEC DE")
    {}

};

class IncrementHL : public Instruction
{
public:
    IncrementHL()
            : Instruction(opcodes::INCREMENT_HL,
                          "INC HL")
    {}
};

class DecrementHL : public Instruction
{
public:
    DecrementHL()
            : Instruction(opcodes::DECREMENT_HL,
                          "DEC HL")
    {}

};

class IncrementSP : public Instruction
{
public:
    IncrementSP()
            : Instruction(opcodes::INCREMENT_SP,
                          "INC SP")
    {}
};

class DecrementSP : public Instruction
{
public:
    DecrementSP()
            : Instruction(opcodes::DECREMENT_SP,
                          "DEC SP")
    {}

};

#endif //GAMEBOY_DISASSEMBLE_INSTRUCTIONS_INCREMENT_DECREMENT_H
