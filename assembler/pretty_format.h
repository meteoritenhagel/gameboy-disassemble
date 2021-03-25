#ifndef GAMEBOY_DISASSEMBLE_PRETTY_FORMAT_H
#define GAMEBOY_DISASSEMBLE_PRETTY_FORMAT_H

#include "auxiliiary.h"

#include <iostream>
#include <string>
#include <sstream>

/**
 * Returns a string containing all token data in pretty form.
 * @param token token
 * @return pretty string representation of @p token
 */
std::string to_pretty_string(const Token& token) noexcept;

/**
 * Returns the @p lineNumber and the @p columnNumber in the following format: "lineNumber:columnNumber",
 * i.e. get_position_string(2,10) = "2:10"
 *
 * @param lineNumber line number
 * @param columnNumber column number
 * @return string containing the two numbers separated by ':'
 */
std::string get_position_string(const size_t lineNumber, const size_t columnNumber) noexcept;

/**
 * Returns a string representing a line which is split into two parts by '|', yielding "     left |    right",
 * i.e. separated_line(std::to_string(6), "ADD SP, 2") = "     6 |    ADD SP, 200"
 *
 * @param left string displayed on the left side
 * @param right string displayed on the right side
 * @return string containing the line
 */
std::string separated_line(const std::string &left, const std::string &right);

/**
 * Returns a string, which is essentially the source code contained in @p code
 * but with line numbers on the left side
 *
 * @param code source code to display
 * @return string containing the code with line numbers
 */
std::string to_string_with_line_numbers(const std::string &code);

/**
 * Returns the @p lineNumber-th line of @p code with the line number on the left side
 * @param code source code to display
 * @param lineNumber line to print of @p code
 * @return string containing the single line
 */
std::string to_string_single_line(const std::string &code, const size_t lineNumber);

/**
 * Returns the @p lineNumber-th line of @p code with the line number on the left side
 * and additionally a highlighted area under the printed line.
 *
 * @param code source code to display
 * @param lineNumber line to print of @p code
 * @param columnNumber starting position for the highlighting
 * @param highlightWidth width of highlighted area starting from columnNumber
 * @return string containing the highlighted line
 */
std::string to_string_line_and_highlight(const std::string &code, const size_t lineNumber, const size_t columnNumber, const size_t highlightWidth = 1);

#endif //GAMEBOY_DISASSEMBLE_PRETTY_FORMAT_H
