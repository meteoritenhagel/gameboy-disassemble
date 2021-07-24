#include "decoder.h"

Decoder::Decoder(const Bytestring &bytecode, const word entryPoint)
        : _bytecode(bytecode),
          _programCounter(entryPoint) {}

size_t Decoder::get_size() const noexcept {
    return _bytecode.size();
}

word Decoder::get_current_position() const noexcept {
    return _programCounter;
}

bool Decoder::is_out_of_range() const noexcept {
    try {
        return (get_current_position() >= get_size());
    }
    catch (const std::exception &e) {
        return true;
    }

}

std::pair<word, InstructionPtr> Decoder::decode() {
    word opcodePosition = get_current_position();
    const Opcode opcode = fetch_opcode();
    return std::make_pair(opcodePosition, decode_opcode(opcode));
}

void Decoder::increment_program_counter() noexcept {
    if (!is_out_of_range()) {
        ++_programCounter;
    }
}

byte Decoder::read_byte() const {
    if (is_out_of_range()) {
        throw std::out_of_range("Decoder error: Program counter pointing to position out of range.");
    }

    return _bytecode[get_current_position()];
}

byte Decoder::fetch_byte() {
    const byte currentByte = read_byte();
    increment_program_counter();

    return currentByte;
}

word Decoder::fetch_word() {
    const byte lsb = fetch_byte();
    const byte msb = fetch_byte();

    return little_endian_to_number(lsb, msb); // note that evaluation order is not fixed in C++!
}

Opcode Decoder::fetch_opcode() {
    word opcode = fetch_byte();

    // check if prefix
    if (opcode == 0xCB) {
        opcode = big_endian_to_number(0xCB, fetch_byte());
    }

    return opcode;
}

InstructionPtr Decoder::decode_opcode(const Opcode opcode) {
    switch (opcode)
    {
        case opcodes::NOP                                        : return std::make_unique<Nop>();
        case opcodes::LOAD_IMMEDIATE_INTO_BC                     : return std::make_unique<LoadImmediateInto16BitRegister>(Register16Bit::BC, fetch_word());
        case opcodes::LOAD_A_INTO_ADDRESS_BC                     : return std::make_unique<LoadAIntoAddress16BitRegister>(Register16Bit::BC);
        case opcodes::INCREMENT_BC                               : return std::make_unique<IncrementRegister>(Register16Bit::BC);
        case opcodes::INCREMENT_B                                : return std::make_unique<IncrementRegister>(Register8Bit::B);
        case opcodes::DECREMENT_B                                : return std::make_unique<DecrementRegister>(Register8Bit::B);
        case opcodes::LOAD_IMMEDIATE_INTO_B                      : return std::make_unique<LoadImmediateInto8BitRegister>(Register8Bit::B, fetch_byte());
        case opcodes::ROTATE_LEFT_CONTENTS_OF_A_AND_CLEAR_ZERO   : return std::make_unique<RotateLeftContentsOfAAndClearZero>();
        case opcodes::LOAD_SP_INTO_ADDRESS_IMMEDIATE             : return std::make_unique<LoadSPIntoAddressImmediate>(fetch_word());
        case opcodes::ADD_HL_AND_BC                              : return std::make_unique<AddHLAnd16BitRegister>(Register16Bit::BC);
        case opcodes::LOAD_ADDRESS_BC_INTO_A                     : return std::make_unique<LoadAddress16BitRegisterIntoA>(Register16Bit::BC);
        case opcodes::DECREMENT_BC                               : return std::make_unique<DecrementRegister>(Register16Bit::BC);
        case opcodes::INCREMENT_C                                : return std::make_unique<IncrementRegister>(Register8Bit::C);
        case opcodes::DECREMENT_C                                : return std::make_unique<DecrementRegister>(Register8Bit::C);
        case opcodes::LOAD_IMMEDIATE_INTO_C                      : return std::make_unique<LoadImmediateInto8BitRegister>(Register8Bit::C, fetch_byte());
        case opcodes::ROTATE_RIGHT_CONTENTS_OF_A_AND_CLEAR_ZERO  : return std::make_unique<RotateRightContentsOfAAndClearZero>();

        case opcodes::STOP                                       : return std::make_unique<Stop>();
        case opcodes::LOAD_IMMEDIATE_INTO_DE                     : return std::make_unique<LoadImmediateInto16BitRegister>(Register16Bit::DE, fetch_word());
        case opcodes::LOAD_A_INTO_ADDRESS_DE                     : return std::make_unique<LoadAIntoAddress16BitRegister>(Register16Bit::DE);
        case opcodes::INCREMENT_DE                               : return std::make_unique<IncrementRegister>(Register16Bit::DE);
        case opcodes::INCREMENT_D                                : return std::make_unique<IncrementRegister>(Register8Bit::D);
        case opcodes::DECREMENT_D                                : return std::make_unique<DecrementRegister>(Register8Bit::D);
        case opcodes::LOAD_IMMEDIATE_INTO_D                      : return std::make_unique<LoadImmediateInto8BitRegister>(Register8Bit::D, fetch_byte());
        case opcodes::ROTATE_LEFT_A_AND_CLEAR_ZERO               : return std::make_unique<RotateLeftAAndClearZero>();
        case opcodes::JUMP_RELATIVE                              : return std::make_unique<JumpRelative>(fetch_byte());
        case opcodes::ADD_HL_AND_DE                              : return std::make_unique<AddHLAnd16BitRegister>(Register16Bit::DE);
        case opcodes::LOAD_ADDRESS_DE_INTO_A                     : return std::make_unique<LoadAddress16BitRegisterIntoA>(Register16Bit::DE);
        case opcodes::DECREMENT_DE                               : return std::make_unique<DecrementRegister>(Register16Bit::DE);
        case opcodes::INCREMENT_E                                : return std::make_unique<IncrementRegister>(Register8Bit::E);
        case opcodes::DECREMENT_E                                : return std::make_unique<DecrementRegister>(Register8Bit::E);
        case opcodes::LOAD_IMMEDIATE_INTO_E                      : return std::make_unique<LoadImmediateInto8BitRegister>(Register8Bit::E, fetch_byte());
        case opcodes::ROTATE_RIGHT_A_AND_CLEAR_ZERO              : return std::make_unique<RotateRightAAndClearZero>();

        case opcodes::JUMP_RELATIVE_IF_NOT_ZERO                  : return std::make_unique<JumpRelativeConditional>(FlagCondition::NOT_ZERO, fetch_byte());
        case opcodes::LOAD_IMMEDIATE_INTO_HL                     : return std::make_unique<LoadImmediateInto16BitRegister>(Register16Bit::HL, fetch_word());
        case opcodes::LOAD_A_INTO_ADDRESS_HL_INCREMENT           : return std::make_unique<LoadAIntoAddressHLIncrement>();
        case opcodes::INCREMENT_HL                               : return std::make_unique<IncrementRegister>(Register16Bit::HL);
        case opcodes::INCREMENT_H                                : return std::make_unique<IncrementRegister>(Register8Bit::H);
        case opcodes::DECREMENT_H                                : return std::make_unique<DecrementRegister>(Register8Bit::H);
        case opcodes::LOAD_IMMEDIATE_INTO_H                      : return std::make_unique<LoadImmediateInto8BitRegister>(Register8Bit::H, fetch_byte());
        case opcodes::DECIMAL_ADJUST_A                           : return std::make_unique<DecimalAdjustA>();
        case opcodes::JUMP_RELATIVE_IF_ZERO                      : return std::make_unique<JumpRelativeConditional>(FlagCondition::ZERO, fetch_byte());
        case opcodes::ADD_HL_AND_HL                              : return std::make_unique<AddHLAnd16BitRegister>(Register16Bit::HL);
        case opcodes::LOAD_ADDRESS_HL_INCREMENT_INTO_A           : return std::make_unique<LoadAddressHLIncrementIntoA>();
        case opcodes::DECREMENT_HL                               : return std::make_unique<DecrementRegister>(Register16Bit::HL);
        case opcodes::INCREMENT_L                                : return std::make_unique<IncrementRegister>(Register8Bit::L);
        case opcodes::DECREMENT_L                                : return std::make_unique<DecrementRegister>(Register8Bit::L);
        case opcodes::LOAD_IMMEDIATE_INTO_L                      : return std::make_unique<LoadImmediateInto8BitRegister>(Register8Bit::L, fetch_byte());
        case opcodes::COMPLEMENT_A                               : return std::make_unique<ComplementA>();

        case opcodes::JUMP_RELATIVE_IF_NOT_CARRY                 : return std::make_unique<JumpRelativeConditional>(FlagCondition::NOT_CARRY, fetch_byte());
        case opcodes::LOAD_IMMEDIATE_INTO_SP                     : return std::make_unique<LoadImmediateInto16BitRegister>(Register16Bit::SP, fetch_word());
        case opcodes::LOAD_A_INTO_ADDRESS_HL_DECREMENT           : return std::make_unique<LoadAIntoAddressHLDecrement>();
        case opcodes::INCREMENT_SP                               : return std::make_unique<IncrementRegister>(Register16Bit::SP);
        case opcodes::INCREMENT_ADDRESS_HL                       : return std::make_unique<IncrementRegister>(Register8Bit::ADDRESS_HL);
        case opcodes::DECREMENT_ADDRESS_HL                       : return std::make_unique<DecrementRegister>(Register8Bit::ADDRESS_HL);
        case opcodes::LOAD_IMMEDIATE_INTO_ADDRESS_HL             : return std::make_unique<LoadImmediateInto8BitRegister>(Register8Bit::ADDRESS_HL, fetch_byte());
        case opcodes::SET_CARRY                                  : return std::make_unique<SetCarry>();
        case opcodes::JUMP_RELATIVE_IF_CARRY                     : return std::make_unique<JumpRelativeConditional>(FlagCondition::CARRY, fetch_byte());
        case opcodes::ADD_HL_AND_SP                              : return std::make_unique<AddHLAnd16BitRegister>(Register16Bit::SP);
        case opcodes::LOAD_ADDRESS_HL_DECREMENT_INTO_A           : return std::make_unique<LoadAddressHLDecrementIntoA>();
        case opcodes::DECREMENT_SP                               : return std::make_unique<DecrementRegister>(Register16Bit::SP);
        case opcodes::INCREMENT_A                                : return std::make_unique<IncrementRegister>(Register8Bit::A);
        case opcodes::DECREMENT_A                                : return std::make_unique<DecrementRegister>(Register8Bit::A);
        case opcodes::LOAD_IMMEDIATE_INTO_A                      : return std::make_unique<LoadImmediateInto8BitRegister>(Register8Bit::A, fetch_byte());
        case opcodes::FLIP_CARRY                                 : return std::make_unique<FlipCarry>();

        case opcodes::LOAD_B_INTO_B                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::B, Register8Bit::B);
        case opcodes::LOAD_C_INTO_B                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::C, Register8Bit::B);
        case opcodes::LOAD_D_INTO_B                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::D, Register8Bit::B);
        case opcodes::LOAD_E_INTO_B                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::E, Register8Bit::B);
        case opcodes::LOAD_H_INTO_B                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::H, Register8Bit::B);
        case opcodes::LOAD_L_INTO_B                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::L, Register8Bit::B);
        case opcodes::LOAD_ADDRESS_HL_INTO_B                     : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::ADDRESS_HL, Register8Bit::B);
        case opcodes::LOAD_A_INTO_B                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::A, Register8Bit::B);
        case opcodes::LOAD_B_INTO_C                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::B, Register8Bit::C);
        case opcodes::LOAD_C_INTO_C                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::C, Register8Bit::C);
        case opcodes::LOAD_D_INTO_C                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::D, Register8Bit::C);
        case opcodes::LOAD_E_INTO_C                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::E, Register8Bit::C);
        case opcodes::LOAD_H_INTO_C                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::H, Register8Bit::C);
        case opcodes::LOAD_L_INTO_C                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::L, Register8Bit::C);
        case opcodes::LOAD_ADDRESS_HL_INTO_C                     : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::ADDRESS_HL, Register8Bit::C);
        case opcodes::LOAD_A_INTO_C                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::A, Register8Bit::C);

        case opcodes::LOAD_B_INTO_D                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::B, Register8Bit::D);
        case opcodes::LOAD_C_INTO_D                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::C, Register8Bit::D);
        case opcodes::LOAD_D_INTO_D                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::D, Register8Bit::D);
        case opcodes::LOAD_E_INTO_D                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::E, Register8Bit::D);
        case opcodes::LOAD_H_INTO_D                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::H, Register8Bit::D);
        case opcodes::LOAD_L_INTO_D                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::L, Register8Bit::D);
        case opcodes::LOAD_ADDRESS_HL_INTO_D                     : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::ADDRESS_HL, Register8Bit::D);
        case opcodes::LOAD_A_INTO_D                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::A, Register8Bit::D);
        case opcodes::LOAD_B_INTO_E                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::B, Register8Bit::E);
        case opcodes::LOAD_C_INTO_E                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::C, Register8Bit::E);
        case opcodes::LOAD_D_INTO_E                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::D, Register8Bit::E);
        case opcodes::LOAD_E_INTO_E                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::E, Register8Bit::E);
        case opcodes::LOAD_H_INTO_E                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::H, Register8Bit::E);
        case opcodes::LOAD_L_INTO_E                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::L, Register8Bit::E);
        case opcodes::LOAD_ADDRESS_HL_INTO_E                     : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::ADDRESS_HL, Register8Bit::E);
        case opcodes::LOAD_A_INTO_E                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::A, Register8Bit::E);

        case opcodes::LOAD_B_INTO_H                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::B, Register8Bit::H);
        case opcodes::LOAD_C_INTO_H                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::C, Register8Bit::H);
        case opcodes::LOAD_D_INTO_H                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::D, Register8Bit::H);
        case opcodes::LOAD_E_INTO_H                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::E, Register8Bit::H);
        case opcodes::LOAD_H_INTO_H                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::H, Register8Bit::H);
        case opcodes::LOAD_L_INTO_H                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::L, Register8Bit::H);
        case opcodes::LOAD_ADDRESS_HL_INTO_H                     : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::ADDRESS_HL, Register8Bit::H);
        case opcodes::LOAD_A_INTO_H                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::A, Register8Bit::H);
        case opcodes::LOAD_B_INTO_L                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::B, Register8Bit::L);
        case opcodes::LOAD_C_INTO_L                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::C, Register8Bit::L);
        case opcodes::LOAD_D_INTO_L                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::D, Register8Bit::L);
        case opcodes::LOAD_E_INTO_L                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::E, Register8Bit::L);
        case opcodes::LOAD_H_INTO_L                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::H, Register8Bit::L);
        case opcodes::LOAD_L_INTO_L                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::L, Register8Bit::L);
        case opcodes::LOAD_ADDRESS_HL_INTO_L                     : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::ADDRESS_HL, Register8Bit::L);
        case opcodes::LOAD_A_INTO_L                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::A, Register8Bit::L);

        case opcodes::LOAD_B_INTO_ADDRESS_HL                     : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::B, Register8Bit::ADDRESS_HL);
        case opcodes::LOAD_C_INTO_ADDRESS_HL                     : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::C, Register8Bit::ADDRESS_HL);
        case opcodes::LOAD_D_INTO_ADDRESS_HL                     : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::D, Register8Bit::ADDRESS_HL);
        case opcodes::LOAD_E_INTO_ADDRESS_HL                     : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::E, Register8Bit::ADDRESS_HL);
        case opcodes::LOAD_H_INTO_ADDRESS_HL                     : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::H, Register8Bit::ADDRESS_HL);
        case opcodes::LOAD_L_INTO_ADDRESS_HL                     : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::L, Register8Bit::ADDRESS_HL);
        case opcodes::HALT                                       : return std::make_unique<Halt>();
        case opcodes::LOAD_A_INTO_ADDRESS_HL                     : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::A, Register8Bit::ADDRESS_HL);
        case opcodes::LOAD_B_INTO_A                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::B, Register8Bit::A);
        case opcodes::LOAD_C_INTO_A                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::C, Register8Bit::A);
        case opcodes::LOAD_D_INTO_A                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::D, Register8Bit::A);
        case opcodes::LOAD_E_INTO_A                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::E, Register8Bit::A);
        case opcodes::LOAD_H_INTO_A                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::H, Register8Bit::A);
        case opcodes::LOAD_L_INTO_A                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::L, Register8Bit::A);
        case opcodes::LOAD_ADDRESS_HL_INTO_A                     : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::ADDRESS_HL, Register8Bit::A);
        case opcodes::LOAD_A_INTO_A                              : return std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::A, Register8Bit::A);

        case opcodes::ADD_A_AND_B                                : return std::make_unique<AddAAnd8BitRegister>(Register8Bit::B);
        case opcodes::ADD_A_AND_C                                : return std::make_unique<AddAAnd8BitRegister>(Register8Bit::C);
        case opcodes::ADD_A_AND_D                                : return std::make_unique<AddAAnd8BitRegister>(Register8Bit::D);
        case opcodes::ADD_A_AND_E                                : return std::make_unique<AddAAnd8BitRegister>(Register8Bit::E);
        case opcodes::ADD_A_AND_H                                : return std::make_unique<AddAAnd8BitRegister>(Register8Bit::H);
        case opcodes::ADD_A_AND_L                                : return std::make_unique<AddAAnd8BitRegister>(Register8Bit::L);
        case opcodes::ADD_A_AND_ADDRESS_HL                       : return std::make_unique<AddAAnd8BitRegister>(Register8Bit::ADDRESS_HL);
        case opcodes::ADD_A_AND_A                                : return std::make_unique<AddAAnd8BitRegister>(Register8Bit::A);
        case opcodes::ADD_WITH_CARRY_A_AND_B                     : return std::make_unique<AddWithCarryAAnd8BitRegister>(Register8Bit::B);
        case opcodes::ADD_WITH_CARRY_A_AND_C                     : return std::make_unique<AddWithCarryAAnd8BitRegister>(Register8Bit::C);
        case opcodes::ADD_WITH_CARRY_A_AND_D                     : return std::make_unique<AddWithCarryAAnd8BitRegister>(Register8Bit::D);
        case opcodes::ADD_WITH_CARRY_A_AND_E                     : return std::make_unique<AddWithCarryAAnd8BitRegister>(Register8Bit::E);
        case opcodes::ADD_WITH_CARRY_A_AND_H                     : return std::make_unique<AddWithCarryAAnd8BitRegister>(Register8Bit::H);
        case opcodes::ADD_WITH_CARRY_A_AND_L                     : return std::make_unique<AddWithCarryAAnd8BitRegister>(Register8Bit::L);
        case opcodes::ADD_WITH_CARRY_A_AND_ADDRESS_HL            : return std::make_unique<AddWithCarryAAnd8BitRegister>(Register8Bit::ADDRESS_HL);
        case opcodes::ADD_WITH_CARRY_A_AND_A                     : return std::make_unique<AddWithCarryAAnd8BitRegister>(Register8Bit::A);

        case opcodes::SUBTRACT_A_AND_B                           : return std::make_unique<SubtractAAnd8BitRegister>(Register8Bit::B);
        case opcodes::SUBTRACT_A_AND_C                           : return std::make_unique<SubtractAAnd8BitRegister>(Register8Bit::C);
        case opcodes::SUBTRACT_A_AND_D                           : return std::make_unique<SubtractAAnd8BitRegister>(Register8Bit::D);
        case opcodes::SUBTRACT_A_AND_E                           : return std::make_unique<SubtractAAnd8BitRegister>(Register8Bit::E);
        case opcodes::SUBTRACT_A_AND_H                           : return std::make_unique<SubtractAAnd8BitRegister>(Register8Bit::H);
        case opcodes::SUBTRACT_A_AND_L                           : return std::make_unique<SubtractAAnd8BitRegister>(Register8Bit::L);
        case opcodes::SUBTRACT_A_AND_ADDRESS_HL                  : return std::make_unique<SubtractAAnd8BitRegister>(Register8Bit::ADDRESS_HL);
        case opcodes::SUBTRACT_A_AND_A                           : return std::make_unique<SubtractAAnd8BitRegister>(Register8Bit::A);
        case opcodes::SUBTRACT_WITH_CARRY_A_AND_B                : return std::make_unique<SubtractWithCarryAAnd8BitRegister>(Register8Bit::B);
        case opcodes::SUBTRACT_WITH_CARRY_A_AND_C                : return std::make_unique<SubtractWithCarryAAnd8BitRegister>(Register8Bit::C);
        case opcodes::SUBTRACT_WITH_CARRY_A_AND_D                : return std::make_unique<SubtractWithCarryAAnd8BitRegister>(Register8Bit::D);
        case opcodes::SUBTRACT_WITH_CARRY_A_AND_E                : return std::make_unique<SubtractWithCarryAAnd8BitRegister>(Register8Bit::E);
        case opcodes::SUBTRACT_WITH_CARRY_A_AND_H                : return std::make_unique<SubtractWithCarryAAnd8BitRegister>(Register8Bit::H);
        case opcodes::SUBTRACT_WITH_CARRY_A_AND_L                : return std::make_unique<SubtractWithCarryAAnd8BitRegister>(Register8Bit::L);
        case opcodes::SUBTRACT_WITH_CARRY_A_AND_ADDRESS_HL       : return std::make_unique<SubtractWithCarryAAnd8BitRegister>(Register8Bit::ADDRESS_HL);
        case opcodes::SUBTRACT_WITH_CARRY_A_AND_A                : return std::make_unique<SubtractWithCarryAAnd8BitRegister>(Register8Bit::A);

        case opcodes::AND_A_AND_B                                : return std::make_unique<AndAAnd8BitRegister>(Register8Bit::B);
        case opcodes::AND_A_AND_C                                : return std::make_unique<AndAAnd8BitRegister>(Register8Bit::C);
        case opcodes::AND_A_AND_D                                : return std::make_unique<AndAAnd8BitRegister>(Register8Bit::D);
        case opcodes::AND_A_AND_E                                : return std::make_unique<AndAAnd8BitRegister>(Register8Bit::E);
        case opcodes::AND_A_AND_H                                : return std::make_unique<AndAAnd8BitRegister>(Register8Bit::H);
        case opcodes::AND_A_AND_L                                : return std::make_unique<AndAAnd8BitRegister>(Register8Bit::L);
        case opcodes::AND_A_AND_ADDRESS_HL                       : return std::make_unique<AndAAnd8BitRegister>(Register8Bit::ADDRESS_HL);
        case opcodes::AND_A_AND_A                                : return std::make_unique<AndAAnd8BitRegister>(Register8Bit::A);
        case opcodes::XOR_A_AND_B                                : return std::make_unique<XorAAnd8BitRegister>(Register8Bit::B);
        case opcodes::XOR_A_AND_C                                : return std::make_unique<XorAAnd8BitRegister>(Register8Bit::C);
        case opcodes::XOR_A_AND_D                                : return std::make_unique<XorAAnd8BitRegister>(Register8Bit::D);
        case opcodes::XOR_A_AND_E                                : return std::make_unique<XorAAnd8BitRegister>(Register8Bit::E);
        case opcodes::XOR_A_AND_H                                : return std::make_unique<XorAAnd8BitRegister>(Register8Bit::H);
        case opcodes::XOR_A_AND_L                                : return std::make_unique<XorAAnd8BitRegister>(Register8Bit::L);
        case opcodes::XOR_A_AND_ADDRESS_HL                       : return std::make_unique<XorAAnd8BitRegister>(Register8Bit::ADDRESS_HL);
        case opcodes::XOR_A_AND_A                                : return std::make_unique<XorAAnd8BitRegister>(Register8Bit::A);

        case opcodes::OR_A_AND_B                                 : return std::make_unique<OrAAnd8BitRegister>(Register8Bit::B);
        case opcodes::OR_A_AND_C                                 : return std::make_unique<OrAAnd8BitRegister>(Register8Bit::C);
        case opcodes::OR_A_AND_D                                 : return std::make_unique<OrAAnd8BitRegister>(Register8Bit::D);
        case opcodes::OR_A_AND_E                                 : return std::make_unique<OrAAnd8BitRegister>(Register8Bit::E);
        case opcodes::OR_A_AND_H                                 : return std::make_unique<OrAAnd8BitRegister>(Register8Bit::H);
        case opcodes::OR_A_AND_L                                 : return std::make_unique<OrAAnd8BitRegister>(Register8Bit::L);
        case opcodes::OR_A_AND_ADDRESS_HL                        : return std::make_unique<OrAAnd8BitRegister>(Register8Bit::ADDRESS_HL);
        case opcodes::OR_A_AND_A                                 : return std::make_unique<OrAAnd8BitRegister>(Register8Bit::A);
        case opcodes::COMPARE_A_AND_B                            : return std::make_unique<CompareAAnd8BitRegister>(Register8Bit::B);
        case opcodes::COMPARE_A_AND_C                            : return std::make_unique<CompareAAnd8BitRegister>(Register8Bit::C);
        case opcodes::COMPARE_A_AND_D                            : return std::make_unique<CompareAAnd8BitRegister>(Register8Bit::D);
        case opcodes::COMPARE_A_AND_E                            : return std::make_unique<CompareAAnd8BitRegister>(Register8Bit::E);
        case opcodes::COMPARE_A_AND_H                            : return std::make_unique<CompareAAnd8BitRegister>(Register8Bit::H);
        case opcodes::COMPARE_A_AND_L                            : return std::make_unique<CompareAAnd8BitRegister>(Register8Bit::L);
        case opcodes::COMPARE_A_AND_ADDRESS_HL                   : return std::make_unique<CompareAAnd8BitRegister>(Register8Bit::ADDRESS_HL);
        case opcodes::COMPARE_A_AND_A                            : return std::make_unique<CompareAAnd8BitRegister>(Register8Bit::A);

        case opcodes::RETURN_IF_NOT_ZERO                         : return std::make_unique<ReturnConditional>(FlagCondition::NOT_ZERO);
        case opcodes::POP_BC                                     : return std::make_unique<Pop16BitRegister>(Register16Bit::BC);
        case opcodes::JUMP_IF_NOT_ZERO                           : return std::make_unique<JumpConditional>(FlagCondition::NOT_ZERO, fetch_word());
        case opcodes::JUMP                                       : return std::make_unique<Jump>(fetch_word());
        case opcodes::CALL_IF_NOT_ZERO                           : return std::make_unique<CallConditional>(FlagCondition::NOT_ZERO, fetch_word());
        case opcodes::PUSH_BC                                    : return std::make_unique<Push16BitRegister>(Register16Bit::BC);
        case opcodes::ADD_A_AND_IMMEDIATE                        : return std::make_unique<AddAAndImmediate>(fetch_byte());
        case opcodes::RESTART_0                                  : return std::make_unique<Restart>(0);
        case opcodes::RETURN_IF_ZERO                             : return std::make_unique<ReturnConditional>(FlagCondition::ZERO);
        case opcodes::RETURN                                     : return std::make_unique<Return>();
        case opcodes::JUMP_IF_ZERO                               : return std::make_unique<JumpConditional>(FlagCondition::ZERO, fetch_word());
        case opcodes::UNUSED_0                                   : return std::make_unique<Unused>(0);
        case opcodes::CALL_IF_ZERO                               : return std::make_unique<CallConditional>(FlagCondition::ZERO, fetch_word());
        case opcodes::CALL                                       : return std::make_unique<Call>(fetch_word());
        case opcodes::ADD_WITH_CARRY_A_AND_IMMEDIATE             : return std::make_unique<AddWithCarryAAndImmediate>(fetch_byte());
        case opcodes::RESTART_1                                  : return std::make_unique<Restart>(1);

        case opcodes::RETURN_IF_NOT_CARRY                        : return std::make_unique<ReturnConditional>(FlagCondition::NOT_CARRY);
        case opcodes::POP_DE                                     : return std::make_unique<Pop16BitRegister>(Register16Bit::DE);
        case opcodes::JUMP_IF_NOT_CARRY                          : return std::make_unique<JumpConditional>(FlagCondition::NOT_CARRY, fetch_word());
        case opcodes::UNUSED_1                                   : return std::make_unique<Unused>(1);
        case opcodes::CALL_IF_NOT_CARRY                          : return std::make_unique<CallConditional>(FlagCondition::NOT_CARRY, fetch_word());
        case opcodes::PUSH_DE                                    : return std::make_unique<Push16BitRegister>(Register16Bit::DE);
        case opcodes::SUBTRACT_A_AND_IMMEDIATE                   : return std::make_unique<SubtractAAndImmediate>(fetch_byte());
        case opcodes::RESTART_2                                  : return std::make_unique<Restart>(2);
        case opcodes::RETURN_IF_CARRY                            : return std::make_unique<ReturnConditional>(FlagCondition::CARRY);
        case opcodes::RETURN_FROM_INTERRUPT                      : return std::make_unique<ReturnFromInterrupt>();
        case opcodes::JUMP_IF_CARRY                              : return std::make_unique<JumpConditional>(FlagCondition::CARRY, fetch_word());
        case opcodes::UNUSED_2                                   : return std::make_unique<Unused>(2);
        case opcodes::CALL_IF_CARRY                              : return std::make_unique<CallConditional>(FlagCondition::CARRY, fetch_word());
        case opcodes::UNUSED_3                                   : return std::make_unique<Unused>(3);
        case opcodes::SUBTRACT_WITH_CARRY_A_AND_IMMEDIATE        : return std::make_unique<SubtractWithCarryAAndImmediate>(fetch_byte());
        case opcodes::RESTART_3                                  : return std::make_unique<Restart>(3);

        case opcodes::LOAD_A_INTO_PORT_ADDRESS_IMMEDIATE         : return std::make_unique<LoadAIntoPortAddressImmediate>(fetch_byte());
        case opcodes::POP_HL                                     : return std::make_unique<Pop16BitRegister>(Register16Bit::HL);
        case opcodes::LOAD_A_INTO_PORT_ADDRESS_C                 : return std::make_unique<LoadAIntoPortAddressC>();
        case opcodes::UNUSED_4                                   : return std::make_unique<Unused>(4);
        case opcodes::UNUSED_5                                   : return std::make_unique<Unused>(5);
        case opcodes::PUSH_HL                                    : return std::make_unique<Push16BitRegister>(Register16Bit::HL);
        case opcodes::AND_A_AND_IMMEDIATE                        : return std::make_unique<AndAAndImmediate>(fetch_byte());
        case opcodes::RESTART_4                                  : return std::make_unique<Restart>(4);
        case opcodes::ADD_SP_AND_IMMEDIATE                       : return std::make_unique<AddSPAndImmediate>(fetch_word());
        case opcodes::JUMP_TO_HL                                 : return std::make_unique<JumpToHL>();
        case opcodes::LOAD_A_INTO_ADDRESS_IMMEDIATE              : return std::make_unique<LoadAIntoAddressImmediate>(fetch_word());
        case opcodes::UNUSED_6                                   : return std::make_unique<Unused>(6);
        case opcodes::UNUSED_7                                   : return std::make_unique<Unused>(7);
        case opcodes::UNUSED_8                                   : return std::make_unique<Unused>(8);
        case opcodes::XOR_A_AND_IMMEDIATE                        : return std::make_unique<XorAAndImmediate>(fetch_byte());
        case opcodes::RESTART_5                                  : return std::make_unique<Restart>(5);

        case opcodes::LOAD_PORT_ADDRESS_IMMEDIATE_INTO_A         : return std::make_unique<LoadPortAddressImmediateIntoA>(fetch_byte());
        case opcodes::POP_AF                                     : return std::make_unique<Pop16BitRegister>(Register16Bit::AF);
        case opcodes::LOAD_PORT_ADDRESS_C_INTO_A                 : return std::make_unique<LoadPortAddressCIntoA>();
        case opcodes::DISABLE_INTERRUPTS                         : return std::make_unique<DisableInterrupts>();
        case opcodes::UNUSED_9                                   : return std::make_unique<Unused>(9);
        case opcodes::PUSH_AF                                    : return std::make_unique<Push16BitRegister>(Register16Bit::AF);
        case opcodes::OR_A_AND_IMMEDIATE                         : return std::make_unique<OrAAndImmediate>(fetch_byte());
        case opcodes::RESTART_6                                  : return std::make_unique<Restart>(6);
        case opcodes::LOAD_SP_SHIFTED_BY_IMMEDIATE_INTO_HL       : return std::make_unique<LoadSPShiftedByImmediateIntoHL>(fetch_byte());
        case opcodes::LOAD_HL_INTO_SP                            : return std::make_unique<LoadHLIntoSP>();
        case opcodes::LOAD_ADDRESS_IMMEDIATE_INTO_A              : return std::make_unique<LoadAddressImmediateIntoA>(fetch_word());
        case opcodes::ENABLE_INTERRUPTS                          : return std::make_unique<EnableInterrupts>();
        case opcodes::UNUSED_10                                  : return std::make_unique<Unused>(10);
        case opcodes::UNUSED_11                                  : return std::make_unique<Unused>(11);
        case opcodes::COMPARE_A_AND_IMMEDIATE                    : return std::make_unique<CompareAAndImmediate>(fetch_byte());
        case opcodes::RESTART_7                                  : return std::make_unique<Restart>(7);

            //

        case opcodes::ROTATE_LEFT_CONTENTS_OF_B                  : return std::make_unique<RotateLeftContentsOf8BitRegister>(Register8Bit::B);
        case opcodes::ROTATE_LEFT_CONTENTS_OF_C                  : return std::make_unique<RotateLeftContentsOf8BitRegister>(Register8Bit::C);
        case opcodes::ROTATE_LEFT_CONTENTS_OF_D                  : return std::make_unique<RotateLeftContentsOf8BitRegister>(Register8Bit::D);
        case opcodes::ROTATE_LEFT_CONTENTS_OF_E                  : return std::make_unique<RotateLeftContentsOf8BitRegister>(Register8Bit::E);
        case opcodes::ROTATE_LEFT_CONTENTS_OF_H                  : return std::make_unique<RotateLeftContentsOf8BitRegister>(Register8Bit::H);
        case opcodes::ROTATE_LEFT_CONTENTS_OF_L                  : return std::make_unique<RotateLeftContentsOf8BitRegister>(Register8Bit::L);
        case opcodes::ROTATE_LEFT_CONTENTS_OF_ADDRESS_HL         : return std::make_unique<RotateLeftContentsOf8BitRegister>(Register8Bit::ADDRESS_HL);
        case opcodes::ROTATE_LEFT_CONTENTS_OF_A                  : return std::make_unique<RotateLeftContentsOf8BitRegister>(Register8Bit::A);
        case opcodes::ROTATE_RIGHT_CONTENTS_OF_B                 : return std::make_unique<RotateRightContentsOf8BitRegister>(Register8Bit::B);
        case opcodes::ROTATE_RIGHT_CONTENTS_OF_C                 : return std::make_unique<RotateRightContentsOf8BitRegister>(Register8Bit::C);
        case opcodes::ROTATE_RIGHT_CONTENTS_OF_D                 : return std::make_unique<RotateRightContentsOf8BitRegister>(Register8Bit::D);
        case opcodes::ROTATE_RIGHT_CONTENTS_OF_E                 : return std::make_unique<RotateRightContentsOf8BitRegister>(Register8Bit::E);
        case opcodes::ROTATE_RIGHT_CONTENTS_OF_H                 : return std::make_unique<RotateRightContentsOf8BitRegister>(Register8Bit::H);
        case opcodes::ROTATE_RIGHT_CONTENTS_OF_L                 : return std::make_unique<RotateRightContentsOf8BitRegister>(Register8Bit::L);
        case opcodes::ROTATE_RIGHT_CONTENTS_OF_ADDRESS_HL        : return std::make_unique<RotateRightContentsOf8BitRegister>(Register8Bit::ADDRESS_HL);
        case opcodes::ROTATE_RIGHT_CONTENTS_OF_A                 : return std::make_unique<RotateRightContentsOf8BitRegister>(Register8Bit::A);

        case opcodes::ROTATE_LEFT_B                              : return std::make_unique<RotateLeft8BitRegister>(Register8Bit::B);
        case opcodes::ROTATE_LEFT_C                              : return std::make_unique<RotateLeft8BitRegister>(Register8Bit::C);
        case opcodes::ROTATE_LEFT_D                              : return std::make_unique<RotateLeft8BitRegister>(Register8Bit::D);
        case opcodes::ROTATE_LEFT_E                              : return std::make_unique<RotateLeft8BitRegister>(Register8Bit::E);
        case opcodes::ROTATE_LEFT_H                              : return std::make_unique<RotateLeft8BitRegister>(Register8Bit::H);
        case opcodes::ROTATE_LEFT_L                              : return std::make_unique<RotateLeft8BitRegister>(Register8Bit::L);
        case opcodes::ROTATE_LEFT_ADDRESS_HL                     : return std::make_unique<RotateLeft8BitRegister>(Register8Bit::ADDRESS_HL);
        case opcodes::ROTATE_LEFT_A                              : return std::make_unique<RotateLeft8BitRegister>(Register8Bit::A);
        case opcodes::ROTATE_RIGHT_B                             : return std::make_unique<RotateRight8BitRegister>(Register8Bit::B);
        case opcodes::ROTATE_RIGHT_C                             : return std::make_unique<RotateRight8BitRegister>(Register8Bit::C);
        case opcodes::ROTATE_RIGHT_D                             : return std::make_unique<RotateRight8BitRegister>(Register8Bit::D);
        case opcodes::ROTATE_RIGHT_E                             : return std::make_unique<RotateRight8BitRegister>(Register8Bit::E);
        case opcodes::ROTATE_RIGHT_H                             : return std::make_unique<RotateRight8BitRegister>(Register8Bit::H);
        case opcodes::ROTATE_RIGHT_L                             : return std::make_unique<RotateRight8BitRegister>(Register8Bit::L);
        case opcodes::ROTATE_RIGHT_ADDRESS_HL                    : return std::make_unique<RotateRight8BitRegister>(Register8Bit::ADDRESS_HL);
        case opcodes::ROTATE_RIGHT_A                             : return std::make_unique<RotateRight8BitRegister>(Register8Bit::A);

        case opcodes::SHIFT_LEFT_ARITHMETICAL_B                  : return std::make_unique<ShiftLeftArithmetical8BitRegister>(Register8Bit::B);
        case opcodes::SHIFT_LEFT_ARITHMETICAL_C                  : return std::make_unique<ShiftLeftArithmetical8BitRegister>(Register8Bit::C);
        case opcodes::SHIFT_LEFT_ARITHMETICAL_D                  : return std::make_unique<ShiftLeftArithmetical8BitRegister>(Register8Bit::D);
        case opcodes::SHIFT_LEFT_ARITHMETICAL_E                  : return std::make_unique<ShiftLeftArithmetical8BitRegister>(Register8Bit::E);
        case opcodes::SHIFT_LEFT_ARITHMETICAL_H                  : return std::make_unique<ShiftLeftArithmetical8BitRegister>(Register8Bit::H);
        case opcodes::SHIFT_LEFT_ARITHMETICAL_L                  : return std::make_unique<ShiftLeftArithmetical8BitRegister>(Register8Bit::L);
        case opcodes::SHIFT_LEFT_ARITHMETICAL_ADDRESS_HL         : return std::make_unique<ShiftLeftArithmetical8BitRegister>(Register8Bit::ADDRESS_HL);
        case opcodes::SHIFT_LEFT_ARITHMETICAL_A                  : return std::make_unique<ShiftLeftArithmetical8BitRegister>(Register8Bit::A);
        case opcodes::SHIFT_RIGHT_ARITHMETICAL_B                 : return std::make_unique<ShiftRightArithmetical8BitRegister>(Register8Bit::B);
        case opcodes::SHIFT_RIGHT_ARITHMETICAL_C                 : return std::make_unique<ShiftRightArithmetical8BitRegister>(Register8Bit::C);
        case opcodes::SHIFT_RIGHT_ARITHMETICAL_D                 : return std::make_unique<ShiftRightArithmetical8BitRegister>(Register8Bit::D);
        case opcodes::SHIFT_RIGHT_ARITHMETICAL_E                 : return std::make_unique<ShiftRightArithmetical8BitRegister>(Register8Bit::E);
        case opcodes::SHIFT_RIGHT_ARITHMETICAL_H                 : return std::make_unique<ShiftRightArithmetical8BitRegister>(Register8Bit::H);
        case opcodes::SHIFT_RIGHT_ARITHMETICAL_L                 : return std::make_unique<ShiftRightArithmetical8BitRegister>(Register8Bit::L);
        case opcodes::SHIFT_RIGHT_ARITHMETICAL_ADDRESS_HL        : return std::make_unique<ShiftRightArithmetical8BitRegister>(Register8Bit::ADDRESS_HL);
        case opcodes::SHIFT_RIGHT_ARITHMETICAL_A                 : return std::make_unique<ShiftRightArithmetical8BitRegister>(Register8Bit::A);

        case opcodes::SWAP_B                                     : return std::make_unique<Swap8BitRegister>(Register8Bit::B);
        case opcodes::SWAP_C                                     : return std::make_unique<Swap8BitRegister>(Register8Bit::C);
        case opcodes::SWAP_D                                     : return std::make_unique<Swap8BitRegister>(Register8Bit::D);
        case opcodes::SWAP_E                                     : return std::make_unique<Swap8BitRegister>(Register8Bit::E);
        case opcodes::SWAP_H                                     : return std::make_unique<Swap8BitRegister>(Register8Bit::H);
        case opcodes::SWAP_L                                     : return std::make_unique<Swap8BitRegister>(Register8Bit::L);
        case opcodes::SWAP_ADDRESS_HL                            : return std::make_unique<Swap8BitRegister>(Register8Bit::ADDRESS_HL);
        case opcodes::SWAP_A                                     : return std::make_unique<Swap8BitRegister>(Register8Bit::A);
        case opcodes::SHIFT_RIGHT_LOGICAL_B                      : return std::make_unique<ShiftRightLogical8BitRegister>(Register8Bit::B);
        case opcodes::SHIFT_RIGHT_LOGICAL_C                      : return std::make_unique<ShiftRightLogical8BitRegister>(Register8Bit::C);
        case opcodes::SHIFT_RIGHT_LOGICAL_D                      : return std::make_unique<ShiftRightLogical8BitRegister>(Register8Bit::D);
        case opcodes::SHIFT_RIGHT_LOGICAL_E                      : return std::make_unique<ShiftRightLogical8BitRegister>(Register8Bit::E);
        case opcodes::SHIFT_RIGHT_LOGICAL_H                      : return std::make_unique<ShiftRightLogical8BitRegister>(Register8Bit::H);
        case opcodes::SHIFT_RIGHT_LOGICAL_L                      : return std::make_unique<ShiftRightLogical8BitRegister>(Register8Bit::L);
        case opcodes::SHIFT_RIGHT_LOGICAL_ADDRESS_HL             : return std::make_unique<ShiftRightLogical8BitRegister>(Register8Bit::ADDRESS_HL);
        case opcodes::SHIFT_RIGHT_LOGICAL_A                      : return std::make_unique<ShiftRightLogical8BitRegister>(Register8Bit::A);

        case opcodes::BIT_0_OF_B_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(0, Register8Bit::B);
        case opcodes::BIT_0_OF_C_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(0, Register8Bit::C);
        case opcodes::BIT_0_OF_D_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(0, Register8Bit::D);
        case opcodes::BIT_0_OF_E_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(0, Register8Bit::E);
        case opcodes::BIT_0_OF_H_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(0, Register8Bit::H);
        case opcodes::BIT_0_OF_L_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(0, Register8Bit::L);
        case opcodes::BIT_0_OF_ADDRESS_HL_COMPLEMENT_INTO_ZERO   : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(0, Register8Bit::ADDRESS_HL);
        case opcodes::BIT_0_OF_A_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(0, Register8Bit::A);
        case opcodes::BIT_1_OF_B_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(1, Register8Bit::B);
        case opcodes::BIT_1_OF_C_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(1, Register8Bit::C);
        case opcodes::BIT_1_OF_D_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(1, Register8Bit::D);
        case opcodes::BIT_1_OF_E_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(1, Register8Bit::E);
        case opcodes::BIT_1_OF_H_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(1, Register8Bit::H);
        case opcodes::BIT_1_OF_L_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(1, Register8Bit::L);
        case opcodes::BIT_1_OF_ADDRESS_HL_COMPLEMENT_INTO_ZERO   : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(1, Register8Bit::ADDRESS_HL);
        case opcodes::BIT_1_OF_A_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(1, Register8Bit::A);

        case opcodes::BIT_2_OF_B_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(2, Register8Bit::B);
        case opcodes::BIT_2_OF_C_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(2, Register8Bit::C);
        case opcodes::BIT_2_OF_D_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(2, Register8Bit::D);
        case opcodes::BIT_2_OF_E_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(2, Register8Bit::E);
        case opcodes::BIT_2_OF_H_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(2, Register8Bit::H);
        case opcodes::BIT_2_OF_L_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(2, Register8Bit::L);
        case opcodes::BIT_2_OF_ADDRESS_HL_COMPLEMENT_INTO_ZERO   : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(2, Register8Bit::ADDRESS_HL);
        case opcodes::BIT_2_OF_A_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(2, Register8Bit::A);
        case opcodes::BIT_3_OF_B_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(3, Register8Bit::B);
        case opcodes::BIT_3_OF_C_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(3, Register8Bit::C);
        case opcodes::BIT_3_OF_D_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(3, Register8Bit::D);
        case opcodes::BIT_3_OF_E_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(3, Register8Bit::E);
        case opcodes::BIT_3_OF_H_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(3, Register8Bit::H);
        case opcodes::BIT_3_OF_L_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(3, Register8Bit::L);
        case opcodes::BIT_3_OF_ADDRESS_HL_COMPLEMENT_INTO_ZERO   : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(3, Register8Bit::ADDRESS_HL);
        case opcodes::BIT_3_OF_A_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(3, Register8Bit::A);

        case opcodes::BIT_4_OF_B_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(4, Register8Bit::B);
        case opcodes::BIT_4_OF_C_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(4, Register8Bit::C);
        case opcodes::BIT_4_OF_D_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(4, Register8Bit::D);
        case opcodes::BIT_4_OF_E_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(4, Register8Bit::E);
        case opcodes::BIT_4_OF_H_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(4, Register8Bit::H);
        case opcodes::BIT_4_OF_L_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(4, Register8Bit::L);
        case opcodes::BIT_4_OF_ADDRESS_HL_COMPLEMENT_INTO_ZERO   : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(4, Register8Bit::ADDRESS_HL);
        case opcodes::BIT_4_OF_A_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(4, Register8Bit::A);
        case opcodes::BIT_5_OF_B_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(5, Register8Bit::B);
        case opcodes::BIT_5_OF_C_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(5, Register8Bit::C);
        case opcodes::BIT_5_OF_D_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(5, Register8Bit::D);
        case opcodes::BIT_5_OF_E_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(5, Register8Bit::E);
        case opcodes::BIT_5_OF_H_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(5, Register8Bit::H);
        case opcodes::BIT_5_OF_L_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(5, Register8Bit::L);
        case opcodes::BIT_5_OF_ADDRESS_HL_COMPLEMENT_INTO_ZERO   : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(5, Register8Bit::ADDRESS_HL);
        case opcodes::BIT_5_OF_A_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(5, Register8Bit::A);

        case opcodes::BIT_6_OF_B_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(6, Register8Bit::B);
        case opcodes::BIT_6_OF_C_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(6, Register8Bit::C);
        case opcodes::BIT_6_OF_D_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(6, Register8Bit::D);
        case opcodes::BIT_6_OF_E_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(6, Register8Bit::E);
        case opcodes::BIT_6_OF_H_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(6, Register8Bit::H);
        case opcodes::BIT_6_OF_L_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(6, Register8Bit::L);
        case opcodes::BIT_6_OF_ADDRESS_HL_COMPLEMENT_INTO_ZERO   : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(6, Register8Bit::ADDRESS_HL);
        case opcodes::BIT_6_OF_A_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(6, Register8Bit::A);
        case opcodes::BIT_7_OF_B_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(7, Register8Bit::B);
        case opcodes::BIT_7_OF_C_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(7, Register8Bit::C);
        case opcodes::BIT_7_OF_D_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(7, Register8Bit::D);
        case opcodes::BIT_7_OF_E_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(7, Register8Bit::E);
        case opcodes::BIT_7_OF_H_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(7, Register8Bit::H);
        case opcodes::BIT_7_OF_L_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(7, Register8Bit::L);
        case opcodes::BIT_7_OF_ADDRESS_HL_COMPLEMENT_INTO_ZERO   : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(7, Register8Bit::ADDRESS_HL);
        case opcodes::BIT_7_OF_A_COMPLEMENT_INTO_ZERO            : return std::make_unique<BitOf8BitRegisterComplementIntoZero>(7, Register8Bit::A);

        case opcodes::RESET_BIT_0_OF_B                           : return std::make_unique<ResetBitOf8BitRegister>(0, Register8Bit::B);
        case opcodes::RESET_BIT_0_OF_C                           : return std::make_unique<ResetBitOf8BitRegister>(0, Register8Bit::C);
        case opcodes::RESET_BIT_0_OF_D                           : return std::make_unique<ResetBitOf8BitRegister>(0, Register8Bit::D);
        case opcodes::RESET_BIT_0_OF_E                           : return std::make_unique<ResetBitOf8BitRegister>(0, Register8Bit::E);
        case opcodes::RESET_BIT_0_OF_H                           : return std::make_unique<ResetBitOf8BitRegister>(0, Register8Bit::H);
        case opcodes::RESET_BIT_0_OF_L                           : return std::make_unique<ResetBitOf8BitRegister>(0, Register8Bit::L);
        case opcodes::RESET_BIT_0_OF_ADDRESS_HL                  : return std::make_unique<ResetBitOf8BitRegister>(0, Register8Bit::ADDRESS_HL);
        case opcodes::RESET_BIT_0_OF_A                           : return std::make_unique<ResetBitOf8BitRegister>(0, Register8Bit::A);
        case opcodes::RESET_BIT_1_OF_B                           : return std::make_unique<ResetBitOf8BitRegister>(1, Register8Bit::B);
        case opcodes::RESET_BIT_1_OF_C                           : return std::make_unique<ResetBitOf8BitRegister>(1, Register8Bit::C);
        case opcodes::RESET_BIT_1_OF_D                           : return std::make_unique<ResetBitOf8BitRegister>(1, Register8Bit::D);
        case opcodes::RESET_BIT_1_OF_E                           : return std::make_unique<ResetBitOf8BitRegister>(1, Register8Bit::E);
        case opcodes::RESET_BIT_1_OF_H                           : return std::make_unique<ResetBitOf8BitRegister>(1, Register8Bit::H);
        case opcodes::RESET_BIT_1_OF_L                           : return std::make_unique<ResetBitOf8BitRegister>(1, Register8Bit::L);
        case opcodes::RESET_BIT_1_OF_ADDRESS_HL                  : return std::make_unique<ResetBitOf8BitRegister>(1, Register8Bit::ADDRESS_HL);
        case opcodes::RESET_BIT_1_OF_A                           : return std::make_unique<ResetBitOf8BitRegister>(1, Register8Bit::A);

        case opcodes::RESET_BIT_2_OF_B                           : return std::make_unique<ResetBitOf8BitRegister>(2, Register8Bit::B);
        case opcodes::RESET_BIT_2_OF_C                           : return std::make_unique<ResetBitOf8BitRegister>(2, Register8Bit::C);
        case opcodes::RESET_BIT_2_OF_D                           : return std::make_unique<ResetBitOf8BitRegister>(2, Register8Bit::D);
        case opcodes::RESET_BIT_2_OF_E                           : return std::make_unique<ResetBitOf8BitRegister>(2, Register8Bit::E);
        case opcodes::RESET_BIT_2_OF_H                           : return std::make_unique<ResetBitOf8BitRegister>(2, Register8Bit::H);
        case opcodes::RESET_BIT_2_OF_L                           : return std::make_unique<ResetBitOf8BitRegister>(2, Register8Bit::L);
        case opcodes::RESET_BIT_2_OF_ADDRESS_HL                  : return std::make_unique<ResetBitOf8BitRegister>(2, Register8Bit::ADDRESS_HL);
        case opcodes::RESET_BIT_2_OF_A                           : return std::make_unique<ResetBitOf8BitRegister>(2, Register8Bit::A);
        case opcodes::RESET_BIT_3_OF_B                           : return std::make_unique<ResetBitOf8BitRegister>(3, Register8Bit::B);
        case opcodes::RESET_BIT_3_OF_C                           : return std::make_unique<ResetBitOf8BitRegister>(3, Register8Bit::C);
        case opcodes::RESET_BIT_3_OF_D                           : return std::make_unique<ResetBitOf8BitRegister>(3, Register8Bit::D);
        case opcodes::RESET_BIT_3_OF_E                           : return std::make_unique<ResetBitOf8BitRegister>(3, Register8Bit::E);
        case opcodes::RESET_BIT_3_OF_H                           : return std::make_unique<ResetBitOf8BitRegister>(3, Register8Bit::H);
        case opcodes::RESET_BIT_3_OF_L                           : return std::make_unique<ResetBitOf8BitRegister>(3, Register8Bit::L);
        case opcodes::RESET_BIT_3_OF_ADDRESS_HL                  : return std::make_unique<ResetBitOf8BitRegister>(3, Register8Bit::ADDRESS_HL);
        case opcodes::RESET_BIT_3_OF_A                           : return std::make_unique<ResetBitOf8BitRegister>(3, Register8Bit::A);

        case opcodes::RESET_BIT_4_OF_B                           : return std::make_unique<ResetBitOf8BitRegister>(4, Register8Bit::B);
        case opcodes::RESET_BIT_4_OF_C                           : return std::make_unique<ResetBitOf8BitRegister>(4, Register8Bit::C);
        case opcodes::RESET_BIT_4_OF_D                           : return std::make_unique<ResetBitOf8BitRegister>(4, Register8Bit::D);
        case opcodes::RESET_BIT_4_OF_E                           : return std::make_unique<ResetBitOf8BitRegister>(4, Register8Bit::E);
        case opcodes::RESET_BIT_4_OF_H                           : return std::make_unique<ResetBitOf8BitRegister>(4, Register8Bit::H);
        case opcodes::RESET_BIT_4_OF_L                           : return std::make_unique<ResetBitOf8BitRegister>(4, Register8Bit::L);
        case opcodes::RESET_BIT_4_OF_ADDRESS_HL                  : return std::make_unique<ResetBitOf8BitRegister>(4, Register8Bit::ADDRESS_HL);
        case opcodes::RESET_BIT_4_OF_A                           : return std::make_unique<ResetBitOf8BitRegister>(4, Register8Bit::A);
        case opcodes::RESET_BIT_5_OF_B                           : return std::make_unique<ResetBitOf8BitRegister>(5, Register8Bit::B);
        case opcodes::RESET_BIT_5_OF_C                           : return std::make_unique<ResetBitOf8BitRegister>(5, Register8Bit::C);
        case opcodes::RESET_BIT_5_OF_D                           : return std::make_unique<ResetBitOf8BitRegister>(5, Register8Bit::D);
        case opcodes::RESET_BIT_5_OF_E                           : return std::make_unique<ResetBitOf8BitRegister>(5, Register8Bit::E);
        case opcodes::RESET_BIT_5_OF_H                           : return std::make_unique<ResetBitOf8BitRegister>(5, Register8Bit::H);
        case opcodes::RESET_BIT_5_OF_L                           : return std::make_unique<ResetBitOf8BitRegister>(5, Register8Bit::L);
        case opcodes::RESET_BIT_5_OF_ADDRESS_HL                  : return std::make_unique<ResetBitOf8BitRegister>(5, Register8Bit::ADDRESS_HL);
        case opcodes::RESET_BIT_5_OF_A                           : return std::make_unique<ResetBitOf8BitRegister>(5, Register8Bit::A);

        case opcodes::RESET_BIT_6_OF_B                           : return std::make_unique<ResetBitOf8BitRegister>(6, Register8Bit::B);
        case opcodes::RESET_BIT_6_OF_C                           : return std::make_unique<ResetBitOf8BitRegister>(6, Register8Bit::C);
        case opcodes::RESET_BIT_6_OF_D                           : return std::make_unique<ResetBitOf8BitRegister>(6, Register8Bit::D);
        case opcodes::RESET_BIT_6_OF_E                           : return std::make_unique<ResetBitOf8BitRegister>(6, Register8Bit::E);
        case opcodes::RESET_BIT_6_OF_H                           : return std::make_unique<ResetBitOf8BitRegister>(6, Register8Bit::H);
        case opcodes::RESET_BIT_6_OF_L                           : return std::make_unique<ResetBitOf8BitRegister>(6, Register8Bit::L);
        case opcodes::RESET_BIT_6_OF_ADDRESS_HL                  : return std::make_unique<ResetBitOf8BitRegister>(6, Register8Bit::ADDRESS_HL);
        case opcodes::RESET_BIT_6_OF_A                           : return std::make_unique<ResetBitOf8BitRegister>(6, Register8Bit::A);
        case opcodes::RESET_BIT_7_OF_B                           : return std::make_unique<ResetBitOf8BitRegister>(7, Register8Bit::B);
        case opcodes::RESET_BIT_7_OF_C                           : return std::make_unique<ResetBitOf8BitRegister>(7, Register8Bit::C);
        case opcodes::RESET_BIT_7_OF_D                           : return std::make_unique<ResetBitOf8BitRegister>(7, Register8Bit::D);
        case opcodes::RESET_BIT_7_OF_E                           : return std::make_unique<ResetBitOf8BitRegister>(7, Register8Bit::E);
        case opcodes::RESET_BIT_7_OF_H                           : return std::make_unique<ResetBitOf8BitRegister>(7, Register8Bit::H);
        case opcodes::RESET_BIT_7_OF_L                           : return std::make_unique<ResetBitOf8BitRegister>(7, Register8Bit::L);
        case opcodes::RESET_BIT_7_OF_ADDRESS_HL                  : return std::make_unique<ResetBitOf8BitRegister>(7, Register8Bit::ADDRESS_HL);
        case opcodes::RESET_BIT_7_OF_A                           : return std::make_unique<ResetBitOf8BitRegister>(7, Register8Bit::A);

        case opcodes::SET_BIT_0_OF_B                             : return std::make_unique<SetBitOf8BitRegister>(0, Register8Bit::B);
        case opcodes::SET_BIT_0_OF_C                             : return std::make_unique<SetBitOf8BitRegister>(0, Register8Bit::C);
        case opcodes::SET_BIT_0_OF_D                             : return std::make_unique<SetBitOf8BitRegister>(0, Register8Bit::D);
        case opcodes::SET_BIT_0_OF_E                             : return std::make_unique<SetBitOf8BitRegister>(0, Register8Bit::E);
        case opcodes::SET_BIT_0_OF_H                             : return std::make_unique<SetBitOf8BitRegister>(0, Register8Bit::H);
        case opcodes::SET_BIT_0_OF_L                             : return std::make_unique<SetBitOf8BitRegister>(0, Register8Bit::L);
        case opcodes::SET_BIT_0_OF_ADDRESS_HL                    : return std::make_unique<SetBitOf8BitRegister>(0, Register8Bit::ADDRESS_HL);
        case opcodes::SET_BIT_0_OF_A                             : return std::make_unique<SetBitOf8BitRegister>(0, Register8Bit::A);
        case opcodes::SET_BIT_1_OF_B                             : return std::make_unique<SetBitOf8BitRegister>(1, Register8Bit::B);
        case opcodes::SET_BIT_1_OF_C                             : return std::make_unique<SetBitOf8BitRegister>(1, Register8Bit::C);
        case opcodes::SET_BIT_1_OF_D                             : return std::make_unique<SetBitOf8BitRegister>(1, Register8Bit::D);
        case opcodes::SET_BIT_1_OF_E                             : return std::make_unique<SetBitOf8BitRegister>(1, Register8Bit::E);
        case opcodes::SET_BIT_1_OF_H                             : return std::make_unique<SetBitOf8BitRegister>(1, Register8Bit::H);
        case opcodes::SET_BIT_1_OF_L                             : return std::make_unique<SetBitOf8BitRegister>(1, Register8Bit::L);
        case opcodes::SET_BIT_1_OF_ADDRESS_HL                    : return std::make_unique<SetBitOf8BitRegister>(1, Register8Bit::ADDRESS_HL);
        case opcodes::SET_BIT_1_OF_A                             : return std::make_unique<SetBitOf8BitRegister>(1, Register8Bit::A);

        case opcodes::SET_BIT_2_OF_B                             : return std::make_unique<SetBitOf8BitRegister>(2, Register8Bit::B);
        case opcodes::SET_BIT_2_OF_C                             : return std::make_unique<SetBitOf8BitRegister>(2, Register8Bit::C);
        case opcodes::SET_BIT_2_OF_D                             : return std::make_unique<SetBitOf8BitRegister>(2, Register8Bit::D);
        case opcodes::SET_BIT_2_OF_E                             : return std::make_unique<SetBitOf8BitRegister>(2, Register8Bit::E);
        case opcodes::SET_BIT_2_OF_H                             : return std::make_unique<SetBitOf8BitRegister>(2, Register8Bit::H);
        case opcodes::SET_BIT_2_OF_L                             : return std::make_unique<SetBitOf8BitRegister>(2, Register8Bit::L);
        case opcodes::SET_BIT_2_OF_ADDRESS_HL                    : return std::make_unique<SetBitOf8BitRegister>(2, Register8Bit::ADDRESS_HL);
        case opcodes::SET_BIT_2_OF_A                             : return std::make_unique<SetBitOf8BitRegister>(2, Register8Bit::A);
        case opcodes::SET_BIT_3_OF_B                             : return std::make_unique<SetBitOf8BitRegister>(3, Register8Bit::B);
        case opcodes::SET_BIT_3_OF_C                             : return std::make_unique<SetBitOf8BitRegister>(3, Register8Bit::C);
        case opcodes::SET_BIT_3_OF_D                             : return std::make_unique<SetBitOf8BitRegister>(3, Register8Bit::D);
        case opcodes::SET_BIT_3_OF_E                             : return std::make_unique<SetBitOf8BitRegister>(3, Register8Bit::E);
        case opcodes::SET_BIT_3_OF_H                             : return std::make_unique<SetBitOf8BitRegister>(3, Register8Bit::H);
        case opcodes::SET_BIT_3_OF_L                             : return std::make_unique<SetBitOf8BitRegister>(3, Register8Bit::L);
        case opcodes::SET_BIT_3_OF_ADDRESS_HL                    : return std::make_unique<SetBitOf8BitRegister>(3, Register8Bit::ADDRESS_HL);
        case opcodes::SET_BIT_3_OF_A                             : return std::make_unique<SetBitOf8BitRegister>(3, Register8Bit::A);

        case opcodes::SET_BIT_4_OF_B                             : return std::make_unique<SetBitOf8BitRegister>(4, Register8Bit::B);
        case opcodes::SET_BIT_4_OF_C                             : return std::make_unique<SetBitOf8BitRegister>(4, Register8Bit::C);
        case opcodes::SET_BIT_4_OF_D                             : return std::make_unique<SetBitOf8BitRegister>(4, Register8Bit::D);
        case opcodes::SET_BIT_4_OF_E                             : return std::make_unique<SetBitOf8BitRegister>(4, Register8Bit::E);
        case opcodes::SET_BIT_4_OF_H                             : return std::make_unique<SetBitOf8BitRegister>(4, Register8Bit::H);
        case opcodes::SET_BIT_4_OF_L                             : return std::make_unique<SetBitOf8BitRegister>(4, Register8Bit::L);
        case opcodes::SET_BIT_4_OF_ADDRESS_HL                    : return std::make_unique<SetBitOf8BitRegister>(4, Register8Bit::ADDRESS_HL);
        case opcodes::SET_BIT_4_OF_A                             : return std::make_unique<SetBitOf8BitRegister>(4, Register8Bit::A);
        case opcodes::SET_BIT_5_OF_B                             : return std::make_unique<SetBitOf8BitRegister>(5, Register8Bit::B);
        case opcodes::SET_BIT_5_OF_C                             : return std::make_unique<SetBitOf8BitRegister>(5, Register8Bit::C);
        case opcodes::SET_BIT_5_OF_D                             : return std::make_unique<SetBitOf8BitRegister>(5, Register8Bit::D);
        case opcodes::SET_BIT_5_OF_E                             : return std::make_unique<SetBitOf8BitRegister>(5, Register8Bit::E);
        case opcodes::SET_BIT_5_OF_H                             : return std::make_unique<SetBitOf8BitRegister>(5, Register8Bit::H);
        case opcodes::SET_BIT_5_OF_L                             : return std::make_unique<SetBitOf8BitRegister>(5, Register8Bit::L);
        case opcodes::SET_BIT_5_OF_ADDRESS_HL                    : return std::make_unique<SetBitOf8BitRegister>(5, Register8Bit::ADDRESS_HL);
        case opcodes::SET_BIT_5_OF_A                             : return std::make_unique<SetBitOf8BitRegister>(5, Register8Bit::A);

        case opcodes::SET_BIT_6_OF_B                             : return std::make_unique<SetBitOf8BitRegister>(6, Register8Bit::B);
        case opcodes::SET_BIT_6_OF_C                             : return std::make_unique<SetBitOf8BitRegister>(6, Register8Bit::C);
        case opcodes::SET_BIT_6_OF_D                             : return std::make_unique<SetBitOf8BitRegister>(6, Register8Bit::D);
        case opcodes::SET_BIT_6_OF_E                             : return std::make_unique<SetBitOf8BitRegister>(6, Register8Bit::E);
        case opcodes::SET_BIT_6_OF_H                             : return std::make_unique<SetBitOf8BitRegister>(6, Register8Bit::H);
        case opcodes::SET_BIT_6_OF_L                             : return std::make_unique<SetBitOf8BitRegister>(6, Register8Bit::L);
        case opcodes::SET_BIT_6_OF_ADDRESS_HL                    : return std::make_unique<SetBitOf8BitRegister>(6, Register8Bit::ADDRESS_HL);
        case opcodes::SET_BIT_6_OF_A                             : return std::make_unique<SetBitOf8BitRegister>(6, Register8Bit::A);
        case opcodes::SET_BIT_7_OF_B                             : return std::make_unique<SetBitOf8BitRegister>(7, Register8Bit::B);
        case opcodes::SET_BIT_7_OF_C                             : return std::make_unique<SetBitOf8BitRegister>(7, Register8Bit::C);
        case opcodes::SET_BIT_7_OF_D                             : return std::make_unique<SetBitOf8BitRegister>(7, Register8Bit::D);
        case opcodes::SET_BIT_7_OF_E                             : return std::make_unique<SetBitOf8BitRegister>(7, Register8Bit::E);
        case opcodes::SET_BIT_7_OF_H                             : return std::make_unique<SetBitOf8BitRegister>(7, Register8Bit::H);
        case opcodes::SET_BIT_7_OF_L                             : return std::make_unique<SetBitOf8BitRegister>(7, Register8Bit::L);
        case opcodes::SET_BIT_7_OF_ADDRESS_HL                    : return std::make_unique<SetBitOf8BitRegister>(7, Register8Bit::ADDRESS_HL);
        case opcodes::SET_BIT_7_OF_A                             : return std::make_unique<SetBitOf8BitRegister>(7, Register8Bit::A);

        default: return std::make_unique<Unknown>();
    }
}