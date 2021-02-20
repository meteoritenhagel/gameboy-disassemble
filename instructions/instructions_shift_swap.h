#ifndef GAMEBOY_DISASSEMBLE_INSTRUCTIONS_SHIFT_SWAP_H
#define GAMEBOY_DISASSEMBLE_INSTRUCTIONS_SHIFT_SWAP_H

#include "instructions_interface.h"

class InstructionShiftLeftArithmetical8BitRegister : public Instruction {
protected:
    InstructionShiftLeftArithmetical8BitRegister(const Register8Bit reg, const Opcode opc)
            : Instruction("SLA " + to_string(reg),
                          opc),
              _register(reg) {}

private:
    const Register8Bit _register;
};

class InstructionShiftRightArithmetical8BitRegister : public Instruction {
protected:
    InstructionShiftRightArithmetical8BitRegister(const Register8Bit reg, const Opcode opc)
            : Instruction("SRA " + to_string(reg),
                          opc),
              _register(reg) {}

private:
    const Register8Bit _register;
};

class InstructionShiftRightLogical8BitRegister : public Instruction {
protected:
    InstructionShiftRightLogical8BitRegister(const Register8Bit reg, const Opcode opc)
            : Instruction("SRL " + to_string(reg),
                          opc),
              _register(reg) {}

private:
    const Register8Bit _register;
};

class InstructionSwap8BitRegister : public Instruction {
protected:
    InstructionSwap8BitRegister(const Register8Bit reg, const Opcode opc)
            : Instruction("SWAP " + to_string(reg),
                          opc),
              _register(reg) {}

private:
    const Register8Bit _register;
};





// child classes

// Shift left arithmetical 8 bit registers
class ShiftLeftArithmeticalB : public InstructionShiftLeftArithmetical8BitRegister {
public:
    ShiftLeftArithmeticalB()
            : InstructionShiftLeftArithmetical8BitRegister(Register8Bit::B,
                                                           opcodes::SHIFT_LEFT_ARITHMETICAL_B) {}
};

class ShiftLeftArithmeticalC : public InstructionShiftLeftArithmetical8BitRegister {
public:
    ShiftLeftArithmeticalC()
            : InstructionShiftLeftArithmetical8BitRegister(Register8Bit::C,
                                                           opcodes::SHIFT_LEFT_ARITHMETICAL_C) {}
};

class ShiftLeftArithmeticalD : public InstructionShiftLeftArithmetical8BitRegister {
public:
    ShiftLeftArithmeticalD()
            : InstructionShiftLeftArithmetical8BitRegister(Register8Bit::D,
                                                           opcodes::SHIFT_LEFT_ARITHMETICAL_D) {}
};

class ShiftLeftArithmeticalE : public InstructionShiftLeftArithmetical8BitRegister {
public:
    ShiftLeftArithmeticalE()
            : InstructionShiftLeftArithmetical8BitRegister(Register8Bit::E,
                                                           opcodes::SHIFT_LEFT_ARITHMETICAL_E) {}
};

class ShiftLeftArithmeticalH : public InstructionShiftLeftArithmetical8BitRegister {
public:
    ShiftLeftArithmeticalH()
            : InstructionShiftLeftArithmetical8BitRegister(Register8Bit::H,
                                                           opcodes::SHIFT_LEFT_ARITHMETICAL_H) {}
};

class ShiftLeftArithmeticalL : public InstructionShiftLeftArithmetical8BitRegister {
public:
    ShiftLeftArithmeticalL()
            : InstructionShiftLeftArithmetical8BitRegister(Register8Bit::L,
                                                           opcodes::SHIFT_LEFT_ARITHMETICAL_L) {}
};

class ShiftLeftArithmeticalAddressHL : public InstructionShiftLeftArithmetical8BitRegister {
public:
    ShiftLeftArithmeticalAddressHL()
            : InstructionShiftLeftArithmetical8BitRegister(Register8Bit::ADDRESS_HL,
                                                           opcodes::SHIFT_LEFT_ARITHMETICAL_ADDRESS_HL) {}
};

class ShiftLeftArithmeticalA : public InstructionShiftLeftArithmetical8BitRegister {
public:
    ShiftLeftArithmeticalA()
            : InstructionShiftLeftArithmetical8BitRegister(Register8Bit::A,
                                                           opcodes::SHIFT_LEFT_ARITHMETICAL_A) {}
};

// Shift right arithmetical 8 bit registers
class ShiftRightArithmeticalB : public InstructionShiftRightArithmetical8BitRegister {
public:
    ShiftRightArithmeticalB()
            : InstructionShiftRightArithmetical8BitRegister(Register8Bit::B,
                                                            opcodes::SHIFT_RIGHT_ARITHMETICAL_B) {}
};

class ShiftRightArithmeticalC : public InstructionShiftRightArithmetical8BitRegister {
public:
    ShiftRightArithmeticalC()
            : InstructionShiftRightArithmetical8BitRegister(Register8Bit::C,
                                                            opcodes::SHIFT_RIGHT_ARITHMETICAL_C) {}
};

class ShiftRightArithmeticalD : public InstructionShiftRightArithmetical8BitRegister {
public:
    ShiftRightArithmeticalD()
            : InstructionShiftRightArithmetical8BitRegister(Register8Bit::D,
                                                            opcodes::SHIFT_RIGHT_ARITHMETICAL_D) {}
};

class ShiftRightArithmeticalE : public InstructionShiftRightArithmetical8BitRegister {
public:
    ShiftRightArithmeticalE()
            : InstructionShiftRightArithmetical8BitRegister(Register8Bit::E,
                                                            opcodes::SHIFT_RIGHT_ARITHMETICAL_E) {}
};

class ShiftRightArithmeticalH : public InstructionShiftRightArithmetical8BitRegister {
public:
    ShiftRightArithmeticalH()
            : InstructionShiftRightArithmetical8BitRegister(Register8Bit::H,
                                                            opcodes::SHIFT_RIGHT_ARITHMETICAL_H) {}
};

class ShiftRightArithmeticalL : public InstructionShiftRightArithmetical8BitRegister {
public:
    ShiftRightArithmeticalL()
            : InstructionShiftRightArithmetical8BitRegister(Register8Bit::L,
                                                            opcodes::SHIFT_RIGHT_ARITHMETICAL_L) {}
};

class ShiftRightArithmeticalAddressHL : public InstructionShiftRightArithmetical8BitRegister {
public:
    ShiftRightArithmeticalAddressHL()
            : InstructionShiftRightArithmetical8BitRegister(Register8Bit::ADDRESS_HL,
                                                            opcodes::SHIFT_RIGHT_ARITHMETICAL_ADDRESS_HL) {}
};

class ShiftRightArithmeticalA : public InstructionShiftRightArithmetical8BitRegister {
public:
    ShiftRightArithmeticalA()
            : InstructionShiftRightArithmetical8BitRegister(Register8Bit::A,
                                                            opcodes::SHIFT_RIGHT_ARITHMETICAL_A) {}
};

// Shift right logical 8 bit registers
class ShiftRightLogicalB : public InstructionShiftRightLogical8BitRegister {
public:
    ShiftRightLogicalB()
            : InstructionShiftRightLogical8BitRegister(Register8Bit::B,
                                                       opcodes::SHIFT_RIGHT_LOGICAL_B) {}
};

class ShiftRightLogicalC : public InstructionShiftRightLogical8BitRegister {
public:
    ShiftRightLogicalC()
            : InstructionShiftRightLogical8BitRegister(Register8Bit::C,
                                                       opcodes::SHIFT_RIGHT_LOGICAL_C) {}
};

class ShiftRightLogicalD : public InstructionShiftRightLogical8BitRegister {
public:
    ShiftRightLogicalD()
            : InstructionShiftRightLogical8BitRegister(Register8Bit::D,
                                                       opcodes::SHIFT_RIGHT_LOGICAL_D) {}
};

class ShiftRightLogicalE : public InstructionShiftRightLogical8BitRegister {
public:
    ShiftRightLogicalE()
            : InstructionShiftRightLogical8BitRegister(Register8Bit::E,
                                                       opcodes::SHIFT_RIGHT_LOGICAL_E) {}
};

class ShiftRightLogicalH : public InstructionShiftRightLogical8BitRegister {
public:
    ShiftRightLogicalH()
            : InstructionShiftRightLogical8BitRegister(Register8Bit::H,
                                                       opcodes::SHIFT_RIGHT_LOGICAL_H) {}
};

class ShiftRightLogicalL : public InstructionShiftRightLogical8BitRegister {
public:
    ShiftRightLogicalL()
            : InstructionShiftRightLogical8BitRegister(Register8Bit::L,
                                                       opcodes::SHIFT_RIGHT_LOGICAL_L) {}
};

class ShiftRightLogicalAddressHL : public InstructionShiftRightLogical8BitRegister {
public:
    ShiftRightLogicalAddressHL()
            : InstructionShiftRightLogical8BitRegister(Register8Bit::ADDRESS_HL,
                                                       opcodes::SHIFT_RIGHT_LOGICAL_ADDRESS_HL) {}
};

class ShiftRightLogicalA : public InstructionShiftRightLogical8BitRegister {
public:
    ShiftRightLogicalA()
            : InstructionShiftRightLogical8BitRegister(Register8Bit::A,
                                                       opcodes::SHIFT_RIGHT_LOGICAL_A) {}
};

// Swap 8 bit registers
class SwapB : public InstructionSwap8BitRegister {
public:
    SwapB()
            : InstructionSwap8BitRegister(Register8Bit::B,
                                          opcodes::SWAP_B) {}
};

class SwapC : public InstructionSwap8BitRegister {
public:
    SwapC()
            : InstructionSwap8BitRegister(Register8Bit::C,
                                          opcodes::SWAP_C) {}
};

class SwapD : public InstructionSwap8BitRegister {
public:
    SwapD()
            : InstructionSwap8BitRegister(Register8Bit::D,
                                          opcodes::SWAP_D) {}
};

class SwapE : public InstructionSwap8BitRegister {
public:
    SwapE()
            : InstructionSwap8BitRegister(Register8Bit::E,
                                          opcodes::SWAP_E) {}
};

class SwapH : public InstructionSwap8BitRegister {
public:
    SwapH()
            : InstructionSwap8BitRegister(Register8Bit::H,
                                          opcodes::SWAP_H) {}
};

class SwapL : public InstructionSwap8BitRegister {
public:
    SwapL()
            : InstructionSwap8BitRegister(Register8Bit::L,
                                          opcodes::SWAP_L) {}
};

class SwapAddressHL : public InstructionSwap8BitRegister {
public:
    SwapAddressHL()
            : InstructionSwap8BitRegister(Register8Bit::ADDRESS_HL,
                                          opcodes::SWAP_ADDRESS_HL) {}
};

class SwapA : public InstructionSwap8BitRegister {
public:
    SwapA()
            : InstructionSwap8BitRegister(Register8Bit::A,
                                          opcodes::SWAP_A) {}
};


#endif //GAMEBOY_DISASSEMBLE_INSTRUCTIONS_SHIFT_SWAP_H
