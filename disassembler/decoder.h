#ifndef GAMEBOY_DEBUG_DISASSEMBLER_H
#define GAMEBOY_DEBUG_DISASSEMBLER_H

#include <iomanip>
#include <stdexcept>

#include "../instructions/instructions.h"

class Decoder
{
public:
    Decoder(byte const * const startOfByteCode, const word sizeOfByteCode)
            :_startOfByteCode{startOfByteCode}, _sizeOfByteCode{sizeOfByteCode}
    {}

    bool is_out_of_range() const
    {
        return (_programCounter >= _sizeOfByteCode);
    }

    std::string disassemble() // TODO: own class
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

    // throws std::out_of_range if program counter is out of range.
    InstructionPtr decode(Opcode opcode);

private:

    void increment_program_counter()
    {
        if (!is_out_of_range())
        {
            ++_programCounter;
        }
    }

    // throws std::out_of_range if program counter is out of range.
    byte read_byte() const
    {
        if (is_out_of_range())
        {
            throw std::out_of_range("Program counter pointing to position out of range.");
        }

        return *(_startOfByteCode + _programCounter);
    }

    // throws std::out_of_range if program counter is out of range.
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
