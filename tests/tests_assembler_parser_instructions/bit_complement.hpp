#include "../../src/assembler/parser.h"

TEST_CASE("'BIT' commands are parsed correctly", "[Parser::parse]") {
    SECTION("BIT 0, B") {
        TokenVector tokenVector {
                {1, 1, TokenType::IDENTIFIER, "BIT"},
                {1, 1, TokenType::NUMBER, "0"},
                {1, 1, TokenType::COMMA, ","},
                {1, 1, TokenType::IDENTIFIER, "B"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = BitOf8BitRegisterComplementIntoZero(0, Register8Bit::B);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("BIT 7, C") {
        TokenVector tokenVector {
                {1, 1, TokenType::IDENTIFIER, "BIT"},
                {1, 1, TokenType::NUMBER, "7"},
                {1, 1, TokenType::COMMA, ","},
                {1, 1, TokenType::IDENTIFIER, "C"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = BitOf8BitRegisterComplementIntoZero(7, Register8Bit::C);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("Invalid: BIT 8, C") {
        TokenVector tokenVector {
                {1, 1, TokenType::IDENTIFIER, "BIT"},
                {1, 1, TokenType::NUMBER, "8"},
                {1, 1, TokenType::COMMA, ","},
                {1, 1, TokenType::IDENTIFIER, "C"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);

        REQUIRE_THROWS_AS(parser.parse(), std::logic_error);
    }
}