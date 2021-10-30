#include "../../src/assembler/parser.h"

TEST_CASE("'RR' commands are parsed correctly", "[Parser::parse]") {
    TokenVector tokenVector{
            {1, 1, TokenType::IDENTIFIER,  "RR"},
            {1, 1, TokenType::IDENTIFIER,  "B"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
    };
    Parser parser("", tokenVector);
    InstructionVector instructionVector = parser.parse();

    REQUIRE(instructionVector.size() == 1);

    const BaseInstruction currentInstruction = *instructionVector[0];
    const BaseInstruction correctInstruction = RotateRight8BitRegister(Register8Bit::B);
    REQUIRE(currentInstruction == correctInstruction);
}

TEST_CASE("'RL' commands are parsed correctly", "[Parser::parse]") {
    TokenVector tokenVector{
            {1, 1, TokenType::IDENTIFIER,  "RL"},
            {1, 1, TokenType::IDENTIFIER,  "A"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
    };
    Parser parser("", tokenVector);
    InstructionVector instructionVector = parser.parse();

    REQUIRE(instructionVector.size() == 1);

    const BaseInstruction currentInstruction = *instructionVector[0];
    const BaseInstruction correctInstruction = RotateLeft8BitRegister(Register8Bit::A);
    REQUIRE(currentInstruction == correctInstruction);
}

TEST_CASE("'RRC' commands are parsed correctly", "[Parser::parse]") {
    TokenVector tokenVector{
            {1, 1, TokenType::IDENTIFIER,  "RRC"},
            {1, 1, TokenType::IDENTIFIER,  "H"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
    };
    Parser parser("", tokenVector);
    InstructionVector instructionVector = parser.parse();

    REQUIRE(instructionVector.size() == 1);

    const BaseInstruction currentInstruction = *instructionVector[0];
    const BaseInstruction correctInstruction = RotateRightCircular8BitRegister(Register8Bit::H);
    REQUIRE(currentInstruction == correctInstruction);
}

TEST_CASE("'RLC' commands are parsed correctly", "[Parser::parse]") {
    TokenVector tokenVector{
            {1, 1, TokenType::IDENTIFIER,  "RLC"},
            {1, 1, TokenType::IDENTIFIER,  "L"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
    };
    Parser parser("", tokenVector);
    InstructionVector instructionVector = parser.parse();

    REQUIRE(instructionVector.size() == 1);

    const BaseInstruction currentInstruction = *instructionVector[0];
    const BaseInstruction correctInstruction = RotateRightCircular8BitRegister(Register8Bit::L);
    REQUIRE(currentInstruction == correctInstruction);
}

TEST_CASE("'RLA' command is parsed correctly", "[Parser::parse]") {
    TokenVector tokenVector{
            {1, 1, TokenType::IDENTIFIER,  "RLA"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
    };
    Parser parser("", tokenVector);
    InstructionVector instructionVector = parser.parse();

    REQUIRE(instructionVector.size() == 1);

    const BaseInstruction currentInstruction = *instructionVector[0];
    const BaseInstruction correctInstruction = RotateLeftAAndClearZero();
    REQUIRE(currentInstruction == correctInstruction);
}

TEST_CASE("'RRA' command is parsed correctly", "[Parser::parse]") {
    TokenVector tokenVector{
            {1, 1, TokenType::IDENTIFIER,  "RRA"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
    };
    Parser parser("", tokenVector);
    InstructionVector instructionVector = parser.parse();

    REQUIRE(instructionVector.size() == 1);

    const BaseInstruction currentInstruction = *instructionVector[0];
    const BaseInstruction correctInstruction = RotateRightAAndClearZero();
    REQUIRE(currentInstruction == correctInstruction);
}

TEST_CASE("'RLCA' command is parsed correctly", "[Parser::parse]") {
    TokenVector tokenVector{
            {1, 1, TokenType::IDENTIFIER,  "RLCA"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
    };
    Parser parser("", tokenVector);
    InstructionVector instructionVector = parser.parse();

    REQUIRE(instructionVector.size() == 1);

    const BaseInstruction currentInstruction = *instructionVector[0];
    const BaseInstruction correctInstruction = RotateLeftCircularAAndClearZero();
    REQUIRE(currentInstruction == correctInstruction);
}

TEST_CASE("'RRCA' command is parsed correctly", "[Parser::parse]") {
    TokenVector tokenVector{
            {1, 1, TokenType::IDENTIFIER,  "RRCA"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
    };
    Parser parser("", tokenVector);
    InstructionVector instructionVector = parser.parse();

    REQUIRE(instructionVector.size() == 1);

    const BaseInstruction currentInstruction = *instructionVector[0];
    const BaseInstruction correctInstruction = RotateRightCircularAAndClearZero();
    REQUIRE(currentInstruction == correctInstruction);
}