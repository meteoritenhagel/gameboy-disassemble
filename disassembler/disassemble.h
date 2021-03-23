#ifndef GAMEBOY_DISASSEMBLE_DISASSEMBLE_H
#define GAMEBOY_DISASSEMBLE_DISASSEMBLE_H

#include "../instructions/instructions.h"
#include "decoder.h"

void disassemble(const Bytestring& code, std::ostream &ostr = std::cout);

std::string disassemble_instruction(const std::pair<word, InstructionPtr> &decoderOutput);


#endif //GAMEBOY_DISASSEMBLE_DISASSEMBLE_H
