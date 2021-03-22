#ifndef GAMEBOY_DISASSEMBLE_PARSER_H
#define GAMEBOY_DISASSEMBLE_PARSER_H

#include "../instructions/constants.h"
#include "../instructions/instructions.h"
#include "tokenizer.h"

class Parser {
public:
    Parser(const Tokenizer& tokenizer)
    : _tokenizer(tokenizer)
    {}

    InstructionPtr parse_next_instruction()
    {
        // All valid commands must start with an identifier
        Token currentToken = fetch_and_expect(TokenType::IDENTIFIER);
        if (currentToken.get_string() == "ADD") return parse_add();
    }

private:

    std::string get_position_string()
    {
        return read().get_position_string();
    }

    InstructionPtr parse_add()
    {
//        // first token must always be a register
//        const Register reg = to_register(fetch_and_expect(TokenType::IDENTIFIER).get_string());
//        check_register_is_valid(reg);
//
//        if (is_8_bit_register(reg)) // Case 1: 8-bit (destination is A)
//        {
//            expect_register(reg, Register8Bit::A);
//        }
//        else // Case 2: 16-bit (destination is HL or SP)
//        {
//
//        }
//
//

    }

    Token read()
    {
        return _currentToken;
    }

    // may throw std::out_of_range or std::logic_error
    Token fetch()
    {
        _currentToken = _tokenizer.get_next_token();
        return read();
    }

    // may throw std::out_of_range or std::logic_error
    Token fetch_and_expect(const TokenType expectedType)
    {
        expect(read().get_token_type(), expectedType);
        return fetch();
    }

    // warning: must be called before any subsequent call to fetch(), else the position data is wrong!
    void expect(const TokenType currentType, const TokenType expectedType)
    {
        if (currentType != expectedType)
        {
            throw std::logic_error(std::string("Parser error: Found token type ") + to_string(currentType) +
                                   ". Expected token type " + to_string(expectedType) + " at position " + get_position_string());
        }
    }

    // warning: must be called before any subsequent call to fetch(), else the position data is wrong!
    long check_range_8_bit(const long num) {
        if (!((-128 <= num && num <= 127) || (0 <= num && num <= 255)))
        {
            throw std::range_error("Parser error: Number " + std::to_string(num) + " is expected to be 8-bit at " + get_position_string());
        }
    }

    // warning: must be called before any subsequent call to fetch(), else the position data is wrong!
    long check_range_16_bit(const long num) {
        if (!((-32768 <= num && num <= 32767) || (0 <= num && num <= 65535)))
        {
            throw std::range_error("Parser error: Number " + std::to_string(num) + " is expected to be 16-bit at " + get_position_string());
        }
    }

    // warning: must be called before any subsequent call to fetch(), else the position data is wrong!
    Register token_to_register(const Token &token)
    {
        expect(token.get_token_type(), TokenType::IDENTIFIER);
        const std::string tokenString = token.get_string();
        const Register reg = to_register(tokenString);
        check_register_is_valid(reg);

        return reg;
    }

    // warning: must be called before any subsequent call to fetch(), else the position data is wrong!
    void check_register_is_valid(const Register &reg)
    {
        if (is_valid(reg))
        {
            throw std::logic_error(std::string("Parser error: Found expression \"") + read().get_string() +
                                   "\". Expected register at position " + get_position_string());
        }
    }

    void expect_register(const Register &currentRegister, const Register &expectedRegister)
    {
        if (currentRegister != expectedRegister)
        {
            throw std::logic_error(std::string("Parser error: Found register ") + to_string(currentRegister) +
                                   ". Expected  register " + to_string(expectedRegister) + " at position " + get_position_string());
        }
    }

//    // may throw std::out_of_range or std::logic_error
//    Token get_next_token_and_expect_string(const std::string &str)
//    {
//        const Token token = read();
//        const std::string currentTokenString = token.get_string();
//        if (currentTokenString != str)
//        {
//            throw std::logic_error(std::string("Parser error: Found token type ") + to_string(currentTokenType) +
//                                   ". Expected token type " + to_string(tokenType) + " at position " + token.get_position_string());
//        }
//        return _tokenizer.read();
//    }

    Tokenizer _tokenizer;
    Token _currentToken{};
};


#endif //GAMEBOY_DISASSEMBLE_PARSER_H
