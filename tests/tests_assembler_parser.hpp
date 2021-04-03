#include "../src/assembler/parser.h"

TEST_CASE("'ADD' commands are parsed correctly", "[Parser::parse") {

    SECTION("ADD A and 8-bit register: long form") {
        TokenVector tokenVector {
                {1, 1, TokenType::IDENTIFIER, "ADD"},
                {1, 1, TokenType::IDENTIFIER, "A"},
                {1, 1, TokenType::COMMA, ","},
                {1, 1, TokenType::IDENTIFIER, "B"},
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
        TokenVector tokenVector {
                {1, 1, TokenType::IDENTIFIER, "ADD"},
                {1, 1, TokenType::IDENTIFIER, "B"},
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
        TokenVector tokenVector {
                {1, 1, TokenType::IDENTIFIER, "ADD"},
                {1, 1, TokenType::IDENTIFIER, "A"},
                {1, 1, TokenType::COMMA, ","},
                {1, 1, TokenType::NUMBER, "0x01"},
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
        TokenVector tokenVector {
                {1, 1, TokenType::IDENTIFIER, "ADD"},
                {1, 1, TokenType::NUMBER, "0x01"},
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
        TokenVector tokenVector {
                {1, 1, TokenType::IDENTIFIER, "ADD"},
                {1, 1, TokenType::IDENTIFIER, "HL"},
                {1, 1, TokenType::COMMA, ","},
                {1, 1, TokenType::IDENTIFIER, "BC"},
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
        TokenVector tokenVector {
                {1, 1, TokenType::IDENTIFIER, "ADD"},
                {1, 1, TokenType::IDENTIFIER, "SP"},
                {1, 1, TokenType::COMMA, ","},
                {1, 1, TokenType::NUMBER, "-0x01"},
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

TEST_CASE("'ADC' commands are parsed correctly", "[Parser::parse") {
    SECTION("ADC A and 8-bit register: long form") {
        TokenVector tokenVector {
                {1, 1, TokenType::IDENTIFIER, "ADC"},
                {1, 1, TokenType::IDENTIFIER, "A"},
                {1, 1, TokenType::COMMA, ","},
                {1, 1, TokenType::IDENTIFIER, "B"},
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
        TokenVector tokenVector {
                {1, 1, TokenType::IDENTIFIER, "ADC"},
                {1, 1, TokenType::IDENTIFIER, "B"},
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
        TokenVector tokenVector {
                {1, 1, TokenType::IDENTIFIER, "ADC"},
                {1, 1, TokenType::IDENTIFIER, "A"},
                {1, 1, TokenType::COMMA, ","},
                {1, 1, TokenType::NUMBER, "0x01"},
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
        TokenVector tokenVector {
                {1, 1, TokenType::IDENTIFIER, "ADC"},
                {1, 1, TokenType::NUMBER, "0x01"},
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

TEST_CASE("'BIT' commands are parsed correctly", "[Parser::parse") {
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

TEST_CASE("'INC' commands are parsed correctly", "[Parser::parse") {
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
}

TEST_CASE("'DEC' commands are parsed correctly", "[Parser::parse") {
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
}

TEST_CASE("'JP' commands are parsed correctly", "[Parser::parse") {
    SECTION("JP to 16-bit immediate") {
        TokenVector tokenVector {
                {1, 1, TokenType::IDENTIFIER, "JP"},
                {1, 1, TokenType::NUMBER, "0x1234"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = Jump(0x1234);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("JP to previously declared label") {
        TokenVector tokenVector {
                {1, 1, TokenType::GLOBAL_LABEL, "LABEL1:"},
                {1, 1, TokenType::END_OF_LINE, "\\n"},

                {1, 1, TokenType::IDENTIFIER, "DEC"},
                {1, 1, TokenType::IDENTIFIER, "HL"},
                {1, 1, TokenType::END_OF_LINE, "\\n"},

                {1, 1, TokenType::IDENTIFIER, "JP"},
                {1, 1, TokenType::IDENTIFIER, "LABEL1"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 2);

        const BaseInstruction currentInstruction = *instructionVector[1];
        const BaseInstruction correctInstruction = Jump(0x0000);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("JP to label declared later") {
        TokenVector tokenVector {
                {1, 1, TokenType::IDENTIFIER, "JP"},
                {1, 1, TokenType::IDENTIFIER, "LABEL1"},
                {1, 1, TokenType::END_OF_LINE, "\\n"},

                {1, 1, TokenType::GLOBAL_LABEL, "LABEL1:"},
                {1, 1, TokenType::END_OF_LINE, "\\n"},

                {1, 1, TokenType::IDENTIFIER, "DEC"},
                {1, 1, TokenType::IDENTIFIER, "HL"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 2);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = Jump(0x0003);
        REQUIRE(currentInstruction == correctInstruction);
    }
}