#include <iostream>
#include <vector>

#include "disassembler.h"

void test1()
{
    const std::vector<uint8_t> byteCode{0x00, 0x3E, 0xFF, 0x00, 0x00, 0x00};
    uint8_t const * const startOfByteCode = byteCode.data();

    Disassembler disassembler(startOfByteCode, byteCode.size());

    for (unsigned i = 0; i < 8; ++i)
        std::cout << disassembler.disassemble() << std::endl;
}

void test_eof()
{
    const std::vector<uint8_t> byteCode{0x00, 0x3E};
    uint8_t const * const startOfByteCode = byteCode.data();

    Disassembler disassembler(startOfByteCode, byteCode.size());

    for (unsigned i = 0; i < 2; ++i)
        std::cout << disassembler.disassemble() << std::endl;
}

int main()
{
    const std::vector<uint8_t> byteCode{0x00, 0x3E, 0xFF, 0x3E};
    uint8_t const * const startOfByteCode = byteCode.data();

    Disassembler disassembler(startOfByteCode, byteCode.size());

    for (unsigned i = 0; i < 8; ++i)
        std::cout << disassembler.disassemble() << std::endl;

    return 0;
}