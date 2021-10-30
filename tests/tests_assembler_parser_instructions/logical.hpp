#include "../../src/assembler/parser.h"

TEST_CASE("'AND' commands are parsed correctly", "[Parser::parse]") {
    SECTION("AND A and 8-bit register: long form") {
        TokenVector tokenVector{
                {1, 1, TokenType::IDENTIFIER,  "AND"},
                {1, 1, TokenType::IDENTIFIER,  "A"},
                {1, 1, TokenType::COMMA,       ","},
                {1, 1, TokenType::IDENTIFIER,  "B"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = AndAAnd8BitRegister(Register8Bit::B);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("AND A and 8-bit register: short form") {
        TokenVector tokenVector{
                {1, 1, TokenType::IDENTIFIER,  "AND"},
                {1, 1, TokenType::IDENTIFIER,  "B"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = AndAAnd8BitRegister(Register8Bit::B);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("AND A and immediate: long form") {
        TokenVector tokenVector{
                {1, 1, TokenType::IDENTIFIER,  "AND"},
                {1, 1, TokenType::IDENTIFIER,  "A"},
                {1, 1, TokenType::COMMA,       ","},
                {1, 1, TokenType::NUMBER,      "0x01"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = AndAAndImmediate(0x01);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("AND A and immediate: short form") {
        TokenVector tokenVector{
                {1, 1, TokenType::IDENTIFIER,  "AND"},
                {1, 1, TokenType::NUMBER,      "0x01"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = AndAAndImmediate(0x01);
        REQUIRE(currentInstruction == correctInstruction);
    }
}

TEST_CASE("'OR' commands are parsed correctly", "[Parser::parse]") {
    SECTION("OR A and 8-bit register: long form") {
        TokenVector tokenVector{
                {1, 1, TokenType::IDENTIFIER,  "OR"},
                {1, 1, TokenType::IDENTIFIER,  "A"},
                {1, 1, TokenType::COMMA,       ","},
                {1, 1, TokenType::IDENTIFIER,  "B"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = OrAAnd8BitRegister(Register8Bit::B);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("OR A and 8-bit register: short form") {
        TokenVector tokenVector{
                {1, 1, TokenType::IDENTIFIER,  "OR"},
                {1, 1, TokenType::IDENTIFIER,  "B"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = OrAAnd8BitRegister(Register8Bit::B);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("OR A and immediate: long form") {
        TokenVector tokenVector{
                {1, 1, TokenType::IDENTIFIER,  "OR"},
                {1, 1, TokenType::IDENTIFIER,  "A"},
                {1, 1, TokenType::COMMA,       ","},
                {1, 1, TokenType::NUMBER,      "0x01"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = OrAAndImmediate(0x01);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("OR A and immediate: short form") {
        TokenVector tokenVector{
                {1, 1, TokenType::IDENTIFIER,  "OR"},
                {1, 1, TokenType::NUMBER,      "0x01"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = OrAAndImmediate(0x01);
        REQUIRE(currentInstruction == correctInstruction);
    }
}

TEST_CASE("'XOR' commands are parsed correctly", "[Parser::parse]") {
    SECTION("XOR A and 8-bit register: long form") {
        TokenVector tokenVector{
                {1, 1, TokenType::IDENTIFIER,  "XOR"},
                {1, 1, TokenType::IDENTIFIER,  "A"},
                {1, 1, TokenType::COMMA,       ","},
                {1, 1, TokenType::IDENTIFIER,  "B"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = XorAAnd8BitRegister(Register8Bit::B);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("XOR A and 8-bit register: short form") {
        TokenVector tokenVector{
                {1, 1, TokenType::IDENTIFIER,  "XOR"},
                {1, 1, TokenType::IDENTIFIER,  "B"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = XorAAnd8BitRegister(Register8Bit::B);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("XOR A and immediate: long form") {
        TokenVector tokenVector{
                {1, 1, TokenType::IDENTIFIER,  "XOR"},
                {1, 1, TokenType::IDENTIFIER,  "A"},
                {1, 1, TokenType::COMMA,       ","},
                {1, 1, TokenType::NUMBER,      "0x01"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = XorAAndImmediate(0x01);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("XOR A and immediate: short form") {
        TokenVector tokenVector{
                {1, 1, TokenType::IDENTIFIER,  "XOR"},
                {1, 1, TokenType::NUMBER,      "0x01"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = XorAAndImmediate(0x01);
        REQUIRE(currentInstruction == correctInstruction);
    }
}

TEST_CASE("'CP' commands are parsed correctly", "[Parser::parse]") {
    SECTION("CP A and 8-bit register: long form") {
        TokenVector tokenVector{
                {1, 1, TokenType::IDENTIFIER,  "CP"},
                {1, 1, TokenType::IDENTIFIER,  "A"},
                {1, 1, TokenType::COMMA,       ","},
                {1, 1, TokenType::IDENTIFIER,  "B"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = CompareAAnd8BitRegister(Register8Bit::B);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("CP A and 8-bit register: short form") {
        TokenVector tokenVector{
                {1, 1, TokenType::IDENTIFIER,  "CP"},
                {1, 1, TokenType::IDENTIFIER,  "B"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = CompareAAnd8BitRegister(Register8Bit::B);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("CP A and immediate: long form") {
        TokenVector tokenVector{
                {1, 1, TokenType::IDENTIFIER,  "CP"},
                {1, 1, TokenType::IDENTIFIER,  "A"},
                {1, 1, TokenType::COMMA,       ","},
                {1, 1, TokenType::NUMBER,      "0x01"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = CompareAAndImmediate(0x01);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("CP A and immediate: short form") {
        TokenVector tokenVector{
                {1, 1, TokenType::IDENTIFIER,  "CP"},
                {1, 1, TokenType::NUMBER,      "0x01"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = CompareAAndImmediate(0x01);
        REQUIRE(currentInstruction == correctInstruction);
    }
}

TEST_CASE("'CPL' command is parsed correctly", "[Parser::parse]") {
    TokenVector tokenVector{
            {1, 1, TokenType::IDENTIFIER,  "CPL"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
    };
    Parser parser("", tokenVector);
    InstructionVector instructionVector = parser.parse();

    REQUIRE(instructionVector.size() == 1);

    const BaseInstruction currentInstruction = *instructionVector[0];
    const BaseInstruction correctInstruction = ComplementA();
    REQUIRE(currentInstruction == correctInstruction);
}

TEST_CASE("'DAA' commands is parsed correctly", "[Parser::parse]") {
    TokenVector tokenVector{
            {1, 1, TokenType::IDENTIFIER,  "DAA"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
    };
    Parser parser("", tokenVector);
    InstructionVector instructionVector = parser.parse();

    REQUIRE(instructionVector.size() == 1);

    const BaseInstruction currentInstruction = *instructionVector[0];
    const BaseInstruction correctInstruction = DecimalAdjustA();
    REQUIRE(currentInstruction == correctInstruction);
}
