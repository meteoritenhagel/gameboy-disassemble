#include "auxiliary.h"

#include <algorithm>

#include "../disassembler/disassemble.h"

std::string to_string(const std::string &str) {
    return str;
}

unsigned get_length(const InstructionPtr &instruction)
{
    return decode_length(instruction->opcode());
}

bool is_sign(const char character) noexcept {
    return (character == '+' || character == '-') ? true : false;
}

std::string to_upper(const std::string &str) {
    std::string tmp(str);
    std::transform(tmp.begin(), tmp.end(), tmp.begin(), [](const char c) { return toupper(c); } );
    return tmp;
}

std::string remove_last_character(const std::string &str) {
    if (str!="") {
        std::string tmp(str);
        tmp.pop_back();
        return tmp;
    } else {
        throw std::out_of_range("Error: Cannot remove last character from empty string.");
    }
}

bool is_flag_condition(const Token &token) noexcept {
    return is_flag_condition(token.get_string());
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