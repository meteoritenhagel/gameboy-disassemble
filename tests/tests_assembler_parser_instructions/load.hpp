#include "../../src/assembler/parser.h"

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