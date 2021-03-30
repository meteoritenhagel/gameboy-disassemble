#include "../src/assembler/auxiliary.h"

TEST_CASE("test whether a character is + or -", "[issign]") {
    REQUIRE( issign('+') == true );
    REQUIRE( issign('-') == true );
    REQUIRE( issign('2') == false );
    REQUIRE( issign('x') == false );
    REQUIRE( issign('Z') == false );
    REQUIRE( issign('9') == false );
    REQUIRE( issign('?') == false );
}

TEST_CASE("test whether a token can be converted to an arbitrary register", "[is_register]") {

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

TEST_CASE("test whether a token can be converted to an 8-bit register", "[is_register_8_bit]") {

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

TEST_CASE("test whether a token can be converted to a 16-bit register", "[is_register_16_bit]") {

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