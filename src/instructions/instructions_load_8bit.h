#ifndef GAMEBOY_DISASSEMBLE_INSTRUCTIONS_LOAD_8BIT_H
#define GAMEBOY_DISASSEMBLE_INSTRUCTIONS_LOAD_8BIT_H

#include "baseinstruction.h"

class LoadImmediateInto8BitRegister : public BaseInstruction {
public:
    LoadImmediateInto8BitRegister(const Register8Bit destination = {},
                                  const byte immediate = {})
            : BaseInstruction("LD " + to_string(destination) + ", " + to_string_hex_prefixed(immediate),
                              determine_opcode(destination),
                              Bytestring{immediate}),
              _destination(destination),
              _immediate(immediate) {}

//    emulate(VirtualGameboy& gb) const
//    {
//        gb.access_register(_destination) = _immediate;
//
//        unsigned cycles = 2;
//        if (_destination == Register8Bit::ADDRESS_HL)
//        {
//            ++cycles;
//        }
//        gb.wait(cycles)
//    }

private:
    Opcode determine_opcode(const Register8Bit destination) const {
        switch (destination) {
            case Register8Bit::B:          return opcodes::LOAD_IMMEDIATE_INTO_B;
            case Register8Bit::C:          return opcodes::LOAD_IMMEDIATE_INTO_C;
            case Register8Bit::D:          return opcodes::LOAD_IMMEDIATE_INTO_D;
            case Register8Bit::E:          return opcodes::LOAD_IMMEDIATE_INTO_E;
            case Register8Bit::H:          return opcodes::LOAD_IMMEDIATE_INTO_H;
            case Register8Bit::L:          return opcodes::LOAD_IMMEDIATE_INTO_L;
            case Register8Bit::ADDRESS_HL: return opcodes::LOAD_IMMEDIATE_INTO_ADDRESS_HL;
            case Register8Bit::A:          return opcodes::LOAD_IMMEDIATE_INTO_A;
            default:                       return opcodes::INVALID_OPCODE;
        }
    }

    const Register8Bit _destination;
    const byte _immediate;
};

class Load8BitRegisterInto8BitRegister : public BaseInstruction {
public:
    Load8BitRegisterInto8BitRegister(const Register8Bit source = {},
                                     const Register8Bit destination = {})
            : BaseInstruction("LD " + to_string(destination) + ", " + to_string(source),
                              determine_opcode(source, destination)),
              _source(source),
              _destination(destination) {}

//    emulate(VirtualGameboy& gb) const
//    {
//        gb.access_register(_destination) = gb.read_register(_destination);
//
//        unsigned cycles = 2;
//        if ((_destination == Register8Bit::ADDRESS_HL) || (_destination == Register8Bit::ADDRESS_HL))
//        {
//            ++cycles;
//        }
//        gb.wait(cycles)
//    }

private:
    Opcode determine_opcode(const Register8Bit source, const Register8Bit destination) const {
        switch (source) {
            case Register8Bit::B: switch (destination) {
                    case Register8Bit::B:          return opcodes::LOAD_B_INTO_B;
                    case Register8Bit::C:          return opcodes::LOAD_C_INTO_B;
                    case Register8Bit::D:          return opcodes::LOAD_D_INTO_B;
                    case Register8Bit::E:          return opcodes::LOAD_E_INTO_B;
                    case Register8Bit::H:          return opcodes::LOAD_H_INTO_B;
                    case Register8Bit::L:          return opcodes::LOAD_L_INTO_B;
                    case Register8Bit::ADDRESS_HL: return opcodes::LOAD_ADDRESS_HL_INTO_B;
                    case Register8Bit::A:          return opcodes::LOAD_A_INTO_B;
                    default:                       break;
                }
            case Register8Bit::C: switch (destination) {
                    case Register8Bit::B:          return opcodes::LOAD_B_INTO_C;
                    case Register8Bit::C:          return opcodes::LOAD_C_INTO_C;
                    case Register8Bit::D:          return opcodes::LOAD_D_INTO_C;
                    case Register8Bit::E:          return opcodes::LOAD_E_INTO_C;
                    case Register8Bit::H:          return opcodes::LOAD_H_INTO_C;
                    case Register8Bit::L:          return opcodes::LOAD_L_INTO_C;
                    case Register8Bit::ADDRESS_HL: return opcodes::LOAD_ADDRESS_HL_INTO_C;
                    case Register8Bit::A:          return opcodes::LOAD_A_INTO_C;
                    default:                       break;
                }
            case Register8Bit::D: switch (destination) {
                    case Register8Bit::B:          return opcodes::LOAD_B_INTO_D;
                    case Register8Bit::C:          return opcodes::LOAD_C_INTO_D;
                    case Register8Bit::D:          return opcodes::LOAD_D_INTO_D;
                    case Register8Bit::E:          return opcodes::LOAD_E_INTO_D;
                    case Register8Bit::H:          return opcodes::LOAD_H_INTO_D;
                    case Register8Bit::L:          return opcodes::LOAD_L_INTO_D;
                    case Register8Bit::ADDRESS_HL: return opcodes::LOAD_ADDRESS_HL_INTO_D;
                    case Register8Bit::A:          return opcodes::LOAD_A_INTO_D;
                    default:                       break;
                }
            case Register8Bit::E: switch (destination) {
                    case Register8Bit::B:          return opcodes::LOAD_B_INTO_E;
                    case Register8Bit::C:          return opcodes::LOAD_C_INTO_E;
                    case Register8Bit::D:          return opcodes::LOAD_D_INTO_E;
                    case Register8Bit::E:          return opcodes::LOAD_E_INTO_E;
                    case Register8Bit::H:          return opcodes::LOAD_H_INTO_E;
                    case Register8Bit::L:          return opcodes::LOAD_L_INTO_E;
                    case Register8Bit::ADDRESS_HL: return opcodes::LOAD_ADDRESS_HL_INTO_E;
                    case Register8Bit::A:          return opcodes::LOAD_A_INTO_E;
                    default:                       break;
                }
            case Register8Bit::H: switch (destination) {
                    case Register8Bit::B:          return opcodes::LOAD_B_INTO_H;
                    case Register8Bit::C:          return opcodes::LOAD_C_INTO_H;
                    case Register8Bit::D:          return opcodes::LOAD_D_INTO_H;
                    case Register8Bit::E:          return opcodes::LOAD_E_INTO_H;
                    case Register8Bit::H:          return opcodes::LOAD_H_INTO_H;
                    case Register8Bit::L:          return opcodes::LOAD_L_INTO_H;
                    case Register8Bit::ADDRESS_HL: return opcodes::LOAD_ADDRESS_HL_INTO_H;
                    case Register8Bit::A:          return opcodes::LOAD_A_INTO_H;
                    default:                       break;
                }
            case Register8Bit::L: switch (destination) {
                    case Register8Bit::B:          return opcodes::LOAD_B_INTO_L;
                    case Register8Bit::C:          return opcodes::LOAD_C_INTO_L;
                    case Register8Bit::D:          return opcodes::LOAD_D_INTO_L;
                    case Register8Bit::E:          return opcodes::LOAD_E_INTO_L;
                    case Register8Bit::H:          return opcodes::LOAD_H_INTO_L;
                    case Register8Bit::L:          return opcodes::LOAD_L_INTO_L;
                    case Register8Bit::ADDRESS_HL: return opcodes::LOAD_ADDRESS_HL_INTO_L;
                    case Register8Bit::A:          return opcodes::LOAD_A_INTO_L;
                    default:                       break;
                }
            case Register8Bit::ADDRESS_HL: switch (destination) {
                    case Register8Bit::B:          return opcodes::LOAD_B_INTO_ADDRESS_HL;
                    case Register8Bit::C:          return opcodes::LOAD_C_INTO_ADDRESS_HL;
                    case Register8Bit::D:          return opcodes::LOAD_D_INTO_ADDRESS_HL;
                    case Register8Bit::E:          return opcodes::LOAD_E_INTO_ADDRESS_HL;
                    case Register8Bit::H:          return opcodes::LOAD_H_INTO_ADDRESS_HL;
                    case Register8Bit::L:          return opcodes::LOAD_L_INTO_ADDRESS_HL;
                    case Register8Bit::ADDRESS_HL: break; // INVALID
                    case Register8Bit::A:          return opcodes::LOAD_A_INTO_ADDRESS_HL;
                    default:                       break;
                }
            case Register8Bit::A: switch (destination) {
                    case Register8Bit::B:          return opcodes::LOAD_B_INTO_A;
                    case Register8Bit::C:          return opcodes::LOAD_C_INTO_A;
                    case Register8Bit::D:          return opcodes::LOAD_D_INTO_A;
                    case Register8Bit::E:          return opcodes::LOAD_E_INTO_A;
                    case Register8Bit::H:          return opcodes::LOAD_H_INTO_A;
                    case Register8Bit::L:          return opcodes::LOAD_L_INTO_A;
                    case Register8Bit::ADDRESS_HL: return opcodes::LOAD_ADDRESS_HL_INTO_A;
                    case Register8Bit::A:          return opcodes::LOAD_A_INTO_A;
                    default:                       break;
                }
            default: break;
        }
        return opcodes::INVALID_OPCODE;
    }

    const Register8Bit _source;
    const Register8Bit _destination;
};

class LoadAIntoAddressImmediate : public BaseInstruction {
public:
    LoadAIntoAddressImmediate(const word immediate = {})
            : BaseInstruction("LD (" + to_string_hex_prefixed(immediate) + "), A",
                              opcodes::LOAD_A_INTO_ADDRESS_IMMEDIATE,
                              to_bytestring_little_endian(immediate)),
              _immediate(immediate) {}

//    void emulate(const VirtualGameboy& gb)
//    {
//        gb.dereference(_immediate) = gb.access_register(_destination);
//
//        const unsigned cycles = 4;
//        gb.wait(cycles);
//    }

private:
    word _immediate;
};

class LoadAddressImmediateIntoA : public BaseInstruction {
public:
    LoadAddressImmediateIntoA(const word immediate = {})
            : BaseInstruction("LD A, (" + to_string_hex_prefixed(immediate) + ")",
                              opcodes::LOAD_ADDRESS_IMMEDIATE_INTO_A),
              _immediate(immediate) {}

//    void emulate(const VirtualGameboy& gb)
//    {
//        gb.access_register(_destination) = gb.dereference(_immediate);
//
//        const unsigned cycles = 4;
//        gb.wait(cycles);
//    }

private:
    word _immediate;
};

// LOAD with 16 bit addresses

class LoadAIntoAddress16BitRegister : public BaseInstruction {
public:
    LoadAIntoAddress16BitRegister(const Register16Bit destination = {})
            : BaseInstruction("LD (" + to_string(destination) + "), A", determine_opcode(destination)),
              _destination(destination) {}

private:
    Opcode determine_opcode(const Register16Bit destination) {
        switch(destination) {
            case Register16Bit::BC: return opcodes::LOAD_A_INTO_ADDRESS_BC;
            case Register16Bit::DE: return opcodes::LOAD_A_INTO_ADDRESS_DE;
            default:                return opcodes::INVALID_OPCODE;
        }
    }

    Register16Bit  _destination;
};

class LoadAddress16BitRegisterIntoA : public BaseInstruction {
public:
    LoadAddress16BitRegisterIntoA(const Register16Bit source = {})
            : BaseInstruction("LD A, (" + to_string(source) + ")", determine_opcode(source)),
              _source(source) {}

private:
    Opcode determine_opcode(const Register16Bit destination) {
        switch(destination) {
            case Register16Bit::BC: return opcodes::LOAD_ADDRESS_BC_INTO_A;
            case Register16Bit::DE: return opcodes::LOAD_ADDRESS_DE_INTO_A;
            default:                return opcodes::INVALID_OPCODE;
        }
    }

    Register16Bit _source;
};


class LoadAIntoAddressHLIncrement : public BaseInstruction {
public:
    LoadAIntoAddressHLIncrement()
            : BaseInstruction(
            "LD (HL+), A", opcodes::LOAD_A_INTO_ADDRESS_HL_INCREMENT) {}
};

class LoadAddressHLIncrementIntoA : public BaseInstruction {
public:
    LoadAddressHLIncrementIntoA()
            : BaseInstruction(
            "LD A, (HL+)", opcodes::LOAD_ADDRESS_HL_INCREMENT_INTO_A) {}
};

class LoadAIntoAddressHLDecrement : public BaseInstruction {
public:
    LoadAIntoAddressHLDecrement()
            : BaseInstruction(
            "LD (HL-), A", opcodes::LOAD_A_INTO_ADDRESS_HL_DECREMENT) {}
};

class LoadAddressHLDecrementIntoA : public BaseInstruction {
public:
    LoadAddressHLDecrementIntoA()
            : BaseInstruction(
            "LD A, (HL-)", opcodes::LOAD_ADDRESS_HL_DECREMENT_INTO_A) {}
};

// Load with port addresses (i.e. 0xFF + 8 bit address)

class LoadAIntoPortAddressImmediate : public BaseInstruction {
public:
    LoadAIntoPortAddressImmediate(const byte portAddress = {})
            : BaseInstruction("LDH (" + to_string_hex_prefixed(portAddress) + "), A",
                              opcodes::LOAD_A_INTO_PORT_ADDRESS_IMMEDIATE),
              _portAddress(portAddress) {}

private:
    byte _portAddress;
};

class LoadAIntoPortAddressC : public BaseInstruction {
public:
    LoadAIntoPortAddressC()
            : BaseInstruction("LD (C), A",
                              opcodes::LOAD_A_INTO_PORT_ADDRESS_C) {}
};

class LoadPortAddressImmediateIntoA : public BaseInstruction {
public:
    LoadPortAddressImmediateIntoA(const byte portAddress = {})
            : BaseInstruction("LDH A, (" + to_string_hex_prefixed(portAddress) + ")",
                              opcodes::LOAD_PORT_ADDRESS_IMMEDIATE_INTO_A),
              _portAddress(portAddress) {}

private:
    byte _portAddress;
};

class LoadPortAddressCIntoA : public BaseInstruction {
public:
    LoadPortAddressCIntoA()
            : BaseInstruction("LD A, (C)",
                              opcodes::LOAD_PORT_ADDRESS_C_INTO_A) {}
};

#endif //GAMEBOY_DISASSEMBLE_INSTRUCTIONS_LOAD_8BIT_H
