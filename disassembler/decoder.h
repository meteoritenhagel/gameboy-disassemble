#ifndef GAMEBOY_DEBUG_DISASSEMBLER_H
#define GAMEBOY_DEBUG_DISASSEMBLER_H

#include <iomanip>
#include <stdexcept>

#include "../instructions/instructions.h"

class Decoder;

unsigned decode_length(const Opcode opcode);

class Decoder
{
public:
    Decoder(const Bytestring& bytecode, const word entryPoint = 0x0000);

    bool is_out_of_range() const noexcept;

    size_t get_size() const;

    word get_current_position() const;

    // throws std::out_of_range if program counter is out of range.
    std::pair<word, InstructionPtr> decode();

private:

    void increment_program_counter();

    // throws std::out_of_range if program counter is out of range.
    byte read_byte() const;

    // throws std::out_of_range if program counter is out of range.
    // only increments program counter after reading if not out of range.
    byte fetch_byte();

    // throws std::out_of_range if program counter out of range.
    // only increments program counter after reading if not out of range.
    // returns the value according to the word (LSB, MSB)
    // i.e. (0x34, 0x12) is mapped to the value 0x1234
    word fetch_word();

    // throws std::out_of_range if program counter is out of range.
    // only increments program counter after reading if not out of range.
    Opcode fetch_opcode();

    InstructionPtr decode_opcode(const Opcode opcode);

private:
    const Bytestring& _bytecode;
    word _programCounter{0x0000};
};

#endif //GAMEBOY_DEBUG_DISASSEMBLER_H
