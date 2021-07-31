#include "../src/assembler/parser.h"

TEST_CASE("'ADD' commands are parsed correctly", "[Parser::parse]") {
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

TEST_CASE("'ADC' commands are parsed correctly", "[Parser::parse]") {
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

TEST_CASE("'JP' commands are parsed correctly", "[Parser::parse]") {
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

    SECTION("JP to previously declared local label") {
        TokenVector tokenVector {
                {1, 1, TokenType::GLOBAL_LABEL, "LABEL1:"},
                {1, 1, TokenType::END_OF_LINE, "\\n"},

                {1, 1, TokenType::IDENTIFIER, "DEC"},
                {1, 1, TokenType::IDENTIFIER, "HL"},
                {1, 1, TokenType::END_OF_LINE, "\\n"},

                {1, 1, TokenType::LOCAL_LABEL, ".LOCAL"},
                {1, 1, TokenType::END_OF_LINE, "\\n"},

                {1, 1, TokenType::IDENTIFIER, "DEC"},
                {1, 1, TokenType::IDENTIFIER, "HL"},
                {1, 1, TokenType::END_OF_LINE, "\\n"},

                {1, 1, TokenType::IDENTIFIER, "JP"},
                {1, 1, TokenType::LOCAL_LABEL, ".LOCAL"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 3);

        const BaseInstruction currentInstruction = *instructionVector[2];
        const BaseInstruction correctInstruction = Jump(0x0001);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("JP to local label declared later") {
        TokenVector tokenVector {
                {1, 1, TokenType::GLOBAL_LABEL, "LABEL1:"},
                {1, 1, TokenType::END_OF_LINE, "\\n"},

                {1, 1, TokenType::IDENTIFIER, "JP"},
                {1, 1, TokenType::LOCAL_LABEL, ".LOCAL"},
                {1, 1, TokenType::END_OF_LINE, "\\n"},

                {1, 1, TokenType::IDENTIFIER, "DEC"},
                {1, 1, TokenType::IDENTIFIER, "HL"},
                {1, 1, TokenType::END_OF_LINE, "\\n"},

                {1, 1, TokenType::LOCAL_LABEL, ".LOCAL"},
                {1, 1, TokenType::END_OF_LINE, "\\n"},

                {1, 1, TokenType::IDENTIFIER, "DEC"},
                {1, 1, TokenType::IDENTIFIER, "HL"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 3);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = Jump(0x0004);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("JP with flag conditions") {
        TokenVector tokenVector {
                {1, 1, TokenType::IDENTIFIER, "JP"},
                {1, 1, TokenType::IDENTIFIER, "NZ"},
                {1, 1, TokenType::COMMA, ","},
                {1, 1, TokenType::NUMBER, "0x1234"},
                {1, 1, TokenType::END_OF_LINE, "\\n"},

                {1, 1, TokenType::IDENTIFIER, "JP"},
                {1, 1, TokenType::IDENTIFIER, "Z"},
                {1, 1, TokenType::COMMA, ","},
                {1, 1, TokenType::NUMBER, "0x1234"},
                {1, 1, TokenType::END_OF_LINE, "\\n"},

                {1, 1, TokenType::IDENTIFIER, "JP"},
                {1, 1, TokenType::IDENTIFIER, "NC"},
                {1, 1, TokenType::COMMA, ","},
                {1, 1, TokenType::NUMBER, "0x1234"},
                {1, 1, TokenType::END_OF_LINE, "\\n"},

                {1, 1, TokenType::IDENTIFIER, "JP"},
                {1, 1, TokenType::IDENTIFIER, "C"},
                {1, 1, TokenType::COMMA, ","},
                {1, 1, TokenType::NUMBER, "0x1234"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 4);

        const BaseInstruction firstInstruction = *instructionVector[0];
        const BaseInstruction firstCorrectInstruction = JumpConditional(FlagCondition::NOT_ZERO, 0x1234);
        REQUIRE(firstInstruction == firstCorrectInstruction);

        const BaseInstruction secondInstruction = *instructionVector[1];
        const BaseInstruction secondCorrectInstruction = JumpConditional(FlagCondition::ZERO, 0x1234);
        REQUIRE(secondInstruction == secondCorrectInstruction);

        const BaseInstruction thirdInstruction = *instructionVector[2];
        const BaseInstruction thirdCorrectInstruction = JumpConditional(FlagCondition::NOT_CARRY, 0x1234);
        REQUIRE(thirdInstruction == thirdCorrectInstruction);

        const BaseInstruction forthInstruction = *instructionVector[3];
        const BaseInstruction forthCorrectInstruction = JumpConditional(FlagCondition::CARRY, 0x1234);
        REQUIRE(forthInstruction == forthCorrectInstruction);
    }
}

TEST_CASE("Loading commands ('LD', 'LDI', 'LDD', 'LDH') are parsed correctly", "[Parser::parse]") {
    SECTION("LD 8-bit register, immediate") {
        TokenVector tokenVector {
            {1, 1, TokenType::IDENTIFIER, "LD"},
            {1, 1, TokenType::IDENTIFIER, "B"},
            {1, 1, TokenType::COMMA, ","},
            {1, 1, TokenType::NUMBER, "0xFF"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = LoadImmediateInto8BitRegister(Register8Bit::B, 0xFF);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("LD 16-bit register, immediate") {
        TokenVector tokenVector {
            {1, 1, TokenType::IDENTIFIER, "LD"},
            {1, 1, TokenType::IDENTIFIER, "SP"},
            {1, 1, TokenType::COMMA, ","},
            {1, 1, TokenType::NUMBER, "0xFFFF"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = LoadImmediateInto16BitRegister(Register16Bit::SP, 0xFFFF);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("LD AF, immediate is invalid command") {
        TokenVector tokenVector {
            {1, 1, TokenType::IDENTIFIER, "LD"},
            {1, 1, TokenType::IDENTIFIER, "AF"},
            {1, 1, TokenType::COMMA, ","},
            {1, 1, TokenType::NUMBER, "0xFFFF"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        REQUIRE_THROWS(parser.parse());
    }

    SECTION("LD 8-bit register, 8-bit register") {
        TokenVector tokenVector {
            {1, 1, TokenType::IDENTIFIER, "LD"},
            {1, 1, TokenType::IDENTIFIER, "A"},
            {1, 1, TokenType::COMMA, ","},
            {1, 1, TokenType::IDENTIFIER, "B"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = Load8BitRegisterInto8BitRegister(Register8Bit::B, Register8Bit::A);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("LD (HL), (HL) is invalid command") {
        TokenVector tokenVector {
            {1, 1, TokenType::IDENTIFIER, "LD"},
            {1, 1, TokenType::IDENTIFIER, "(HL)"},
            {1, 1, TokenType::COMMA, ","},
            {1, 1, TokenType::IDENTIFIER, "(HL)"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        REQUIRE_THROWS(parser.parse());
    }

    SECTION("LD (immediate), A") {
        TokenVector tokenVector {
            {1, 1, TokenType::IDENTIFIER, "LD"},
            {1, 1, TokenType::ADDRESS, "(0xABAB)"},
            {1, 1, TokenType::COMMA, ","},
            {1, 1, TokenType::IDENTIFIER, "A"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = LoadAIntoAddressImmediate(0xABAB);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("LD [immediate], A (with square brackets)") {
        TokenVector tokenVector {
            {1, 1, TokenType::IDENTIFIER, "LD"},
            {1, 1, TokenType::ADDRESS, "[0xABAB]"},
            {1, 1, TokenType::COMMA, ","},
            {1, 1, TokenType::IDENTIFIER, "A"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = LoadAIntoAddressImmediate(0xABAB);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("LD (immediate), B does not work, since only A can be correct") {
        TokenVector tokenVector {
            {1, 1, TokenType::IDENTIFIER, "LD"},
            {1, 1, TokenType::ADDRESS, "(0xABAB)"},
            {1, 1, TokenType::COMMA, ","},
            {1, 1, TokenType::IDENTIFIER, "B"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        REQUIRE_THROWS(parser.parse());
    }

    SECTION("LD (BC)|(DE), A") {
        TokenVector tokenVector {
            {1, 1, TokenType::IDENTIFIER, "LD"},
            {1, 1, TokenType::IDENTIFIER, "(BC)"},
            {1, 1, TokenType::COMMA, ","},
            {1, 1, TokenType::IDENTIFIER, "A"},
            {1, 1, TokenType::END_OF_LINE, "\n"},

            {1, 1, TokenType::IDENTIFIER, "LD"},
            {1, 1, TokenType::IDENTIFIER, "(DE)"},
            {1, 1, TokenType::COMMA, ","},
            {1, 1, TokenType::IDENTIFIER, "A"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 2);

        const BaseInstruction currentInstruction1 = *instructionVector[0];
        const BaseInstruction correctInstruction1 = LoadAIntoAddress16BitRegister(Register16Bit::BC);
        REQUIRE(currentInstruction1 == correctInstruction1);

        const BaseInstruction currentInstruction2 = *instructionVector[1];
        const BaseInstruction correctInstruction2 = LoadAIntoAddress16BitRegister(Register16Bit::DE);
        REQUIRE(currentInstruction2 == correctInstruction2);
    }

    SECTION("LD (SP), A does not work") {
        TokenVector tokenVector {
            {1, 1, TokenType::IDENTIFIER, "LD"},
            {1, 1, TokenType::IDENTIFIER, "(SP)"},
            {1, 1, TokenType::COMMA, ","},
            {1, 1, TokenType::IDENTIFIER, "A"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        REQUIRE_THROWS(parser.parse());
    }

    SECTION("LD (BC), B does not work") {
        TokenVector tokenVector {
            {1, 1, TokenType::IDENTIFIER, "LD"},
            {1, 1, TokenType::IDENTIFIER, "(BC)"},
            {1, 1, TokenType::COMMA, ","},
            {1, 1, TokenType::IDENTIFIER, "B"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        REQUIRE_THROWS(parser.parse());
    }

    SECTION("LD (HL+), A") {
        TokenVector tokenVector {
            {1, 1, TokenType::IDENTIFIER, "LD"},
            {1, 1, TokenType::IDENTIFIER, "(HL+)"},
            {1, 1, TokenType::COMMA, ","},
            {1, 1, TokenType::IDENTIFIER, "A"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = LoadAIntoAddressHLIncrement();
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("LD (HLI), A") {
        TokenVector tokenVector {
            {1, 1, TokenType::IDENTIFIER, "LD"},
            {1, 1, TokenType::IDENTIFIER, "(HLI)"},
            {1, 1, TokenType::COMMA, ","},
            {1, 1, TokenType::IDENTIFIER, "A"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = LoadAIntoAddressHLIncrement();
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("LDI (HL), A") {
        TokenVector tokenVector {
            {1, 1, TokenType::IDENTIFIER, "LDI"},
            {1, 1, TokenType::IDENTIFIER, "(HL)"},
            {1, 1, TokenType::COMMA, ","},
            {1, 1, TokenType::IDENTIFIER, "A"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = LoadAIntoAddressHLIncrement();
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("LD (HL-), A") {
        TokenVector tokenVector {
            {1, 1, TokenType::IDENTIFIER, "LD"},
            {1, 1, TokenType::IDENTIFIER, "(HL-)"},
            {1, 1, TokenType::COMMA, ","},
            {1, 1, TokenType::IDENTIFIER, "A"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = LoadAIntoAddressHLDecrement();
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("LD (HLD), A") {
        TokenVector tokenVector {
            {1, 1, TokenType::IDENTIFIER, "LD"},
            {1, 1, TokenType::IDENTIFIER, "(HLD)"},
            {1, 1, TokenType::COMMA, ","},
            {1, 1, TokenType::IDENTIFIER, "A"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = LoadAIntoAddressHLDecrement();
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("LDD (HL), A") {
        TokenVector tokenVector {
            {1, 1, TokenType::IDENTIFIER, "LDD"},
            {1, 1, TokenType::IDENTIFIER, "(HL)"},
            {1, 1, TokenType::COMMA, ","},
            {1, 1, TokenType::IDENTIFIER, "A"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = LoadAIntoAddressHLDecrement();
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("LD (C), A") {
        TokenVector tokenVector {
            {1, 1, TokenType::IDENTIFIER, "LD"},
            {1, 1, TokenType::IDENTIFIER, "(C)"},
            {1, 1, TokenType::COMMA, ","},
            {1, 1, TokenType::IDENTIFIER, "A"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = LoadAIntoPortAddressC();
        REQUIRE(currentInstruction == correctInstruction);
    }

    // ###################################################################

    SECTION("LD (immediate), SP") {
        TokenVector tokenVector {
            {1, 1, TokenType::IDENTIFIER, "LD"},
            {1, 1, TokenType::ADDRESS, "(0xBABE)"},
            {1, 1, TokenType::COMMA, ","},
            {1, 1, TokenType::IDENTIFIER, "SP"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = LoadSPIntoAddressImmediate(0xBABE);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("LD SP, HL") {
        TokenVector tokenVector {
            {1, 1, TokenType::IDENTIFIER, "LD"},
            {1, 1, TokenType::IDENTIFIER, "SP"},
            {1, 1, TokenType::COMMA, ","},
            {1, 1, TokenType::IDENTIFIER, "HL"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = LoadHLIntoSP();
        REQUIRE(currentInstruction == correctInstruction);
    }

    // #####################################################################

    SECTION("LD A, (immediate)") {
        TokenVector tokenVector {
            {1, 1, TokenType::IDENTIFIER, "LD"},
            {1, 1, TokenType::IDENTIFIER, "A"},
            {1, 1, TokenType::COMMA, ","},
            {1, 1, TokenType::ADDRESS, "(0xBABE)"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = LoadAddressImmediateIntoA(0xBABE);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("LD B, (immediate) does not work, since only A can be correct") {
        TokenVector tokenVector {
            {1, 1, TokenType::IDENTIFIER, "LD"},
            {1, 1, TokenType::IDENTIFIER, "B"},
            {1, 1, TokenType::COMMA, ","},
            {1, 1, TokenType::ADDRESS, "(0xABAB)"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        REQUIRE_THROWS(parser.parse());
    }

    SECTION("LD A, (BC)|(DE)") {
        TokenVector tokenVector {
            {1, 1, TokenType::IDENTIFIER, "LD"},
            {1, 1, TokenType::IDENTIFIER, "A"},
            {1, 1, TokenType::COMMA, ","},
            {1, 1, TokenType::IDENTIFIER, "(BC)"},
            {1, 1, TokenType::END_OF_LINE, "\n"},

            {1, 1, TokenType::IDENTIFIER, "LD"},
            {1, 1, TokenType::IDENTIFIER, "A"},
            {1, 1, TokenType::COMMA, ","},
            {1, 1, TokenType::IDENTIFIER, "(DE)"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 2);

        const BaseInstruction currentInstruction1 = *instructionVector[0];
        const BaseInstruction correctInstruction1 = LoadAddress16BitRegisterIntoA(Register16Bit::BC);
        REQUIRE(currentInstruction1 == correctInstruction1);

        const BaseInstruction currentInstruction2 = *instructionVector[1];
        const BaseInstruction correctInstruction2 = LoadAddress16BitRegisterIntoA(Register16Bit::DE);
        REQUIRE(currentInstruction2 == correctInstruction2);
    }

    SECTION("LD A, (SP) does not work") {
        TokenVector tokenVector {
            {1, 1, TokenType::IDENTIFIER, "LD"},
            {1, 1, TokenType::IDENTIFIER, "A"},
            {1, 1, TokenType::COMMA, ","},
            {1, 1, TokenType::IDENTIFIER, "(SP)"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        REQUIRE_THROWS(parser.parse());
    }

    SECTION("LD B, (BC) does not work") {
        TokenVector tokenVector {
            {1, 1, TokenType::IDENTIFIER, "LD"},
            {1, 1, TokenType::IDENTIFIER, "(B"},
            {1, 1, TokenType::COMMA, ","},
            {1, 1, TokenType::IDENTIFIER, "(BC)"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        REQUIRE_THROWS(parser.parse());
    }

    SECTION("LD A, (HL+)") {
        TokenVector tokenVector {
            {1, 1, TokenType::IDENTIFIER, "LD"},
            {1, 1, TokenType::IDENTIFIER, "A"},
            {1, 1, TokenType::COMMA, ","},
            {1, 1, TokenType::IDENTIFIER, "(HL+)"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = LoadAddressHLIncrementIntoA();
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("LD A, (HLI)") {
        TokenVector tokenVector {
            {1, 1, TokenType::IDENTIFIER, "LD"},
            {1, 1, TokenType::IDENTIFIER, "A"},
            {1, 1, TokenType::COMMA, ","},
            {1, 1, TokenType::IDENTIFIER, "(HLI)"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = LoadAddressHLIncrementIntoA();
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("LDI A, (HL)") {
        TokenVector tokenVector {
            {1, 1, TokenType::IDENTIFIER, "LDI"},
            {1, 1, TokenType::IDENTIFIER, "A"},
            {1, 1, TokenType::COMMA, ","},
            {1, 1, TokenType::IDENTIFIER, "(HL)"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = LoadAddressHLIncrementIntoA();
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("LD A, (HL-)") {
        TokenVector tokenVector {
            {1, 1, TokenType::IDENTIFIER, "LD"},
            {1, 1, TokenType::IDENTIFIER, "A"},
            {1, 1, TokenType::COMMA, ","},
            {1, 1, TokenType::IDENTIFIER, "(HL-)"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = LoadAddressHLDecrementIntoA();
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("LD A, (HLD)") {
        TokenVector tokenVector {
            {1, 1, TokenType::IDENTIFIER, "LD"},
            {1, 1, TokenType::IDENTIFIER, "A"},
            {1, 1, TokenType::COMMA, ","},
            {1, 1, TokenType::IDENTIFIER, "(HLD)"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = LoadAddressHLDecrementIntoA();
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("LDD A, (HL)") {
        TokenVector tokenVector {
            {1, 1, TokenType::IDENTIFIER, "LDD"},
            {1, 1, TokenType::IDENTIFIER, "A"},
            {1, 1, TokenType::COMMA, ","},
            {1, 1, TokenType::IDENTIFIER, "(HL)"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = LoadAddressHLDecrementIntoA();
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("LD A, (C)") {
        TokenVector tokenVector {
            {1, 1, TokenType::IDENTIFIER, "LD"},
            {1, 1, TokenType::IDENTIFIER, "A"},
            {1, 1, TokenType::COMMA, ","},
            {1, 1, TokenType::IDENTIFIER, "(C)"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = LoadPortAddressCIntoA();
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("LD HL, SP shifted by positive signed 8-bit number") {
        TokenVector tokenVector {
            {1, 1, TokenType::IDENTIFIER, "LD"},
            {1, 1, TokenType::IDENTIFIER, "HL"},
            {1, 1, TokenType::COMMA, ","},
            {1, 1, TokenType::SP_SHIFTED, "SP+0x02"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = LoadSPShiftedByImmediateIntoHL(0x02);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("LD HL, SP shifted by negative signed 8-bit number") {
        TokenVector tokenVector {
            {1, 1, TokenType::IDENTIFIER, "LD"},
            {1, 1, TokenType::IDENTIFIER, "HL"},
            {1, 1, TokenType::COMMA, ","},
            {1, 1, TokenType::SP_SHIFTED, "SP-0x02"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = LoadSPShiftedByImmediateIntoHL(-0x02);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("LD HL, SP shifted by too big number throws") {
        TokenVector tokenVector {
            {1, 1, TokenType::IDENTIFIER, "LD"},
            {1, 1, TokenType::IDENTIFIER, "HL"},
            {1, 1, TokenType::COMMA, ","},
            {1, 1, TokenType::SP_SHIFTED, "SP-0xFF"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        REQUIRE_THROWS(parser.parse());
    }

    SECTION("LDHL SP, shifted by signed 8-bit number") {
        TokenVector tokenVector {
            {1, 1, TokenType::IDENTIFIER, "LDHL"},
            {1, 1, TokenType::IDENTIFIER, "SP"},
            {1, 1, TokenType::COMMA, ","},
            {1, 1, TokenType::NUMBER, "-0x01"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = LoadSPShiftedByImmediateIntoHL(-0x01);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("LDH (immediate), A") {
        TokenVector tokenVector {
            {1, 1, TokenType::IDENTIFIER, "LDH"},
            {1, 1, TokenType::ADDRESS, "(0x12)"},
            {1, 1, TokenType::COMMA, ","},
            {1, 1, TokenType::IDENTIFIER, "A"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = LoadAIntoPortAddressImmediate(0x12);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("LDH A, (immediate)") {
        TokenVector tokenVector {
            {1, 1, TokenType::IDENTIFIER, "LDH"},
            {1, 1, TokenType::IDENTIFIER, "A"},
            {1, 1, TokenType::COMMA, ","},
            {1, 1, TokenType::ADDRESS, "(0x12)"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = LoadPortAddressImmediateIntoA(0x12);
        REQUIRE(currentInstruction == correctInstruction);
    }
}

TEST_CASE("Assembler specific commands are parsed correctly", "[Parser::parse]") {
    SECTION("EQU definitions") {
        TokenVector tokenVector {
                {1, 1, TokenType::IDENTIFIER, "constant"},
                {1, 1, TokenType::IDENTIFIER, "EQU"},
                {1, 1, TokenType::NUMBER, "0xAF"},
                {1, 1, TokenType::END_OF_LINE, "\\n"},

                {1, 1, TokenType::IDENTIFIER, "ADC"},
                {1, 1, TokenType::IDENTIFIER, "constant"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = AddWithCarryAAndImmediate(0xAF);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("Multiple EQU definitions") {
        TokenVector tokenVector {
                {1, 1, TokenType::IDENTIFIER, "constant1"},
                {1, 1, TokenType::IDENTIFIER, "EQU"},
                {1, 1, TokenType::NUMBER, "0xAF"},
                {1, 1, TokenType::END_OF_LINE, "\\n"},

                {1, 1, TokenType::IDENTIFIER, "constant2"},
                {1, 1, TokenType::IDENTIFIER, "EQU"},
                {1, 1, TokenType::NUMBER, "0xCD"},
                {1, 1, TokenType::END_OF_LINE, "\\n"},

                {1, 1, TokenType::IDENTIFIER, "ADC"},
                {1, 1, TokenType::IDENTIFIER, "constant1"},
                {1, 1, TokenType::END_OF_LINE, "\\n"},

                {1, 1, TokenType::IDENTIFIER, "ADC"},
                {1, 1, TokenType::IDENTIFIER, "constant2"},
                {1, 1, TokenType::END_OF_LINE, "\\n"},

                {1, 1, TokenType::IDENTIFIER, "ADC"},
                {1, 1, TokenType::IDENTIFIER, "constant1"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 3);

        const BaseInstruction firstInstruction = *instructionVector[0];
        const BaseInstruction firstCorrectInstruction = AddWithCarryAAndImmediate(0xAF);
        REQUIRE(firstInstruction == firstCorrectInstruction);

        const BaseInstruction secondInstruction = *instructionVector[1];
        const BaseInstruction secondCorrectInstruction = AddWithCarryAAndImmediate(0xCD);
        REQUIRE(secondInstruction == secondCorrectInstruction);

        const BaseInstruction thirdInstruction = *instructionVector[2];
        const BaseInstruction thirdCorrectInstruction = AddWithCarryAAndImmediate(0xAF);
        REQUIRE(thirdInstruction == thirdCorrectInstruction);
    }

    SECTION("Using one EQU definition twice") {
        TokenVector tokenVector {
                {1, 1, TokenType::IDENTIFIER, "constant"},
                {1, 1, TokenType::IDENTIFIER, "EQU"},
                {1, 1, TokenType::NUMBER, "0xCD"},
                {1, 1, TokenType::END_OF_LINE, "\\n"},

                {1, 1, TokenType::IDENTIFIER, "ADC"},
                {1, 1, TokenType::IDENTIFIER, "constant"},
                {1, 1, TokenType::END_OF_LINE, "\\n"},

                {1, 1, TokenType::IDENTIFIER, "ADD"},
                {1, 1, TokenType::IDENTIFIER, "constant"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 2);

        const BaseInstruction firstInstruction = *instructionVector[0];
        const BaseInstruction firstCorrectInstruction = AddWithCarryAAndImmediate(0xCD);
        REQUIRE(firstInstruction == firstCorrectInstruction);

        const BaseInstruction secondInstruction = *instructionVector[1];
        const BaseInstruction secondCorrectInstruction = AddAAndImmediate(0xCD);
        REQUIRE(secondInstruction == secondCorrectInstruction);
    }

    SECTION("EQU definition defined later") {
        TokenVector tokenVector {
                {1, 1, TokenType::IDENTIFIER, "ADC"},
                {1, 1, TokenType::IDENTIFIER, "constant"},
                {1, 1, TokenType::END_OF_LINE, "\\n"},

                {1, 1, TokenType::IDENTIFIER, "constant"},
                {1, 1, TokenType::IDENTIFIER, "EQU"},
                {1, 1, TokenType::NUMBER, "0xBF"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction firstInstruction = *instructionVector[0];
        const BaseInstruction firstCorrectInstruction = AddWithCarryAAndImmediate(0xBF);
        REQUIRE(firstInstruction == firstCorrectInstruction);
    }
}

// ...