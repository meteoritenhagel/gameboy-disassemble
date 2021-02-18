#ifndef GAMEBOY_DEBUG_DISASSEMBLER_H
#define GAMEBOY_DEBUG_DISASSEMBLER_H

#include <iomanip>
#include <stdexcept>

#include "instructions/instructions.h"

class Disassembler
{
public:
    Disassembler(uint8_t const * const startOfByteCode, const uint16_t sizeOfByteCode)
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

    InstructionPtr decode(uint8_t opcode)
    {
        switch (opcode)
        {
            case opcodes::NOP: return std::make_unique<Nop>();
            case opcodes::LOAD_IMMEDIATE_INTO_BC: return std::make_unique<LoadImmediateIntoBC>(fetch_word());
            case opcodes::LOAD_A_INTO_ADDRESS_BC: return std::make_unique<LoadAIntoAddressBC>();
            case opcodes::INCREMENT_BC: return std::make_unique<IncrementBC>();
            case opcodes::INCREMENT_B: return std::make_unique<IncrementB>();
            case opcodes::DECREMENT_B: return std::make_unique<DecrementB>();
            case opcodes::LOAD_IMMEDIATE_INTO_B: return std::make_unique<LoadImmediateIntoB>(fetch_byte());
            case opcodes::ROTATE_LEFT_CONTENTS_A_AND_CLEAR_ZERO: return std::make_unique<RotateLeftContentsA>();
            case opcodes::LOAD_SP_INTO_ADDRESS_IMMEDIATE: return std::make_unique<LoadSPIntoAddressImmediate>(fetch_word());
            case opcodes::ADD_HL_AND_BC: return std::make_unique<AddHLAndBC>();
            case opcodes::LOAD_ADDRESS_BC_INTO_A: return std::make_unique<LoadAddressBCIntoA>();
            case opcodes::DECREMENT_BC: return std::make_unique<DecrementBC>();
            case opcodes::INCREMENT_C: return std::make_unique<IncrementC>();
            case opcodes::DECREMENT_C: return std::make_unique<DecrementC>();
            case opcodes::LOAD_IMMEDIATE_INTO_C: return std::make_unique<LoadImmediateIntoC>(fetch_byte());
            case opcodes::ROTATE_RIGHT_CONTENTS_A: return std::make_unique<RotateRightContentsA>();
                /*
                case 0x0E:
                    instruction = "LD C, 0x" + to_string_hex(fetch_byte());
                    break;
                case 0x0F:
                    instruction = "RRC A";
                    break;
                */

            case opcodes::LOAD_IMMEDIATE_INTO_A: return std::make_unique<LoadImmediateIntoA>(fetch_byte());


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
    uint8_t read_byte() const
    {
        if (is_out_of_range())
        {
            throw std::out_of_range("Program counter pointing to position out of range.");
        }

        return *(_startOfByteCode + _programCounter);
    }

    // throws std::out_of_range if program counter out of range.
    // only increments program counter after reading if not out of range.
    uint8_t fetch_byte()
    {
        const uint8_t currentByte = read_byte();
        increment_program_counter();

        return currentByte;
    }

    // throws std::out_of_range if program counter out of range.
    // only increments program counter after reading if not out of range.
    // returns the value according to the word (LSB, MSB)
    // i.e. (0x34, 0x12) is mapped to the value 0x1234
    uint16_t fetch_word()
    {
        const uint8_t lsb = fetch_byte();
        const uint8_t msb = fetch_byte();

        return little_endian_to_number(lsb, msb); // note that evaluation order is not fixed in C++!
    }

    // throws std::out_of_range if program counter out of range.
    // only increments program counter after reading if not out of range.
    Opcode fetch_opcode()
    {
        uint16_t opcode = fetch_byte();

        // check if prefix
        if (opcode == 0xCB)
        {
            opcode = big_endian_to_number(0xCB, fetch_byte());
        }

        return opcode;
    }

private:
    uint8_t const * _startOfByteCode;
    uint16_t _sizeOfByteCode{0x0000};
    uint16_t _programCounter{0x0000};
};


#endif //GAMEBOY_DEBUG_DISASSEMBLER_H
