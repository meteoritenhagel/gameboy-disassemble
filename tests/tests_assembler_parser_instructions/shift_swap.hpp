#include "../../src/assembler/parser.h"

TEST_CASE("'SLA' commands are parsed correctly", "[Parser::parse]") {
    TokenVector tokenVector{
            {1, 1, TokenType::IDENTIFIER,  "SLA"},
            {1, 1, TokenType::IDENTIFIER,  "B"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
    };
    Parser parser("", tokenVector);
    InstructionVector instructionVector = parser.parse();

    REQUIRE(instructionVector.size() == 1);

    const BaseInstruction currentInstruction = *instructionVector[0];
    const BaseInstruction correctInstruction = ShiftLeftArithmetical8BitRegister(Register8Bit::B);
    REQUIRE(currentInstruction == correctInstruction);
}

TEST_CASE("'SRA' commands are parsed correctly", "[Parser::parse]") {
    TokenVector tokenVector{
            {1, 1, TokenType::IDENTIFIER,  "SRA"},
            {1, 1, TokenType::IDENTIFIER,  "C"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
    };
    Parser parser("", tokenVector);
    InstructionVector instructionVector = parser.parse();

    REQUIRE(instructionVector.size() == 1);

    const BaseInstruction currentInstruction = *instructionVector[0];
    const BaseInstruction correctInstruction = ShiftRightArithmetical8BitRegister(Register8Bit::C);
    REQUIRE(currentInstruction == correctInstruction);
}

TEST_CASE("'SRL' commands are parsed correctly", "[Parser::parse]") {
    TokenVector tokenVector{
            {1, 1, TokenType::IDENTIFIER,  "SRL"},
            {1, 1, TokenType::IDENTIFIER,  "(HL)"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
    };
    Parser parser("", tokenVector);
    InstructionVector instructionVector = parser.parse();

    REQUIRE(instructionVector.size() == 1);

    const BaseInstruction currentInstruction = *instructionVector[0];
    const BaseInstruction correctInstruction = ShiftRightLogical8BitRegister(Register8Bit::ADDRESS_HL);
    REQUIRE(currentInstruction == correctInstruction);
}

TEST_CASE("'SWAP' commands are parsed correctly", "[Parser::parse]") {
    TokenVector tokenVector{
            {1, 1, TokenType::IDENTIFIER,  "SWAP"},
            {1, 1, TokenType::IDENTIFIER,  "E"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
    };
    Parser parser("", tokenVector);
    InstructionVector instructionVector = parser.parse();

    REQUIRE(instructionVector.size() == 1);

    const BaseInstruction currentInstruction = *instructionVector[0];
    const BaseInstruction correctInstruction = Swap8BitRegister(Register8Bit::E);
    REQUIRE(currentInstruction == correctInstruction);
}