#include "../../src/assembler/parser.h"

TEST_CASE("'INC' commands are parsed correctly", "[Parser::parse]") {
    SECTION("INC 8-bit register") {
        TokenVector tokenVector {
                {1, 1, TokenType::IDENTIFIER, "INC"},
                {1, 1, TokenType::IDENTIFIER, "B"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = IncrementRegister(Register8Bit::B);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("INC 16-bit register") {
        TokenVector tokenVector {
                {1, 1, TokenType::IDENTIFIER, "INC"},
                {1, 1, TokenType::IDENTIFIER, "HL"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = IncrementRegister(Register16Bit::HL);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("INC AF is invalid command") {
        TokenVector tokenVector {
                {1, 1, TokenType::IDENTIFIER, "INC"},
                {1, 1, TokenType::IDENTIFIER, "AF"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        REQUIRE_THROWS(parser.parse());
    }
}

TEST_CASE("'DEC' commands are parsed correctly", "[Parser::parse]") {
    SECTION("DEC 8-bit register") {
        TokenVector tokenVector {
                {1, 1, TokenType::IDENTIFIER, "DEC"},
                {1, 1, TokenType::IDENTIFIER, "B"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = DecrementRegister(Register8Bit::B);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("DEC 16-bit register") {
        TokenVector tokenVector {
                {1, 1, TokenType::IDENTIFIER, "DEC"},
                {1, 1, TokenType::IDENTIFIER, "HL"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = DecrementRegister(Register16Bit::HL);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("DEC AF is invalid command") {
        TokenVector tokenVector {
                {1, 1, TokenType::IDENTIFIER, "DEC"},
                {1, 1, TokenType::IDENTIFIER, "AF"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        REQUIRE_THROWS(parser.parse());
    }
}