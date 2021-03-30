#include "disassemble.h"

void disassemble(const Bytestring &bytecode, std::ostream &ostr) {
    Decoder decoder(bytecode);

    while (!decoder.is_out_of_range())
        ostr << disassemble_instruction(decoder.decode()) << std::endl;
}

std::string disassemble_instruction(const std::pair<word, InstructionPtr> &decoderOutput) {
    const word opcodePosition = decoderOutput.first;
    const Instruction instruction = *decoderOutput.second;
    const Opcode opcode = instruction.opcode();

    std::string displayedText;

    displayedText += "0x" + to_string_hex(opcodePosition);

    displayedText += " : " "[0x" + to_string_hex(opcode, 2) + "] ";
    displayedText += instruction.str();

    return displayedText;
}
