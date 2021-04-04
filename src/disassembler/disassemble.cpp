#include "disassemble.h"

unsigned decode_length(const Opcode opcode) {
    constexpr size_t maxInstructionLength = 4;
    Bytestring bytecode(maxInstructionLength, 0x00);

    const Bytestring opc = opcode_to_bytestring(opcode);
    std::copy(std::begin(opc), std::end(opc), std::begin(bytecode));

    Decoder decoder(bytecode);

    // calculate number of bytes read_current
    const auto [address, decodedInstruction] = decoder.decode();

    return decodedInstruction->length();
}

void disassemble(const Bytestring &bytecode, std::ostream &ostr) {
    Decoder decoder(bytecode);

    while (!decoder.is_out_of_range())
        ostr << disassemble_instruction(decoder.decode()) << std::endl;
}

std::string disassemble_instruction(const std::pair<word, InstructionPtr> &decoderOutput) {
    const word opcodePosition = decoderOutput.first;
    const BaseInstruction instruction = *decoderOutput.second;
    const Opcode opcode = instruction.opcode();

    std::string displayedText;

    displayedText += "0x" + to_string_hex(opcodePosition);

    displayedText += " : " "[0x" + to_string_hex(opcode, 2) + "] ";
    displayedText += instruction.str();

    return displayedText;
}
