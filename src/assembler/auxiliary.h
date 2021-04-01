#ifndef GAMEBOY_DISASSEMBLE_AUXILIIARY_H
#define GAMEBOY_DISASSEMBLE_AUXILIIARY_H

#include "../instructions/instructions.h"
#include "token.h"

/**
 * Returns the string. Used for the templated function below,
 * so that also std::strings can be used as T.
 * @param str string to return
 * @return @str
 */
std::string to_string(const std::string &str);

/**
 * Converts a vector of @p T into a string.
 * @tparam T type which supports the free function to_string(const T&).
 * @param vector vector to stringify
 * @return string composed of the individual elements of @p vector
 */
template<typename T>
std::string to_string(const std::vector<T> &vector);

/**
 * Returns the bytecode length in byte of a given @p instruction.
 * @param instruction instruction
 * @return bytecode length in bytes
 */
unsigned get_length(const InstructionPtr &instruction);

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
 * Checks whether a @p character is either '+' or '-'
 * @param character
 * @return
 */
bool issign(const char character) noexcept;

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

#include "auxiliary.hpp"
#endif //GAMEBOY_DISASSEMBLE_AUXILIIARY_H
