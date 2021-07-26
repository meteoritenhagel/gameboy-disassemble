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
        case opcodes::NOP                                        : return create_instruction<Nop>();
        case opcodes::LOAD_IMMEDIATE_INTO_BC                     : return create_instruction<LoadImmediateInto16BitRegister>(Register16Bit::BC, fetch_word());
        case opcodes::LOAD_A_INTO_ADDRESS_BC                     : return create_instruction<LoadAIntoAddress16BitRegister>(Register16Bit::BC);
        case opcodes::INCREMENT_BC                               : return create_instruction<IncrementRegister>(Register16Bit::BC);
        case opcodes::INCREMENT_B                                : return create_instruction<IncrementRegister>(Register8Bit::B);
        case opcodes::DECREMENT_B                                : return create_instruction<DecrementRegister>(Register8Bit::B);
        case opcodes::LOAD_IMMEDIATE_INTO_B                      : return create_instruction<LoadImmediateInto8BitRegister>(Register8Bit::B, fetch_byte());
        case opcodes::ROTATE_LEFT_CONTENTS_OF_A_AND_CLEAR_ZERO   : return create_instruction<RotateLeftContentsOfAAndClearZero>();
        case opcodes::LOAD_SP_INTO_ADDRESS_IMMEDIATE             : return create_instruction<LoadSPIntoAddressImmediate>(fetch_word());
        case opcodes::ADD_HL_AND_BC                              : return create_instruction<AddHLAnd16BitRegister>(Register16Bit::BC);
        case opcodes::LOAD_ADDRESS_BC_INTO_A                     : return create_instruction<LoadAddress16BitRegisterIntoA>(Register16Bit::BC);
        case opcodes::DECREMENT_BC                               : return create_instruction<DecrementRegister>(Register16Bit::BC);
        case opcodes::INCREMENT_C                                : return create_instruction<IncrementRegister>(Register8Bit::C);
        case opcodes::DECREMENT_C                                : return create_instruction<DecrementRegister>(Register8Bit::C);
        case opcodes::LOAD_IMMEDIATE_INTO_C                      : return create_instruction<LoadImmediateInto8BitRegister>(Register8Bit::C, fetch_byte());
        case opcodes::ROTATE_RIGHT_CONTENTS_OF_A_AND_CLEAR_ZERO  : return create_instruction<RotateRightContentsOfAAndClearZero>();

        case opcodes::STOP                                       : return create_instruction<Stop>();
        case opcodes::LOAD_IMMEDIATE_INTO_DE                     : return create_instruction<LoadImmediateInto16BitRegister>(Register16Bit::DE, fetch_word());
        case opcodes::LOAD_A_INTO_ADDRESS_DE                     : return create_instruction<LoadAIntoAddress16BitRegister>(Register16Bit::DE);
        case opcodes::INCREMENT_DE                               : return create_instruction<IncrementRegister>(Register16Bit::DE);
        case opcodes::INCREMENT_D                                : return create_instruction<IncrementRegister>(Register8Bit::D);
        case opcodes::DECREMENT_D                                : return create_instruction<DecrementRegister>(Register8Bit::D);
        case opcodes::LOAD_IMMEDIATE_INTO_D                      : return create_instruction<LoadImmediateInto8BitRegister>(Register8Bit::D, fetch_byte());
        case opcodes::ROTATE_LEFT_A_AND_CLEAR_ZERO               : return create_instruction<RotateLeftAAndClearZero>();
        case opcodes::JUMP_RELATIVE                              : return create_instruction<JumpRelative>(fetch_byte());
        case opcodes::ADD_HL_AND_DE                              : return create_instruction<AddHLAnd16BitRegister>(Register16Bit::DE);
        case opcodes::LOAD_ADDRESS_DE_INTO_A                     : return create_instruction<LoadAddress16BitRegisterIntoA>(Register16Bit::DE);
        case opcodes::DECREMENT_DE                               : return create_instruction<DecrementRegister>(Register16Bit::DE);
        case opcodes::INCREMENT_E                                : return create_instruction<IncrementRegister>(Register8Bit::E);
        case opcodes::DECREMENT_E                                : return create_instruction<DecrementRegister>(Register8Bit::E);
        case opcodes::LOAD_IMMEDIATE_INTO_E                      : return create_instruction<LoadImmediateInto8BitRegister>(Register8Bit::E, fetch_byte());
        case opcodes::ROTATE_RIGHT_A_AND_CLEAR_ZERO              : return create_instruction<RotateRightAAndClearZero>();

        case opcodes::JUMP_RELATIVE_IF_NOT_ZERO                  : return create_instruction<JumpRelativeConditional>(FlagCondition::NOT_ZERO, fetch_byte());
        case opcodes::LOAD_IMMEDIATE_INTO_HL                     : return create_instruction<LoadImmediateInto16BitRegister>(Register16Bit::HL, fetch_word());
        case opcodes::LOAD_A_INTO_ADDRESS_HL_INCREMENT           : return create_instruction<LoadAIntoAddressHLIncrement>();
        case opcodes::INCREMENT_HL                               : return create_instruction<IncrementRegister>(Register16Bit::HL);
        case opcodes::INCREMENT_H                                : return create_instruction<IncrementRegister>(Register8Bit::H);
        case opcodes::DECREMENT_H                                : return create_instruction<DecrementRegister>(Register8Bit::H);
        case opcodes::LOAD_IMMEDIATE_INTO_H                      : return create_instruction<LoadImmediateInto8BitRegister>(Register8Bit::H, fetch_byte());
        case opcodes::DECIMAL_ADJUST_A                           : return create_instruction<DecimalAdjustA>();
        case opcodes::JUMP_RELATIVE_IF_ZERO                      : return create_instruction<JumpRelativeConditional>(FlagCondition::ZERO, fetch_byte());
        case opcodes::ADD_HL_AND_HL                              : return create_instruction<AddHLAnd16BitRegister>(Register16Bit::HL);
        case opcodes::LOAD_ADDRESS_HL_INCREMENT_INTO_A           : return create_instruction<LoadAddressHLIncrementIntoA>();
        case opcodes::DECREMENT_HL                               : return create_instruction<DecrementRegister>(Register16Bit::HL);
        case opcodes::INCREMENT_L                                : return create_instruction<IncrementRegister>(Register8Bit::L);
        case opcodes::DECREMENT_L                                : return create_instruction<DecrementRegister>(Register8Bit::L);
        case opcodes::LOAD_IMMEDIATE_INTO_L                      : return create_instruction<LoadImmediateInto8BitRegister>(Register8Bit::L, fetch_byte());
        case opcodes::COMPLEMENT_A                               : return create_instruction<ComplementA>();

        case opcodes::JUMP_RELATIVE_IF_NOT_CARRY                 : return create_instruction<JumpRelativeConditional>(FlagCondition::NOT_CARRY, fetch_byte());
        case opcodes::LOAD_IMMEDIATE_INTO_SP                     : return create_instruction<LoadImmediateInto16BitRegister>(Register16Bit::SP, fetch_word());
        case opcodes::LOAD_A_INTO_ADDRESS_HL_DECREMENT           : return create_instruction<LoadAIntoAddressHLDecrement>();
        case opcodes::INCREMENT_SP                               : return create_instruction<IncrementRegister>(Register16Bit::SP);
        case opcodes::INCREMENT_ADDRESS_HL                       : return create_instruction<IncrementRegister>(Register8Bit::ADDRESS_HL);
        case opcodes::DECREMENT_ADDRESS_HL                       : return create_instruction<DecrementRegister>(Register8Bit::ADDRESS_HL);
        case opcodes::LOAD_IMMEDIATE_INTO_ADDRESS_HL             : return create_instruction<LoadImmediateInto8BitRegister>(Register8Bit::ADDRESS_HL, fetch_byte());
        case opcodes::SET_CARRY                                  : return create_instruction<SetCarry>();
        case opcodes::JUMP_RELATIVE_IF_CARRY                     : return create_instruction<JumpRelativeConditional>(FlagCondition::CARRY, fetch_byte());
        case opcodes::ADD_HL_AND_SP                              : return create_instruction<AddHLAnd16BitRegister>(Register16Bit::SP);
        case opcodes::LOAD_ADDRESS_HL_DECREMENT_INTO_A           : return create_instruction<LoadAddressHLDecrementIntoA>();
        case opcodes::DECREMENT_SP                               : return create_instruction<DecrementRegister>(Register16Bit::SP);
        case opcodes::INCREMENT_A                                : return create_instruction<IncrementRegister>(Register8Bit::A);
        case opcodes::DECREMENT_A                                : return create_instruction<DecrementRegister>(Register8Bit::A);
        case opcodes::LOAD_IMMEDIATE_INTO_A                      : return create_instruction<LoadImmediateInto8BitRegister>(Register8Bit::A, fetch_byte());
        case opcodes::FLIP_CARRY                                 : return create_instruction<FlipCarry>();

        case opcodes::LOAD_B_INTO_B                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::B, Register8Bit::B);
        case opcodes::LOAD_C_INTO_B                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::C, Register8Bit::B);
        case opcodes::LOAD_D_INTO_B                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::D, Register8Bit::B);
        case opcodes::LOAD_E_INTO_B                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::E, Register8Bit::B);
        case opcodes::LOAD_H_INTO_B                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::H, Register8Bit::B);
        case opcodes::LOAD_L_INTO_B                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::L, Register8Bit::B);
        case opcodes::LOAD_ADDRESS_HL_INTO_B                     : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::ADDRESS_HL, Register8Bit::B);
        case opcodes::LOAD_A_INTO_B                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::A, Register8Bit::B);
        case opcodes::LOAD_B_INTO_C                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::B, Register8Bit::C);
        case opcodes::LOAD_C_INTO_C                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::C, Register8Bit::C);
        case opcodes::LOAD_D_INTO_C                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::D, Register8Bit::C);
        case opcodes::LOAD_E_INTO_C                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::E, Register8Bit::C);
        case opcodes::LOAD_H_INTO_C                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::H, Register8Bit::C);
        case opcodes::LOAD_L_INTO_C                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::L, Register8Bit::C);
        case opcodes::LOAD_ADDRESS_HL_INTO_C                     : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::ADDRESS_HL, Register8Bit::C);
        case opcodes::LOAD_A_INTO_C                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::A, Register8Bit::C);

        case opcodes::LOAD_B_INTO_D                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::B, Register8Bit::D);
        case opcodes::LOAD_C_INTO_D                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::C, Register8Bit::D);
        case opcodes::LOAD_D_INTO_D                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::D, Register8Bit::D);
        case opcodes::LOAD_E_INTO_D                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::E, Register8Bit::D);
        case opcodes::LOAD_H_INTO_D                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::H, Register8Bit::D);
        case opcodes::LOAD_L_INTO_D                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::L, Register8Bit::D);
        case opcodes::LOAD_ADDRESS_HL_INTO_D                     : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::ADDRESS_HL, Register8Bit::D);
        case opcodes::LOAD_A_INTO_D                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::A, Register8Bit::D);
        case opcodes::LOAD_B_INTO_E                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::B, Register8Bit::E);
        case opcodes::LOAD_C_INTO_E                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::C, Register8Bit::E);
        case opcodes::LOAD_D_INTO_E                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::D, Register8Bit::E);
        case opcodes::LOAD_E_INTO_E                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::E, Register8Bit::E);
        case opcodes::LOAD_H_INTO_E                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::H, Register8Bit::E);
        case opcodes::LOAD_L_INTO_E                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::L, Register8Bit::E);
        case opcodes::LOAD_ADDRESS_HL_INTO_E                     : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::ADDRESS_HL, Register8Bit::E);
        case opcodes::LOAD_A_INTO_E                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::A, Register8Bit::E);

        case opcodes::LOAD_B_INTO_H                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::B, Register8Bit::H);
        case opcodes::LOAD_C_INTO_H                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::C, Register8Bit::H);
        case opcodes::LOAD_D_INTO_H                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::D, Register8Bit::H);
        case opcodes::LOAD_E_INTO_H                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::E, Register8Bit::H);
        case opcodes::LOAD_H_INTO_H                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::H, Register8Bit::H);
        case opcodes::LOAD_L_INTO_H                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::L, Register8Bit::H);
        case opcodes::LOAD_ADDRESS_HL_INTO_H                     : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::ADDRESS_HL, Register8Bit::H);
        case opcodes::LOAD_A_INTO_H                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::A, Register8Bit::H);
        case opcodes::LOAD_B_INTO_L                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::B, Register8Bit::L);
        case opcodes::LOAD_C_INTO_L                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::C, Register8Bit::L);
        case opcodes::LOAD_D_INTO_L                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::D, Register8Bit::L);
        case opcodes::LOAD_E_INTO_L                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::E, Register8Bit::L);
        case opcodes::LOAD_H_INTO_L                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::H, Register8Bit::L);
        case opcodes::LOAD_L_INTO_L                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::L, Register8Bit::L);
        case opcodes::LOAD_ADDRESS_HL_INTO_L                     : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::ADDRESS_HL, Register8Bit::L);
        case opcodes::LOAD_A_INTO_L                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::A, Register8Bit::L);

        case opcodes::LOAD_B_INTO_ADDRESS_HL                     : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::B, Register8Bit::ADDRESS_HL);
        case opcodes::LOAD_C_INTO_ADDRESS_HL                     : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::C, Register8Bit::ADDRESS_HL);
        case opcodes::LOAD_D_INTO_ADDRESS_HL                     : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::D, Register8Bit::ADDRESS_HL);
        case opcodes::LOAD_E_INTO_ADDRESS_HL                     : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::E, Register8Bit::ADDRESS_HL);
        case opcodes::LOAD_H_INTO_ADDRESS_HL                     : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::H, Register8Bit::ADDRESS_HL);
        case opcodes::LOAD_L_INTO_ADDRESS_HL                     : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::L, Register8Bit::ADDRESS_HL);
        case opcodes::HALT                                       : return create_instruction<Halt>();
        case opcodes::LOAD_A_INTO_ADDRESS_HL                     : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::A, Register8Bit::ADDRESS_HL);
        case opcodes::LOAD_B_INTO_A                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::B, Register8Bit::A);
        case opcodes::LOAD_C_INTO_A                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::C, Register8Bit::A);
        case opcodes::LOAD_D_INTO_A                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::D, Register8Bit::A);
        case opcodes::LOAD_E_INTO_A                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::E, Register8Bit::A);
        case opcodes::LOAD_H_INTO_A                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::H, Register8Bit::A);
        case opcodes::LOAD_L_INTO_A                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::L, Register8Bit::A);
        case opcodes::LOAD_ADDRESS_HL_INTO_A                     : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::ADDRESS_HL, Register8Bit::A);
        case opcodes::LOAD_A_INTO_A                              : return create_instruction<Load8BitRegisterInto8BitRegister>(Register8Bit::A, Register8Bit::A);

        case opcodes::ADD_A_AND_B                                : return create_instruction<AddAAnd8BitRegister>(Register8Bit::B);
        case opcodes::ADD_A_AND_C                                : return create_instruction<AddAAnd8BitRegister>(Register8Bit::C);
        case opcodes::ADD_A_AND_D                                : return create_instruction<AddAAnd8BitRegister>(Register8Bit::D);
        case opcodes::ADD_A_AND_E                                : return create_instruction<AddAAnd8BitRegister>(Register8Bit::E);
        case opcodes::ADD_A_AND_H                                : return create_instruction<AddAAnd8BitRegister>(Register8Bit::H);
        case opcodes::ADD_A_AND_L                                : return create_instruction<AddAAnd8BitRegister>(Register8Bit::L);
        case opcodes::ADD_A_AND_ADDRESS_HL                       : return create_instruction<AddAAnd8BitRegister>(Register8Bit::ADDRESS_HL);
        case opcodes::ADD_A_AND_A                                : return create_instruction<AddAAnd8BitRegister>(Register8Bit::A);
        case opcodes::ADD_WITH_CARRY_A_AND_B                     : return create_instruction<AddWithCarryAAnd8BitRegister>(Register8Bit::B);
        case opcodes::ADD_WITH_CARRY_A_AND_C                     : return create_instruction<AddWithCarryAAnd8BitRegister>(Register8Bit::C);
        case opcodes::ADD_WITH_CARRY_A_AND_D                     : return create_instruction<AddWithCarryAAnd8BitRegister>(Register8Bit::D);
        case opcodes::ADD_WITH_CARRY_A_AND_E                     : return create_instruction<AddWithCarryAAnd8BitRegister>(Register8Bit::E);
        case opcodes::ADD_WITH_CARRY_A_AND_H                     : return create_instruction<AddWithCarryAAnd8BitRegister>(Register8Bit::H);
        case opcodes::ADD_WITH_CARRY_A_AND_L                     : return create_instruction<AddWithCarryAAnd8BitRegister>(Register8Bit::L);
        case opcodes::ADD_WITH_CARRY_A_AND_ADDRESS_HL            : return create_instruction<AddWithCarryAAnd8BitRegister>(Register8Bit::ADDRESS_HL);
        case opcodes::ADD_WITH_CARRY_A_AND_A                     : return create_instruction<AddWithCarryAAnd8BitRegister>(Register8Bit::A);

        case opcodes::SUBTRACT_A_AND_B                           : return create_instruction<SubtractAAnd8BitRegister>(Register8Bit::B);
        case opcodes::SUBTRACT_A_AND_C                           : return create_instruction<SubtractAAnd8BitRegister>(Register8Bit::C);
        case opcodes::SUBTRACT_A_AND_D                           : return create_instruction<SubtractAAnd8BitRegister>(Register8Bit::D);
        case opcodes::SUBTRACT_A_AND_E                           : return create_instruction<SubtractAAnd8BitRegister>(Register8Bit::E);
        case opcodes::SUBTRACT_A_AND_H                           : return create_instruction<SubtractAAnd8BitRegister>(Register8Bit::H);
        case opcodes::SUBTRACT_A_AND_L                           : return create_instruction<SubtractAAnd8BitRegister>(Register8Bit::L);
        case opcodes::SUBTRACT_A_AND_ADDRESS_HL                  : return create_instruction<SubtractAAnd8BitRegister>(Register8Bit::ADDRESS_HL);
        case opcodes::SUBTRACT_A_AND_A                           : return create_instruction<SubtractAAnd8BitRegister>(Register8Bit::A);
        case opcodes::SUBTRACT_WITH_CARRY_A_AND_B                : return create_instruction<SubtractWithCarryAAnd8BitRegister>(Register8Bit::B);
        case opcodes::SUBTRACT_WITH_CARRY_A_AND_C                : return create_instruction<SubtractWithCarryAAnd8BitRegister>(Register8Bit::C);
        case opcodes::SUBTRACT_WITH_CARRY_A_AND_D                : return create_instruction<SubtractWithCarryAAnd8BitRegister>(Register8Bit::D);
        case opcodes::SUBTRACT_WITH_CARRY_A_AND_E                : return create_instruction<SubtractWithCarryAAnd8BitRegister>(Register8Bit::E);
        case opcodes::SUBTRACT_WITH_CARRY_A_AND_H                : return create_instruction<SubtractWithCarryAAnd8BitRegister>(Register8Bit::H);
        case opcodes::SUBTRACT_WITH_CARRY_A_AND_L                : return create_instruction<SubtractWithCarryAAnd8BitRegister>(Register8Bit::L);
        case opcodes::SUBTRACT_WITH_CARRY_A_AND_ADDRESS_HL       : return create_instruction<SubtractWithCarryAAnd8BitRegister>(Register8Bit::ADDRESS_HL);
        case opcodes::SUBTRACT_WITH_CARRY_A_AND_A                : return create_instruction<SubtractWithCarryAAnd8BitRegister>(Register8Bit::A);

        case opcodes::AND_A_AND_B                                : return create_instruction<AndAAnd8BitRegister>(Register8Bit::B);
        case opcodes::AND_A_AND_C                                : return create_instruction<AndAAnd8BitRegister>(Register8Bit::C);
        case opcodes::AND_A_AND_D                                : return create_instruction<AndAAnd8BitRegister>(Register8Bit::D);
        case opcodes::AND_A_AND_E                                : return create_instruction<AndAAnd8BitRegister>(Register8Bit::E);
        case opcodes::AND_A_AND_H                                : return create_instruction<AndAAnd8BitRegister>(Register8Bit::H);
        case opcodes::AND_A_AND_L                                : return create_instruction<AndAAnd8BitRegister>(Register8Bit::L);
        case opcodes::AND_A_AND_ADDRESS_HL                       : return create_instruction<AndAAnd8BitRegister>(Register8Bit::ADDRESS_HL);
        case opcodes::AND_A_AND_A                                : return create_instruction<AndAAnd8BitRegister>(Register8Bit::A);
        case opcodes::XOR_A_AND_B                                : return create_instruction<XorAAnd8BitRegister>(Register8Bit::B);
        case opcodes::XOR_A_AND_C                                : return create_instruction<XorAAnd8BitRegister>(Register8Bit::C);
        case opcodes::XOR_A_AND_D                                : return create_instruction<XorAAnd8BitRegister>(Register8Bit::D);
        case opcodes::XOR_A_AND_E                                : return create_instruction<XorAAnd8BitRegister>(Register8Bit::E);
        case opcodes::XOR_A_AND_H                                : return create_instruction<XorAAnd8BitRegister>(Register8Bit::H);
        case opcodes::XOR_A_AND_L                                : return create_instruction<XorAAnd8BitRegister>(Register8Bit::L);
        case opcodes::XOR_A_AND_ADDRESS_HL                       : return create_instruction<XorAAnd8BitRegister>(Register8Bit::ADDRESS_HL);
        case opcodes::XOR_A_AND_A                                : return create_instruction<XorAAnd8BitRegister>(Register8Bit::A);

        case opcodes::OR_A_AND_B                                 : return create_instruction<OrAAnd8BitRegister>(Register8Bit::B);
        case opcodes::OR_A_AND_C                                 : return create_instruction<OrAAnd8BitRegister>(Register8Bit::C);
        case opcodes::OR_A_AND_D                                 : return create_instruction<OrAAnd8BitRegister>(Register8Bit::D);
        case opcodes::OR_A_AND_E                                 : return create_instruction<OrAAnd8BitRegister>(Register8Bit::E);
        case opcodes::OR_A_AND_H                                 : return create_instruction<OrAAnd8BitRegister>(Register8Bit::H);
        case opcodes::OR_A_AND_L                                 : return create_instruction<OrAAnd8BitRegister>(Register8Bit::L);
        case opcodes::OR_A_AND_ADDRESS_HL                        : return create_instruction<OrAAnd8BitRegister>(Register8Bit::ADDRESS_HL);
        case opcodes::OR_A_AND_A                                 : return create_instruction<OrAAnd8BitRegister>(Register8Bit::A);
        case opcodes::COMPARE_A_AND_B                            : return create_instruction<CompareAAnd8BitRegister>(Register8Bit::B);
        case opcodes::COMPARE_A_AND_C                            : return create_instruction<CompareAAnd8BitRegister>(Register8Bit::C);
        case opcodes::COMPARE_A_AND_D                            : return create_instruction<CompareAAnd8BitRegister>(Register8Bit::D);
        case opcodes::COMPARE_A_AND_E                            : return create_instruction<CompareAAnd8BitRegister>(Register8Bit::E);
        case opcodes::COMPARE_A_AND_H                            : return create_instruction<CompareAAnd8BitRegister>(Register8Bit::H);
        case opcodes::COMPARE_A_AND_L                            : return create_instruction<CompareAAnd8BitRegister>(Register8Bit::L);
        case opcodes::COMPARE_A_AND_ADDRESS_HL                   : return create_instruction<CompareAAnd8BitRegister>(Register8Bit::ADDRESS_HL);
        case opcodes::COMPARE_A_AND_A                            : return create_instruction<CompareAAnd8BitRegister>(Register8Bit::A);

        case opcodes::RETURN_IF_NOT_ZERO                         : return create_instruction<ReturnConditional>(FlagCondition::NOT_ZERO);
        case opcodes::POP_BC                                     : return create_instruction<Pop16BitRegister>(Register16Bit::BC);
        case opcodes::JUMP_IF_NOT_ZERO                           : return create_instruction<JumpConditional>(FlagCondition::NOT_ZERO, fetch_word());
        case opcodes::JUMP                                       : return create_instruction<Jump>(fetch_word());
        case opcodes::CALL_IF_NOT_ZERO                           : return create_instruction<CallConditional>(FlagCondition::NOT_ZERO, fetch_word());
        case opcodes::PUSH_BC                                    : return create_instruction<Push16BitRegister>(Register16Bit::BC);
        case opcodes::ADD_A_AND_IMMEDIATE                        : return create_instruction<AddAAndImmediate>(fetch_byte());
        case opcodes::RESTART_0                                  : return create_instruction<Restart>(0);
        case opcodes::RETURN_IF_ZERO                             : return create_instruction<ReturnConditional>(FlagCondition::ZERO);
        case opcodes::RETURN                                     : return create_instruction<Return>();
        case opcodes::JUMP_IF_ZERO                               : return create_instruction<JumpConditional>(FlagCondition::ZERO, fetch_word());
        case opcodes::UNUSED_0                                   : return create_instruction<Unused>(0);
        case opcodes::CALL_IF_ZERO                               : return create_instruction<CallConditional>(FlagCondition::ZERO, fetch_word());
        case opcodes::CALL                                       : return create_instruction<Call>(fetch_word());
        case opcodes::ADD_WITH_CARRY_A_AND_IMMEDIATE             : return create_instruction<AddWithCarryAAndImmediate>(fetch_byte());
        case opcodes::RESTART_1                                  : return create_instruction<Restart>(1);

        case opcodes::RETURN_IF_NOT_CARRY                        : return create_instruction<ReturnConditional>(FlagCondition::NOT_CARRY);
        case opcodes::POP_DE                                     : return create_instruction<Pop16BitRegister>(Register16Bit::DE);
        case opcodes::JUMP_IF_NOT_CARRY                          : return create_instruction<JumpConditional>(FlagCondition::NOT_CARRY, fetch_word());
        case opcodes::UNUSED_1                                   : return create_instruction<Unused>(1);
        case opcodes::CALL_IF_NOT_CARRY                          : return create_instruction<CallConditional>(FlagCondition::NOT_CARRY, fetch_word());
        case opcodes::PUSH_DE                                    : return create_instruction<Push16BitRegister>(Register16Bit::DE);
        case opcodes::SUBTRACT_A_AND_IMMEDIATE                   : return create_instruction<SubtractAAndImmediate>(fetch_byte());
        case opcodes::RESTART_2                                  : return create_instruction<Restart>(2);
        case opcodes::RETURN_IF_CARRY                            : return create_instruction<ReturnConditional>(FlagCondition::CARRY);
        case opcodes::RETURN_FROM_INTERRUPT                      : return create_instruction<ReturnFromInterrupt>();
        case opcodes::JUMP_IF_CARRY                              : return create_instruction<JumpConditional>(FlagCondition::CARRY, fetch_word());
        case opcodes::UNUSED_2                                   : return create_instruction<Unused>(2);
        case opcodes::CALL_IF_CARRY                              : return create_instruction<CallConditional>(FlagCondition::CARRY, fetch_word());
        case opcodes::UNUSED_3                                   : return create_instruction<Unused>(3);
        case opcodes::SUBTRACT_WITH_CARRY_A_AND_IMMEDIATE        : return create_instruction<SubtractWithCarryAAndImmediate>(fetch_byte());
        case opcodes::RESTART_3                                  : return create_instruction<Restart>(3);

        case opcodes::LOAD_A_INTO_PORT_ADDRESS_IMMEDIATE         : return create_instruction<LoadAIntoPortAddressImmediate>(fetch_byte());
        case opcodes::POP_HL                                     : return create_instruction<Pop16BitRegister>(Register16Bit::HL);
        case opcodes::LOAD_A_INTO_PORT_ADDRESS_C                 : return create_instruction<LoadAIntoPortAddressC>();
        case opcodes::UNUSED_4                                   : return create_instruction<Unused>(4);
        case opcodes::UNUSED_5                                   : return create_instruction<Unused>(5);
        case opcodes::PUSH_HL                                    : return create_instruction<Push16BitRegister>(Register16Bit::HL);
        case opcodes::AND_A_AND_IMMEDIATE                        : return create_instruction<AndAAndImmediate>(fetch_byte());
        case opcodes::RESTART_4                                  : return create_instruction<Restart>(4);
        case opcodes::ADD_SP_AND_IMMEDIATE                       : return create_instruction<AddSPAndImmediate>(fetch_word());
        case opcodes::JUMP_TO_HL                                 : return create_instruction<JumpToHL>();
        case opcodes::LOAD_A_INTO_ADDRESS_IMMEDIATE              : return create_instruction<LoadAIntoAddressImmediate>(fetch_word());
        case opcodes::UNUSED_6                                   : return create_instruction<Unused>(6);
        case opcodes::UNUSED_7                                   : return create_instruction<Unused>(7);
        case opcodes::UNUSED_8                                   : return create_instruction<Unused>(8);
        case opcodes::XOR_A_AND_IMMEDIATE                        : return create_instruction<XorAAndImmediate>(fetch_byte());
        case opcodes::RESTART_5                                  : return create_instruction<Restart>(5);

        case opcodes::LOAD_PORT_ADDRESS_IMMEDIATE_INTO_A         : return create_instruction<LoadPortAddressImmediateIntoA>(fetch_byte());
        case opcodes::POP_AF                                     : return create_instruction<Pop16BitRegister>(Register16Bit::AF);
        case opcodes::LOAD_PORT_ADDRESS_C_INTO_A                 : return create_instruction<LoadPortAddressCIntoA>();
        case opcodes::DISABLE_INTERRUPTS                         : return create_instruction<DisableInterrupts>();
        case opcodes::UNUSED_9                                   : return create_instruction<Unused>(9);
        case opcodes::PUSH_AF                                    : return create_instruction<Push16BitRegister>(Register16Bit::AF);
        case opcodes::OR_A_AND_IMMEDIATE                         : return create_instruction<OrAAndImmediate>(fetch_byte());
        case opcodes::RESTART_6                                  : return create_instruction<Restart>(6);
        case opcodes::LOAD_SP_SHIFTED_BY_IMMEDIATE_INTO_HL       : return create_instruction<LoadSPShiftedByImmediateIntoHL>(fetch_byte());
        case opcodes::LOAD_HL_INTO_SP                            : return create_instruction<LoadHLIntoSP>();
        case opcodes::LOAD_ADDRESS_IMMEDIATE_INTO_A              : return create_instruction<LoadAddressImmediateIntoA>(fetch_word());
        case opcodes::ENABLE_INTERRUPTS                          : return create_instruction<EnableInterrupts>();
        case opcodes::UNUSED_10                                  : return create_instruction<Unused>(10);
        case opcodes::UNUSED_11                                  : return create_instruction<Unused>(11);
        case opcodes::COMPARE_A_AND_IMMEDIATE                    : return create_instruction<CompareAAndImmediate>(fetch_byte());
        case opcodes::RESTART_7                                  : return create_instruction<Restart>(7);

            //

        case opcodes::ROTATE_LEFT_CONTENTS_OF_B                  : return create_instruction<RotateLeftContentsOf8BitRegister>(Register8Bit::B);
        case opcodes::ROTATE_LEFT_CONTENTS_OF_C                  : return create_instruction<RotateLeftContentsOf8BitRegister>(Register8Bit::C);
        case opcodes::ROTATE_LEFT_CONTENTS_OF_D                  : return create_instruction<RotateLeftContentsOf8BitRegister>(Register8Bit::D);
        case opcodes::ROTATE_LEFT_CONTENTS_OF_E                  : return create_instruction<RotateLeftContentsOf8BitRegister>(Register8Bit::E);
        case opcodes::ROTATE_LEFT_CONTENTS_OF_H                  : return create_instruction<RotateLeftContentsOf8BitRegister>(Register8Bit::H);
        case opcodes::ROTATE_LEFT_CONTENTS_OF_L                  : return create_instruction<RotateLeftContentsOf8BitRegister>(Register8Bit::L);
        case opcodes::ROTATE_LEFT_CONTENTS_OF_ADDRESS_HL         : return create_instruction<RotateLeftContentsOf8BitRegister>(Register8Bit::ADDRESS_HL);
        case opcodes::ROTATE_LEFT_CONTENTS_OF_A                  : return create_instruction<RotateLeftContentsOf8BitRegister>(Register8Bit::A);
        case opcodes::ROTATE_RIGHT_CONTENTS_OF_B                 : return create_instruction<RotateRightContentsOf8BitRegister>(Register8Bit::B);
        case opcodes::ROTATE_RIGHT_CONTENTS_OF_C                 : return create_instruction<RotateRightContentsOf8BitRegister>(Register8Bit::C);
        case opcodes::ROTATE_RIGHT_CONTENTS_OF_D                 : return create_instruction<RotateRightContentsOf8BitRegister>(Register8Bit::D);
        case opcodes::ROTATE_RIGHT_CONTENTS_OF_E                 : return create_instruction<RotateRightContentsOf8BitRegister>(Register8Bit::E);
        case opcodes::ROTATE_RIGHT_CONTENTS_OF_H                 : return create_instruction<RotateRightContentsOf8BitRegister>(Register8Bit::H);
        case opcodes::ROTATE_RIGHT_CONTENTS_OF_L                 : return create_instruction<RotateRightContentsOf8BitRegister>(Register8Bit::L);
        case opcodes::ROTATE_RIGHT_CONTENTS_OF_ADDRESS_HL        : return create_instruction<RotateRightContentsOf8BitRegister>(Register8Bit::ADDRESS_HL);
        case opcodes::ROTATE_RIGHT_CONTENTS_OF_A                 : return create_instruction<RotateRightContentsOf8BitRegister>(Register8Bit::A);

        case opcodes::ROTATE_LEFT_B                              : return create_instruction<RotateLeft8BitRegister>(Register8Bit::B);
        case opcodes::ROTATE_LEFT_C                              : return create_instruction<RotateLeft8BitRegister>(Register8Bit::C);
        case opcodes::ROTATE_LEFT_D                              : return create_instruction<RotateLeft8BitRegister>(Register8Bit::D);
        case opcodes::ROTATE_LEFT_E                              : return create_instruction<RotateLeft8BitRegister>(Register8Bit::E);
        case opcodes::ROTATE_LEFT_H                              : return create_instruction<RotateLeft8BitRegister>(Register8Bit::H);
        case opcodes::ROTATE_LEFT_L                              : return create_instruction<RotateLeft8BitRegister>(Register8Bit::L);
        case opcodes::ROTATE_LEFT_ADDRESS_HL                     : return create_instruction<RotateLeft8BitRegister>(Register8Bit::ADDRESS_HL);
        case opcodes::ROTATE_LEFT_A                              : return create_instruction<RotateLeft8BitRegister>(Register8Bit::A);
        case opcodes::ROTATE_RIGHT_B                             : return create_instruction<RotateRight8BitRegister>(Register8Bit::B);
        case opcodes::ROTATE_RIGHT_C                             : return create_instruction<RotateRight8BitRegister>(Register8Bit::C);
        case opcodes::ROTATE_RIGHT_D                             : return create_instruction<RotateRight8BitRegister>(Register8Bit::D);
        case opcodes::ROTATE_RIGHT_E                             : return create_instruction<RotateRight8BitRegister>(Register8Bit::E);
        case opcodes::ROTATE_RIGHT_H                             : return create_instruction<RotateRight8BitRegister>(Register8Bit::H);
        case opcodes::ROTATE_RIGHT_L                             : return create_instruction<RotateRight8BitRegister>(Register8Bit::L);
        case opcodes::ROTATE_RIGHT_ADDRESS_HL                    : return create_instruction<RotateRight8BitRegister>(Register8Bit::ADDRESS_HL);
        case opcodes::ROTATE_RIGHT_A                             : return create_instruction<RotateRight8BitRegister>(Register8Bit::A);

        case opcodes::SHIFT_LEFT_ARITHMETICAL_B                  : return create_instruction<ShiftLeftArithmetical8BitRegister>(Register8Bit::B);
        case opcodes::SHIFT_LEFT_ARITHMETICAL_C                  : return create_instruction<ShiftLeftArithmetical8BitRegister>(Register8Bit::C);
        case opcodes::SHIFT_LEFT_ARITHMETICAL_D                  : return create_instruction<ShiftLeftArithmetical8BitRegister>(Register8Bit::D);
        case opcodes::SHIFT_LEFT_ARITHMETICAL_E                  : return create_instruction<ShiftLeftArithmetical8BitRegister>(Register8Bit::E);
        case opcodes::SHIFT_LEFT_ARITHMETICAL_H                  : return create_instruction<ShiftLeftArithmetical8BitRegister>(Register8Bit::H);
        case opcodes::SHIFT_LEFT_ARITHMETICAL_L                  : return create_instruction<ShiftLeftArithmetical8BitRegister>(Register8Bit::L);
        case opcodes::SHIFT_LEFT_ARITHMETICAL_ADDRESS_HL         : return create_instruction<ShiftLeftArithmetical8BitRegister>(Register8Bit::ADDRESS_HL);
        case opcodes::SHIFT_LEFT_ARITHMETICAL_A                  : return create_instruction<ShiftLeftArithmetical8BitRegister>(Register8Bit::A);
        case opcodes::SHIFT_RIGHT_ARITHMETICAL_B                 : return create_instruction<ShiftRightArithmetical8BitRegister>(Register8Bit::B);
        case opcodes::SHIFT_RIGHT_ARITHMETICAL_C                 : return create_instruction<ShiftRightArithmetical8BitRegister>(Register8Bit::C);
        case opcodes::SHIFT_RIGHT_ARITHMETICAL_D                 : return create_instruction<ShiftRightArithmetical8BitRegister>(Register8Bit::D);
        case opcodes::SHIFT_RIGHT_ARITHMETICAL_E                 : return create_instruction<ShiftRightArithmetical8BitRegister>(Register8Bit::E);
        case opcodes::SHIFT_RIGHT_ARITHMETICAL_H                 : return create_instruction<ShiftRightArithmetical8BitRegister>(Register8Bit::H);
        case opcodes::SHIFT_RIGHT_ARITHMETICAL_L                 : return create_instruction<ShiftRightArithmetical8BitRegister>(Register8Bit::L);
        case opcodes::SHIFT_RIGHT_ARITHMETICAL_ADDRESS_HL        : return create_instruction<ShiftRightArithmetical8BitRegister>(Register8Bit::ADDRESS_HL);
        case opcodes::SHIFT_RIGHT_ARITHMETICAL_A                 : return create_instruction<ShiftRightArithmetical8BitRegister>(Register8Bit::A);

        case opcodes::SWAP_B                                     : return create_instruction<Swap8BitRegister>(Register8Bit::B);
        case opcodes::SWAP_C                                     : return create_instruction<Swap8BitRegister>(Register8Bit::C);
        case opcodes::SWAP_D                                     : return create_instruction<Swap8BitRegister>(Register8Bit::D);
        case opcodes::SWAP_E                                     : return create_instruction<Swap8BitRegister>(Register8Bit::E);
        case opcodes::SWAP_H                                     : return create_instruction<Swap8BitRegister>(Register8Bit::H);
        case opcodes::SWAP_L                                     : return create_instruction<Swap8BitRegister>(Register8Bit::L);
        case opcodes::SWAP_ADDRESS_HL                            : return create_instruction<Swap8BitRegister>(Register8Bit::ADDRESS_HL);
        case opcodes::SWAP_A                                     : return create_instruction<Swap8BitRegister>(Register8Bit::A);
        case opcodes::SHIFT_RIGHT_LOGICAL_B                      : return create_instruction<ShiftRightLogical8BitRegister>(Register8Bit::B);
        case opcodes::SHIFT_RIGHT_LOGICAL_C                      : return create_instruction<ShiftRightLogical8BitRegister>(Register8Bit::C);
        case opcodes::SHIFT_RIGHT_LOGICAL_D                      : return create_instruction<ShiftRightLogical8BitRegister>(Register8Bit::D);
        case opcodes::SHIFT_RIGHT_LOGICAL_E                      : return create_instruction<ShiftRightLogical8BitRegister>(Register8Bit::E);
        case opcodes::SHIFT_RIGHT_LOGICAL_H                      : return create_instruction<ShiftRightLogical8BitRegister>(Register8Bit::H);
        case opcodes::SHIFT_RIGHT_LOGICAL_L                      : return create_instruction<ShiftRightLogical8BitRegister>(Register8Bit::L);
        case opcodes::SHIFT_RIGHT_LOGICAL_ADDRESS_HL             : return create_instruction<ShiftRightLogical8BitRegister>(Register8Bit::ADDRESS_HL);
        case opcodes::SHIFT_RIGHT_LOGICAL_A                      : return create_instruction<ShiftRightLogical8BitRegister>(Register8Bit::A);

        case opcodes::BIT_0_OF_B_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(0, Register8Bit::B);
        case opcodes::BIT_0_OF_C_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(0, Register8Bit::C);
        case opcodes::BIT_0_OF_D_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(0, Register8Bit::D);
        case opcodes::BIT_0_OF_E_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(0, Register8Bit::E);
        case opcodes::BIT_0_OF_H_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(0, Register8Bit::H);
        case opcodes::BIT_0_OF_L_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(0, Register8Bit::L);
        case opcodes::BIT_0_OF_ADDRESS_HL_COMPLEMENT_INTO_ZERO   : return create_instruction<BitOf8BitRegisterComplementIntoZero>(0, Register8Bit::ADDRESS_HL);
        case opcodes::BIT_0_OF_A_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(0, Register8Bit::A);
        case opcodes::BIT_1_OF_B_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(1, Register8Bit::B);
        case opcodes::BIT_1_OF_C_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(1, Register8Bit::C);
        case opcodes::BIT_1_OF_D_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(1, Register8Bit::D);
        case opcodes::BIT_1_OF_E_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(1, Register8Bit::E);
        case opcodes::BIT_1_OF_H_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(1, Register8Bit::H);
        case opcodes::BIT_1_OF_L_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(1, Register8Bit::L);
        case opcodes::BIT_1_OF_ADDRESS_HL_COMPLEMENT_INTO_ZERO   : return create_instruction<BitOf8BitRegisterComplementIntoZero>(1, Register8Bit::ADDRESS_HL);
        case opcodes::BIT_1_OF_A_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(1, Register8Bit::A);

        case opcodes::BIT_2_OF_B_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(2, Register8Bit::B);
        case opcodes::BIT_2_OF_C_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(2, Register8Bit::C);
        case opcodes::BIT_2_OF_D_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(2, Register8Bit::D);
        case opcodes::BIT_2_OF_E_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(2, Register8Bit::E);
        case opcodes::BIT_2_OF_H_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(2, Register8Bit::H);
        case opcodes::BIT_2_OF_L_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(2, Register8Bit::L);
        case opcodes::BIT_2_OF_ADDRESS_HL_COMPLEMENT_INTO_ZERO   : return create_instruction<BitOf8BitRegisterComplementIntoZero>(2, Register8Bit::ADDRESS_HL);
        case opcodes::BIT_2_OF_A_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(2, Register8Bit::A);
        case opcodes::BIT_3_OF_B_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(3, Register8Bit::B);
        case opcodes::BIT_3_OF_C_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(3, Register8Bit::C);
        case opcodes::BIT_3_OF_D_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(3, Register8Bit::D);
        case opcodes::BIT_3_OF_E_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(3, Register8Bit::E);
        case opcodes::BIT_3_OF_H_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(3, Register8Bit::H);
        case opcodes::BIT_3_OF_L_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(3, Register8Bit::L);
        case opcodes::BIT_3_OF_ADDRESS_HL_COMPLEMENT_INTO_ZERO   : return create_instruction<BitOf8BitRegisterComplementIntoZero>(3, Register8Bit::ADDRESS_HL);
        case opcodes::BIT_3_OF_A_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(3, Register8Bit::A);

        case opcodes::BIT_4_OF_B_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(4, Register8Bit::B);
        case opcodes::BIT_4_OF_C_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(4, Register8Bit::C);
        case opcodes::BIT_4_OF_D_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(4, Register8Bit::D);
        case opcodes::BIT_4_OF_E_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(4, Register8Bit::E);
        case opcodes::BIT_4_OF_H_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(4, Register8Bit::H);
        case opcodes::BIT_4_OF_L_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(4, Register8Bit::L);
        case opcodes::BIT_4_OF_ADDRESS_HL_COMPLEMENT_INTO_ZERO   : return create_instruction<BitOf8BitRegisterComplementIntoZero>(4, Register8Bit::ADDRESS_HL);
        case opcodes::BIT_4_OF_A_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(4, Register8Bit::A);
        case opcodes::BIT_5_OF_B_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(5, Register8Bit::B);
        case opcodes::BIT_5_OF_C_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(5, Register8Bit::C);
        case opcodes::BIT_5_OF_D_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(5, Register8Bit::D);
        case opcodes::BIT_5_OF_E_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(5, Register8Bit::E);
        case opcodes::BIT_5_OF_H_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(5, Register8Bit::H);
        case opcodes::BIT_5_OF_L_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(5, Register8Bit::L);
        case opcodes::BIT_5_OF_ADDRESS_HL_COMPLEMENT_INTO_ZERO   : return create_instruction<BitOf8BitRegisterComplementIntoZero>(5, Register8Bit::ADDRESS_HL);
        case opcodes::BIT_5_OF_A_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(5, Register8Bit::A);

        case opcodes::BIT_6_OF_B_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(6, Register8Bit::B);
        case opcodes::BIT_6_OF_C_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(6, Register8Bit::C);
        case opcodes::BIT_6_OF_D_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(6, Register8Bit::D);
        case opcodes::BIT_6_OF_E_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(6, Register8Bit::E);
        case opcodes::BIT_6_OF_H_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(6, Register8Bit::H);
        case opcodes::BIT_6_OF_L_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(6, Register8Bit::L);
        case opcodes::BIT_6_OF_ADDRESS_HL_COMPLEMENT_INTO_ZERO   : return create_instruction<BitOf8BitRegisterComplementIntoZero>(6, Register8Bit::ADDRESS_HL);
        case opcodes::BIT_6_OF_A_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(6, Register8Bit::A);
        case opcodes::BIT_7_OF_B_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(7, Register8Bit::B);
        case opcodes::BIT_7_OF_C_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(7, Register8Bit::C);
        case opcodes::BIT_7_OF_D_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(7, Register8Bit::D);
        case opcodes::BIT_7_OF_E_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(7, Register8Bit::E);
        case opcodes::BIT_7_OF_H_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(7, Register8Bit::H);
        case opcodes::BIT_7_OF_L_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(7, Register8Bit::L);
        case opcodes::BIT_7_OF_ADDRESS_HL_COMPLEMENT_INTO_ZERO   : return create_instruction<BitOf8BitRegisterComplementIntoZero>(7, Register8Bit::ADDRESS_HL);
        case opcodes::BIT_7_OF_A_COMPLEMENT_INTO_ZERO            : return create_instruction<BitOf8BitRegisterComplementIntoZero>(7, Register8Bit::A);

        case opcodes::RESET_BIT_0_OF_B                           : return create_instruction<ResetBitOf8BitRegister>(0, Register8Bit::B);
        case opcodes::RESET_BIT_0_OF_C                           : return create_instruction<ResetBitOf8BitRegister>(0, Register8Bit::C);
        case opcodes::RESET_BIT_0_OF_D                           : return create_instruction<ResetBitOf8BitRegister>(0, Register8Bit::D);
        case opcodes::RESET_BIT_0_OF_E                           : return create_instruction<ResetBitOf8BitRegister>(0, Register8Bit::E);
        case opcodes::RESET_BIT_0_OF_H                           : return create_instruction<ResetBitOf8BitRegister>(0, Register8Bit::H);
        case opcodes::RESET_BIT_0_OF_L                           : return create_instruction<ResetBitOf8BitRegister>(0, Register8Bit::L);
        case opcodes::RESET_BIT_0_OF_ADDRESS_HL                  : return create_instruction<ResetBitOf8BitRegister>(0, Register8Bit::ADDRESS_HL);
        case opcodes::RESET_BIT_0_OF_A                           : return create_instruction<ResetBitOf8BitRegister>(0, Register8Bit::A);
        case opcodes::RESET_BIT_1_OF_B                           : return create_instruction<ResetBitOf8BitRegister>(1, Register8Bit::B);
        case opcodes::RESET_BIT_1_OF_C                           : return create_instruction<ResetBitOf8BitRegister>(1, Register8Bit::C);
        case opcodes::RESET_BIT_1_OF_D                           : return create_instruction<ResetBitOf8BitRegister>(1, Register8Bit::D);
        case opcodes::RESET_BIT_1_OF_E                           : return create_instruction<ResetBitOf8BitRegister>(1, Register8Bit::E);
        case opcodes::RESET_BIT_1_OF_H                           : return create_instruction<ResetBitOf8BitRegister>(1, Register8Bit::H);
        case opcodes::RESET_BIT_1_OF_L                           : return create_instruction<ResetBitOf8BitRegister>(1, Register8Bit::L);
        case opcodes::RESET_BIT_1_OF_ADDRESS_HL                  : return create_instruction<ResetBitOf8BitRegister>(1, Register8Bit::ADDRESS_HL);
        case opcodes::RESET_BIT_1_OF_A                           : return create_instruction<ResetBitOf8BitRegister>(1, Register8Bit::A);

        case opcodes::RESET_BIT_2_OF_B                           : return create_instruction<ResetBitOf8BitRegister>(2, Register8Bit::B);
        case opcodes::RESET_BIT_2_OF_C                           : return create_instruction<ResetBitOf8BitRegister>(2, Register8Bit::C);
        case opcodes::RESET_BIT_2_OF_D                           : return create_instruction<ResetBitOf8BitRegister>(2, Register8Bit::D);
        case opcodes::RESET_BIT_2_OF_E                           : return create_instruction<ResetBitOf8BitRegister>(2, Register8Bit::E);
        case opcodes::RESET_BIT_2_OF_H                           : return create_instruction<ResetBitOf8BitRegister>(2, Register8Bit::H);
        case opcodes::RESET_BIT_2_OF_L                           : return create_instruction<ResetBitOf8BitRegister>(2, Register8Bit::L);
        case opcodes::RESET_BIT_2_OF_ADDRESS_HL                  : return create_instruction<ResetBitOf8BitRegister>(2, Register8Bit::ADDRESS_HL);
        case opcodes::RESET_BIT_2_OF_A                           : return create_instruction<ResetBitOf8BitRegister>(2, Register8Bit::A);
        case opcodes::RESET_BIT_3_OF_B                           : return create_instruction<ResetBitOf8BitRegister>(3, Register8Bit::B);
        case opcodes::RESET_BIT_3_OF_C                           : return create_instruction<ResetBitOf8BitRegister>(3, Register8Bit::C);
        case opcodes::RESET_BIT_3_OF_D                           : return create_instruction<ResetBitOf8BitRegister>(3, Register8Bit::D);
        case opcodes::RESET_BIT_3_OF_E                           : return create_instruction<ResetBitOf8BitRegister>(3, Register8Bit::E);
        case opcodes::RESET_BIT_3_OF_H                           : return create_instruction<ResetBitOf8BitRegister>(3, Register8Bit::H);
        case opcodes::RESET_BIT_3_OF_L                           : return create_instruction<ResetBitOf8BitRegister>(3, Register8Bit::L);
        case opcodes::RESET_BIT_3_OF_ADDRESS_HL                  : return create_instruction<ResetBitOf8BitRegister>(3, Register8Bit::ADDRESS_HL);
        case opcodes::RESET_BIT_3_OF_A                           : return create_instruction<ResetBitOf8BitRegister>(3, Register8Bit::A);

        case opcodes::RESET_BIT_4_OF_B                           : return create_instruction<ResetBitOf8BitRegister>(4, Register8Bit::B);
        case opcodes::RESET_BIT_4_OF_C                           : return create_instruction<ResetBitOf8BitRegister>(4, Register8Bit::C);
        case opcodes::RESET_BIT_4_OF_D                           : return create_instruction<ResetBitOf8BitRegister>(4, Register8Bit::D);
        case opcodes::RESET_BIT_4_OF_E                           : return create_instruction<ResetBitOf8BitRegister>(4, Register8Bit::E);
        case opcodes::RESET_BIT_4_OF_H                           : return create_instruction<ResetBitOf8BitRegister>(4, Register8Bit::H);
        case opcodes::RESET_BIT_4_OF_L                           : return create_instruction<ResetBitOf8BitRegister>(4, Register8Bit::L);
        case opcodes::RESET_BIT_4_OF_ADDRESS_HL                  : return create_instruction<ResetBitOf8BitRegister>(4, Register8Bit::ADDRESS_HL);
        case opcodes::RESET_BIT_4_OF_A                           : return create_instruction<ResetBitOf8BitRegister>(4, Register8Bit::A);
        case opcodes::RESET_BIT_5_OF_B                           : return create_instruction<ResetBitOf8BitRegister>(5, Register8Bit::B);
        case opcodes::RESET_BIT_5_OF_C                           : return create_instruction<ResetBitOf8BitRegister>(5, Register8Bit::C);
        case opcodes::RESET_BIT_5_OF_D                           : return create_instruction<ResetBitOf8BitRegister>(5, Register8Bit::D);
        case opcodes::RESET_BIT_5_OF_E                           : return create_instruction<ResetBitOf8BitRegister>(5, Register8Bit::E);
        case opcodes::RESET_BIT_5_OF_H                           : return create_instruction<ResetBitOf8BitRegister>(5, Register8Bit::H);
        case opcodes::RESET_BIT_5_OF_L                           : return create_instruction<ResetBitOf8BitRegister>(5, Register8Bit::L);
        case opcodes::RESET_BIT_5_OF_ADDRESS_HL                  : return create_instruction<ResetBitOf8BitRegister>(5, Register8Bit::ADDRESS_HL);
        case opcodes::RESET_BIT_5_OF_A                           : return create_instruction<ResetBitOf8BitRegister>(5, Register8Bit::A);

        case opcodes::RESET_BIT_6_OF_B                           : return create_instruction<ResetBitOf8BitRegister>(6, Register8Bit::B);
        case opcodes::RESET_BIT_6_OF_C                           : return create_instruction<ResetBitOf8BitRegister>(6, Register8Bit::C);
        case opcodes::RESET_BIT_6_OF_D                           : return create_instruction<ResetBitOf8BitRegister>(6, Register8Bit::D);
        case opcodes::RESET_BIT_6_OF_E                           : return create_instruction<ResetBitOf8BitRegister>(6, Register8Bit::E);
        case opcodes::RESET_BIT_6_OF_H                           : return create_instruction<ResetBitOf8BitRegister>(6, Register8Bit::H);
        case opcodes::RESET_BIT_6_OF_L                           : return create_instruction<ResetBitOf8BitRegister>(6, Register8Bit::L);
        case opcodes::RESET_BIT_6_OF_ADDRESS_HL                  : return create_instruction<ResetBitOf8BitRegister>(6, Register8Bit::ADDRESS_HL);
        case opcodes::RESET_BIT_6_OF_A                           : return create_instruction<ResetBitOf8BitRegister>(6, Register8Bit::A);
        case opcodes::RESET_BIT_7_OF_B                           : return create_instruction<ResetBitOf8BitRegister>(7, Register8Bit::B);
        case opcodes::RESET_BIT_7_OF_C                           : return create_instruction<ResetBitOf8BitRegister>(7, Register8Bit::C);
        case opcodes::RESET_BIT_7_OF_D                           : return create_instruction<ResetBitOf8BitRegister>(7, Register8Bit::D);
        case opcodes::RESET_BIT_7_OF_E                           : return create_instruction<ResetBitOf8BitRegister>(7, Register8Bit::E);
        case opcodes::RESET_BIT_7_OF_H                           : return create_instruction<ResetBitOf8BitRegister>(7, Register8Bit::H);
        case opcodes::RESET_BIT_7_OF_L                           : return create_instruction<ResetBitOf8BitRegister>(7, Register8Bit::L);
        case opcodes::RESET_BIT_7_OF_ADDRESS_HL                  : return create_instruction<ResetBitOf8BitRegister>(7, Register8Bit::ADDRESS_HL);
        case opcodes::RESET_BIT_7_OF_A                           : return create_instruction<ResetBitOf8BitRegister>(7, Register8Bit::A);

        case opcodes::SET_BIT_0_OF_B                             : return create_instruction<SetBitOf8BitRegister>(0, Register8Bit::B);
        case opcodes::SET_BIT_0_OF_C                             : return create_instruction<SetBitOf8BitRegister>(0, Register8Bit::C);
        case opcodes::SET_BIT_0_OF_D                             : return create_instruction<SetBitOf8BitRegister>(0, Register8Bit::D);
        case opcodes::SET_BIT_0_OF_E                             : return create_instruction<SetBitOf8BitRegister>(0, Register8Bit::E);
        case opcodes::SET_BIT_0_OF_H                             : return create_instruction<SetBitOf8BitRegister>(0, Register8Bit::H);
        case opcodes::SET_BIT_0_OF_L                             : return create_instruction<SetBitOf8BitRegister>(0, Register8Bit::L);
        case opcodes::SET_BIT_0_OF_ADDRESS_HL                    : return create_instruction<SetBitOf8BitRegister>(0, Register8Bit::ADDRESS_HL);
        case opcodes::SET_BIT_0_OF_A                             : return create_instruction<SetBitOf8BitRegister>(0, Register8Bit::A);
        case opcodes::SET_BIT_1_OF_B                             : return create_instruction<SetBitOf8BitRegister>(1, Register8Bit::B);
        case opcodes::SET_BIT_1_OF_C                             : return create_instruction<SetBitOf8BitRegister>(1, Register8Bit::C);
        case opcodes::SET_BIT_1_OF_D                             : return create_instruction<SetBitOf8BitRegister>(1, Register8Bit::D);
        case opcodes::SET_BIT_1_OF_E                             : return create_instruction<SetBitOf8BitRegister>(1, Register8Bit::E);
        case opcodes::SET_BIT_1_OF_H                             : return create_instruction<SetBitOf8BitRegister>(1, Register8Bit::H);
        case opcodes::SET_BIT_1_OF_L                             : return create_instruction<SetBitOf8BitRegister>(1, Register8Bit::L);
        case opcodes::SET_BIT_1_OF_ADDRESS_HL                    : return create_instruction<SetBitOf8BitRegister>(1, Register8Bit::ADDRESS_HL);
        case opcodes::SET_BIT_1_OF_A                             : return create_instruction<SetBitOf8BitRegister>(1, Register8Bit::A);

        case opcodes::SET_BIT_2_OF_B                             : return create_instruction<SetBitOf8BitRegister>(2, Register8Bit::B);
        case opcodes::SET_BIT_2_OF_C                             : return create_instruction<SetBitOf8BitRegister>(2, Register8Bit::C);
        case opcodes::SET_BIT_2_OF_D                             : return create_instruction<SetBitOf8BitRegister>(2, Register8Bit::D);
        case opcodes::SET_BIT_2_OF_E                             : return create_instruction<SetBitOf8BitRegister>(2, Register8Bit::E);
        case opcodes::SET_BIT_2_OF_H                             : return create_instruction<SetBitOf8BitRegister>(2, Register8Bit::H);
        case opcodes::SET_BIT_2_OF_L                             : return create_instruction<SetBitOf8BitRegister>(2, Register8Bit::L);
        case opcodes::SET_BIT_2_OF_ADDRESS_HL                    : return create_instruction<SetBitOf8BitRegister>(2, Register8Bit::ADDRESS_HL);
        case opcodes::SET_BIT_2_OF_A                             : return create_instruction<SetBitOf8BitRegister>(2, Register8Bit::A);
        case opcodes::SET_BIT_3_OF_B                             : return create_instruction<SetBitOf8BitRegister>(3, Register8Bit::B);
        case opcodes::SET_BIT_3_OF_C                             : return create_instruction<SetBitOf8BitRegister>(3, Register8Bit::C);
        case opcodes::SET_BIT_3_OF_D                             : return create_instruction<SetBitOf8BitRegister>(3, Register8Bit::D);
        case opcodes::SET_BIT_3_OF_E                             : return create_instruction<SetBitOf8BitRegister>(3, Register8Bit::E);
        case opcodes::SET_BIT_3_OF_H                             : return create_instruction<SetBitOf8BitRegister>(3, Register8Bit::H);
        case opcodes::SET_BIT_3_OF_L                             : return create_instruction<SetBitOf8BitRegister>(3, Register8Bit::L);
        case opcodes::SET_BIT_3_OF_ADDRESS_HL                    : return create_instruction<SetBitOf8BitRegister>(3, Register8Bit::ADDRESS_HL);
        case opcodes::SET_BIT_3_OF_A                             : return create_instruction<SetBitOf8BitRegister>(3, Register8Bit::A);

        case opcodes::SET_BIT_4_OF_B                             : return create_instruction<SetBitOf8BitRegister>(4, Register8Bit::B);
        case opcodes::SET_BIT_4_OF_C                             : return create_instruction<SetBitOf8BitRegister>(4, Register8Bit::C);
        case opcodes::SET_BIT_4_OF_D                             : return create_instruction<SetBitOf8BitRegister>(4, Register8Bit::D);
        case opcodes::SET_BIT_4_OF_E                             : return create_instruction<SetBitOf8BitRegister>(4, Register8Bit::E);
        case opcodes::SET_BIT_4_OF_H                             : return create_instruction<SetBitOf8BitRegister>(4, Register8Bit::H);
        case opcodes::SET_BIT_4_OF_L                             : return create_instruction<SetBitOf8BitRegister>(4, Register8Bit::L);
        case opcodes::SET_BIT_4_OF_ADDRESS_HL                    : return create_instruction<SetBitOf8BitRegister>(4, Register8Bit::ADDRESS_HL);
        case opcodes::SET_BIT_4_OF_A                             : return create_instruction<SetBitOf8BitRegister>(4, Register8Bit::A);
        case opcodes::SET_BIT_5_OF_B                             : return create_instruction<SetBitOf8BitRegister>(5, Register8Bit::B);
        case opcodes::SET_BIT_5_OF_C                             : return create_instruction<SetBitOf8BitRegister>(5, Register8Bit::C);
        case opcodes::SET_BIT_5_OF_D                             : return create_instruction<SetBitOf8BitRegister>(5, Register8Bit::D);
        case opcodes::SET_BIT_5_OF_E                             : return create_instruction<SetBitOf8BitRegister>(5, Register8Bit::E);
        case opcodes::SET_BIT_5_OF_H                             : return create_instruction<SetBitOf8BitRegister>(5, Register8Bit::H);
        case opcodes::SET_BIT_5_OF_L                             : return create_instruction<SetBitOf8BitRegister>(5, Register8Bit::L);
        case opcodes::SET_BIT_5_OF_ADDRESS_HL                    : return create_instruction<SetBitOf8BitRegister>(5, Register8Bit::ADDRESS_HL);
        case opcodes::SET_BIT_5_OF_A                             : return create_instruction<SetBitOf8BitRegister>(5, Register8Bit::A);

        case opcodes::SET_BIT_6_OF_B                             : return create_instruction<SetBitOf8BitRegister>(6, Register8Bit::B);
        case opcodes::SET_BIT_6_OF_C                             : return create_instruction<SetBitOf8BitRegister>(6, Register8Bit::C);
        case opcodes::SET_BIT_6_OF_D                             : return create_instruction<SetBitOf8BitRegister>(6, Register8Bit::D);
        case opcodes::SET_BIT_6_OF_E                             : return create_instruction<SetBitOf8BitRegister>(6, Register8Bit::E);
        case opcodes::SET_BIT_6_OF_H                             : return create_instruction<SetBitOf8BitRegister>(6, Register8Bit::H);
        case opcodes::SET_BIT_6_OF_L                             : return create_instruction<SetBitOf8BitRegister>(6, Register8Bit::L);
        case opcodes::SET_BIT_6_OF_ADDRESS_HL                    : return create_instruction<SetBitOf8BitRegister>(6, Register8Bit::ADDRESS_HL);
        case opcodes::SET_BIT_6_OF_A                             : return create_instruction<SetBitOf8BitRegister>(6, Register8Bit::A);
        case opcodes::SET_BIT_7_OF_B                             : return create_instruction<SetBitOf8BitRegister>(7, Register8Bit::B);
        case opcodes::SET_BIT_7_OF_C                             : return create_instruction<SetBitOf8BitRegister>(7, Register8Bit::C);
        case opcodes::SET_BIT_7_OF_D                             : return create_instruction<SetBitOf8BitRegister>(7, Register8Bit::D);
        case opcodes::SET_BIT_7_OF_E                             : return create_instruction<SetBitOf8BitRegister>(7, Register8Bit::E);
        case opcodes::SET_BIT_7_OF_H                             : return create_instruction<SetBitOf8BitRegister>(7, Register8Bit::H);
        case opcodes::SET_BIT_7_OF_L                             : return create_instruction<SetBitOf8BitRegister>(7, Register8Bit::L);
        case opcodes::SET_BIT_7_OF_ADDRESS_HL                    : return create_instruction<SetBitOf8BitRegister>(7, Register8Bit::ADDRESS_HL);
        case opcodes::SET_BIT_7_OF_A                             : return create_instruction<SetBitOf8BitRegister>(7, Register8Bit::A);

        default: return create_instruction<Unknown>();
    }
}