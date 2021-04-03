#include "../src/assembler/auxiliary.h"

TEST_CASE("to_string(std::string) is the identity function", "[to_string(std::string)]") {
    REQUIRE( to_string("abc") == "abc" );
    REQUIRE( to_string("Xajsdf02!") == "Xajsdf02!" );
}

TEST_CASE("to_string function template works correctly", "[to_string(std::vector)]") {
    SECTION("An empty vector is converted to an empty string") {
        REQUIRE( to_string(std::vector<std::string>{}) == "" );
    }
    SECTION("1-element vectors yield the element itself") {
        REQUIRE( to_string(std::vector<std::string>{"abc"}) == "abc" );
    }
    SECTION("2-element vectors are converted correctly") {
        REQUIRE( to_string(std::vector<std::string>{"abc", "def"}) == "abc, or def" );
    }
    SECTION("3-element vectors get converted correctly") {
        REQUIRE( to_string(std::vector<std::string>{"abc", "def", "ghi"}) == "abc, def, or ghi" );
    }
}

TEST_CASE("get_length function returns correct length for some instructions", "[get_length]") {
    SECTION("'nop' and 'ld b, l' are 1 byte instructions") {
        const InstructionPtr nop = std::make_unique<Nop>();
        REQUIRE( get_length(nop) == 1 );
        const InstructionPtr ld_b_l = std::make_unique<Load8BitRegisterInto8BitRegister>(Register8Bit::L, Register8Bit::B);
        REQUIRE( get_length(ld_b_l) == 1 );
    }
    SECTION("'rl h' and 'ld b, 0x01' are 2 byte instructions") {
        const InstructionPtr rl_h = std::make_unique<RotateLeft8BitRegister>(Register8Bit::H);
        REQUIRE( get_length(rl_h) == 2 );
        const InstructionPtr ld_b_1 = std::make_unique<LoadImmediateInto8BitRegister>(Register8Bit::B, 0x01);
        REQUIRE( get_length(ld_b_1) == 2 );
    }
    SECTION("'ld de, 0x1234' and 'ld (0x1234), sp' are 3 byte instructions") {
        const InstructionPtr ld_de_1234 = std::make_unique<LoadImmediateInto16BitRegister>(Register16Bit::DE, 0x1234);
        REQUIRE( get_length(ld_de_1234) == 3 );
        const InstructionPtr ld_address_1234_sp = std::make_unique<LoadSPIntoAddressImmediate>(0x1234);
        REQUIRE( get_length(ld_address_1234_sp) == 3 );
    }
}

TEST_CASE("throw_exception_and_highlight throws a logic_error", "[throw_exception_and_highlight]") {
    REQUIRE_THROWS_AS(throw_exception_and_highlight("abc", 1, 1, "abc"), std::logic_error);
}

TEST_CASE("Test whether a character is + or -", "[is_sign]") {
    REQUIRE(is_sign('+') == true );
    REQUIRE(is_sign('-') == true );
    REQUIRE(is_sign('2') == false );
    REQUIRE(is_sign('x') == false );
    REQUIRE(is_sign('Z') == false );
    REQUIRE(is_sign('9') == false );
    REQUIRE(is_sign('?') == false );
}

TEST_CASE("Convert a string to uppercase", "[to_upper]") {
    REQUIRE(to_upper("...?") == "...?");
    REQUIRE(to_upper("abc") == "ABC");
    REQUIRE(to_upper("ABC") == "ABC");
}

TEST_CASE("Remove last character of std::string", "[remove_last_character]") {
    REQUIRE(remove_last_character("...?") == "...");
    REQUIRE(remove_last_character("abc") == "ab");
    REQUIRE(remove_last_character("ABC") == "AB");
    REQUIRE_THROWS(remove_last_character(""));
}

TEST_CASE("Test whether a token can be converted to an arbitrary register", "[is_register]") {

    SECTION("8-bit registers are recognized correctly") {
        const Token TokenB(1, 1, TokenType::IDENTIFIER, "B");
        const Token TokenC(1, 1, TokenType::IDENTIFIER, "C");
        const Token TokenD(1, 1, TokenType::IDENTIFIER, "D");
        const Token TokenE(1, 1, TokenType::IDENTIFIER, "E");
        const Token TokenH(1, 1, TokenType::IDENTIFIER, "H");
        const Token TokenL(1, 1, TokenType::IDENTIFIER, "L");
        const Token TokenRegisterHL(1, 1, TokenType::IDENTIFIER, "(HL)");
        const Token TokenA(1, 1, TokenType::IDENTIFIER, "A");
        REQUIRE( is_register(TokenB) == true );
        REQUIRE( is_register(TokenC) == true );
        REQUIRE( is_register(TokenD) == true );
        REQUIRE( is_register(TokenE) == true );
        REQUIRE( is_register(TokenH) == true );
        REQUIRE( is_register(TokenL) == true );
        REQUIRE( is_register(TokenRegisterHL) == true );
        REQUIRE( is_register(TokenA) == true );
    }

    SECTION("16-bit registers are recognized correctly") {
        const Token TokenAF(1, 1, TokenType::IDENTIFIER, "AF");
        const Token TokenBC(1, 1, TokenType::IDENTIFIER, "BC");
        const Token TokenDE(1, 1, TokenType::IDENTIFIER, "DE");
        const Token TokenHL(1, 1, TokenType::IDENTIFIER, "HL");
        const Token TokenSP(1, 1, TokenType::IDENTIFIER, "SP");

        REQUIRE( is_register(TokenAF) == true );
        REQUIRE( is_register(TokenBC) == true );
        REQUIRE( is_register(TokenDE) == true );
        REQUIRE( is_register(TokenHL) == true );
        REQUIRE( is_register(TokenSP) == true );
    }

    SECTION("No-register-tokens are recognized correctly") {
        const Token Token1(1, 1, TokenType::NUMBER, "2");
        const Token Token2(1, 1, TokenType::IDENTIFIER, "X");
        const Token Token3(1, 1, TokenType::ADDRESS, "(0x1234)");
        const Token Token4(1, 1, TokenType::END_OF_LINE, "Y");

        REQUIRE( is_register(Token1) == false );
        REQUIRE( is_register(Token2) == false );
        REQUIRE( is_register(Token3) == false );
        REQUIRE( is_register(Token4) == false );
    }
}

TEST_CASE("Test whether a token can be converted to an 8-bit register", "[is_register_8_bit]") {

    SECTION("8-bit registers are recognized correctly") {
        const Token TokenB(1, 1, TokenType::IDENTIFIER, "B");
        const Token TokenC(1, 1, TokenType::IDENTIFIER, "C");
        const Token TokenD(1, 1, TokenType::IDENTIFIER, "D");
        const Token TokenE(1, 1, TokenType::IDENTIFIER, "E");
        const Token TokenH(1, 1, TokenType::IDENTIFIER, "H");
        const Token TokenL(1, 1, TokenType::IDENTIFIER, "L");
        const Token TokenRegisterHL(1, 1, TokenType::IDENTIFIER, "(HL)");
        const Token TokenA(1, 1, TokenType::IDENTIFIER, "A");
        REQUIRE( is_register_8_bit(TokenB) == true );
        REQUIRE( is_register_8_bit(TokenC) == true );
        REQUIRE( is_register_8_bit(TokenD) == true );
        REQUIRE( is_register_8_bit(TokenE) == true );
        REQUIRE( is_register_8_bit(TokenH) == true );
        REQUIRE( is_register_8_bit(TokenL) == true );
        REQUIRE( is_register_8_bit(TokenRegisterHL) == true );
        REQUIRE( is_register_8_bit(TokenA) == true );
    }

    SECTION("16-bit registers are recognized as non-8-bit") {
        const Token TokenAF(1, 1, TokenType::IDENTIFIER, "AF");
        const Token TokenBC(1, 1, TokenType::IDENTIFIER, "BC");
        const Token TokenDE(1, 1, TokenType::IDENTIFIER, "DE");
        const Token TokenHL(1, 1, TokenType::IDENTIFIER, "HL");
        const Token TokenSP(1, 1, TokenType::IDENTIFIER, "SP");

        REQUIRE( is_register_8_bit(TokenAF) == false );
        REQUIRE( is_register_8_bit(TokenBC) == false );
        REQUIRE( is_register_8_bit(TokenDE) == false );
        REQUIRE( is_register_8_bit(TokenHL) == false );
        REQUIRE( is_register_8_bit(TokenSP) == false );
    }

    SECTION("No-register-tokens are recognized correctly") {
        const Token Token1(1, 1, TokenType::NUMBER, "2");
        const Token Token2(1, 1, TokenType::IDENTIFIER, "X");
        const Token Token3(1, 1, TokenType::ADDRESS, "(0x1234)");
        const Token Token4(1, 1, TokenType::END_OF_LINE, "Y");

        REQUIRE( is_register_8_bit(Token1) == false );
        REQUIRE( is_register_8_bit(Token2) == false );
        REQUIRE( is_register_8_bit(Token3) == false );
        REQUIRE( is_register_8_bit(Token4) == false );
    }
}

TEST_CASE("Test whether a token can be converted to a 16-bit register", "[is_register_16_bit]") {

    SECTION("8-bit registers are recognized as non-16-bit") {
        const Token TokenB(1, 1, TokenType::IDENTIFIER, "B");
        const Token TokenC(1, 1, TokenType::IDENTIFIER, "C");
        const Token TokenD(1, 1, TokenType::IDENTIFIER, "D");
        const Token TokenE(1, 1, TokenType::IDENTIFIER, "E");
        const Token TokenH(1, 1, TokenType::IDENTIFIER, "H");
        const Token TokenL(1, 1, TokenType::IDENTIFIER, "L");
        const Token TokenRegisterHL(1, 1, TokenType::IDENTIFIER, "(HL)");
        const Token TokenA(1, 1, TokenType::IDENTIFIER, "A");
        REQUIRE( is_register_16_bit(TokenB) == false );
        REQUIRE( is_register_16_bit(TokenC) == false );
        REQUIRE( is_register_16_bit(TokenD) == false );
        REQUIRE( is_register_16_bit(TokenE) == false );
        REQUIRE( is_register_16_bit(TokenH) == false );
        REQUIRE( is_register_16_bit(TokenL) == false );
        REQUIRE( is_register_16_bit(TokenRegisterHL) == false );
        REQUIRE( is_register_16_bit(TokenA) == false );
    }

    SECTION("16-bit registers are recognized correctly") {
        const Token TokenAF(1, 1, TokenType::IDENTIFIER, "AF");
        const Token TokenBC(1, 1, TokenType::IDENTIFIER, "BC");
        const Token TokenDE(1, 1, TokenType::IDENTIFIER, "DE");
        const Token TokenHL(1, 1, TokenType::IDENTIFIER, "HL");
        const Token TokenSP(1, 1, TokenType::IDENTIFIER, "SP");

        REQUIRE( is_register_16_bit(TokenAF) == true );
        REQUIRE( is_register_16_bit(TokenBC) == true );
        REQUIRE( is_register_16_bit(TokenDE) == true );
        REQUIRE( is_register_16_bit(TokenHL) == true );
        REQUIRE( is_register_16_bit(TokenSP) == true );
    }

    SECTION("No-register-tokens are recognized correctly") {
        const Token Token1(1, 1, TokenType::NUMBER, "2");
        const Token Token2(1, 1, TokenType::IDENTIFIER, "X");
        const Token Token3(1, 1, TokenType::ADDRESS, "(0x1234)");
        const Token Token4(1, 1, TokenType::END_OF_LINE, "Y");

        REQUIRE( is_register_16_bit(Token1) == false );
        REQUIRE( is_register_16_bit(Token2) == false );
        REQUIRE( is_register_16_bit(Token3) == false );
        REQUIRE( is_register_16_bit(Token4) == false );
    }
}