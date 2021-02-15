#ifndef GAMEBOY_DEBUG_DISASSEMBLER_H
#define GAMEBOY_DEBUG_DISASSEMBLER_H

#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <string>

#include "instructions.h"

class Disassembler
{
public:
    Disassembler(uint8_t const * const startOfByteCode, const uint16_t sizeOfByteCode)
            :_startOfByteCode{startOfByteCode}, _sizeOfByteCode{sizeOfByteCode}
    {}

    std::string disassemble()
    {
        std::string displayedText;
        uint8_t opcode = 0;

        try // to get opcode
        {
            displayedText += "0x" + to_string_hex(_programCounter, 4);

            opcode = fetch();
            displayedText += " : " "[0x" + to_string_hex(opcode) + "] ";

            displayedText += decode(opcode).str();
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
            case Nop::OPCODE: return std::make_unique<Nop>();

                /*
                case 0x01:
                {
                    const uint8_t lsb = fetch();
                    const uint8_t msb = fetch();
                    instruction = "LD BC, 0x" + to_string_hex(msb) + to_string_hex(lsb);
                    break;
                }
                case 0x02:
                    instruction = "LD (BC), A";
                    break;
                case 0x03:
                    instruction = "INC BC";
                    break;
                case 0x04:
                    instruction = "INC B";
                    break;
                case 0x05:
                    instruction = "DEC B";
                    break;
                case 0x06:
                    instruction = "LD B, 0x" + to_string_hex(fetch());
                    break;
                case 0x07:
                    instruction = "RLC A";
                    break;
                case 0x08:
                {
                    const uint8_t lsb = fetch();
                    const uint8_t msb = fetch();
                    instruction = "LD (0x" + to_string_hex(msb) + to_string_hex(lsb) + "), SP";
                    break;
                }
                case 0x09:
                    instruction = "ADD HL, BC";
                    break;
                case 0x0A:
                    instruction = "LD A, (BC)";
                    break;
                case 0x0B:
                    instruction = "DEC BC";
                    break;
                case 0x0C:
                    instruction = "INC C";
                    break;
                case 0x0D:
                    instruction = "DEC C";
                    break;
                case 0x0E:
                    instruction = "LD C, 0x" + to_string_hex(fetch());
                    break;
                case 0x0F:
                    instruction = "RRC A";
                    break;
                */

            case LoadImmediateA::OPCODE: return std::make_unique<LoadImmediateA>(fetch());


            default: return std::make_unique<Unknown>();

        }
        return instruction;
    }

private:

    void increment_program_counter()
    {
        if (!is_out_of_range())
        {
            ++_programCounter;
        }
    }

    bool is_out_of_range() const
    {
        return (_programCounter >= _sizeOfByteCode);
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
    uint8_t fetch()
    {
        const uint8_t currentByte = read_byte();
        increment_program_counter();

        return currentByte;
    }

private:
    uint8_t const * _startOfByteCode;
    uint16_t _sizeOfByteCode{0x0000};
    uint16_t _programCounter{0x0000};
};


#endif //GAMEBOY_DEBUG_DISASSEMBLER_H
