#include "../../src/assembler/parser.h"

TEST_CASE("'ADD' commands are parsed correctly", "[Parser::parse]") {
    SECTION("ADD A and 8-bit register: long form") {
        TokenVector tokenVector{
                {1, 1, TokenType::IDENTIFIER,  "ADD"},
                {1, 1, TokenType::IDENTIFIER,  "A"},
                {1, 1, TokenType::COMMA,       ","},
                {1, 1, TokenType::IDENTIFIER,  "B"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = AddAAnd8BitRegister(Register8Bit::B);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("ADD A and 8-bit register: short form") {
        TokenVector tokenVector{
                {1, 1, TokenType::IDENTIFIER,  "ADD"},
                {1, 1, TokenType::IDENTIFIER,  "B"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = AddAAnd8BitRegister(Register8Bit::B);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("ADD A and immediate: long form") {
        TokenVector tokenVector{
                {1, 1, TokenType::IDENTIFIER,  "ADD"},
                {1, 1, TokenType::IDENTIFIER,  "A"},
                {1, 1, TokenType::COMMA,       ","},
                {1, 1, TokenType::NUMBER,      "0x01"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = AddAAndImmediate(0x01);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("ADD A and immediate: short form") {
        TokenVector tokenVector{
                {1, 1, TokenType::IDENTIFIER,  "ADD"},
                {1, 1, TokenType::NUMBER,      "0x01"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = AddAAndImmediate(0x01);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("ADD HL and 16-bit register") {
        TokenVector tokenVector{
                {1, 1, TokenType::IDENTIFIER,  "ADD"},
                {1, 1, TokenType::IDENTIFIER,  "HL"},
                {1, 1, TokenType::COMMA,       ","},
                {1, 1, TokenType::IDENTIFIER,  "BC"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = AddHLAnd16BitRegister(Register16Bit::BC);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("ADD SP and signed 8-bit immediate") {
        TokenVector tokenVector{
                {1, 1, TokenType::IDENTIFIER,  "ADD"},
                {1, 1, TokenType::IDENTIFIER,  "SP"},
                {1, 1, TokenType::COMMA,       ","},
                {1, 1, TokenType::NUMBER,      "-0x01"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = AddSPAndImmediate(-0x01);
        REQUIRE(currentInstruction == correctInstruction);
    }
}

TEST_CASE("'ADC' commands are parsed correctly", "[Parser::parse]") {
    SECTION("ADC A and 8-bit register: long form") {
        TokenVector tokenVector{
                {1, 1, TokenType::IDENTIFIER,  "ADC"},
                {1, 1, TokenType::IDENTIFIER,  "A"},
                {1, 1, TokenType::COMMA,       ","},
                {1, 1, TokenType::IDENTIFIER,  "B"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = AddWithCarryAAnd8BitRegister(Register8Bit::B);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("ADC A and 8-bit register: short form") {
        TokenVector tokenVector{
                {1, 1, TokenType::IDENTIFIER,  "ADC"},
                {1, 1, TokenType::IDENTIFIER,  "B"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = AddWithCarryAAnd8BitRegister(Register8Bit::B);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("ADC A and immediate: long form") {
        TokenVector tokenVector{
                {1, 1, TokenType::IDENTIFIER,  "ADC"},
                {1, 1, TokenType::IDENTIFIER,  "A"},
                {1, 1, TokenType::COMMA,       ","},
                {1, 1, TokenType::NUMBER,      "0x01"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = AddWithCarryAAndImmediate(0x01);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("ADC A and immediate: short form") {
        TokenVector tokenVector{
                {1, 1, TokenType::IDENTIFIER,  "ADC"},
                {1, 1, TokenType::NUMBER,      "0x01"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = AddWithCarryAAndImmediate(0x01);
        REQUIRE(currentInstruction == correctInstruction);
    }
}