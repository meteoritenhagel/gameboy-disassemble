#ifndef GAMEBOY_DEBUG_INSTRUCTIONS_H
#define GAMEBOY_DEBUG_INSTRUCTIONS_H

#include "instructions_interface.h"

#include "instructions_increment_decrement.h"
#include "instructions_add_subtract.h"
#include "instructions_jump.h"
#include "instructions_load_8bit.h"
#include "instructions_load_16bit.h"
#include "instructions_rotation.h"

#include <memory>
#include <vector>;

class Nop : public Instruction
{
public:
    Nop()
    : Instruction(opcodes::NOP,
                  "NOP")
    {}
};

class Stop : public Instruction
{
public:
    Stop(const uint8_t ignored)
    : Instruction(opcodes::STOP,
                  "STOP")
    {}
private:
    uint8_t _ignored;
};

class Halt : public Instruction
{
public:
    Halt()
    : Instruction(opcodes::HALT,
                  "HALT")
    {}
};

//


#endif //GAMEBOY_DEBUG_INSTRUCTIONS_H
