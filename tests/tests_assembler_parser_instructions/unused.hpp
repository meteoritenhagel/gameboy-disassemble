#include "../../src/assembler/parser.h"

TEST_CASE("'UNU' commands are parsed correctly", "[Parser::parse]") {
    SECTION("UNU 7") {
        TokenVector tokenVector {
                {1, 1, TokenType::IDENTIFIER, "UNU"},
                {1, 1, TokenType::NUMBER, "7"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = Unused(7);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("Invalid: UNU 12") {
        TokenVector tokenVector {
                {1, 1, TokenType::IDENTIFIER, "UNU"},
                {1, 1, TokenType::NUMBER, "12"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);

        REQUIRE_THROWS_AS(parser.parse(), std::logic_error);
    }

    SECTION("Invalid: UNU 12") {
        TokenVector tokenVector {
                {1, 1, TokenType::IDENTIFIER, "UNU"},
                {1, 1, TokenType::NUMBER, "-1"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);

        REQUIRE_THROWS_AS(parser.parse(), std::logic_error);
    }
}