#ifndef GAMEBOY_DEBUG_DISASSEMBLER_H
#define GAMEBOY_DEBUG_DISASSEMBLER_H

#include <iomanip>
#include <stdexcept>

#include "../instructions/instructions.h"

class Decoder;

/**
 * Given an opcode @p opcode, decode the number of bytes (including the opcode) the whole instruction has.
 * @param opcode opcode
 * @return length in bytes of instruction corresponding to opcode
 */
unsigned decode_length(const Opcode opcode);

/**
 * Class Decoder. Given a bytestring, it decodes it and returns the instructions one by one.
 */
class Decoder
{
public:
    /**
     * Constructor.
     * @param bytecode bytecode to decode
     * @param entryPoint entry point address, i.e. address at which the decoding starts
     */
    Decoder(const Bytestring& bytecode, const word entryPoint = 0x0000);

    /**
     * Checks whether the internal program counter points to an address outside of valid code.
     * @return true if out of range
     */
    bool is_out_of_range() const noexcept;

    /**
     * Returns the bytecode's size in bytes.
     * @return
     */
    size_t get_size() const noexcept;

    /**
     * Returns current position of internal program counter
     * @return current position
     */
    word get_current_position() const noexcept;

    // throws std::out_of_range if program counter is out of range.
    /**
     * Decodes an instruction and returns the address and the pointer to the instruction as a std::pair.
     * @return address/instruction
     */
    std::pair<word, InstructionPtr> decode();

private:

    /**
     * Increments the program counter if not out of range.
     */
    void increment_program_counter() noexcept;

    /**
     * Reads the current byte.
     * @throws std::out_of_range if out of range
     * @return the current byte
     */
    byte read_byte() const;


    /**
     * Reads the current byte and increments the program counter if possible.
     * @throws std::out_of_range if out of range
     * @return the current byte
     */
    byte fetch_byte();

    /**
     * Fetches two bytes, interprets them as little endian and returns the number
     * E.g. when (0x34, 0x12) are fetched, the output value is 0x1234.
     * @throws std::out_of_range if out of range
     * @return little endian representation of the two fetched bytes.
     */
    word fetch_word();

    /**
     * Fetches two bytes, interprets them as opcode (i.e. big endian) and returns it
     * E.g. when (0xCB, 0x12) are fetched, the output value is 0xCB12.
     * @throws std::out_of_range if out of range
     * @return opcode.
     */
    Opcode fetch_opcode();

    /**
     * Decodes the opcode by fetching the needed amount of bytes and returns a pointer to the instruction.
     * @throws std::out_of_range if out of range
     * @param opcode opcode to decode
     * @return pointer to instruction
     */
    InstructionPtr decode_opcode(const Opcode opcode);

private:
    const Bytestring& _bytecode; ///< bytecode to decode
    word _programCounter{0x0000}; ///< program counter, i.e. current position in bytecode
};

#endif //GAMEBOY_DEBUG_DISASSEMBLER_H
