#ifndef GAMEBOY_DISASSEMBLE_TOKEN_H
#define GAMEBOY_DISASSEMBLE_TOKEN_H

#include "../instructions/auxiliary_and_conversions.h"

#include <iostream>
#include <optional>
#include <string>
#include <vector>

enum class TokenType {
    INVALID,
    IDENTIFIER,
    COMMA,
    NUMBER,
    ADDRESS,
    END_OF_LINE,
    END_OF_FILE
};

std::string to_string(const TokenType tokenType);

class Token;

using VectorOfTokens = std::vector<Token>;

class Token{
public:

    Token() = default;

    Token(const size_t lineNumber, const size_t columnNumber, const TokenType tokenType, const std::string &tokenString);

    size_t get_line() const;

    size_t get_column() const;

    TokenType get_token_type() const;

    std::string get_string() const;

    // if no numeric value is contained, std::bad_optional_access is thrown.
    long get_numeric() const;

    void print() const;

    std::string get_position_string() const;

private:
    size_t _lineNumber{0};
    size_t _columnNumber{0};
    TokenType _tokenType{TokenType::INVALID};
    std::string _tokenString{};
    std::optional<long> _numericValue{};
};

#endif //GAMEBOY_DISASSEMBLE_TOKEN_H
