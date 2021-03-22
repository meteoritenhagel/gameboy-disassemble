#ifndef GAMEBOY_DISASSEMBLE_INSTRUCTIONS_LOAD_8BIT_H
#define GAMEBOY_DISASSEMBLE_INSTRUCTIONS_LOAD_8BIT_H

#include "interface.h"

/**********************************************************+
 * Helper classes ******************************************
 ***********************************************************/

class InstructionLoadImmediateInto8BitRegister : public Instruction {
protected:
    InstructionLoadImmediateInto8BitRegister(const Register8Bit reg,
                                             const byte immediate,
                                             const Opcode opcode)
            : Instruction("LD " + to_string(reg) + ", " + to_string_hex_prefixed(immediate),
                          opcode,
                          bytestring{immediate}),
              _register(reg),
              _immediate(immediate) {}

//    emulate(VirtualGameboy& gb) const
//    {
//        gb.access_register(_register) = _immediate;
//
//        unsigned cycles = 2;
//        if (_register == Register8Bit::ADDRESS_HL)
//        {
//            ++cycles;
//        }
//        gb.wait(cycles)
//    }

private:
    const Register8Bit _register;
    const byte _immediate;
};


class InstructionLoad8BitRegisterInto8BitRegister : public Instruction {
protected:
    InstructionLoad8BitRegisterInto8BitRegister(const Register8Bit source,
                                                const Register8Bit destination,
                                                const Opcode opcode)
            : Instruction("LD " + to_string(destination) + ", " + to_string(source),
                          opcode),
              _source(source),
              _destination(destination) {}

//    emulate(VirtualGameboy& gb) const
//    {
//        gb.access_register(_destination) = gb.read_register(_register);
//
//        unsigned cycles = 2;
//        if ((_register == Register8Bit::ADDRESS_HL) || (_destination == Register8Bit::ADDRESS_HL))
//        {
//            ++cycles;
//        }
//        gb.wait(cycles)
//    }

private:
    const Register8Bit _source;
    const Register8Bit _destination;
};

/**********************************************************+
 * Public interface ****************************************
 ***********************************************************/

class LoadAIntoAddressImmediate : public Instruction {
public:
    LoadAIntoAddressImmediate(const word immediate)
            : Instruction("LD (" + to_string_hex_prefixed(immediate) + "), A",
                          opcodes::LOAD_A_INTO_ADDRESS_IMMEDIATE),
              _immediate(immediate) {}

//    void emulate(const VirtualGameboy& gb)
//    {
//        gb.dereference(_immediate) = gb.access_register(_register);
//
//        const unsigned cycles = 4;
//        gb.wait(cycles);
//    }

private:
    word _immediate;
};

class LoadAddressImmediateIntoA : public Instruction {
public:
    LoadAddressImmediateIntoA(const word immediate)
            : Instruction("LD A, (" + to_string_hex_prefixed(immediate) + ")",
                          opcodes::LOAD_ADDRESS_IMMEDIATE_INTO_A),
              _immediate(immediate) {}

//    void emulate(const VirtualGameboy& gb)
//    {
//        gb.access_register(_register) = gb.dereference(_immediate);
//
//        const unsigned cycles = 4;
//        gb.wait(cycles);
//    }

private:
    word _immediate;
};

// LOAD with 16 bit addresses

class LoadAIntoAddressBC : public Instruction {
public:
    LoadAIntoAddressBC()
            : Instruction(
            "LD (BC), A", opcodes::LOAD_A_INTO_ADDRESS_BC) {}
};

class LoadAddressBCIntoA : public Instruction {
public:
    LoadAddressBCIntoA()
            : Instruction(
            "LD A, (BC)", opcodes::LOAD_ADDRESS_BC_INTO_A) {}
};

class LoadAIntoAddressDE : public Instruction {
public:
    LoadAIntoAddressDE()
            : Instruction(
            "LD (DE), A", opcodes::LOAD_A_INTO_ADDRESS_DE) {}
};

class LoadAddressDEIntoA : public Instruction {
public:
    LoadAddressDEIntoA()
            : Instruction(
            "LD A, (DE)", opcodes::LOAD_ADDRESS_DE_INTO_A) {}
};

class LoadAIntoAddressHLIncrement : public Instruction {
public:
    LoadAIntoAddressHLIncrement()
            : Instruction(
            "LD (HL+), A", opcodes::LOAD_A_INTO_ADDRESS_HL_INCREMENT) {}
};

class LoadAddressHLIncrementIntoA : public Instruction {
public:
    LoadAddressHLIncrementIntoA()
            : Instruction(
            "LD A, (HL+)", opcodes::LOAD_ADDRESS_HL_INCREMENT_INTO_A) {}
};

class LoadAIntoAddressHLDecrement : public Instruction {
public:
    LoadAIntoAddressHLDecrement()
            : Instruction(
            "LD (HL-), A", opcodes::LOAD_A_INTO_ADDRESS_HL_DECREMENT) {}
};

class LoadAddressHLDecrementIntoA : public Instruction {
public:
    LoadAddressHLDecrementIntoA()
            : Instruction(
            "LD A, (HL-)", opcodes::LOAD_ADDRESS_HL_DECREMENT_INTO_A) {}
};

// Load with port addresses (i.e. 0xFF + 8 bit address)

class LoadAIntoPortAddressImmediate : public Instruction {
public:
    LoadAIntoPortAddressImmediate(const byte portAddress)
            : Instruction("LD (" + to_string_hex_prefixed(portAddress) + "), A",
                          opcodes::LOAD_A_INTO_PORT_ADDRESS_IMMEDIATE),
              _portAddress(portAddress) {}

private:
    byte _portAddress;
};

class LoadAIntoPortAddressC : public Instruction {
public:
    LoadAIntoPortAddressC()
            : Instruction("LD (C), A",
                          opcodes::LOAD_A_INTO_PORT_ADDRESS_C) {}
};

class LoadPortAddressImmediateIntoA : public Instruction {
public:
    LoadPortAddressImmediateIntoA(const byte portAddress)
            : Instruction("LD A, (" + to_string_hex_prefixed(portAddress) + ")",
                          opcodes::LOAD_PORT_ADDRESS_IMMEDIATE_INTO_A),
              _portAddress(portAddress) {}

private:
    byte _portAddress;
};

class LoadPortAddressCIntoA : public Instruction {
public:
    LoadPortAddressCIntoA()
            : Instruction("LD A, (C)",
                          opcodes::LOAD_PORT_ADDRESS_C_INTO_A) {}
};

/** Doubly derived classes ***********************************/

class LoadImmediateIntoB : public InstructionLoadImmediateInto8BitRegister {
public:
    LoadImmediateIntoB(const byte immediate)
            : InstructionLoadImmediateInto8BitRegister(Register8Bit::B,
                                                       immediate,
                                                       opcodes::LOAD_IMMEDIATE_INTO_B) {}
};

class LoadImmediateIntoC : public InstructionLoadImmediateInto8BitRegister {
public:
    LoadImmediateIntoC(const byte immediate)
            : InstructionLoadImmediateInto8BitRegister(Register8Bit::C,
                                                       immediate,
                                                       opcodes::LOAD_IMMEDIATE_INTO_C) {}
};

class LoadImmediateIntoD : public InstructionLoadImmediateInto8BitRegister {
public:
    LoadImmediateIntoD(const byte immediate)
            : InstructionLoadImmediateInto8BitRegister(Register8Bit::D,
                                                       immediate,
                                                       opcodes::LOAD_IMMEDIATE_INTO_D) {}
};

class LoadImmediateIntoE : public InstructionLoadImmediateInto8BitRegister {
public:
    LoadImmediateIntoE(const byte immediate)
            : InstructionLoadImmediateInto8BitRegister(Register8Bit::E,
                                                       immediate,
                                                       opcodes::LOAD_IMMEDIATE_INTO_E) {}
};

class LoadImmediateIntoH : public InstructionLoadImmediateInto8BitRegister {
public:
    LoadImmediateIntoH(const byte immediate)
            : InstructionLoadImmediateInto8BitRegister(Register8Bit::H,
                                                       immediate,
                                                       opcodes::LOAD_IMMEDIATE_INTO_H) {}
};

class LoadImmediateIntoL : public InstructionLoadImmediateInto8BitRegister {
public:
    LoadImmediateIntoL(const byte immediate)
            : InstructionLoadImmediateInto8BitRegister(Register8Bit::L,
                                                       immediate,
                                                       opcodes::LOAD_IMMEDIATE_INTO_L) {}
};

class LoadImmediateIntoAddressHL : public InstructionLoadImmediateInto8BitRegister {
public:
    LoadImmediateIntoAddressHL(const byte immediate)
            : InstructionLoadImmediateInto8BitRegister(Register8Bit::ADDRESS_HL,
                                                       immediate,
                                                       opcodes::LOAD_IMMEDIATE_INTO_ADDRESS_HL) {}
};

class LoadImmediateIntoA : public InstructionLoadImmediateInto8BitRegister {
public:
    LoadImmediateIntoA(const byte immediate)
            : InstructionLoadImmediateInto8BitRegister(Register8Bit::A,
                                                       immediate,
                                                       opcodes::LOAD_IMMEDIATE_INTO_A) {}
};

// LOAD INTO B

class LoadBIntoB : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadBIntoB()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::B,
                                                          Register8Bit::B,
                                                          opcodes::LOAD_B_INTO_B) {}
};

class LoadCIntoB : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadCIntoB()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::C,
                                                          Register8Bit::B,
                                                          opcodes::LOAD_C_INTO_B) {}
};

class LoadDIntoB : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadDIntoB()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::D,
                                                          Register8Bit::B,
                                                          opcodes::LOAD_D_INTO_B) {}
};

class LoadEIntoB : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadEIntoB()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::E,
                                                          Register8Bit::B,
                                                          opcodes::LOAD_E_INTO_B) {}
};

class LoadHIntoB : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadHIntoB()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::H,
                                                          Register8Bit::B,
                                                          opcodes::LOAD_H_INTO_B) {}
};

class LoadLIntoB : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadLIntoB()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::L,
                                                          Register8Bit::B,
                                                          opcodes::LOAD_L_INTO_B) {}
};

class LoadAddressHLIntoB : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadAddressHLIntoB()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::ADDRESS_HL,
                                                          Register8Bit::B,
                                                          opcodes::LOAD_ADDRESS_HL_INTO_B) {}
};

class LoadAIntoB : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadAIntoB()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::A,
                                                          Register8Bit::B,
                                                          opcodes::LOAD_A_INTO_B) {}
};

// LOAD INTO C

class LoadBIntoC : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadBIntoC()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::B,
                                                          Register8Bit::C,
                                                          opcodes::LOAD_B_INTO_C) {}
};

class LoadCIntoC : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadCIntoC()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::C,
                                                          Register8Bit::C,
                                                          opcodes::LOAD_C_INTO_C) {}
};

class LoadDIntoC : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadDIntoC()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::D,
                                                          Register8Bit::C,
                                                          opcodes::LOAD_D_INTO_C) {}
};

class LoadEIntoC : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadEIntoC()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::E,
                                                          Register8Bit::C,
                                                          opcodes::LOAD_E_INTO_C) {}
};

class LoadHIntoC : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadHIntoC()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::H,
                                                          Register8Bit::C,
                                                          opcodes::LOAD_H_INTO_C) {}
};

class LoadLIntoC : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadLIntoC()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::L,
                                                          Register8Bit::C,
                                                          opcodes::LOAD_L_INTO_C) {}
};

class LoadAddressHLIntoC : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadAddressHLIntoC()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::ADDRESS_HL,
                                                          Register8Bit::C,
                                                          opcodes::LOAD_ADDRESS_HL_INTO_C) {}
};

class LoadAIntoC : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadAIntoC()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::A,
                                                          Register8Bit::C,
                                                          opcodes::LOAD_A_INTO_C) {}
};

// LOAD INTO D
class LoadBIntoD : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadBIntoD()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::B,
                                                          Register8Bit::D,
                                                          opcodes::LOAD_B_INTO_D) {}
};

class LoadCIntoD : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadCIntoD()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::C,
                                                          Register8Bit::D,
                                                          opcodes::LOAD_C_INTO_D) {}
};

class LoadDIntoD : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadDIntoD()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::D,
                                                          Register8Bit::D,
                                                          opcodes::LOAD_D_INTO_D) {}
};

class LoadEIntoD : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadEIntoD()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::E,
                                                          Register8Bit::D,
                                                          opcodes::LOAD_E_INTO_D) {}
};

class LoadHIntoD : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadHIntoD()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::H,
                                                          Register8Bit::D,
                                                          opcodes::LOAD_H_INTO_D) {}
};

class LoadLIntoD : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadLIntoD()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::L,
                                                          Register8Bit::D,
                                                          opcodes::LOAD_L_INTO_D) {}
};

class LoadAddressHLIntoD : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadAddressHLIntoD()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::ADDRESS_HL,
                                                          Register8Bit::D,
                                                          opcodes::LOAD_ADDRESS_HL_INTO_D) {}
};

class LoadAIntoD : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadAIntoD()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::A,
                                                          Register8Bit::D,
                                                          opcodes::LOAD_A_INTO_D) {}
};

// LOAD INTO E
class LoadBIntoE : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadBIntoE()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::B,
                                                          Register8Bit::E,
                                                          opcodes::LOAD_B_INTO_E) {}
};

class LoadCIntoE : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadCIntoE()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::C,
                                                          Register8Bit::E,
                                                          opcodes::LOAD_C_INTO_E) {}
};

class LoadDIntoE : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadDIntoE()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::D,
                                                          Register8Bit::E,
                                                          opcodes::LOAD_D_INTO_E) {}
};

class LoadEIntoE : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadEIntoE()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::E,
                                                          Register8Bit::E,
                                                          opcodes::LOAD_E_INTO_E) {}
};

class LoadHIntoE : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadHIntoE()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::H,
                                                          Register8Bit::E,
                                                          opcodes::LOAD_H_INTO_E) {}
};

class LoadLIntoE : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadLIntoE()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::L,
                                                          Register8Bit::E,
                                                          opcodes::LOAD_L_INTO_E) {}
};

class LoadAddressHLIntoE : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadAddressHLIntoE()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::ADDRESS_HL,
                                                          Register8Bit::E,
                                                          opcodes::LOAD_ADDRESS_HL_INTO_E) {}
};

class LoadAIntoE : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadAIntoE()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::A,
                                                          Register8Bit::E,
                                                          opcodes::LOAD_A_INTO_E) {}
};

// LOAD INTO H
class LoadBIntoH : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadBIntoH()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::B,
                                                          Register8Bit::H,
                                                          opcodes::LOAD_B_INTO_H) {}
};

class LoadCIntoH : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadCIntoH()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::C,
                                                          Register8Bit::H,
                                                          opcodes::LOAD_C_INTO_H) {}
};

class LoadDIntoH : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadDIntoH()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::D,
                                                          Register8Bit::H,
                                                          opcodes::LOAD_D_INTO_H) {}
};

class LoadEIntoH : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadEIntoH()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::E,
                                                          Register8Bit::H,
                                                          opcodes::LOAD_E_INTO_H) {}
};

class LoadHIntoH : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadHIntoH()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::H,
                                                          Register8Bit::H,
                                                          opcodes::LOAD_H_INTO_H) {}
};

class LoadLIntoH : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadLIntoH()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::L,
                                                          Register8Bit::H,
                                                          opcodes::LOAD_L_INTO_H) {}
};

class LoadAddressHLIntoH : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadAddressHLIntoH()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::ADDRESS_HL,
                                                          Register8Bit::H,
                                                          opcodes::LOAD_ADDRESS_HL_INTO_H) {}
};

class LoadAIntoH : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadAIntoH()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::A,
                                                          Register8Bit::H,
                                                          opcodes::LOAD_A_INTO_H) {}
};

// LOAD INTO L
class LoadBIntoL : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadBIntoL()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::B,
                                                          Register8Bit::L,
                                                          opcodes::LOAD_B_INTO_L) {}
};

class LoadCIntoL : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadCIntoL()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::C,
                                                          Register8Bit::L,
                                                          opcodes::LOAD_C_INTO_L) {}
};

class LoadDIntoL : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadDIntoL()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::D,
                                                          Register8Bit::L,
                                                          opcodes::LOAD_D_INTO_L) {}
};

class LoadEIntoL : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadEIntoL()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::E,
                                                          Register8Bit::L,
                                                          opcodes::LOAD_E_INTO_L) {}
};

class LoadHIntoL : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadHIntoL()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::H,
                                                          Register8Bit::L,
                                                          opcodes::LOAD_H_INTO_L) {}
};

class LoadLIntoL : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadLIntoL()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::L,
                                                          Register8Bit::L,
                                                          opcodes::LOAD_L_INTO_L) {}
};

class LoadAddressHLIntoL : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadAddressHLIntoL()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::ADDRESS_HL,
                                                          Register8Bit::L,
                                                          opcodes::LOAD_ADDRESS_HL_INTO_L) {}
};

class LoadAIntoL : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadAIntoL()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::A,
                                                          Register8Bit::L,
                                                          opcodes::LOAD_A_INTO_L) {}
};

// LOAD INTO ADDRESS_HL
class LoadBIntoAddressHL : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadBIntoAddressHL()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::B,
                                                          Register8Bit::ADDRESS_HL,
                                                          opcodes::LOAD_B_INTO_ADDRESS_HL) {}
};

class LoadCIntoAddressHL : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadCIntoAddressHL()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::C,
                                                          Register8Bit::ADDRESS_HL,
                                                          opcodes::LOAD_C_INTO_ADDRESS_HL) {}
};

class LoadDIntoAddressHL : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadDIntoAddressHL()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::D,
                                                          Register8Bit::ADDRESS_HL,
                                                          opcodes::LOAD_D_INTO_ADDRESS_HL) {}
};

class LoadEIntoAddressHL : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadEIntoAddressHL()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::E,
                                                          Register8Bit::ADDRESS_HL,
                                                          opcodes::LOAD_E_INTO_ADDRESS_HL) {}
};

class LoadHIntoAddressHL : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadHIntoAddressHL()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::H,
                                                          Register8Bit::ADDRESS_HL,
                                                          opcodes::LOAD_H_INTO_ADDRESS_HL) {}
};

class LoadLIntoAddressHL : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadLIntoAddressHL()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::L,
                                                          Register8Bit::ADDRESS_HL,
                                                          opcodes::LOAD_L_INTO_ADDRESS_HL) {}
};

class LoadAIntoAddressHL : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadAIntoAddressHL()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::A,
                                                          Register8Bit::ADDRESS_HL,
                                                          opcodes::LOAD_A_INTO_ADDRESS_HL) {}
};

// LOAD INTO A
class LoadBIntoA : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadBIntoA()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::B,
                                                          Register8Bit::A,
                                                          opcodes::LOAD_B_INTO_A) {}
};

class LoadCIntoA : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadCIntoA()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::C,
                                                          Register8Bit::A,
                                                          opcodes::LOAD_C_INTO_A) {}
};

class LoadDIntoA : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadDIntoA()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::D,
                                                          Register8Bit::A,
                                                          opcodes::LOAD_D_INTO_A) {}
};

class LoadEIntoA : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadEIntoA()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::E,
                                                          Register8Bit::A,
                                                          opcodes::LOAD_E_INTO_A) {}
};

class LoadHIntoA : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadHIntoA()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::H,
                                                          Register8Bit::A,
                                                          opcodes::LOAD_H_INTO_A) {}
};

class LoadLIntoA : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadLIntoA()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::L,
                                                          Register8Bit::A,
                                                          opcodes::LOAD_L_INTO_A) {}
};

class LoadAddressHLIntoA : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadAddressHLIntoA()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::ADDRESS_HL,
                                                          Register8Bit::A,
                                                          opcodes::LOAD_ADDRESS_HL_INTO_A) {}
};

class LoadAIntoA : public InstructionLoad8BitRegisterInto8BitRegister {
public:
    LoadAIntoA()
            : InstructionLoad8BitRegisterInto8BitRegister(Register8Bit::A,
                                                          Register8Bit::A,
                                                          opcodes::LOAD_A_INTO_A) {}
};

#endif //GAMEBOY_DISASSEMBLE_INSTRUCTIONS_LOAD_8BIT_H
