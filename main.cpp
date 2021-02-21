#include <iostream>
#include <vector>

#include "assembler.h"
#include "disassembler.h"

void test_disassembler()
{
    const std::vector<byte> byteCode{0x00, 0x3E, 0xFF, 0x00, 0x00, 0x00};
    byte const * const startOfByteCode = byteCode.data();

    Disassembler disassembler(startOfByteCode, byteCode.size());

    for (unsigned i = 0; i < 8; ++i)
        std::cout << disassembler.disassemble() << std::endl;
}

void test_disassembler_eof()
{
    const std::vector<byte> byteCode{0x00, 0x3E};
    byte const * const startOfByteCode = byteCode.data();

    Disassembler disassembler(startOfByteCode, byteCode.size());

    for (unsigned i = 0; i < 2; ++i)
        std::cout << disassembler.disassemble() << std::endl;
}

void test_disassembler_longer()
{
    const std::vector<byte> byteCode{0x00,
                                     0x01, 0x34, 0x12,
                                     0x02,
                                     0x03,
                                     0x04,
                                     0x05,
                                     0x06, 0xCC,
                                     0x07,
                                     0x08, 0x34, 0x12,
                                     0x09,
                                     0x0A,
                                     0x0B,
                                     0x0C,
                                     0x0D,
                                     0x0E, 0xCC,
                                     0x0F,};
    byte const * const startOfByteCode = byteCode.data();

    Disassembler disassembler(startOfByteCode, byteCode.size());

    while (!disassembler.is_out_of_range())
        std::cout << disassembler.disassemble() << std::endl;
}

int main()
{
    std::string line = "LD (HL), A ;abc abcde\noh no, second line!";

    auto vec = tokenize_line(line);
    print_vector_of_tokens(vec);

    return 0;
}