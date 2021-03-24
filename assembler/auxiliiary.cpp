#include "auxiliiary.h"
#include "print_code.h"

void throw_logic_error_and_highlight(const std::string& code, const size_t lineNumber, const size_t columnNumber, const std::string &errorMessage, const size_t highlightWidth)
{
    std::string extendedString = errorMessage + " at " + get_position_string(lineNumber, columnNumber) + '\n';
    if (!code.empty())
    {
        extendedString += to_string_line_and_highlight(code, lineNumber, columnNumber, highlightWidth);
    }
    throw std::logic_error(extendedString);
}

bool is_register(const Token &token) {
    return is_valid(to_register(token.get_string()));
}

bool is_register_8_bit(const Token &token) {
    return is_register_8_bit(to_register(token.get_string()));
}

bool is_register_16_bit(const Token &token) {
    return is_register_16_bit(to_register(token.get_string()));
}

std::string to_string(const TokenType tokenType) {
    switch(tokenType)
    {
        case TokenType::IDENTIFIER:  return "IDENTIFIER";
        case TokenType::COMMA:       return "COMMA";
        case TokenType::NUMBER:      return "NUMBER";
        case TokenType::ADDRESS:     return "ADDRESS";
        case TokenType::END_OF_LINE: return "END_OF_LINE";
        case TokenType::END_OF_FILE: return "END_OF_FILE";
        default: return "INVALID";
    }
}