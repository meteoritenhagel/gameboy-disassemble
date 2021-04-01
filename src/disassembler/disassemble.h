#ifndef GAMEBOY_DISASSEMBLE_DISASSEMBLE_H
#define GAMEBOY_DISASSEMBLE_DISASSEMBLE_H

#include "../instructions/instructions.h"
#include "decoder.h"


/**
 * Given an opcode @p opcode, decode the number of bytes (including the opcode) the whole instruction has.
 * @param opcode opcode
 * @return length in bytes of instruction corresponding to opcode
 */
unsigned decode_length(const Opcode opcode);

/**
 * Disassembles bytecode and prints it to @p ostr
 * @param bytecode bytecode
 * @param ostr output stream
 */
void disassemble(const Bytestring& bytecode, std::ostream &ostr = std::cout);

/**
 * Disassembles single instruction and returns it as string
 * @param decoderOutput output of decoder, consisting of a word containing the address and the pointer to the
 *        disassembled instruction.
 * @return disassembled instruction
 */
std::string disassemble_instruction(const std::pair<word, InstructionPtr> &decoderOutput);


#endif //GAMEBOY_DISASSEMBLE_DISASSEMBLE_H
