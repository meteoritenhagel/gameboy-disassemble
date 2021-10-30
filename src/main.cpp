#include <iostream>
#include <vector>

#include "assembler/assemble.h"
#include "assembler/tokenizer.h"
#include "assembler/parser.h"
#include "disassembler/decoder.h"
#include "disassembler/disassemble.h"

#include "assembler/pretty_format.h"

#include "assembler/unresolvedinstruction.h"

//void test_decoder()
//{
//    const Bytestring bytecode {0x00, 0x3E, 0xFF, 0x00, 0x00, 0x00};
//    disassemble(bytecode);
//}
//
//void test_decoder_eof()
//{
//    const Bytestring bytecode {0x00, 0x3E};
//    disassemble(bytecode);
//}
//
//void test_decoder_longer()
//{
//    const Bytestring bytecode {
//        0x00,
//        0x01, 0x34, 0x12,
//        0x02,
//        0x03,
//        0x04,
//        0x05,
//        0x06, 0xCC,
//        0x07,
//        0x08, 0x34, 0x12,
//        0x09,
//        0x0A,
//        0x0B,
//        0x0C,
//        0x0D,
//        0x0E, 0xCC,
//        0x0F,
//        0x8E};
//
//    disassemble(bytecode);
//}
//
//void test_decode_length()
//{
//    bool testPassed = true;
//    testPassed = (testPassed && decode_length(opcodes::JUMP) == 3);
//    testPassed = (testPassed && decode_length(opcodes::ADD_WITH_CARRY_A_AND_IMMEDIATE) == 2);
//    testPassed = (testPassed && decode_length(opcodes::LOAD_ADDRESS_IMMEDIATE_INTO_A) == 3);
//    testPassed = (testPassed && decode_length(opcodes::NOP) == 1);
//
//    std::cout << ((testPassed) ? "Test Passed!" : "Test FAILED!") << '\n';
//}
//
//void test_tokenizer_1()
//{
//    std::string code = std::string("LD (HL), A ;abc abcde\n") +
//                       "LD (HL), 12\n" +
//                       "LD (HL), 0xABCDD\n" +
//                       "JR -0x04\n" +
//                       "oh no, second line!!!!";
//
//    Tokenizer tokenizer(code);
//
//    while (!tokenizer.is_finished())
//    {
//        try
//        {
//            std::cout << to_pretty_string(tokenizer.get_next_token());
//        }
//        catch (std::exception &e)
//        {
//            std::cerr << e.what() << std::endl;
//        }
//    }
//}

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

//    std::string code(
//                     "LABEL1:\n"
//                     "X EQU 0x20\n"
//                     "I EQU 2\n"
//                     "LABEL2:\n"
//                     "add A, 0x01\n"
//                     "add A, 0x01\n"
//                     "LABEL3:\n"
//                     "add A, I\n"
//                     "add A, X\n"
//                     "bit I, A\n"
//                     "JP LABEL3\n"
//                     );

    std::string code(
                     "CONSTANT1 EQU 1\n"
                     "CONSTANT2 EQU 2\n"
                     "CONSTANT3 EQU 0xFFFFF\n"
                     "LABEL1:\n"
                     "DEC HL\n"
                     "JP LABEL1\n"
                     "JP .localLabel\n"
                     "JP END\n"
                     ".localLabel\n"
                     "INC HL\n"
                     "ADD A, CONSTANT1\n"
                     "ADD A, CONSTANT2\n"
                     "END:\n"
                     "ADC 0x99\n"
                     //"ADC 0xFFFFF\n"
                     "ADC CONSTANT3\n"
                     "LD A, CONSTANT1\n"
                     "LD HL, SP+0x11\n"
                     );

    Tokenizer tokenizer(code);
    TokenVector tokenVector = tokenizer.tokenize();

    Parser parser(code, tokenVector);

    InstructionVector instructionVector = parser.parse();

//    while (!tokenizer.is_finished())
//    {
//        try {
//            std::cout << to_pretty_string(tokenizer.get_next_token()) << std::endl;
//        } catch(const std::exception &e) {
//            std::cerr << e.what() << '\n';
//        }
//    }

//    while (!parser.is_finished())
//    {
//        try {
//            auto InstrPtr = parser.parse_next_instruction();
//            assemble_instruction(*InstrPtr);
//            std::cout << '\n';
//            std::cout << "          " << InstrPtr->str() << std::endl;
//        }
//        catch (const std::exception &e)
//        {
//            std::cerr <<  e.what() << '\n';
//        }
//    }

    for (const auto &instPtr : instructionVector)
    {
        try {
            assemble_instruction(*instPtr);
            std::cout << '\n';
            std::cout << "          " << instPtr->str() << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cerr <<  e.what() << '\n';
        }
    }

//    assemble_instruction(AddWithCarryAAndImmediate(0x20));

    return 0;
}