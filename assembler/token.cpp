#include "token.h"

std::string to_string(const TokenType tokenType) {
    switch(tokenType)
    {
        case TokenType::IDENTIFIER: return "IDENTIFIER";
        case TokenType::COMMA: return "COMMA";
        case TokenType::NUMBER: return "NUMBER";
        case TokenType::ADDRESS: return "ADDRESS";
        default: return "INVALID";
    }
}

Token::Token(const size_t lineNumber, const size_t columnNumber, const TokenType tokenType,
             const std::string &tokenString)
        : _lineNumber(lineNumber),
          _columnNumber(columnNumber),
          _tokenType(tokenType),
          _tokenString(tokenString)
{
    if (_tokenType == TokenType::ADDRESS || _tokenType == TokenType::NUMBER)
    {
        // convert string (either octal, decimal or hex to the right long number)
        _numericValue = (stol(_tokenString, nullptr, 0));
    }
}

size_t Token::get_line() const {
    return _lineNumber;
}

size_t Token::get_column() const {
    return _columnNumber;
}

TokenType Token::get_token_type() const {
    return _tokenType;
}

std::string Token::get_string() const {
    return _tokenString;
}

long Token::get_numeric() const {
    return _numericValue.value();
}

void Token::print() const {
    std::cout << to_string(get_token_type()) << " " << get_line() << ":" << get_column() << " " << get_string();
    if (_numericValue.has_value())
    {
        std::cout << " " << get_numeric();
    }
    std::cout << '\n';
}

std::string Token::get_position_string() const {
    return "line: " + std::to_string(get_line()) + " / column: " + std::to_string(get_column());
}

