#ifndef GAMEBOY_DISASSEMBLE_PARSER_H
#define GAMEBOY_DISASSEMBLE_PARSER_H


#include "tokenizer.h"
#include "parse_functions.h"
#include "auxiliiary.h"

#include "print_code.h"


class Parser {
public:
    Parser(const Tokenizer& tokenizer)
    : _tokenizer(tokenizer)
    {}

    bool is_finished() const
    {
        return _tokenizer.is_finished();
    }

    InstructionPtr parse_next_instruction()
    {
        // All valid commands must start with an identifier
        const Token currentToken = fetch_and_expect(TokenType::IDENTIFIER);

        const std::string currStr = currentToken.get_string();

        InstructionPtr instruction;

        if      (currStr == "ADD") { instruction = parse_add(); }
        else if (currStr == "ADC") { instruction = parse_adc(); }
        else if (currStr == "BIT") { instruction = parse_bit(); }

        expect_end_of_context(fetch()); // each valid instruction must end with newline or end of file

        return instruction;
    }

private:

    InstructionPtr parse_add() {
        const Token destinationToken = fetch();
        const Token commaToken = fetch();
        const Token sourceToken = fetch();

        // destinationToken must always be a register
        to_register(destinationToken);

        expect_type(commaToken, TokenType::COMMA);

        if (is_register_8_bit(destinationToken)) // Case 1: 8-bit (destinationToken is A)
        {
            to_register_expect(destinationToken, Register8Bit::A);

            switch (sourceToken.get_token_type()) {
                case TokenType::IDENTIFIER:
                    return std::make_unique<AddAAnd8BitRegister>(to_register_8_bit(sourceToken));
                case TokenType::NUMBER:
                    return std::make_unique<AddAAndImmediate>(to_number_8_bit(sourceToken));
                default: break;
            }
        }
        else if (is_register_16_bit(destinationToken)) // Case 2: 16-bit (destinationToken is HL or SP)
        {
            switch(sourceToken.get_token_type()) {
                case TokenType::IDENTIFIER: // ADD HL, Register16Bit
                    to_register_expect(destinationToken, Register16Bit::HL);
                    return std::make_unique<AddHLAnd16BitRegister>(to_register_16_bit(sourceToken));
                case TokenType::NUMBER: // ADD SP, +16-bit-immediate
                    to_register_expect(destinationToken, Register16Bit::SP);
                    return std::make_unique<AddSPAndImmediate>(to_signed_number_8_bit(sourceToken));
                default: break;
            }
        }
        else
        {
            throw_logic_error_and_highlight(destinationToken, "Parse error: Invalid expression");
        }
    }

    InstructionPtr parse_adc() {
        const Token destinationToken = fetch();
        const Token commaToken = fetch();
        const Token sourceToken = fetch();

        // destinationToken must always be A
        to_register_expect(destinationToken, Register8Bit::A);
        expect_type(commaToken, TokenType::COMMA);

        switch (sourceToken.get_token_type()) {
            case TokenType::IDENTIFIER:
                return std::make_unique<AddWithCarryAAnd8BitRegister>(to_register_8_bit(sourceToken));
            case TokenType::NUMBER:
                return std::make_unique<AddWithCarryAAndImmediate>(to_number_8_bit(sourceToken));
            default: break;
        }
    }

    InstructionPtr parse_bit() {
        const Token indexToken = fetch();
        const Token commaToken = fetch();
        const Token registerToken = fetch();

        // BIT INDEX, 8BitRegister

        // index must be between 0 and 7
        const uint8_t index = to_index(indexToken);

        expect_type(commaToken, TokenType::COMMA);

        const Register8Bit reg = to_register_8_bit(registerToken);

        return std::make_unique<BitOf8BitRegisterComplementIntoZero>(index, reg);
    }

    // may throw std::out_of_range or std::logic_error
    Token fetch()
    {
        return _tokenizer.get_next_token();
    }

    // may throw std::out_of_range or std::logic_error
    Token fetch_and_expect(const TokenType expectedType)
    {
        const Token tkn = fetch();
        expect_type(tkn, expectedType);
        return tkn;
    }

    /****************/

    const std::string& get_code() const {
        return _tokenizer.get_code();
    }

// may throw
    void throw_logic_error_and_highlight(const Token &token, const std::string &errorMessage);

// may throw
    byte to_number_8_bit(const Token &numToken);

// may throw
    byte to_unsigned_number_8_bit(const Token &numToken);

// may throw
    byte to_signed_number_8_bit(const Token &numToken);

// may throw
    long to_number_16_bit(const Token &numToken);

// may throw
    long to_address_16_bit(const Token &addressToken);

// may throw
    byte to_index(const Token &addressToken);

// may throw
    Register to_register(const Token &token);

// may throw
    Register to_register_expect(const Token &token, const Register &reg);

// may throw
    Register8Bit to_register_8_bit(const Token& token);

// may throw
    Register16Bit to_register_16_bit(const Token& token);

// may throw
    void expect_type(const Token& token, const TokenType expectedType);

// may throw
    void expect_end_of_context(const Token& token);

    Tokenizer _tokenizer;
    Token _currentToken{};
};


#endif //GAMEBOY_DISASSEMBLE_PARSER_H
