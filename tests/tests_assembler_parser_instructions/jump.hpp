#include "../../src/assembler/parser.h"

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

TEST_CASE("'JR' commands are parsed correctly", "[Parser::parse]") {
    SECTION("JR to positive 8-bit immediate") {
        TokenVector tokenVector {
                {1, 1, TokenType::IDENTIFIER, "JR"},
                {1, 1, TokenType::NUMBER, "0x12"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = JumpRelative(0x12);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("JR to previously declared label") {
        TokenVector tokenVector {
            {1, 1, TokenType::GLOBAL_LABEL, "LABEL1:"},
            {1, 1, TokenType::END_OF_LINE, "\\n"},

            {1, 1, TokenType::IDENTIFIER, "DEC"},
            {1, 1, TokenType::IDENTIFIER, "HL"},
            {1, 1, TokenType::END_OF_LINE, "\\n"},

            {1, 1, TokenType::IDENTIFIER, "DEC"},
            {1, 1, TokenType::IDENTIFIER, "HL"},
            {1, 1, TokenType::END_OF_LINE, "\\n"},

            {1, 1, TokenType::IDENTIFIER, "DEC"},
            {1, 1, TokenType::IDENTIFIER, "HL"},
            {1, 1, TokenType::END_OF_LINE, "\\n"},

            {1, 1, TokenType::IDENTIFIER, "JR"},
            {1, 1, TokenType::IDENTIFIER, "LABEL1"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 4);

        const BaseInstruction currentInstruction = *instructionVector[3];
        const BaseInstruction correctInstruction = JumpRelative(-0x03);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("JR to label declared later") {
        TokenVector tokenVector {
            {1, 1, TokenType::IDENTIFIER, "JR"},
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
        const BaseInstruction correctInstruction = JumpRelative(0x02);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("JR to previously declared local label") {
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

            {1, 1, TokenType::IDENTIFIER, "JR"},
            {1, 1, TokenType::LOCAL_LABEL, ".LOCAL"},
            {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 3);

        const BaseInstruction currentInstruction = *instructionVector[2];
        const BaseInstruction correctInstruction = JumpRelative(-0x01);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("JR to local label declared later") {
        TokenVector tokenVector {
            {1, 1, TokenType::GLOBAL_LABEL, "LABEL1:"},
            {1, 1, TokenType::END_OF_LINE, "\\n"},

            {1, 1, TokenType::IDENTIFIER, "JR"},
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
        const BaseInstruction correctInstruction = JumpRelative(0x03);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("JR to constant jump declared before") {
        TokenVector tokenVector {
                {1, 1, TokenType::IDENTIFIER, "CONSTANT"},
                {1, 1, TokenType::IDENTIFIER, "EQU"},
                {1, 1, TokenType::NUMBER, "0x7F"},
                {1, 1, TokenType::END_OF_LINE, "\\n"},

                {1, 1, TokenType::IDENTIFIER, "JR"},
                {1, 1, TokenType::IDENTIFIER, "CONSTANT"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };
        Parser parser("", tokenVector);
        InstructionVector instructionVector = parser.parse();

        REQUIRE(instructionVector.size() == 1);

        const BaseInstruction currentInstruction = *instructionVector[0];
        const BaseInstruction correctInstruction = JumpRelative(0x7F);
        REQUIRE(currentInstruction == correctInstruction);
    }

    SECTION("JR throws an error if goal label is too far away") {
        TokenVector tokenVector {
                {1, 1, TokenType::GLOBAL_LABEL, "LABEL1:"},
                {1, 1, TokenType::END_OF_LINE, "\\n"},

                {1, 1, TokenType::IDENTIFIER, "JR"},
                {1, 1, TokenType::LOCAL_LABEL, ".LOCAL"},
                {1, 1, TokenType::END_OF_LINE, "\\n"},

                {1, 1, TokenType::IDENTIFIER, "LD"},
                {1, 1, TokenType::IDENTIFIER, "HL"},
                {1, 1, TokenType::COMMA, ","},
                {1, 1, TokenType::NUMBER, "0x1234"},
                {1, 1, TokenType::END_OF_LINE, "\\n"},

                {1, 1, TokenType::LOCAL_LABEL, ".LOCAL"},
                {1, 1, TokenType::END_OF_LINE, "\\n"},

                {1, 1, TokenType::IDENTIFIER, "DEC"},
                {1, 1, TokenType::IDENTIFIER, "HL"},
                {1, 1, TokenType::END_OF_FILE, "[EOF]"}
        };

        TokenVector tokenVectorMult{100};

        for (size_t i = 0; i < tokenVectorMult.size(); ++i)
        {
            if (i < 2)
                tokenVectorMult[i] = tokenVector[i];
            else if (i > 97)
                tokenVectorMult[i] = tokenVector[i-95];
            else
                tokenVectorMult[i] = tokenVector[2];
        }

        Parser parser("", tokenVectorMult);
        REQUIRE_THROWS(parser.parse());
    }
}