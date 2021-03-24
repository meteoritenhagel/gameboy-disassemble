#ifndef GAMEBOY_DISASSEMBLE_AUXILIIARY_H
#define GAMEBOY_DISASSEMBLE_AUXILIIARY_H

#include "token.h"

// may throw
void throw_logic_error_and_highlight(const std::string& code, const size_t lineNumber, const size_t columnNumber, const std::string &errorMessage, const size_t highlightWidth = 1);

bool is_register(const Token &token);

bool is_register_8_bit(const Token &token);

bool is_register_16_bit(const Token &token);

#endif //GAMEBOY_DISASSEMBLE_AUXILIIARY_H
