#ifndef GAMEBOY_DISASSEMBLE_AUXILIIARY_H
#define GAMEBOY_DISASSEMBLE_AUXILIIARY_H

#include "token.h"

/**
 * Checks whether a @p character is either '+' or '-'
 * @param character
 * @return
 */
bool issign(const char character) noexcept;

/**
 * Throws a logic error containing a string, in which an @p errorMessage is displayed and
 * a certain section of the code's line is highlighted.
 * @throws std::logic_error
 *
 * @param code Source code which is highlighted
 * @param lineNumber number of line in which the marking takes place
 * @param columnNumber column position in which the highlighting starts
 * @param errorMessage an error message printed before the highlighted line
 * @param highlightWidth the width of the highlighting starting from the position @p columnNumber
 */
void throw_logic_error_and_highlight(const std::string &code, const size_t lineNumber, const size_t columnNumber, const std::string &errorMessage, const size_t highlightWidth = 1);

/**
 * Checks whether a token can be converted to an 8-bit or 16-bit GameBoy register
 * @param token a token
 * @return true if @p token can be converted to a register
 */
bool is_register(const Token &token) noexcept;

/**
 * Checks whether a token can be converted to an 8-bit GameBoy register
 * @param token a token
 * @return true if @p token can be converted to an 8-bit register
 */
bool is_register_8_bit(const Token &token) noexcept;

/**
 * Checks whether a token can be converted to a 16-bit GameBoy register
 * @param token a token
 * @return true if @p token can be converted to a 16-bit register
 */
bool is_register_16_bit(const Token &token) noexcept;

#endif //GAMEBOY_DISASSEMBLE_AUXILIIARY_H
