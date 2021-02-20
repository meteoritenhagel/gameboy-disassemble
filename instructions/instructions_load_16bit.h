#ifndef GAMEBOY_DISASSEMBLE_INSTRUCTIONS_LOAD_16BIT_H
#define GAMEBOY_DISASSEMBLE_INSTRUCTIONS_LOAD_16BIT_H

#include "instructions_interface.h"

class InstructionLoadImmediateInto16BitRegister : public Instruction {
protected:
    InstructionLoadImmediateInto16BitRegister(const Register16Bit reg,
                                              const word immediate,
                                              const Opcode opcode)
            : Instruction("LD " + to_string(reg) + ", " + to_string_hex_prefixed(immediate),
                          opcode,
                          to_bytestring_little_endian(immediate)),
              _register(reg),
              _immediate(immediate) {}

//    emulate(VirtualGameboy& gb) const
//    {
//        gb.access_register(_destination) = gb.read_register(_register);
//
//        unsigned cycles = 3;
//        gb.wait(cycles)
//    }

private:
    const Register16Bit _register;
    const word _immediate;
};

class LoadSPIntoAddressImmediate : public Instruction {
public:
    LoadSPIntoAddressImmediate(const word immediate)
            : Instruction("LD (" + to_string_hex_prefixed(immediate) + "), SP",
                          opcodes::LOAD_SP_INTO_ADDRESS_IMMEDIATE,
                          to_bytestring_little_endian(immediate)),
              _immediate(immediate) {}

//    emulate(VirtualGameboy& gb)
//    {
//        gb.dereference(_immediate) = gb.access_register(Register16Bit::SP);
//        unsigned cycles = 5;
//        gb.wait(cycles);
//    }

private:
    word _immediate;
};

class LoadHLIntoSP : public Instruction {
public:
    LoadHLIntoSP()
            : Instruction("LD SP, HL",
                          opcodes::LOAD_HL_INTO_SP) {}

//    emulate(VirtualGameboy& gb)
//    {
//        gb.access_register(Register16Bit::SP) = gb.access_register(Register16Bit::HL);
//        unsigned cycles = 2;
//        gb.wait(cycles);
//    }
};

class LoadSPShiftedByImmediateIntoHL : public Instruction {
public:
    LoadSPShiftedByImmediateIntoHL(const byte immediate)
            : Instruction("LD HL, SP+" + to_string_hex_signed_prefixed(immediate),
                          opcodes::LOAD_SP_SHIFTED_BY_IMMEDIATE_INTO_HL,
                          to_bytestring_little_endian(immediate)),
              _immediate(immediate) {}

//    emulate(VirtualGameboy& gb)
//    {
//        gb.access_register(Register16Bit::HL) = gb.access_register(Register16Bit::SP) + extend_sign(_immediate);
//        unsigned cycles = 3;
//        gb.wait(cycles);
//    }

private:
    byte _immediate;
};


// Derived classes

class LoadImmediateIntoBC : public InstructionLoadImmediateInto16BitRegister {
public:
    LoadImmediateIntoBC(const word immediate)
            : InstructionLoadImmediateInto16BitRegister(Register16Bit::BC,
                                                        immediate,
                                                        opcodes::LOAD_IMMEDIATE_INTO_BC) {}
};

class LoadImmediateIntoDE : public InstructionLoadImmediateInto16BitRegister {
public:
    LoadImmediateIntoDE(const word immediate)
            : InstructionLoadImmediateInto16BitRegister(Register16Bit::DE,
                                                        immediate,
                                                        opcodes::LOAD_IMMEDIATE_INTO_DE) {}
};

class LoadImmediateIntoHL : public InstructionLoadImmediateInto16BitRegister {
public:
    LoadImmediateIntoHL(const word immediate)
            : InstructionLoadImmediateInto16BitRegister(Register16Bit::HL,
                                                        immediate,
                                                        opcodes::LOAD_IMMEDIATE_INTO_HL) {}
};

class LoadImmediateIntoSP : public InstructionLoadImmediateInto16BitRegister {
public:
    LoadImmediateIntoSP(const word immediate)
            : InstructionLoadImmediateInto16BitRegister(Register16Bit::SP,
                                                        immediate,
                                                        opcodes::LOAD_IMMEDIATE_INTO_SP) {}
};

#endif //GAMEBOY_DISASSEMBLE_INSTRUCTIONS_LOAD_16BIT_H
