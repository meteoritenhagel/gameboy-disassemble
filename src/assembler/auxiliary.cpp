#include "auxiliary.h"
#include "../disassembler/disassemble.h"
#include "pretty_format.h"

std::string to_string(const std::string &str) {
    return str;
}

unsigned get_length(const InstructionPtr &instruction)
{
    return decode_length(instruction->opcode());
}

void throw_logic_error_and_highlight(const std::string& code, const size_t lineNumber, const size_t columnNumber, const std::string &errorMessage, const size_t highlightWidth)
{
    std::string extendedString = errorMessage + " at " + get_position_string(lineNumber, columnNumber) + '\n';
    if (!code.empty())
    {
        extendedString += to_string_line_and_highlight(code, lineNumber, columnNumber, highlightWidth);
    }
    throw std::logic_error(extendedString);
}

bool issign(const char character) noexcept {
    return (character == '+' || character == '-') ? true : false;
}

bool is_register(const Token &token) noexcept {
    return is_valid(to_register(token.get_string()));
}

bool is_register_8_bit(const Token &token) noexcept {
    return is_register_8_bit(to_register(token.get_string()));
}

bool is_register_16_bit(const Token &token) noexcept {
    return is_register_16_bit(to_register(token.get_string()));
}