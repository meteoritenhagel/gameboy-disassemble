#ifndef GAMEBOY_DISASSEMBLE_INSTRUCTIONS_LOAD_16BIT_H
#define GAMEBOY_DISASSEMBLE_INSTRUCTIONS_LOAD_16BIT_H

#include "interface.h"

class LoadImmediateInto16BitRegister : public Instruction {
public:
    LoadImmediateInto16BitRegister(const Register16Bit destination,
                                   const word immediate)
            : Instruction("LD " + to_string(destination) + ", " + to_string_hex_prefixed(immediate),
                          determine_opcode(destination),
                          to_bytestring_little_endian(immediate)),
              _destination(destination),
              _immediate(immediate) {}

//    emulate(VirtualGameboy& gb) const
//    {
//        gb.access_register(_destination) = gb.read_register(_destination);
//
//        unsigned cycles = 3;
//        gb.wait(cycles)
//    }

private:
    Opcode determine_opcode(const Register16Bit destination) {
        switch(destination) {
            case Register16Bit::BC: return opcodes::LOAD_IMMEDIATE_INTO_BC;
            case Register16Bit::DE: return opcodes::LOAD_IMMEDIATE_INTO_DE;
            case Register16Bit::HL: return opcodes::LOAD_IMMEDIATE_INTO_HL;
            case Register16Bit::SP: return opcodes::LOAD_IMMEDIATE_INTO_SP;
            default:                return opcodes::INVALID_OPCODE;
        }
    }

    const Register16Bit _destination;
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
            : Instruction("LDHL SP," + to_string_hex_signed_prefixed(immediate),
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

#endif //GAMEBOY_DISASSEMBLE_INSTRUCTIONS_LOAD_16BIT_H
