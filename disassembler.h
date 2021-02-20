#ifndef GAMEBOY_DEBUG_DISASSEMBLER_H
#define GAMEBOY_DEBUG_DISASSEMBLER_H

#include <iomanip>
#include <stdexcept>

#include "instructions/instructions.h"

class Disassembler
{
public:
    Disassembler(byte const * const startOfByteCode, const word sizeOfByteCode)
            :_startOfByteCode{startOfByteCode}, _sizeOfByteCode{sizeOfByteCode}
    {}

    bool is_out_of_range() const
    {
        return (_programCounter >= _sizeOfByteCode);
    }

    std::string disassemble()
    {
        std::string displayedText;
        Opcode opcode = 0;

        try // to get opcode
        {
            displayedText += "0x" + to_string_hex(_programCounter);

            opcode = fetch_opcode();
            displayedText += " : " "[0x" + to_string_hex(opcode, 2) + "] ";

            displayedText += decode(opcode)->str();
        }
        catch(const std::out_of_range &e)
        {
            displayedText = " - EOF - ";
        }

        return displayedText;
    }

    InstructionPtr decode(Opcode opcode)
    {
        switch (opcode)
        {
            case opcodes::NOP                                        : return std::make_unique<Nop>();
            case opcodes::LOAD_IMMEDIATE_INTO_BC                     : return std::make_unique<LoadImmediateIntoBC>(fetch_word());
            case opcodes::LOAD_A_INTO_ADDRESS_BC                     : return std::make_unique<LoadAIntoAddressBC>();
            case opcodes::INCREMENT_BC                               : return std::make_unique<IncrementBC>();
            case opcodes::INCREMENT_B                                : return std::make_unique<IncrementB>();
            case opcodes::DECREMENT_B                                : return std::make_unique<DecrementB>();
            case opcodes::LOAD_IMMEDIATE_INTO_B                      : return std::make_unique<LoadImmediateIntoB>(fetch_byte());
            case opcodes::ROTATE_LEFT_CONTENTS_OF_A_AND_CLEAR_ZERO   : return std::make_unique<RotateLeftContentsOfAAndClearZero>();
            case opcodes::LOAD_SP_INTO_ADDRESS_IMMEDIATE             : return std::make_unique<LoadSPIntoAddressImmediate>(fetch_word());
            case opcodes::ADD_HL_AND_BC                              : return std::make_unique<AddHLAndBC>();
            case opcodes::LOAD_ADDRESS_BC_INTO_A                     : return std::make_unique<LoadAddressBCIntoA>();
            case opcodes::DECREMENT_BC                               : return std::make_unique<DecrementBC>();
            case opcodes::INCREMENT_C                                : return std::make_unique<IncrementC>();
            case opcodes::DECREMENT_C                                : return std::make_unique<DecrementC>();
            case opcodes::LOAD_IMMEDIATE_INTO_C                      : return std::make_unique<LoadImmediateIntoC>(fetch_byte());
            case opcodes::ROTATE_RIGHT_CONTENTS_OF_A_AND_CLEAR_ZERO  : return std::make_unique<RotateRightContentsOfAAndClearZero>();

            case opcodes::STOP                                       : return std::make_unique<Stop>();
            case opcodes::LOAD_IMMEDIATE_INTO_DE                     : return std::make_unique<LoadImmediateIntoDE>(fetch_word());
            case opcodes::LOAD_A_INTO_ADDRESS_DE                     : return std::make_unique<LoadAIntoAddressDE>();
            case opcodes::INCREMENT_DE                               : return std::make_unique<IncrementDE>();
            case opcodes::INCREMENT_D                                : return std::make_unique<IncrementD>();
            case opcodes::DECREMENT_D                                : return std::make_unique<DecrementD>();
            case opcodes::LOAD_IMMEDIATE_INTO_D                      : return std::make_unique<LoadImmediateIntoD>(fetch_byte());
            case opcodes::ROTATE_LEFT_A_AND_CLEAR_ZERO               : return std::make_unique<RotateLeftAAndClearZero>();
            case opcodes::JUMP_RELATIVE                              : return std::make_unique<JumpRelative>(fetch_byte());
            case opcodes::ADD_HL_AND_DE                              : return std::make_unique<AddHLAndDE>();
            case opcodes::LOAD_ADDRESS_DE_INTO_A                     : return std::make_unique<LoadAddressDEIntoA>();
            case opcodes::DECREMENT_DE                               : return std::make_unique<DecrementDE>();
            case opcodes::INCREMENT_E                                : return std::make_unique<IncrementE>();
            case opcodes::DECREMENT_E                                : return std::make_unique<DecrementE>();
            case opcodes::LOAD_IMMEDIATE_INTO_E                      : return std::make_unique<LoadImmediateIntoE>(fetch_byte());
            case opcodes::ROTATE_RIGHT_A_AND_CLEAR_ZERO              : return std::make_unique<RotateRightAAndClearZero>();

            case opcodes::JUMP_RELATIVE_IF_NOT_ZERO                  : return std::make_unique<JumpRelativeIfNotZero>(fetch_byte());
            case opcodes::LOAD_IMMEDIATE_INTO_HL                     : return std::make_unique<LoadImmediateIntoHL>(fetch_word());
            case opcodes::LOAD_A_INTO_ADDRESS_HL_INCREMENT           : return std::make_unique<LoadAIntoAddressHLIncrement>();
            case opcodes::INCREMENT_HL                               : return std::make_unique<IncrementHL>();
            case opcodes::INCREMENT_H                                : return std::make_unique<IncrementH>();
            case opcodes::DECREMENT_H                                : return std::make_unique<DecrementH>();
            case opcodes::LOAD_IMMEDIATE_INTO_H                      : return std::make_unique<LoadImmediateIntoH>(fetch_byte());
            case opcodes::DECIMAL_ADJUST_A                           : return std::make_unique<DecimalAdjustA>();
            case opcodes::JUMP_RELATIVE_IF_ZERO                      : return std::make_unique<JumpRelativeIfZero>(fetch_byte());
            case opcodes::ADD_HL_AND_HL                              : return std::make_unique<AddHLAndHL>();
            case opcodes::LOAD_ADDRESS_HL_INCREMENT_INTO_A           : return std::make_unique<LoadAddressHLIncrementIntoA>();
            case opcodes::DECREMENT_HL                               : return std::make_unique<DecrementHL>();
            case opcodes::INCREMENT_L                                : return std::make_unique<IncrementL>();
            case opcodes::DECREMENT_L                                : return std::make_unique<DecrementL>();
            case opcodes::LOAD_IMMEDIATE_INTO_L                      : return std::make_unique<LoadImmediateIntoL>(fetch_byte());
            case opcodes::COMPLEMENT_A                               : return std::make_unique<ComplementA>();

            case opcodes::JUMP_RELATIVE_IF_NOT_CARRY                 : return std::make_unique<JumpRelativeIfNotCarry>(fetch_byte());
            case opcodes::LOAD_IMMEDIATE_INTO_SP                     : return std::make_unique<LoadImmediateIntoSP>(fetch_word());
            case opcodes::LOAD_A_INTO_ADDRESS_HL_DECREMENT           : return std::make_unique<LoadAIntoAddressHLDecrement>();
            case opcodes::INCREMENT_SP                               : return std::make_unique<IncrementSP>();
            case opcodes::INCREMENT_ADDRESS_HL                       : return std::make_unique<IncrementAddressHL>();
            case opcodes::DECREMENT_ADDRESS_HL                       : return std::make_unique<DecrementAddressHL>();
            case opcodes::LOAD_IMMEDIATE_INTO_ADDRESS_HL             : return std::make_unique<LoadImmediateIntoAddressHL>(fetch_byte());
            case opcodes::SET_CARRY                                  : return std::make_unique<SetCarry>();
            case opcodes::JUMP_RELATIVE_IF_CARRY                     : return std::make_unique<JumpRelativeIfCarry>(fetch_byte());
            case opcodes::ADD_HL_AND_SP                              : return std::make_unique<AddHLAndSP>();
            case opcodes::LOAD_ADDRESS_HL_DECREMENT_INTO_A           : return std::make_unique<LoadAddressHLDecrementIntoA>();
            case opcodes::DECREMENT_SP                               : return std::make_unique<DecrementSP>();
            case opcodes::INCREMENT_A                                : return std::make_unique<IncrementA>();
            case opcodes::DECREMENT_A                                : return std::make_unique<DecrementA>();
            case opcodes::LOAD_IMMEDIATE_INTO_A                      : return std::make_unique<LoadImmediateIntoA>(fetch_byte());
            case opcodes::FLIP_CARRY                                 : return std::make_unique<FlipCarry>();

            case opcodes::LOAD_B_INTO_B                              : return std::make_unique<LoadBIntoB>();
            case opcodes::LOAD_C_INTO_B                              : return std::make_unique<LoadCIntoB>();
            case opcodes::LOAD_D_INTO_B                              : return std::make_unique<LoadDIntoB>();
            case opcodes::LOAD_E_INTO_B                              : return std::make_unique<LoadEIntoB>();
            case opcodes::LOAD_H_INTO_B                              : return std::make_unique<LoadHIntoB>();
            case opcodes::LOAD_L_INTO_B                              : return std::make_unique<LoadLIntoB>();
            case opcodes::LOAD_ADDRESS_HL_INTO_B                     : return std::make_unique<LoadAddressHLIntoB>();
            case opcodes::LOAD_A_INTO_B                              : return std::make_unique<LoadAIntoB>();
            case opcodes::LOAD_B_INTO_C                              : return std::make_unique<LoadBIntoC>();
            case opcodes::LOAD_C_INTO_C                              : return std::make_unique<LoadCIntoC>();
            case opcodes::LOAD_D_INTO_C                              : return std::make_unique<LoadDIntoC>();
            case opcodes::LOAD_E_INTO_C                              : return std::make_unique<LoadEIntoC>();
            case opcodes::LOAD_H_INTO_C                              : return std::make_unique<LoadHIntoC>();
            case opcodes::LOAD_L_INTO_C                              : return std::make_unique<LoadLIntoC>();
            case opcodes::LOAD_ADDRESS_HL_INTO_C                     : return std::make_unique<LoadAddressHLIntoC>();
            case opcodes::LOAD_A_INTO_C                              : return std::make_unique<LoadAIntoC>();

            case opcodes::LOAD_B_INTO_D                              : return std::make_unique<LoadBIntoD>();
            case opcodes::LOAD_C_INTO_D                              : return std::make_unique<LoadCIntoD>();
            case opcodes::LOAD_D_INTO_D                              : return std::make_unique<LoadDIntoD>();
            case opcodes::LOAD_E_INTO_D                              : return std::make_unique<LoadEIntoD>();
            case opcodes::LOAD_H_INTO_D                              : return std::make_unique<LoadHIntoD>();
            case opcodes::LOAD_L_INTO_D                              : return std::make_unique<LoadLIntoD>();
            case opcodes::LOAD_ADDRESS_HL_INTO_D                     : return std::make_unique<LoadAddressHLIntoD>();
            case opcodes::LOAD_A_INTO_D                              : return std::make_unique<LoadAIntoD>();
            case opcodes::LOAD_B_INTO_E                              : return std::make_unique<LoadBIntoE>();
            case opcodes::LOAD_C_INTO_E                              : return std::make_unique<LoadCIntoE>();
            case opcodes::LOAD_D_INTO_E                              : return std::make_unique<LoadDIntoE>();
            case opcodes::LOAD_E_INTO_E                              : return std::make_unique<LoadEIntoE>();
            case opcodes::LOAD_H_INTO_E                              : return std::make_unique<LoadHIntoE>();
            case opcodes::LOAD_L_INTO_E                              : return std::make_unique<LoadLIntoE>();
            case opcodes::LOAD_ADDRESS_HL_INTO_E                     : return std::make_unique<LoadAddressHLIntoE>();
            case opcodes::LOAD_A_INTO_E                              : return std::make_unique<LoadAIntoE>();

            case opcodes::LOAD_B_INTO_H                              : return std::make_unique<LoadBIntoH>();
            case opcodes::LOAD_C_INTO_H                              : return std::make_unique<LoadCIntoH>();
            case opcodes::LOAD_D_INTO_H                              : return std::make_unique<LoadDIntoH>();
            case opcodes::LOAD_E_INTO_H                              : return std::make_unique<LoadEIntoH>();
            case opcodes::LOAD_H_INTO_H                              : return std::make_unique<LoadHIntoH>();
            case opcodes::LOAD_L_INTO_H                              : return std::make_unique<LoadLIntoH>();
            case opcodes::LOAD_ADDRESS_HL_INTO_H                     : return std::make_unique<LoadAddressHLIntoH>();
            case opcodes::LOAD_A_INTO_H                              : return std::make_unique<LoadAIntoH>();
            case opcodes::LOAD_B_INTO_L                              : return std::make_unique<LoadBIntoL>();
            case opcodes::LOAD_C_INTO_L                              : return std::make_unique<LoadCIntoL>();
            case opcodes::LOAD_D_INTO_L                              : return std::make_unique<LoadDIntoL>();
            case opcodes::LOAD_E_INTO_L                              : return std::make_unique<LoadEIntoL>();
            case opcodes::LOAD_H_INTO_L                              : return std::make_unique<LoadHIntoL>();
            case opcodes::LOAD_L_INTO_L                              : return std::make_unique<LoadLIntoL>();
            case opcodes::LOAD_ADDRESS_HL_INTO_L                     : return std::make_unique<LoadAddressHLIntoL>();
            case opcodes::LOAD_A_INTO_L                              : return std::make_unique<LoadAIntoL>();

            case opcodes::LOAD_B_INTO_ADDRESS_HL                     : return std::make_unique<LoadBIntoAddressHL>();
            case opcodes::LOAD_C_INTO_ADDRESS_HL                     : return std::make_unique<LoadCIntoAddressHL>();
            case opcodes::LOAD_D_INTO_ADDRESS_HL                     : return std::make_unique<LoadDIntoAddressHL>();
            case opcodes::LOAD_E_INTO_ADDRESS_HL                     : return std::make_unique<LoadEIntoAddressHL>();
            case opcodes::LOAD_H_INTO_ADDRESS_HL                     : return std::make_unique<LoadHIntoAddressHL>();
            case opcodes::LOAD_L_INTO_ADDRESS_HL                     : return std::make_unique<LoadLIntoAddressHL>();
            case opcodes::HALT                                       : return std::make_unique<Halt>();
            case opcodes::LOAD_A_INTO_ADDRESS_HL                     : return std::make_unique<LoadAIntoAddressHL>();
            case opcodes::LOAD_B_INTO_A                              : return std::make_unique<LoadBIntoA>();
            case opcodes::LOAD_C_INTO_A                              : return std::make_unique<LoadCIntoA>();
            case opcodes::LOAD_D_INTO_A                              : return std::make_unique<LoadDIntoA>();
            case opcodes::LOAD_E_INTO_A                              : return std::make_unique<LoadEIntoA>();
            case opcodes::LOAD_H_INTO_A                              : return std::make_unique<LoadHIntoA>();
            case opcodes::LOAD_L_INTO_A                              : return std::make_unique<LoadLIntoA>();
            case opcodes::LOAD_ADDRESS_HL_INTO_A                     : return std::make_unique<LoadAddressHLIntoA>();
            case opcodes::LOAD_A_INTO_A                              : return std::make_unique<LoadAIntoA>();

            case opcodes::ADD_A_AND_B                                : return std::make_unique<AddAAndB>();
            case opcodes::ADD_A_AND_C                                : return std::make_unique<AddAAndC>();
            case opcodes::ADD_A_AND_D                                : return std::make_unique<AddAAndD>();
            case opcodes::ADD_A_AND_E                                : return std::make_unique<AddAAndE>();
            case opcodes::ADD_A_AND_H                                : return std::make_unique<AddAAndH>();
            case opcodes::ADD_A_AND_L                                : return std::make_unique<AddAAndL>();
            case opcodes::ADD_A_AND_ADDRESS_HL                       : return std::make_unique<AddAAndAddressHL>();
            case opcodes::ADD_A_AND_A                                : return std::make_unique<AddAAndA>();
            case opcodes::ADD_WITH_CARRY_A_AND_B                     : return std::make_unique<AddWithCarryAAndB>();
            case opcodes::ADD_WITH_CARRY_A_AND_C                     : return std::make_unique<AddWithCarryAAndC>();
            case opcodes::ADD_WITH_CARRY_A_AND_D                     : return std::make_unique<AddWithCarryAAndD>();
            case opcodes::ADD_WITH_CARRY_A_AND_E                     : return std::make_unique<AddWithCarryAAndE>();
            case opcodes::ADD_WITH_CARRY_A_AND_H                     : return std::make_unique<AddWithCarryAAndH>();
            case opcodes::ADD_WITH_CARRY_A_AND_L                     : return std::make_unique<AddWithCarryAAndL>();
            case opcodes::ADD_WITH_CARRY_A_AND_ADDRESS_HL            : return std::make_unique<AddWithCarryAAndAddressHL>();
            case opcodes::ADD_WITH_CARRY_A_AND_A                     : return std::make_unique<AddWithCarryAAndA>();

            case opcodes::SUBTRACT_A_AND_B                           : return std::make_unique<SubtractAAndB>();
            case opcodes::SUBTRACT_A_AND_C                           : return std::make_unique<SubtractAAndC>();
            case opcodes::SUBTRACT_A_AND_D                           : return std::make_unique<SubtractAAndD>();
            case opcodes::SUBTRACT_A_AND_E                           : return std::make_unique<SubtractAAndE>();
            case opcodes::SUBTRACT_A_AND_H                           : return std::make_unique<SubtractAAndH>();
            case opcodes::SUBTRACT_A_AND_L                           : return std::make_unique<SubtractAAndL>();
            case opcodes::SUBTRACT_A_AND_ADDRESS_HL                  : return std::make_unique<SubtractAAndAddressHL>();
            case opcodes::SUBTRACT_A_AND_A                           : return std::make_unique<SubtractAAndA>();
            case opcodes::SUBTRACT_WITH_CARRY_A_AND_B                : return std::make_unique<SubtractWithCarryAAndB>();
            case opcodes::SUBTRACT_WITH_CARRY_A_AND_C                : return std::make_unique<SubtractWithCarryAAndC>();
            case opcodes::SUBTRACT_WITH_CARRY_A_AND_D                : return std::make_unique<SubtractWithCarryAAndD>();
            case opcodes::SUBTRACT_WITH_CARRY_A_AND_E                : return std::make_unique<SubtractWithCarryAAndE>();
            case opcodes::SUBTRACT_WITH_CARRY_A_AND_H                : return std::make_unique<SubtractWithCarryAAndH>();
            case opcodes::SUBTRACT_WITH_CARRY_A_AND_L                : return std::make_unique<SubtractWithCarryAAndL>();
            case opcodes::SUBTRACT_WITH_CARRY_A_AND_ADDRESS_HL       : return std::make_unique<SubtractWithCarryAAndAddressHL>();
            case opcodes::SUBTRACT_WITH_CARRY_A_AND_A                : return std::make_unique<SubtractWithCarryAAndA>();

            case opcodes::AND_A_AND_B                                : return std::make_unique<AndAAndB>();
            case opcodes::AND_A_AND_C                                : return std::make_unique<AndAAndC>();
            case opcodes::AND_A_AND_D                                : return std::make_unique<AndAAndD>();
            case opcodes::AND_A_AND_E                                : return std::make_unique<AndAAndE>();
            case opcodes::AND_A_AND_H                                : return std::make_unique<AndAAndH>();
            case opcodes::AND_A_AND_L                                : return std::make_unique<AndAAndL>();
            case opcodes::AND_A_AND_ADDRESS_HL                       : return std::make_unique<AndAAndAddressHL>();
            case opcodes::AND_A_AND_A                                : return std::make_unique<AndAAndA>();
            case opcodes::XOR_A_AND_B                                : return std::make_unique<XorAAndB>();
            case opcodes::XOR_A_AND_C                                : return std::make_unique<XorAAndC>();
            case opcodes::XOR_A_AND_D                                : return std::make_unique<XorAAndD>();
            case opcodes::XOR_A_AND_E                                : return std::make_unique<XorAAndE>();
            case opcodes::XOR_A_AND_H                                : return std::make_unique<XorAAndH>();
            case opcodes::XOR_A_AND_L                                : return std::make_unique<XorAAndL>();
            case opcodes::XOR_A_AND_ADDRESS_HL                       : return std::make_unique<XorAAndAddressHL>();
            case opcodes::XOR_A_AND_A                                : return std::make_unique<XorAAndA>();

            case opcodes::OR_A_AND_B                                 : return std::make_unique<OrAAndB>();
            case opcodes::OR_A_AND_C                                 : return std::make_unique<OrAAndC>();
            case opcodes::OR_A_AND_D                                 : return std::make_unique<OrAAndD>();
            case opcodes::OR_A_AND_E                                 : return std::make_unique<OrAAndE>();
            case opcodes::OR_A_AND_H                                 : return std::make_unique<OrAAndH>();
            case opcodes::OR_A_AND_L                                 : return std::make_unique<OrAAndL>();
            case opcodes::OR_A_AND_ADDRESS_HL                        : return std::make_unique<OrAAndAddressHL>();
            case opcodes::OR_A_AND_A                                 : return std::make_unique<OrAAndA>();
            case opcodes::COMPARE_A_AND_B                            : return std::make_unique<CompareAAndB>();
            case opcodes::COMPARE_A_AND_C                            : return std::make_unique<CompareAAndC>();
            case opcodes::COMPARE_A_AND_D                            : return std::make_unique<CompareAAndD>();
            case opcodes::COMPARE_A_AND_E                            : return std::make_unique<CompareAAndE>();
            case opcodes::COMPARE_A_AND_H                            : return std::make_unique<CompareAAndH>();
            case opcodes::COMPARE_A_AND_L                            : return std::make_unique<CompareAAndL>();
            case opcodes::COMPARE_A_AND_ADDRESS_HL                   : return std::make_unique<CompareAAndAddressHL>();
            case opcodes::COMPARE_A_AND_A                            : return std::make_unique<CompareAAndA>();

            case opcodes::RETURN_IF_NOT_ZERO                         : return std::make_unique<ReturnIfNotZero>();
            case opcodes::POP_BC                                     : return std::make_unique<PopBC>();
            case opcodes::JUMP_IF_NOT_ZERO                           : return std::make_unique<JumpIfNotZero>(fetch_word());
            case opcodes::JUMP                                       : return std::make_unique<Jump>(fetch_word());
            case opcodes::CALL_IF_NOT_ZERO                           : return std::make_unique<CallIfNotZero>(fetch_word());
            case opcodes::PUSH_BC                                    : return std::make_unique<PushBC>();
            case opcodes::ADD_A_AND_IMMEDIATE                        : return std::make_unique<AddAAndImmediate>(fetch_byte());
            case opcodes::RESTART_0                                  : return std::make_unique<Restart0>();
            case opcodes::RETURN_IF_ZERO                             : return std::make_unique<ReturnIfZero>();
            case opcodes::RETURN                                     : return std::make_unique<Return>();
            case opcodes::JUMP_IF_ZERO                               : return std::make_unique<JumpIfZero>(fetch_word());
            case opcodes::UNUSED_0                                   : return std::make_unique<Unused0>();
            case opcodes::CALL_IF_ZERO                               : return std::make_unique<CallIfZero>(fetch_word());
            case opcodes::CALL                                       : return std::make_unique<Call>(fetch_word());
            case opcodes::ADD_WITH_CARRY_A_AND_IMMEDIATE             : return std::make_unique<AddWithCarryAAndImmediate>(fetch_byte());
            case opcodes::RESTART_1                                  : return std::make_unique<Restart1>();

            case opcodes::RETURN_IF_NOT_CARRY                        : return std::make_unique<ReturnIfNotCarry>();
            case opcodes::POP_DE                                     : return std::make_unique<PopDE>();
            case opcodes::JUMP_IF_NOT_CARRY                          : return std::make_unique<JumpIfNotCarry>(fetch_word());
            case opcodes::UNUSED_1                                   : return std::make_unique<Unused1>();
            case opcodes::CALL_IF_NOT_CARRY                          : return std::make_unique<CallIfNotCarry>(fetch_word());
            case opcodes::PUSH_DE                                    : return std::make_unique<PushDE>();
            case opcodes::SUBTRACT_A_AND_IMMEDIATE                   : return std::make_unique<SubtractAAndImmediate>(fetch_byte());
            case opcodes::RESTART_2                                  : return std::make_unique<Restart2>();
            case opcodes::RETURN_IF_CARRY                            : return std::make_unique<ReturnIfCarry>();
            case opcodes::RETURN_FROM_INTERRUPT                      : return std::make_unique<ReturnFromInterrupt>();
            case opcodes::JUMP_IF_CARRY                              : return std::make_unique<JumpIfCarry>(fetch_word());
            case opcodes::UNUSED_2                                   : return std::make_unique<Unused2>();
            case opcodes::CALL_IF_CARRY                              : return std::make_unique<CallIfCarry>(fetch_word());
            case opcodes::UNUSED_3                                   : return std::make_unique<Unused3>();
            case opcodes::SUBTRACT_WITH_CARRY_A_AND_IMMEDIATE        : return std::make_unique<SubtractWithCarryAAndImmediate>(fetch_byte());
            case opcodes::RESTART_3                                  : return std::make_unique<Restart3>();

            case opcodes::LOAD_A_INTO_PORT_ADDRESS_IMMEDIATE         : return std::make_unique<LoadAIntoPortAddressImmediate>(fetch_byte());
            case opcodes::POP_HL                                     : return std::make_unique<PopHL>();
            case opcodes::LOAD_A_INTO_PORT_ADDRESS_C                 : return std::make_unique<LoadAIntoPortAddressC>();
            case opcodes::UNUSED_4                                   : return std::make_unique<Unused4>();
            case opcodes::UNUSED_5                                   : return std::make_unique<Unused5>();
            case opcodes::PUSH_HL                                    : return std::make_unique<PushHL>();
            case opcodes::AND_A_AND_IMMEDIATE                        : return std::make_unique<AndAAndImmediate>(fetch_byte());
            case opcodes::RESTART_4                                  : return std::make_unique<Restart4>();
            case opcodes::ADD_SP_AND_IMMEDIATE                       : return std::make_unique<AddSPAndImmediate>(fetch_word());
            case opcodes::JUMP_TO_HL                                 : return std::make_unique<JumpToHL>();
            case opcodes::LOAD_A_INTO_ADDRESS_IMMEDIATE              : return std::make_unique<LoadAIntoAddressImmediate>(fetch_word());
            case opcodes::UNUSED_6                                   : return std::make_unique<Unused6>();
            case opcodes::UNUSED_7                                   : return std::make_unique<Unused7>();
            case opcodes::UNUSED_8                                   : return std::make_unique<Unused8>();
            case opcodes::XOR_A_AND_IMMEDIATE                        : return std::make_unique<XorAAndImmediate>(fetch_byte());
            case opcodes::RESTART_5                                  : return std::make_unique<Restart5>();

            case opcodes::LOAD_PORT_ADDRESS_IMMEDIATE_INTO_A         : return std::make_unique<LoadPortAddressImmediateIntoA>(fetch_byte());
            case opcodes::POP_AF                                     : return std::make_unique<PopAF>();
            case opcodes::LOAD_PORT_ADDRESS_C_INTO_A                 : return std::make_unique<LoadPortAddressCIntoA>();
            case opcodes::DISABLE_INTERRUPTS                         : return std::make_unique<DisableInterrupts>();
            case opcodes::UNUSED_9                                   : return std::make_unique<Unused9>();
            case opcodes::PUSH_AF                                    : return std::make_unique<PushAF>();
            case opcodes::OR_A_AND_IMMEDIATE                         : return std::make_unique<OrAAndImmediate>(fetch_byte());
            case opcodes::RESTART_6                                  : return std::make_unique<Restart6>();
            case opcodes::LOAD_SP_SHIFTED_BY_IMMEDIATE_INTO_HL       : return std::make_unique<LoadSPShiftedByImmediateIntoHL>(fetch_byte());
            case opcodes::LOAD_HL_INTO_SP                            : return std::make_unique<LoadHLIntoSP>();
            case opcodes::LOAD_ADDRESS_IMMEDIATE_INTO_A              : return std::make_unique<LoadAddressImmediateIntoA>(fetch_word());
            case opcodes::ENABLE_INTERRUPTS                          : return std::make_unique<EnableInterrupts>();
            case opcodes::UNUSED_10                                  : return std::make_unique<Unused10>();
            case opcodes::UNUSED_11                                  : return std::make_unique<Unused11>();
            case opcodes::COMPARE_A_AND_IMMEDIATE                    : return std::make_unique<CompareAAndImmediate>(fetch_byte());
            case opcodes::RESTART_7                                  : return std::make_unique<Restart7>();

            //

            case opcodes::ROTATE_LEFT_CONTENTS_OF_B                  : return std::make_unique<RotateLeftContentsOfB>();
            case opcodes::ROTATE_LEFT_CONTENTS_OF_C                  : return std::make_unique<RotateLeftContentsOfC>();
            case opcodes::ROTATE_LEFT_CONTENTS_OF_D                  : return std::make_unique<RotateLeftContentsOfD>();
            case opcodes::ROTATE_LEFT_CONTENTS_OF_E                  : return std::make_unique<RotateLeftContentsOfE>();
            case opcodes::ROTATE_LEFT_CONTENTS_OF_H                  : return std::make_unique<RotateLeftContentsOfH>();
            case opcodes::ROTATE_LEFT_CONTENTS_OF_L                  : return std::make_unique<RotateLeftContentsOfL>();
            case opcodes::ROTATE_LEFT_CONTENTS_OF_ADDRESS_HL         : return std::make_unique<RotateLeftContentsOfAddressHL>();
            case opcodes::ROTATE_LEFT_CONTENTS_OF_A                  : return std::make_unique<RotateLeftContentsOfA>();
            case opcodes::ROTATE_RIGHT_CONTENTS_OF_B                 : return std::make_unique<RotateRightContentsOfB>();
            case opcodes::ROTATE_RIGHT_CONTENTS_OF_C                 : return std::make_unique<RotateRightContentsOfC>();
            case opcodes::ROTATE_RIGHT_CONTENTS_OF_D                 : return std::make_unique<RotateRightContentsOfD>();
            case opcodes::ROTATE_RIGHT_CONTENTS_OF_E                 : return std::make_unique<RotateRightContentsOfE>();
            case opcodes::ROTATE_RIGHT_CONTENTS_OF_H                 : return std::make_unique<RotateRightContentsOfH>();
            case opcodes::ROTATE_RIGHT_CONTENTS_OF_L                 : return std::make_unique<RotateRightContentsOfL>();
            case opcodes::ROTATE_RIGHT_CONTENTS_OF_ADDRESS_HL        : return std::make_unique<RotateRightContentsOfAddressHL>();
            case opcodes::ROTATE_RIGHT_CONTENTS_OF_A                 : return std::make_unique<RotateRightContentsOfA>();

            case opcodes::ROTATE_LEFT_B                              : return std::make_unique<RotateLeftB>();
            case opcodes::ROTATE_LEFT_C                              : return std::make_unique<RotateLeftC>();
            case opcodes::ROTATE_LEFT_D                              : return std::make_unique<RotateLeftD>();
            case opcodes::ROTATE_LEFT_E                              : return std::make_unique<RotateLeftE>();
            case opcodes::ROTATE_LEFT_H                              : return std::make_unique<RotateLeftH>();
            case opcodes::ROTATE_LEFT_L                              : return std::make_unique<RotateLeftL>();
            case opcodes::ROTATE_LEFT_ADDRESS_HL                     : return std::make_unique<RotateLeftAddressHL>();
            case opcodes::ROTATE_LEFT_A                              : return std::make_unique<RotateLeftA>();
            case opcodes::ROTATE_RIGHT_B                             : return std::make_unique<RotateRightB>();
            case opcodes::ROTATE_RIGHT_C                             : return std::make_unique<RotateRightC>();
            case opcodes::ROTATE_RIGHT_D                             : return std::make_unique<RotateRightD>();
            case opcodes::ROTATE_RIGHT_E                             : return std::make_unique<RotateRightE>();
            case opcodes::ROTATE_RIGHT_H                             : return std::make_unique<RotateRightH>();
            case opcodes::ROTATE_RIGHT_L                             : return std::make_unique<RotateRightL>();
            case opcodes::ROTATE_RIGHT_ADDRESS_HL                    : return std::make_unique<RotateRightAddressHL>();
            case opcodes::ROTATE_RIGHT_A                             : return std::make_unique<RotateRightA>();

            case opcodes::SHIFT_LEFT_ARITHMETICAL_B                  : return std::make_unique<ShiftLeftArithmeticalB>();
            case opcodes::SHIFT_LEFT_ARITHMETICAL_C                  : return std::make_unique<ShiftLeftArithmeticalC>();
            case opcodes::SHIFT_LEFT_ARITHMETICAL_D                  : return std::make_unique<ShiftLeftArithmeticalD>();
            case opcodes::SHIFT_LEFT_ARITHMETICAL_E                  : return std::make_unique<ShiftLeftArithmeticalE>();
            case opcodes::SHIFT_LEFT_ARITHMETICAL_H                  : return std::make_unique<ShiftLeftArithmeticalH>();
            case opcodes::SHIFT_LEFT_ARITHMETICAL_L                  : return std::make_unique<ShiftLeftArithmeticalL>();
            case opcodes::SHIFT_LEFT_ARITHMETICAL_ADDRESS_HL         : return std::make_unique<ShiftLeftArithmeticalAddressHL>();
            case opcodes::SHIFT_LEFT_ARITHMETICAL_A                  : return std::make_unique<ShiftLeftArithmeticalA>();
            case opcodes::SHIFT_RIGHT_ARITHMETICAL_B                 : return std::make_unique<ShiftRightArithmeticalB>();
            case opcodes::SHIFT_RIGHT_ARITHMETICAL_C                 : return std::make_unique<ShiftRightArithmeticalC>();
            case opcodes::SHIFT_RIGHT_ARITHMETICAL_D                 : return std::make_unique<ShiftRightArithmeticalD>();
            case opcodes::SHIFT_RIGHT_ARITHMETICAL_E                 : return std::make_unique<ShiftRightArithmeticalE>();
            case opcodes::SHIFT_RIGHT_ARITHMETICAL_H                 : return std::make_unique<ShiftRightArithmeticalH>();
            case opcodes::SHIFT_RIGHT_ARITHMETICAL_L                 : return std::make_unique<ShiftRightArithmeticalL>();
            case opcodes::SHIFT_RIGHT_ARITHMETICAL_ADDRESS_HL        : return std::make_unique<ShiftRightArithmeticalAddressHL>();
            case opcodes::SHIFT_RIGHT_ARITHMETICAL_A                 : return std::make_unique<ShiftRightArithmeticalA>();

            case opcodes::SWAP_B                                     : return std::make_unique<SwapB>();
            case opcodes::SWAP_C                                     : return std::make_unique<SwapC>();
            case opcodes::SWAP_D                                     : return std::make_unique<SwapD>();
            case opcodes::SWAP_E                                     : return std::make_unique<SwapE>();
            case opcodes::SWAP_H                                     : return std::make_unique<SwapH>();
            case opcodes::SWAP_L                                     : return std::make_unique<SwapL>();
            case opcodes::SWAP_ADDRESS_HL                            : return std::make_unique<SwapAddressHL>();
            case opcodes::SWAP_A                                     : return std::make_unique<SwapA>();
            case opcodes::SHIFT_RIGHT_LOGICAL_B                      : return std::make_unique<ShiftRightLogicalB>();
            case opcodes::SHIFT_RIGHT_LOGICAL_C                      : return std::make_unique<ShiftRightLogicalC>();
            case opcodes::SHIFT_RIGHT_LOGICAL_D                      : return std::make_unique<ShiftRightLogicalD>();
            case opcodes::SHIFT_RIGHT_LOGICAL_E                      : return std::make_unique<ShiftRightLogicalE>();
            case opcodes::SHIFT_RIGHT_LOGICAL_H                      : return std::make_unique<ShiftRightLogicalH>();
            case opcodes::SHIFT_RIGHT_LOGICAL_L                      : return std::make_unique<ShiftRightLogicalL>();
            case opcodes::SHIFT_RIGHT_LOGICAL_ADDRESS_HL             : return std::make_unique<ShiftRightLogicalAddressHL>();
            case opcodes::SHIFT_RIGHT_LOGICAL_A                      : return std::make_unique<ShiftRightLogicalA>();

            case opcodes::BIT_0_OF_B_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit0OfBComplementIntoZero>();
            case opcodes::BIT_0_OF_C_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit0OfCComplementIntoZero>();
            case opcodes::BIT_0_OF_D_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit0OfDComplementIntoZero>();
            case opcodes::BIT_0_OF_E_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit0OfEComplementIntoZero>();
            case opcodes::BIT_0_OF_H_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit0OfHComplementIntoZero>();
            case opcodes::BIT_0_OF_L_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit0OfLComplementIntoZero>();
            case opcodes::BIT_0_OF_ADDRESS_HL_COMPLEMENT_INTO_ZERO   : return std::make_unique<Bit0OfAddressHLComplementIntoZero>();
            case opcodes::BIT_0_OF_A_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit0OfAComplementIntoZero>();
            case opcodes::BIT_1_OF_B_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit1OfBComplementIntoZero>();
            case opcodes::BIT_1_OF_C_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit1OfCComplementIntoZero>();
            case opcodes::BIT_1_OF_D_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit1OfDComplementIntoZero>();
            case opcodes::BIT_1_OF_E_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit1OfEComplementIntoZero>();
            case opcodes::BIT_1_OF_H_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit1OfHComplementIntoZero>();
            case opcodes::BIT_1_OF_L_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit1OfLComplementIntoZero>();
            case opcodes::BIT_1_OF_ADDRESS_HL_COMPLEMENT_INTO_ZERO   : return std::make_unique<Bit1OfAddressHLComplementIntoZero>();
            case opcodes::BIT_1_OF_A_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit1OfAComplementIntoZero>();

            case opcodes::BIT_2_OF_B_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit2OfBComplementIntoZero>();
            case opcodes::BIT_2_OF_C_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit2OfCComplementIntoZero>();
            case opcodes::BIT_2_OF_D_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit2OfDComplementIntoZero>();
            case opcodes::BIT_2_OF_E_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit2OfEComplementIntoZero>();
            case opcodes::BIT_2_OF_H_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit2OfHComplementIntoZero>();
            case opcodes::BIT_2_OF_L_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit2OfLComplementIntoZero>();
            case opcodes::BIT_2_OF_ADDRESS_HL_COMPLEMENT_INTO_ZERO   : return std::make_unique<Bit2OfAddressHLComplementIntoZero>();
            case opcodes::BIT_2_OF_A_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit2OfAComplementIntoZero>();
            case opcodes::BIT_3_OF_B_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit3OfBComplementIntoZero>();
            case opcodes::BIT_3_OF_C_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit3OfCComplementIntoZero>();
            case opcodes::BIT_3_OF_D_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit3OfDComplementIntoZero>();
            case opcodes::BIT_3_OF_E_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit3OfEComplementIntoZero>();
            case opcodes::BIT_3_OF_H_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit3OfHComplementIntoZero>();
            case opcodes::BIT_3_OF_L_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit3OfLComplementIntoZero>();
            case opcodes::BIT_3_OF_ADDRESS_HL_COMPLEMENT_INTO_ZERO   : return std::make_unique<Bit3OfAddressHLComplementIntoZero>();
            case opcodes::BIT_3_OF_A_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit3OfAComplementIntoZero>();

            case opcodes::BIT_4_OF_B_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit4OfBComplementIntoZero>();
            case opcodes::BIT_4_OF_C_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit4OfCComplementIntoZero>();
            case opcodes::BIT_4_OF_D_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit4OfDComplementIntoZero>();
            case opcodes::BIT_4_OF_E_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit4OfEComplementIntoZero>();
            case opcodes::BIT_4_OF_H_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit4OfHComplementIntoZero>();
            case opcodes::BIT_4_OF_L_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit4OfLComplementIntoZero>();
            case opcodes::BIT_4_OF_ADDRESS_HL_COMPLEMENT_INTO_ZERO   : return std::make_unique<Bit4OfAddressHLComplementIntoZero>();
            case opcodes::BIT_4_OF_A_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit4OfAComplementIntoZero>();
            case opcodes::BIT_5_OF_B_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit5OfBComplementIntoZero>();
            case opcodes::BIT_5_OF_C_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit5OfCComplementIntoZero>();
            case opcodes::BIT_5_OF_D_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit5OfDComplementIntoZero>();
            case opcodes::BIT_5_OF_E_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit5OfEComplementIntoZero>();
            case opcodes::BIT_5_OF_H_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit5OfHComplementIntoZero>();
            case opcodes::BIT_5_OF_L_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit5OfLComplementIntoZero>();
            case opcodes::BIT_5_OF_ADDRESS_HL_COMPLEMENT_INTO_ZERO   : return std::make_unique<Bit5OfAddressHLComplementIntoZero>();
            case opcodes::BIT_5_OF_A_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit5OfAComplementIntoZero>();

            case opcodes::BIT_6_OF_B_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit6OfBComplementIntoZero>();
            case opcodes::BIT_6_OF_C_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit6OfCComplementIntoZero>();
            case opcodes::BIT_6_OF_D_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit6OfDComplementIntoZero>();
            case opcodes::BIT_6_OF_E_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit6OfEComplementIntoZero>();
            case opcodes::BIT_6_OF_H_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit6OfHComplementIntoZero>();
            case opcodes::BIT_6_OF_L_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit6OfLComplementIntoZero>();
            case opcodes::BIT_6_OF_ADDRESS_HL_COMPLEMENT_INTO_ZERO   : return std::make_unique<Bit6OfAddressHLComplementIntoZero>();
            case opcodes::BIT_6_OF_A_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit6OfAComplementIntoZero>();
            case opcodes::BIT_7_OF_B_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit7OfBComplementIntoZero>();
            case opcodes::BIT_7_OF_C_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit7OfCComplementIntoZero>();
            case opcodes::BIT_7_OF_D_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit7OfDComplementIntoZero>();
            case opcodes::BIT_7_OF_E_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit7OfEComplementIntoZero>();
            case opcodes::BIT_7_OF_H_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit7OfHComplementIntoZero>();
            case opcodes::BIT_7_OF_L_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit7OfLComplementIntoZero>();
            case opcodes::BIT_7_OF_ADDRESS_HL_COMPLEMENT_INTO_ZERO   : return std::make_unique<Bit7OfAddressHLComplementIntoZero>();
            case opcodes::BIT_7_OF_A_COMPLEMENT_INTO_ZERO            : return std::make_unique<Bit7OfAComplementIntoZero>();

            case opcodes::RESET_BIT_0_OF_B                           : return std::make_unique<ResetBit0OfB>();
            case opcodes::RESET_BIT_0_OF_C                           : return std::make_unique<ResetBit0OfC>();
            case opcodes::RESET_BIT_0_OF_D                           : return std::make_unique<ResetBit0OfD>();
            case opcodes::RESET_BIT_0_OF_E                           : return std::make_unique<ResetBit0OfE>();
            case opcodes::RESET_BIT_0_OF_H                           : return std::make_unique<ResetBit0OfH>();
            case opcodes::RESET_BIT_0_OF_L                           : return std::make_unique<ResetBit0OfL>();
            case opcodes::RESET_BIT_0_OF_ADDRESS_HL                  : return std::make_unique<ResetBit0OfAddressHL>();
            case opcodes::RESET_BIT_0_OF_A                           : return std::make_unique<ResetBit0OfA>();
            case opcodes::RESET_BIT_1_OF_B                           : return std::make_unique<ResetBit1OfB>();
            case opcodes::RESET_BIT_1_OF_C                           : return std::make_unique<ResetBit1OfC>();
            case opcodes::RESET_BIT_1_OF_D                           : return std::make_unique<ResetBit1OfD>();
            case opcodes::RESET_BIT_1_OF_E                           : return std::make_unique<ResetBit1OfE>();
            case opcodes::RESET_BIT_1_OF_H                           : return std::make_unique<ResetBit1OfH>();
            case opcodes::RESET_BIT_1_OF_L                           : return std::make_unique<ResetBit1OfL>();
            case opcodes::RESET_BIT_1_OF_ADDRESS_HL                  : return std::make_unique<ResetBit1OfAddressHL>();
            case opcodes::RESET_BIT_1_OF_A                           : return std::make_unique<ResetBit1OfA>();

            case opcodes::RESET_BIT_2_OF_B                           : return std::make_unique<ResetBit2OfB>();
            case opcodes::RESET_BIT_2_OF_C                           : return std::make_unique<ResetBit2OfC>();
            case opcodes::RESET_BIT_2_OF_D                           : return std::make_unique<ResetBit2OfD>();
            case opcodes::RESET_BIT_2_OF_E                           : return std::make_unique<ResetBit2OfE>();
            case opcodes::RESET_BIT_2_OF_H                           : return std::make_unique<ResetBit2OfH>();
            case opcodes::RESET_BIT_2_OF_L                           : return std::make_unique<ResetBit2OfL>();
            case opcodes::RESET_BIT_2_OF_ADDRESS_HL                  : return std::make_unique<ResetBit2OfAddressHL>();
            case opcodes::RESET_BIT_2_OF_A                           : return std::make_unique<ResetBit2OfA>();
            case opcodes::RESET_BIT_3_OF_B                           : return std::make_unique<ResetBit3OfB>();
            case opcodes::RESET_BIT_3_OF_C                           : return std::make_unique<ResetBit3OfC>();
            case opcodes::RESET_BIT_3_OF_D                           : return std::make_unique<ResetBit3OfD>();
            case opcodes::RESET_BIT_3_OF_E                           : return std::make_unique<ResetBit3OfE>();
            case opcodes::RESET_BIT_3_OF_H                           : return std::make_unique<ResetBit3OfH>();
            case opcodes::RESET_BIT_3_OF_L                           : return std::make_unique<ResetBit3OfL>();
            case opcodes::RESET_BIT_3_OF_ADDRESS_HL                  : return std::make_unique<ResetBit3OfAddressHL>();
            case opcodes::RESET_BIT_3_OF_A                           : return std::make_unique<ResetBit3OfA>();

            case opcodes::RESET_BIT_4_OF_B                           : return std::make_unique<ResetBit4OfB>();
            case opcodes::RESET_BIT_4_OF_C                           : return std::make_unique<ResetBit4OfC>();
            case opcodes::RESET_BIT_4_OF_D                           : return std::make_unique<ResetBit4OfD>();
            case opcodes::RESET_BIT_4_OF_E                           : return std::make_unique<ResetBit4OfE>();
            case opcodes::RESET_BIT_4_OF_H                           : return std::make_unique<ResetBit4OfH>();
            case opcodes::RESET_BIT_4_OF_L                           : return std::make_unique<ResetBit4OfL>();
            case opcodes::RESET_BIT_4_OF_ADDRESS_HL                  : return std::make_unique<ResetBit4OfAddressHL>();
            case opcodes::RESET_BIT_4_OF_A                           : return std::make_unique<ResetBit4OfA>();
            case opcodes::RESET_BIT_5_OF_B                           : return std::make_unique<ResetBit5OfB>();
            case opcodes::RESET_BIT_5_OF_C                           : return std::make_unique<ResetBit5OfC>();
            case opcodes::RESET_BIT_5_OF_D                           : return std::make_unique<ResetBit5OfD>();
            case opcodes::RESET_BIT_5_OF_E                           : return std::make_unique<ResetBit5OfE>();
            case opcodes::RESET_BIT_5_OF_H                           : return std::make_unique<ResetBit5OfH>();
            case opcodes::RESET_BIT_5_OF_L                           : return std::make_unique<ResetBit5OfL>();
            case opcodes::RESET_BIT_5_OF_ADDRESS_HL                  : return std::make_unique<ResetBit5OfAddressHL>();
            case opcodes::RESET_BIT_5_OF_A                           : return std::make_unique<ResetBit5OfA>();

            case opcodes::RESET_BIT_6_OF_B                           : return std::make_unique<ResetBit6OfB>();
            case opcodes::RESET_BIT_6_OF_C                           : return std::make_unique<ResetBit6OfC>();
            case opcodes::RESET_BIT_6_OF_D                           : return std::make_unique<ResetBit6OfD>();
            case opcodes::RESET_BIT_6_OF_E                           : return std::make_unique<ResetBit6OfE>();
            case opcodes::RESET_BIT_6_OF_H                           : return std::make_unique<ResetBit6OfH>();
            case opcodes::RESET_BIT_6_OF_L                           : return std::make_unique<ResetBit6OfL>();
            case opcodes::RESET_BIT_6_OF_ADDRESS_HL                  : return std::make_unique<ResetBit6OfAddressHL>();
            case opcodes::RESET_BIT_6_OF_A                           : return std::make_unique<ResetBit6OfA>();
            case opcodes::RESET_BIT_7_OF_B                           : return std::make_unique<ResetBit7OfB>();
            case opcodes::RESET_BIT_7_OF_C                           : return std::make_unique<ResetBit7OfC>();
            case opcodes::RESET_BIT_7_OF_D                           : return std::make_unique<ResetBit7OfD>();
            case opcodes::RESET_BIT_7_OF_E                           : return std::make_unique<ResetBit7OfE>();
            case opcodes::RESET_BIT_7_OF_H                           : return std::make_unique<ResetBit7OfH>();
            case opcodes::RESET_BIT_7_OF_L                           : return std::make_unique<ResetBit7OfL>();
            case opcodes::RESET_BIT_7_OF_ADDRESS_HL                  : return std::make_unique<ResetBit7OfAddressHL>();
            case opcodes::RESET_BIT_7_OF_A                           : return std::make_unique<ResetBit7OfA>();

            case opcodes::SET_BIT_0_OF_B                             : return std::make_unique<SetBit0OfB>();
            case opcodes::SET_BIT_0_OF_C                             : return std::make_unique<SetBit0OfC>();
            case opcodes::SET_BIT_0_OF_D                             : return std::make_unique<SetBit0OfD>();
            case opcodes::SET_BIT_0_OF_E                             : return std::make_unique<SetBit0OfE>();
            case opcodes::SET_BIT_0_OF_H                             : return std::make_unique<SetBit0OfH>();
            case opcodes::SET_BIT_0_OF_L                             : return std::make_unique<SetBit0OfL>();
            case opcodes::SET_BIT_0_OF_ADDRESS_HL                    : return std::make_unique<SetBit0OfAddressHL>();
            case opcodes::SET_BIT_0_OF_A                             : return std::make_unique<SetBit0OfA>();
            case opcodes::SET_BIT_1_OF_B                             : return std::make_unique<SetBit1OfB>();
            case opcodes::SET_BIT_1_OF_C                             : return std::make_unique<SetBit1OfC>();
            case opcodes::SET_BIT_1_OF_D                             : return std::make_unique<SetBit1OfD>();
            case opcodes::SET_BIT_1_OF_E                             : return std::make_unique<SetBit1OfE>();
            case opcodes::SET_BIT_1_OF_H                             : return std::make_unique<SetBit1OfH>();
            case opcodes::SET_BIT_1_OF_L                             : return std::make_unique<SetBit1OfL>();
            case opcodes::SET_BIT_1_OF_ADDRESS_HL                    : return std::make_unique<SetBit1OfAddressHL>();
            case opcodes::SET_BIT_1_OF_A                             : return std::make_unique<SetBit1OfA>();

            case opcodes::SET_BIT_2_OF_B                             : return std::make_unique<SetBit2OfB>();
            case opcodes::SET_BIT_2_OF_C                             : return std::make_unique<SetBit2OfC>();
            case opcodes::SET_BIT_2_OF_D                             : return std::make_unique<SetBit2OfD>();
            case opcodes::SET_BIT_2_OF_E                             : return std::make_unique<SetBit2OfE>();
            case opcodes::SET_BIT_2_OF_H                             : return std::make_unique<SetBit2OfH>();
            case opcodes::SET_BIT_2_OF_L                             : return std::make_unique<SetBit2OfL>();
            case opcodes::SET_BIT_2_OF_ADDRESS_HL                    : return std::make_unique<SetBit2OfAddressHL>();
            case opcodes::SET_BIT_2_OF_A                             : return std::make_unique<SetBit2OfA>();
            case opcodes::SET_BIT_3_OF_B                             : return std::make_unique<SetBit3OfB>();
            case opcodes::SET_BIT_3_OF_C                             : return std::make_unique<SetBit3OfC>();
            case opcodes::SET_BIT_3_OF_D                             : return std::make_unique<SetBit3OfD>();
            case opcodes::SET_BIT_3_OF_E                             : return std::make_unique<SetBit3OfE>();
            case opcodes::SET_BIT_3_OF_H                             : return std::make_unique<SetBit3OfH>();
            case opcodes::SET_BIT_3_OF_L                             : return std::make_unique<SetBit3OfL>();
            case opcodes::SET_BIT_3_OF_ADDRESS_HL                    : return std::make_unique<SetBit3OfAddressHL>();
            case opcodes::SET_BIT_3_OF_A                             : return std::make_unique<SetBit3OfA>();

            case opcodes::SET_BIT_4_OF_B                             : return std::make_unique<SetBit4OfB>();
            case opcodes::SET_BIT_4_OF_C                             : return std::make_unique<SetBit4OfC>();
            case opcodes::SET_BIT_4_OF_D                             : return std::make_unique<SetBit4OfD>();
            case opcodes::SET_BIT_4_OF_E                             : return std::make_unique<SetBit4OfE>();
            case opcodes::SET_BIT_4_OF_H                             : return std::make_unique<SetBit4OfH>();
            case opcodes::SET_BIT_4_OF_L                             : return std::make_unique<SetBit4OfL>();
            case opcodes::SET_BIT_4_OF_ADDRESS_HL                    : return std::make_unique<SetBit4OfAddressHL>();
            case opcodes::SET_BIT_4_OF_A                             : return std::make_unique<SetBit4OfA>();
            case opcodes::SET_BIT_5_OF_B                             : return std::make_unique<SetBit5OfB>();
            case opcodes::SET_BIT_5_OF_C                             : return std::make_unique<SetBit5OfC>();
            case opcodes::SET_BIT_5_OF_D                             : return std::make_unique<SetBit5OfD>();
            case opcodes::SET_BIT_5_OF_E                             : return std::make_unique<SetBit5OfE>();
            case opcodes::SET_BIT_5_OF_H                             : return std::make_unique<SetBit5OfH>();
            case opcodes::SET_BIT_5_OF_L                             : return std::make_unique<SetBit5OfL>();
            case opcodes::SET_BIT_5_OF_ADDRESS_HL                    : return std::make_unique<SetBit5OfAddressHL>();
            case opcodes::SET_BIT_5_OF_A                             : return std::make_unique<SetBit5OfA>();

            case opcodes::SET_BIT_6_OF_B                             : return std::make_unique<SetBit6OfB>();
            case opcodes::SET_BIT_6_OF_C                             : return std::make_unique<SetBit6OfC>();
            case opcodes::SET_BIT_6_OF_D                             : return std::make_unique<SetBit6OfD>();
            case opcodes::SET_BIT_6_OF_E                             : return std::make_unique<SetBit6OfE>();
            case opcodes::SET_BIT_6_OF_H                             : return std::make_unique<SetBit6OfH>();
            case opcodes::SET_BIT_6_OF_L                             : return std::make_unique<SetBit6OfL>();
            case opcodes::SET_BIT_6_OF_ADDRESS_HL                    : return std::make_unique<SetBit6OfAddressHL>();
            case opcodes::SET_BIT_6_OF_A                             : return std::make_unique<SetBit6OfA>();
            case opcodes::SET_BIT_7_OF_B                             : return std::make_unique<SetBit7OfB>();
            case opcodes::SET_BIT_7_OF_C                             : return std::make_unique<SetBit7OfC>();
            case opcodes::SET_BIT_7_OF_D                             : return std::make_unique<SetBit7OfD>();
            case opcodes::SET_BIT_7_OF_E                             : return std::make_unique<SetBit7OfE>();
            case opcodes::SET_BIT_7_OF_H                             : return std::make_unique<SetBit7OfH>();
            case opcodes::SET_BIT_7_OF_L                             : return std::make_unique<SetBit7OfL>();
            case opcodes::SET_BIT_7_OF_ADDRESS_HL                    : return std::make_unique<SetBit7OfAddressHL>();
            case opcodes::SET_BIT_7_OF_A                             : return std::make_unique<SetBit7OfA>();

            default: return std::make_unique<Unknown>();

        }
    }

private:

    void increment_program_counter()
    {
        if (!is_out_of_range())
        {
            ++_programCounter;
        }
    }

    // throws std::out_of_range if program counter out of range.
    byte read_byte() const
    {
        if (is_out_of_range())
        {
            throw std::out_of_range("Program counter pointing to position out of range.");
        }

        return *(_startOfByteCode + _programCounter);
    }

    // throws std::out_of_range if program counter out of range.
    // only increments program counter after reading if not out of range.
    byte fetch_byte()
    {
        const byte currentByte = read_byte();
        increment_program_counter();

        return currentByte;
    }

    // throws std::out_of_range if program counter out of range.
    // only increments program counter after reading if not out of range.
    // returns the value according to the word (LSB, MSB)
    // i.e. (0x34, 0x12) is mapped to the value 0x1234
    word fetch_word()
    {
        const byte lsb = fetch_byte();
        const byte msb = fetch_byte();

        return little_endian_to_number(lsb, msb); // note that evaluation order is not fixed in C++!
    }

    // throws std::out_of_range if program counter out of range.
    // only increments program counter after reading if not out of range.
    Opcode fetch_opcode()
    {
        word opcode = fetch_byte();

        // check if prefix
        if (opcode == 0xCB)
        {
            opcode = big_endian_to_number(0xCB, fetch_byte());
        }

        return opcode;
    }

private:
    byte const * _startOfByteCode;
    word _sizeOfByteCode{0x0000};
    word _programCounter{0x0000};
};


#endif //GAMEBOY_DEBUG_DISASSEMBLER_H
