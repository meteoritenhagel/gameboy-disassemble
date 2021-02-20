#ifndef GAMEBOY_DISASSEMBLE_INSTRUCTIONS_UNUSED_H
#define GAMEBOY_DISASSEMBLE_INSTRUCTIONS_UNUSED_H

#include "instructions_interface.h"

// If not implemented yet
class Unknown : public Instruction {
public:
    Unknown()
            : Instruction("???",
                          opcodes::NOP) {}
};

class InstructionUnused : public Instruction {
protected:
    InstructionUnused(const std::string &string,
                      const Opcode opcode)
            : Instruction(string,
                          opcode) {}

//    void emulate(VirtualGameboy& gb)
//    {
//        return;
//    }
};


// child classes:

class Unused0 : public InstructionUnused {
public:
    Unused0()
            : InstructionUnused("??0",
                                opcodes::UNUSED_0) {}
};

class Unused1 : public InstructionUnused {
public:
    Unused1()
            : InstructionUnused("??1",
                                opcodes::UNUSED_1) {}
};

class Unused2 : public InstructionUnused {
public:
    Unused2()
            : InstructionUnused("??2",
                                opcodes::UNUSED_2) {}
};

class Unused3 : public InstructionUnused {
public:
    Unused3()
            : InstructionUnused("??3",
                                opcodes::UNUSED_3) {}
};

class Unused4 : public InstructionUnused {
public:
    Unused4()
            : InstructionUnused("??4",
                                opcodes::UNUSED_4) {}
};

class Unused5 : public InstructionUnused {
public:
    Unused5()
            : InstructionUnused("??5",
                                opcodes::UNUSED_5) {}
};

class Unused6 : public InstructionUnused {
public:
    Unused6()
            : InstructionUnused("??6",
                                opcodes::UNUSED_6) {}
};

class Unused7 : public InstructionUnused {
public:
    Unused7()
            : InstructionUnused("??7",
                                opcodes::UNUSED_7) {}
};

class Unused8 : public InstructionUnused {
public:
    Unused8()
            : InstructionUnused("??8",
                                opcodes::UNUSED_8) {}
};

class Unused9 : public InstructionUnused {
public:
    Unused9()
            : InstructionUnused("??9",
                                opcodes::UNUSED_9) {}
};

class Unused10 : public InstructionUnused {
public:
    Unused10()
            : InstructionUnused("?10",
                                opcodes::UNUSED_10) {}
};

class Unused11 : public InstructionUnused {
public:
    Unused11()
            : InstructionUnused("?11",
                                opcodes::UNUSED_11) {}
};

#endif //GAMEBOY_DISASSEMBLE_INSTRUCTIONS_UNUSED_H
