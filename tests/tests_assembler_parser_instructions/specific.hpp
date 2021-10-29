#include "../../src/assembler/parser.h"

TEST_CASE("Numeric conversions throw when a number cannot be converted properly", "[Parser::numeric_conversions]") {
    SECTION("8-bit numbers") {
        TokenVector tokenVector {
                {1, 1, TokenType::IDENTIFIER, "LD"},
                {1, 1, TokenType::IDENTIFIER, "B"},
                {1, 1, TokenType::COMMA, ","},
                {1, 1, TokenType::NUMBER, "0xFFFF"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        REQUIRE_THROWS_WITH(parser.parse(), Catch::Contains("8-bit"));
    }

    SECTION("signed 8-bit numbers") {
        TokenVector tokenVector {
                {1, 1, TokenType::IDENTIFIER, "JR"},
                {1, 1, TokenType::NUMBER, "0xFF"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        REQUIRE_THROWS_WITH(parser.parse(), Catch::Contains("signed 8-bit"));
    }

    SECTION("16-bit numbers") {
        TokenVector tokenVector {
                {1, 1, TokenType::IDENTIFIER, "JP"},
                {1, 1, TokenType::NUMBER, "0x12345678"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        REQUIRE_THROWS_WITH(parser.parse(), Catch::Contains("16-bit"));
    }

    SECTION("unsigned 16-bit numbers") {
        TokenVector tokenVector {
                {1, 1, TokenType::IDENTIFIER, "JP"},
                {1, 1, TokenType::NUMBER, "-0x1234"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        REQUIRE_THROWS_WITH(parser.parse(), Catch::Contains("unsigned 16-bit"));
    }
}

TEST_CASE("Local labels can only occur after some global label", "[Parser::local_labels]") {
    SECTION("Local labels after global label parse without problems") {
        TokenVector tokenVector {
                {1, 1, TokenType::GLOBAL_LABEL, "LABEL1:"},
                {1, 1, TokenType::END_OF_LINE, "\\n"},

                {1, 1, TokenType::LOCAL_LABEL, ".LOCAL"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        REQUIRE_NOTHROW(parser.parse());
    }

    SECTION("Local labels without parent global label throw an exception") {
        TokenVector tokenVector {
                {1, 1, TokenType::LOCAL_LABEL, ".LOCAL"},
                {1, 1, TokenType::END_OF_LINE, "\\n"},

                {1, 1, TokenType::GLOBAL_LABEL, "LABEL1:"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        REQUIRE_THROWS(parser.parse());
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