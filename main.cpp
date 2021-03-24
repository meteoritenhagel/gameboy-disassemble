#include <iostream>
#include <vector>

#include "assembler/assemble.h"
#include "assembler/tokenizer.h"
#include "assembler/parser.h"
#include "disassembler/decoder.h"
#include "disassembler/disassemble.h"

#include "assembler/print_code.h"

void test_decoder()
{
    const Bytestring bytecode {0x00, 0x3E, 0xFF, 0x00, 0x00, 0x00};
    disassemble(bytecode);
}

void test_decoder_eof()
{
    const Bytestring bytecode {0x00, 0x3E};
    disassemble(bytecode);
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

    disassemble(bytecode);
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

    while (!tokenizer.is_finished())
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
//    const Bytestring bytecode{
//                0x00,
//    /*loop:*/   0x00,
//                0x00,
//                0x00,
//                0x00,
//                0xC3, 0x01, 0x00, // JP loop
//    };
//
//    disassemble(bytecode);

    std::string code("ADD A, A\n"
                     "ADD A, B\n"
                     "ADD A, C\n"
                     "ADD A, (HL)\n"
                     //"ADD A, X\n"
                     //"ADD B, H\n"
                     //"ADD B, A\n"
                     //"ADC A\n"
                     "ADD A, A\n"
                     "ADD SP, -200\n"
                     "ADD HL, BC"
                     );

//    std::string code("ADC A, A\n"
//                     "ADC A, 0x20\n"
//                     "ADC A, C\n"
//                     "ADC A, (HL)\n     \n \n"
//                     );

//    std::string code(//"ADC A, (HL)\n"
////                     "ADC A, 0x20\n"
////                     "ADC A, C\n"
////                     "ADC A, (HL)\n"
////                     "ADD A, (HL)\n"
////                     "BIT 0, A\n"
////                     "BIT 7, (HL)\n"
////                     "BIT 0, B\n"
////                     "BIT 3, C\n"
//                     //"BIT /, L"
//                     );

    Tokenizer tokenizer(code);

//    while (!tokenizer.is_finished())
//    {
//        try {
//            tokenizer.get_next_token().print();
//        } catch(const std::exception &e) {
//            std::cerr << e.what() << '\n';
//        }
//    }


    Parser parser(tokenizer);
    while (!parser.is_finished())
    {
        try {
            auto InstrPtr = parser.parse_next_instruction();
            assemble_instruction(*InstrPtr);
            std::cout << '\n';
            //std::cout << "          " << InstrPtr->str() << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cerr <<  e.what() << '\n';
        }
    }

//    assemble_instruction(AddWithCarryAAndImmediate(0x20));

    return 0;
}