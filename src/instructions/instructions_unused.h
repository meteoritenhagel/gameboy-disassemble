#ifndef GAMEBOY_DISASSEMBLE_INSTRUCTIONS_UNUSED_H
#define GAMEBOY_DISASSEMBLE_INSTRUCTIONS_UNUSED_H

#include "interface.h"

class Unused : public Instruction {
public:
    Unused(const uint8_t index)
            : Instruction( "??" + to_string_dec(_index),
                          determine_opcode(index)) {}

//    void emulate(VirtualGameboy& gb)
//    {
//        return;
//    }
private:
    Opcode determine_opcode(const uint8_t index) const {
        switch (index) {
            case 0:   return opcodes::UNUSED_0;
            case 1:   return opcodes::UNUSED_1;
            case 2:   return opcodes::UNUSED_2;
            case 3:   return opcodes::UNUSED_3;
            case 4:   return opcodes::UNUSED_4;
            case 5:   return opcodes::UNUSED_5;
            case 6:   return opcodes::UNUSED_6;
            case 7:   return opcodes::UNUSED_7;
            case 8:   return opcodes::UNUSED_8;
            case 9:   return opcodes::UNUSED_9;
            case 10:  return opcodes::UNUSED_10;
            case 11:  return opcodes::UNUSED_11;
            default:  return opcodes::INVALID_OPCODE;
        }
    }

    uint8_t _index;
};

// If not implemented yet
class Unknown : public Instruction {
public:
    Unknown()
            : Instruction("???",
                          opcodes::INVALID_OPCODE) {}
};


#endif //GAMEBOY_DISASSEMBLE_INSTRUCTIONS_UNUSED_H
