#include "../../src/assembler/parser.h"

TEST_CASE("'NOP' command is parsed correctly", "[Parser::parse]") {
    TokenVector tokenVector{
            {1, 1, TokenType::IDENTIFIER,  "NOP"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
    };
    Parser parser("", tokenVector);
    InstructionVector instructionVector = parser.parse();

    REQUIRE(instructionVector.size() == 1);

    const BaseInstruction currentInstruction = *instructionVector[0];
    const BaseInstruction correctInstruction = Nop();
    REQUIRE(currentInstruction == correctInstruction);
}

TEST_CASE("'STOP' command is parsed correctly", "[Parser::parse]") {
    TokenVector tokenVector{
            {1, 1, TokenType::IDENTIFIER,  "STOP"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
    };
    Parser parser("", tokenVector);
    InstructionVector instructionVector = parser.parse();

    REQUIRE(instructionVector.size() == 1);

    const BaseInstruction currentInstruction = *instructionVector[0];
    const BaseInstruction correctInstruction = Stop();
    REQUIRE(currentInstruction == correctInstruction);
}

TEST_CASE("'HALT' command is parsed correctly", "[Parser::parse]") {
    TokenVector tokenVector{
            {1, 1, TokenType::IDENTIFIER,  "HALT"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
    };
    Parser parser("", tokenVector);
    InstructionVector instructionVector = parser.parse();

    REQUIRE(instructionVector.size() == 1);

    const BaseInstruction currentInstruction = *instructionVector[0];
    const BaseInstruction correctInstruction = Halt();
    REQUIRE(currentInstruction == correctInstruction);
}

TEST_CASE("'SCF' command is parsed correctly", "[Parser::parse]") {
    TokenVector tokenVector{
            {1, 1, TokenType::IDENTIFIER,  "SCF"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
    };
    Parser parser("", tokenVector);
    InstructionVector instructionVector = parser.parse();

    REQUIRE(instructionVector.size() == 1);

    const BaseInstruction currentInstruction = *instructionVector[0];
    const BaseInstruction correctInstruction = SetCarry();
    REQUIRE(currentInstruction == correctInstruction);
}

TEST_CASE("'CCF' command is parsed correctly", "[Parser::parse]") {
    TokenVector tokenVector{
            {1, 1, TokenType::IDENTIFIER,  "CCF"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
    };
    Parser parser("", tokenVector);
    InstructionVector instructionVector = parser.parse();

    REQUIRE(instructionVector.size() == 1);

    const BaseInstruction currentInstruction = *instructionVector[0];
    const BaseInstruction correctInstruction = FlipCarry();
    REQUIRE(currentInstruction == correctInstruction);
}

TEST_CASE("'EI' command is parsed correctly", "[Parser::parse]") {
    TokenVector tokenVector{
            {1, 1, TokenType::IDENTIFIER,  "EI"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
    };
    Parser parser("", tokenVector);
    InstructionVector instructionVector = parser.parse();

    REQUIRE(instructionVector.size() == 1);

    const BaseInstruction currentInstruction = *instructionVector[0];
    const BaseInstruction correctInstruction = EnableInterrupts();
    REQUIRE(currentInstruction == correctInstruction);
}

TEST_CASE("'DI' command is parsed correctly", "[Parser::parse]") {
    TokenVector tokenVector{
            {1, 1, TokenType::IDENTIFIER,  "DI"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
    };
    Parser parser("", tokenVector);
    InstructionVector instructionVector = parser.parse();

    REQUIRE(instructionVector.size() == 1);

    const BaseInstruction currentInstruction = *instructionVector[0];
    const BaseInstruction correctInstruction = DisableInterrupts();
    REQUIRE(currentInstruction == correctInstruction);
}