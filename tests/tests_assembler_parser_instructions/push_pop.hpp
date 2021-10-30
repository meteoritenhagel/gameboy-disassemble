#include "../../src/assembler/parser.h"

TEST_CASE("'PUSH' commands are parsed correctly", "[Parser::parse]") {
    SECTION("PUSH AF") {
        TokenVector tokenVector{
                {1, 1, TokenType::IDENTIFIER,  "PUSH"},
                {1, 1, TokenType::IDENTIFIER,  "AF"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = Push16BitRegister(Register16Bit::AF);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("PUSH BC") {
        TokenVector tokenVector{
                {1, 1, TokenType::IDENTIFIER,  "PUSH"},
                {1, 1, TokenType::IDENTIFIER,  "BC"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = Push16BitRegister(Register16Bit::BC);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("PUSH DE") {
        TokenVector tokenVector{
                {1, 1, TokenType::IDENTIFIER,  "PUSH"},
                {1, 1, TokenType::IDENTIFIER,  "DE"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = Push16BitRegister(Register16Bit::DE);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("PUSH HL") {
        TokenVector tokenVector{
                {1, 1, TokenType::IDENTIFIER,  "PUSH"},
                {1, 1, TokenType::IDENTIFIER,  "HL"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = Push16BitRegister(Register16Bit::HL);
        REQUIRE(currentInstruction == correctInstruction);
    }
}

TEST_CASE("'POP' commands are parsed correctly", "[Parser::parse]") {
    SECTION("POP AF") {
        TokenVector tokenVector{
                {1, 1, TokenType::IDENTIFIER,  "POP"},
                {1, 1, TokenType::IDENTIFIER,  "AF"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = Pop16BitRegister(Register16Bit::AF);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("POP BC") {
        TokenVector tokenVector{
                {1, 1, TokenType::IDENTIFIER,  "POP"},
                {1, 1, TokenType::IDENTIFIER,  "BC"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = Pop16BitRegister(Register16Bit::BC);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("POP DE") {
        TokenVector tokenVector{
                {1, 1, TokenType::IDENTIFIER,  "POP"},
                {1, 1, TokenType::IDENTIFIER,  "DE"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = Pop16BitRegister(Register16Bit::DE);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("POP HL") {
        TokenVector tokenVector{
                {1, 1, TokenType::IDENTIFIER,  "POP"},
                {1, 1, TokenType::IDENTIFIER,  "HL"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = Pop16BitRegister(Register16Bit::HL);
        REQUIRE(currentInstruction == correctInstruction);
    }
}
