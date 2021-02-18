//
// Created by tristan on 16.02.21.
//

#ifndef GAMEBOY_DISASSEMBLE_INSTRUCTIONS_LOAD_8BIT_H
#define GAMEBOY_DISASSEMBLE_INSTRUCTIONS_LOAD_8BIT_H

#include "instructions_interface.h"

class LoadImmediateIntoA : public Instruction
{
public:
    LoadImmediateIntoA(const uint8_t immediate)
    : Instruction(opcodes::LOAD_IMMEDIATE_INTO_A,
                  "LD A, " + to_string_hex_prefixed(immediate),
                  bytestring{immediate}),
      _immediate(immediate)
    {}
private:
    uint8_t _immediate;
};

class LoadImmediateIntoB : public Instruction
{
public:
    LoadImmediateIntoB(const uint8_t immediate)
    : Instruction(opcodes::LOAD_IMMEDIATE_INTO_B,
                  "LD B, " + to_string_hex_prefixed(immediate),
                  bytestring{immediate}),
      _immediate(immediate)
    {}
private:
    uint8_t _immediate;
};

class LoadImmediateIntoC : public Instruction
{
public:
    LoadImmediateIntoC(const uint8_t immediate)
    : Instruction(opcodes::LOAD_IMMEDIATE_INTO_C,
                  "LD C, " + to_string_hex_prefixed(immediate),
                  bytestring{immediate}),
      _immediate(immediate)
    {}
private:
    uint8_t _immediate;
};

class LoadImmediateIntoD : public Instruction
{
public:
    LoadImmediateIntoD(const uint8_t immediate)
    : Instruction(opcodes::LOAD_IMMEDIATE_INTO_D,
                  "LD D, " + to_string_hex_prefixed(immediate),
                  bytestring{immediate}),
      _immediate(immediate)
    {}
private:
    uint8_t _immediate;
};

class LoadImmediateIntoE : public Instruction
{
public:
    LoadImmediateIntoE(const uint8_t immediate)
    : Instruction(opcodes::LOAD_IMMEDIATE_INTO_E,
                  "LD E, " + to_string_hex_prefixed(immediate),
                  bytestring{immediate}),
      _immediate(immediate)
    {}
private:
    uint8_t _immediate;
};

class LoadImmediateIntoH : public Instruction
{
public:
    LoadImmediateIntoH(const uint8_t immediate)
    : Instruction(opcodes::LOAD_IMMEDIATE_INTO_H,
                  "LD H, " + to_string_hex_prefixed(immediate),
                  bytestring{immediate}),
      _immediate(immediate)
    {}
private:
    uint8_t _immediate;
};

class LoadImmediateIntoL : public Instruction
{
public:
    LoadImmediateIntoL(const uint8_t immediate)
    : Instruction(opcodes::LOAD_IMMEDIATE_INTO_L,
                  "LD L, " + to_string_hex_prefixed(immediate),
                  bytestring{immediate}),
      _immediate(immediate)
    {}
private:
    uint8_t _immediate;
};

class LoadImmediateIntoAddressHL : public Instruction
{
public:
    LoadImmediateIntoAddressHL(const uint8_t immediate)
            : Instruction(opcodes::LOAD_IMMEDIATE_INTO_ADDRESS_HL,
                          "LD (HL), " + to_string_hex_prefixed(immediate),
                          bytestring{immediate}),
              _immediate(immediate)
    {}
private:
    uint8_t _immediate;
};

// LOAD INTO B

class LoadBIntoB : public Instruction
{
public:
    LoadBIntoB()
            : Instruction(opcodes::LOAD_B_INTO_B,
                          "LD B, B")
    {}
};

class LoadCIntoB : public Instruction
{
public:
    LoadCIntoB()
            : Instruction(opcodes::LOAD_C_INTO_B,
                          "LD B, C")
    {}
};

class LoadDIntoB : public Instruction
{
public:
    LoadDIntoB()
            : Instruction(opcodes::LOAD_D_INTO_B,
                          "LD B, D")
    {}
};

class LoadEIntoB : public Instruction
{
public:
    LoadEIntoB()
            : Instruction(opcodes::LOAD_E_INTO_B,
                          "LD B, E")
    {}
};

class LoadHIntoB : public Instruction
{
public:
    LoadHIntoB()
            : Instruction(opcodes::LOAD_H_INTO_B,
                          "LD B, H")
    {}
};

class LoadLIntoB : public Instruction
{
public:
    LoadLIntoB()
            : Instruction(opcodes::LOAD_L_INTO_B,
                          "LD B, L")
    {}
};

class LoadAddressHLIntoB : public Instruction
{
public:
    LoadAddressHLIntoB()
            : Instruction(opcodes::LOAD_ADDRESS_HL_INTO_B,
                          "LD B, (HL)")
    {}
};

class LoadAIntoB : public Instruction
{
public:
    LoadAIntoB()
            : Instruction(opcodes::LOAD_A_INTO_B,
                          "LD B, A")
    {}
};

// LOAD INTO C

class LoadBIntoC : public Instruction
{
public:
    LoadBIntoC()
            : Instruction(opcodes::LOAD_B_INTO_C,
                          "LD C, B")
    {}
};

class LoadCIntoC : public Instruction
{
public:
    LoadCIntoC()
            : Instruction(opcodes::LOAD_C_INTO_C,
                          "LD C, C")
    {}
};

class LoadDIntoC : public Instruction
{
public:
    LoadDIntoC()
            : Instruction(opcodes::LOAD_D_INTO_C,
                          "LD C, D")
    {}
};

class LoadEIntoC : public Instruction
{
public:
    LoadEIntoC()
            : Instruction(opcodes::LOAD_E_INTO_C,
                          "LD C, E")
    {}
};

class LoadHIntoC : public Instruction
{
public:
    LoadHIntoC()
            : Instruction(opcodes::LOAD_H_INTO_C,
                          "LD C, H")
    {}
};

class LoadLIntoC : public Instruction
{
public:
    LoadLIntoC()
            : Instruction(opcodes::LOAD_L_INTO_C,
                          "LD C, L")
    {}
};


class LoadAddressHLIntoC : public Instruction
{
public:
    LoadAddressHLIntoC()
            : Instruction(opcodes::LOAD_ADDRESS_HL_INTO_C,
                          "LD C, (HL)")
    {}
};

class LoadAIntoC : public Instruction
{
public:
    LoadAIntoC()
            : Instruction(opcodes::LOAD_A_INTO_C,
                          "LD C, A")
    {}
};

// LOAD INTO D
class LoadBIntoD : public Instruction
{
public:
    LoadBIntoD()
            : Instruction(opcodes::LOAD_B_INTO_D,
                          "LD D, B")
    {}
};

class LoadCIntoD : public Instruction
{
public:
    LoadCIntoD()
            : Instruction(opcodes::LOAD_C_INTO_D,
                          "LD D, C")
    {}
};

class LoadDIntoD : public Instruction
{
public:
    LoadDIntoD()
            : Instruction(opcodes::LOAD_D_INTO_D,
                          "LD D, D")
    {}
};

class LoadEIntoD : public Instruction
{
public:
    LoadEIntoD()
            : Instruction(opcodes::LOAD_E_INTO_D,
                          "LD D, E")
    {}
};

class LoadHIntoD : public Instruction
{
public:
    LoadHIntoD()
            : Instruction(opcodes::LOAD_H_INTO_D,
                          "LD D, H")
    {}
};

class LoadLIntoD : public Instruction
{
public:
    LoadLIntoD()
            : Instruction(opcodes::LOAD_L_INTO_D,
                          "LD D, L")
    {}
};

class LoadAddressHLIntoD : public Instruction
{
public:
    LoadAddressHLIntoD()
            : Instruction(opcodes::LOAD_ADDRESS_HL_INTO_D,
                          "LD D, (HL)")
    {}
};

class LoadAIntoD : public Instruction
{
public:
    LoadAIntoD()
            : Instruction(opcodes::LOAD_A_INTO_D,
                          "LD D, A")
    {}
};

// LOAD INTO E
class LoadBIntoE : public Instruction
{
public:
    LoadBIntoE()
            : Instruction(opcodes::LOAD_B_INTO_E,
                          "LD E, B")
    {}
};

class LoadCIntoE : public Instruction
{
public:
    LoadCIntoE()
            : Instruction(opcodes::LOAD_C_INTO_E,
                          "LD E, C")
    {}
};

class LoadDIntoE : public Instruction
{
public:
    LoadDIntoE()
            : Instruction(opcodes::LOAD_D_INTO_E,
                          "LD E, D")
    {}
};

class LoadEIntoE : public Instruction
{
public:
    LoadEIntoE()
            : Instruction(opcodes::LOAD_E_INTO_E,
                          "LD E, E")
    {}
};

class LoadHIntoE : public Instruction
{
public:
    LoadHIntoE()
            : Instruction(opcodes::LOAD_H_INTO_E,
                          "LD E, H")
    {}
};

class LoadLIntoE : public Instruction
{
public:
    LoadLIntoE()
            : Instruction(opcodes::LOAD_L_INTO_E,
                          "LD E, L")
    {}
};


class LoadAddressHLIntoE : public Instruction
{
public:
    LoadAddressHLIntoE()
            : Instruction(opcodes::LOAD_ADDRESS_HL_INTO_E,
                          "LD E, (HL)")
    {}
};

class LoadAIntoE : public Instruction
{
public:
    LoadAIntoE()
            : Instruction(opcodes::LOAD_A_INTO_E,
                          "LD E, A")
    {}
};

// LOAD INTO H
class LoadBIntoH : public Instruction
{
public:
    LoadBIntoH()
            : Instruction(opcodes::LOAD_B_INTO_H,
                          "LD H, B")
    {}
};

class LoadCIntoH : public Instruction
{
public:
    LoadCIntoH()
            : Instruction(opcodes::LOAD_C_INTO_H,
                          "LD H, C")
    {}
};

class LoadDIntoH : public Instruction
{
public:
    LoadDIntoH()
            : Instruction(opcodes::LOAD_D_INTO_H,
                          "LD H, D")
    {}
};

class LoadEIntoH : public Instruction
{
public:
    LoadEIntoH()
            : Instruction(opcodes::LOAD_E_INTO_H,
                          "LD H, E")
    {}
};

class LoadHIntoH : public Instruction
{
public:
    LoadHIntoH()
            : Instruction(opcodes::LOAD_H_INTO_H,
                          "LD H, H")
    {}
};

class LoadLIntoH : public Instruction
{
public:
    LoadLIntoH()
            : Instruction(opcodes::LOAD_L_INTO_H,
                          "LD H, L")
    {}
};

class LoadAddressHLIntoH : public Instruction
{
public:
    LoadAddressHLIntoH()
            : Instruction(opcodes::LOAD_ADDRESS_HL_INTO_H,
                          "LD H, (HL)")
    {}
};

class LoadAIntoH : public Instruction
{
public:
    LoadAIntoH()
            : Instruction(opcodes::LOAD_A_INTO_H,
                          "LD H, A")
    {}
};

// LOAD INTO L
class LoadBIntoL : public Instruction
{
public:
    LoadBIntoL()
            : Instruction(opcodes::LOAD_B_INTO_L,
                          "LD L, B")
    {}
};

class LoadCIntoL : public Instruction
{
public:
    LoadCIntoL()
            : Instruction(opcodes::LOAD_C_INTO_L,
                          "LD L, C")
    {}
};

class LoadDIntoL : public Instruction
{
public:
    LoadDIntoL()
            : Instruction(opcodes::LOAD_D_INTO_L,
                          "LD L, D")
    {}
};

class LoadEIntoL : public Instruction
{
public:
    LoadEIntoL()
            : Instruction(opcodes::LOAD_E_INTO_L,
                          "LD L, E")
    {}
};

class LoadHIntoL : public Instruction
{
public:
    LoadHIntoL()
            : Instruction(opcodes::LOAD_H_INTO_L,
                          "LD L, H")
    {}
};

class LoadLIntoL : public Instruction
{
public:
    LoadLIntoL()
            : Instruction(opcodes::LOAD_L_INTO_L,
                          "LD L, L")
    {}
};

class LoadAddressHLIntoL : public Instruction
{
public:
    LoadAddressHLIntoL()
            : Instruction(opcodes::LOAD_ADDRESS_HL_INTO_L,
                          "LD L, (HL)")
    {}
};

class LoadAIntoL : public Instruction
{
public:
    LoadAIntoL()
            : Instruction(opcodes::LOAD_A_INTO_L,
                          "LD L, A")
    {}
};

// LOAD INTO ADDRESS_HL

class LoadBIntoAddressHL : public Instruction
{
public:
    LoadBIntoAddressHL()
            : Instruction(opcodes::LOAD_B_INTO_ADDRESS_HL,
                          "LD (HL), B")
    {}
};

class LoadCIntoAddressHL: public Instruction
{
public:
    LoadCIntoAddressHL()
            : Instruction(opcodes::LOAD_C_INTO_ADDRESS_HL,
                          "LD (HL), C")
    {}
};

class LoadDIntoAddressHL : public Instruction
{
public:
    LoadDIntoAddressHL()
            : Instruction(opcodes::LOAD_D_INTO_ADDRESS_HL,
                          "LD (HL), D")
    {}
};

class LoadEIntoAddressHL : public Instruction
{
public:
    LoadEIntoAddressHL()
            : Instruction(opcodes::LOAD_E_INTO_ADDRESS_HL,
                          "LD (HL), E")
    {}
};

class LoadHIntoAddressHL : public Instruction
{
public:
    LoadHIntoAddressHL()
            : Instruction(opcodes::LOAD_H_INTO_ADDRESS_HL,
                          "LD (HL), H")
    {}
};

class LoadLIntoAddressHL : public Instruction
{
public:
    LoadLIntoAddressHL()
            : Instruction(opcodes::LOAD_L_INTO_ADDRESS_HL,
                          "LD (HL), L")
    {}
};

class LoadAIntoAddressHL : public Instruction
{
public:
    LoadAIntoAddressHL()
            : Instruction(opcodes::LOAD_A_INTO_ADDRESS_HL,
                          "LD (HL), A")
    {}
};

// LOAD INTO A
class LoadBIntoA : public Instruction
{
public:
    LoadBIntoA()
            : Instruction(opcodes::LOAD_B_INTO_A,
                          "LD A, B")
    {}
};

class LoadCIntoA : public Instruction
{
public:
    LoadCIntoA()
            : Instruction(opcodes::LOAD_C_INTO_A,
                          "LD A, C")
    {}
};

class LoadDIntoA : public Instruction
{
public:
    LoadDIntoA()
            : Instruction(opcodes::LOAD_D_INTO_A,
                          "LD A, D")
    {}
};

class LoadEIntoA : public Instruction
{
public:
    LoadEIntoA()
            : Instruction(opcodes::LOAD_E_INTO_A,
                          "LD A, E")
    {}
};

class LoadHIntoA : public Instruction
{
public:
    LoadHIntoA()
            : Instruction(opcodes::LOAD_H_INTO_A,
                          "LD A, H")
    {}
};

class LoadLIntoA : public Instruction
{
public:
    LoadLIntoA()
            : Instruction(opcodes::LOAD_L_INTO_A,
                          "LD A, L")
    {}
};


class LoadAddressHLIntoA : public Instruction
{
public:
    LoadAddressHLIntoA()
            : Instruction(opcodes::LOAD_ADDRESS_HL_INTO_A,
                          "LD A, (HL)")
    {}
};

class LoadAIntoA : public Instruction
{
public:
    LoadAIntoA()
            : Instruction(opcodes::LOAD_A_INTO_A,
                          "LD A, A")
    {}
};

// LOAD with 16 bit addresses

class LoadAIntoAddressBC : public Instruction
{
public:
    LoadAIntoAddressBC()
            : Instruction(opcodes::LOAD_A_INTO_ADDRESS_BC,
                          "LD (BC), A")
    {}
};

class LoadAddressBCIntoA : public Instruction
{
public:
    LoadAddressBCIntoA()
            : Instruction(opcodes::LOAD_ADDRESS_BC_INTO_A,
                          "LD A, (BC)")
    {}
};

class LoadAIntoAddressDE : public Instruction
{
public:
    LoadAIntoAddressDE()
            : Instruction(opcodes::LOAD_A_INTO_ADDRESS_DE,
                          "LD (DE), A")
    {}
};

class LoadAddressDEIntoA : public Instruction
{
public:
    LoadAddressDEIntoA()
            : Instruction(opcodes::LOAD_ADDRESS_DE_INTO_A,
                          "LD A, (DE)")
    {}
};

class LoadAIntoAddressHLIncrement : public Instruction
{
public:
    LoadAIntoAddressHLIncrement()
            : Instruction(opcodes::LOAD_A_INTO_ADDRESS_HL_INCREMENT,
                          "LD (HL+), A")
    {}
};

class LoadAddressHLIncrementIntoA : public Instruction
{
public:
    LoadAddressHLIncrementIntoA()
            : Instruction(opcodes::LOAD_ADDRESS_HL_INCREMENT_INTO_A,
                          "LD A, (HL+)")
    {}
};

class LoadAIntoAddressHLDecrement : public Instruction
{
public:
    LoadAIntoAddressHLDecrement()
            : Instruction(opcodes::LOAD_A_INTO_ADDRESS_HL_DECREMENT,
                          "LD (HL-), A")
    {}
};

class LoadAddressHLDecrementIntoA : public Instruction
{
public:
    LoadAddressHLDecrementIntoA()
            : Instruction(opcodes::LOAD_ADDRESS_HL_DECREMENT_INTO_A,
                          "LD A, (HL-)")
    {}
};


#endif //GAMEBOY_DISASSEMBLE_INSTRUCTIONS_LOAD_8BIT_H
