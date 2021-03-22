#ifndef GAMEBOY_DISASSEMBLE_ASSEMBLER_H
#define GAMEBOY_DISASSEMBLE_ASSEMBLER_H

#include "instructions/constants.h"
#include "instructions/instructions.h"
#include "tokenizer.h"

class Assembler {
public:
    Assembler(const Tokenizer& tokenizer)
    : _tokenizer(tokenizer)
    {}

    void assemble()
    {
        // All valid commands must start with an identifier
        Token currentToken = fetch_and_expect(TokenType::IDENTIFIER);
        if (currentToken.get_string() == "ADD") assemble_add();
    }

private:

    std::string get_position_string()
    {
        return read().get_position_string();
    }

    void assemble_add()
    {
//        // first operand must be either register A, HL or SP
//        const Register destination = token_to_register(fetch());
//        check_register_is_valid(destination);
//
//        const Token sourceToken = fetch();
//
//        // destination = A
//        if (is_8_bit_register(destination))
//        {
//            expect_register(destination, Register8Bit::A);
//            Register8Bit destination8Bit = std::get<Register8Bit>(destination);
//
//            // can load immediate
//            if (destination8Bit == Register8Bit::A)
//            {
//                if (sourceToken.get_token_type() == TokenType::NUMBER)
//                {
//                    append_to_program(AddAAndImmediate(check_range_8_bit(sourceToken.get_numeric())).bytestr());
//                    return;
//                }
//            }
//
//            Register8Bit source8Bit = std::get<Register8Bit>(token_to_register(sourceToken));
//
//            switch (source8Bit)
//            {
//                case Register8Bit::B:
//                case Register8Bit::C:
//                case Register8Bit::D:
//                case Register8Bit::E:
//                case Register8Bit::H:
//                case Register8Bit::L:
//                case Register8Bit::ADDRESS_HL:
//                case Register8Bit::A:
//            }
//        }
//        else if (is_16_bit_register(destinationString))
//        {
//            // can load immediate
//            if (destinationString == "SP")
//            {
//
//            }
//        }
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
            throw std::logic_error(std::string("Assembler error: Found token type ") + to_string(currentType) +
                                   ". Expected token type " + to_string(expectedType) + " at position " + get_position_string());
        }
    }

    void append_to_program(const bytestring &code)
    {
        append_to_bytestring(_program, code);
    }

    // warning: must be called before any subsequent call to fetch(), else the position data is wrong!
    long check_range_8_bit(const long num) {
        if (!((-128 <= num && num <= 127) || (0 <= num && num <= 255)))
        {
            throw std::range_error("Assembler error: Number " + std::to_string(num) + " is expected to be 8-bit at " + get_position_string());
        }
    }

    // warning: must be called before any subsequent call to fetch(), else the position data is wrong!
    long check_range_16_bit(const long num) {
        if (!((-32768 <= num && num <= 32767) || (0 <= num && num <= 65535)))
        {
            throw std::range_error("Assembler error: Number " + std::to_string(num) + " is expected to be 16-bit at " + get_position_string());
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
            throw std::logic_error(std::string("Assembler error: Found expression \"") + read().get_string() +
                                   "\". Expected register at position " + get_position_string());
        }
    }

    void expect_register(const Register &currentRegister, const Register &expectedRegister)
    {
        if (currentRegister != expectedRegister)
        {
            throw std::logic_error(std::string("Assembler error: Found register ") + to_string(currentRegister) +
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
//            throw std::logic_error(std::string("Assembler error: Found token type ") + to_string(currentTokenType) +
//                                   ". Expected token type " + to_string(tokenType) + " at position " + token.get_position_string());
//        }
//        return _tokenizer.read();
//    }

    Tokenizer _tokenizer;
    Token _currentToken{};
    bytestring _program{};
};


#endif //GAMEBOY_DISASSEMBLE_ASSEMBLER_H
