#include "assemble.h"

void assemble_instruction(const Instruction instruction) {
    for (const byte bte : instruction.bytestr())
    {
        std::cout << to_string_hex_prefixed(bte) << " ";
    }

}
