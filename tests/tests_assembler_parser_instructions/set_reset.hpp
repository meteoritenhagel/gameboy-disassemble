#include "../../src/assembler/parser.h"

TEST_CASE("'SET' commands are parsed correctly", "[Parser::parse]") {
    SECTION("SET 0, B") {
        TokenVector tokenVector {
                {1, 1, TokenType::IDENTIFIER, "SET"},
                {1, 1, TokenType::NUMBER, "0"},
                {1, 1, TokenType::COMMA, ","},
                {1, 1, TokenType::IDENTIFIER, "B"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = SetBitOf8BitRegister(0, Register8Bit::B);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("SET 7, C") {
        TokenVector tokenVector {
                {1, 1, TokenType::IDENTIFIER, "SET"},
                {1, 1, TokenType::NUMBER, "7"},
                {1, 1, TokenType::COMMA, ","},
                {1, 1, TokenType::IDENTIFIER, "C"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = SetBitOf8BitRegister(7, Register8Bit::C);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("Invalid: SET -1, C") {
        TokenVector tokenVector {
                {1, 1, TokenType::IDENTIFIER, "SET"},
                {1, 1, TokenType::NUMBER, "-1"},
                {1, 1, TokenType::COMMA, ","},
                {1, 1, TokenType::IDENTIFIER, "C"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);

        REQUIRE_THROWS_AS(parser.parse(), std::logic_error);
    }
}

TEST_CASE("'RES' commands are parsed correctly", "[Parser::parse]") {
    SECTION("RES 0, B") {
        TokenVector tokenVector {
                {1, 1, TokenType::IDENTIFIER, "RES"},
                {1, 1, TokenType::NUMBER, "0"},
                {1, 1, TokenType::COMMA, ","},
                {1, 1, TokenType::IDENTIFIER, "B"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = ResetBitOf8BitRegister(0, Register8Bit::B);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("RES 7, C") {
        TokenVector tokenVector {
                {1, 1, TokenType::IDENTIFIER, "RES"},
                {1, 1, TokenType::NUMBER, "7"},
                {1, 1, TokenType::COMMA, ","},
                {1, 1, TokenType::IDENTIFIER, "C"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = ResetBitOf8BitRegister(7, Register8Bit::C);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("Invalid: RES 9, C") {
        TokenVector tokenVector {
                {1, 1, TokenType::IDENTIFIER, "RES"},
                {1, 1, TokenType::NUMBER, "9"},
                {1, 1, TokenType::COMMA, ","},
                {1, 1, TokenType::IDENTIFIER, "C"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);

        REQUIRE_THROWS_AS(parser.parse(), std::logic_error);
    }
}
