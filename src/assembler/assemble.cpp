#include "assemble.h"

void assemble_instruction(const BaseInstruction instruction) {
    for (const byte bte : instruction.bytestr())
    {
        std::cout << to_string_hex_prefixed(bte) << " ";
    }

}
