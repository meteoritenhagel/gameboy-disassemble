#include <iostream>
#include <vector>

#include "assembler/tokenizer.h"
#include "disassembler/decoder.h"
#include "disassembler/disassemble.h"

void test_decoder()
{
    const Bytestring bytecode {0x00, 0x3E, 0xFF, 0x00, 0x00, 0x00};
    Decoder decoder(bytecode);

    while (!decoder.is_out_of_range())
        std::cout << decoder.decode().second->str() << std::endl;


}

void test_decoder_eof()
{
    const Bytestring bytecode {0x00, 0x3E};
    Decoder decoder(bytecode);

    while (!decoder.is_out_of_range())
        std::cout << decoder.decode().second->str() << std::endl;


}

void test_decoder_longer()
{
    const Bytestring bytecode {
        0x00,
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
        0x0F,
        0x8E};

    Decoder decoder(bytecode);

    while (!decoder.is_out_of_range())
        std::cout << decoder.decode().second->str() << std::endl;

}

void test_decode_length()
{
    bool testPassed = true;
    testPassed = (testPassed && decode_length(opcodes::JUMP) == 3);
    testPassed = (testPassed && decode_length(opcodes::ADD_WITH_CARRY_A_AND_IMMEDIATE) == 2);
    testPassed = (testPassed && decode_length(opcodes::LOAD_ADDRESS_IMMEDIATE_INTO_A) == 3);
    testPassed = (testPassed && decode_length(opcodes::NOP) == 1);

    std::cout << ((testPassed) ? "Test Passed!" : "Test FAILED!") << '\n';
}

void test_tokenizer_1()
{
    std::string code = std::string("LD (HL), A ;abc abcde\n") +
                       "LD (HL), 12\n" +
                       "LD (HL), 0xABCDD\n" +
                       "JR -0x04\n" +
                       "oh no, second line!!!!";

    Tokenizer tokenizer(code);


    while (!tokenizer.is_out_of_range())
    {
        try
        {
            tokenizer.get_next_token().print();
        }
        catch (std::exception &e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
}

#include <string>
int main()
{
    const Bytestring bytecode {
            0x00,
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
            0x0F,
            0x8E};

    disassemble(bytecode);

    return 0;
}