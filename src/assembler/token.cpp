#include "token.h"

#include "pretty_format.h"
#include "auxiliary.h"

std::string to_string(const TokenType tokenType) {
    switch(tokenType)
    {
        case TokenType::IDENTIFIER:   return "IDENTIFIER";
        case TokenType::COMMA:        return "COMMA";
        case TokenType::NUMBER:       return "NUMBER";
        case TokenType::ADDRESS:      return "ADDRESS";
        case TokenType::END_OF_LINE:  return "END_OF_LINE";
        case TokenType::END_OF_FILE:  return "END_OF_FILE";
        case TokenType::GLOBAL_LABEL: return "GLOBAL_LABEL";
        case TokenType::LOCAL_LABEL:  return "LOCAL_LABEL";
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
    if (_tokenType == TokenType::NUMBER)
    {
        // convert string (either octal, decimal or hex to the right long number)
        try {
            _numericValue = (stol(_tokenString, nullptr, 0));
        } catch (...) {
            ::throw_exception_and_highlight("", get_line(), get_column(),
                                            "Lexical error: Could not convert '" + _tokenString + "' to number");
        }

    } else if (_tokenType == TokenType::ADDRESS) {
        // convert string without the enclosing brackets (e.g. "(0x1234)") to the right long number
        _numericValue = (stol(_tokenString.substr(1, _tokenString.size()-2), nullptr, 0));
    } else if (_tokenType == TokenType::SP_SHIFTED) { // cut away leading "SP"
        _numericValue = (stol(_tokenString.substr(2, _tokenString.size()-1), nullptr, 0));
    }
}

bool Token::has_numeric_value() const
{
    return _numericValue.has_value();
};

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

std::string Token::get_position_string() const {
    return ::get_position_string(get_line(), get_column());
}

bool Token::is_invalid() const {
    return get_token_type() == TokenType::INVALID;
}

