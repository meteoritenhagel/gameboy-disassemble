#include "../../src/assembler/parser.h"

#include "../../src/assembler/parser.h"

TEST_CASE("'SUB' commands are parsed correctly", "[Parser::parse]") {
    SECTION("SUB A and 8-bit register: long form") {
        TokenVector tokenVector{
                {1, 1, TokenType::IDENTIFIER,  "SUB"},
                {1, 1, TokenType::IDENTIFIER,  "A"},
                {1, 1, TokenType::COMMA,       ","},
                {1, 1, TokenType::IDENTIFIER,  "B"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = SubtractAAnd8BitRegister(Register8Bit::B);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("SUB A and 8-bit register: short form") {
        TokenVector tokenVector{
                {1, 1, TokenType::IDENTIFIER,  "SUB"},
                {1, 1, TokenType::IDENTIFIER,  "B"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = SubtractAAnd8BitRegister(Register8Bit::B);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("SUB A and immediate: long form") {
        TokenVector tokenVector{
                {1, 1, TokenType::IDENTIFIER,  "SUB"},
                {1, 1, TokenType::IDENTIFIER,  "A"},
                {1, 1, TokenType::COMMA,       ","},
                {1, 1, TokenType::NUMBER,      "0x01"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = SubtractAAndImmediate(0x01);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("SUB A and immediate: short form") {
        TokenVector tokenVector{
                {1, 1, TokenType::IDENTIFIER,  "SUB"},
                {1, 1, TokenType::NUMBER,      "0x01"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = SubtractAAndImmediate(0x01);
        REQUIRE(currentInstruction == correctInstruction);
    }
}

TEST_CASE("'SBC' commands are parsed correctly", "[Parser::parse]") {
    SECTION("SBC A and 8-bit register: long form") {
        TokenVector tokenVector{
                {1, 1, TokenType::IDENTIFIER,  "SBC"},
                {1, 1, TokenType::IDENTIFIER,  "A"},
                {1, 1, TokenType::COMMA,       ","},
                {1, 1, TokenType::IDENTIFIER,  "B"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = SubtractWithCarryAAnd8BitRegister(Register8Bit::B);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("SBC A and 8-bit register: short form") {
        TokenVector tokenVector{
                {1, 1, TokenType::IDENTIFIER,  "SBC"},
                {1, 1, TokenType::IDENTIFIER,  "B"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = SubtractWithCarryAAnd8BitRegister(Register8Bit::B);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("SBC A and immediate: long form") {
        TokenVector tokenVector{
                {1, 1, TokenType::IDENTIFIER,  "SBC"},
                {1, 1, TokenType::IDENTIFIER,  "A"},
                {1, 1, TokenType::COMMA,       ","},
                {1, 1, TokenType::NUMBER,      "0x01"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = SubtractWithCarryAAndImmediate(0x01);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("SBC A and immediate: short form") {
        TokenVector tokenVector{
                {1, 1, TokenType::IDENTIFIER,  "SBC"},
                {1, 1, TokenType::NUMBER,      "0x01"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = SubtractWithCarryAAndImmediate(0x01);
        REQUIRE(currentInstruction == correctInstruction);
    }
}