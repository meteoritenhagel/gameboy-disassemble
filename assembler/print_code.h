#ifndef GAMEBOY_DISASSEMBLE_PRINT_CODE_H
#define GAMEBOY_DISASSEMBLE_PRINT_CODE_H

#include "auxiliiary.h"

#include <iostream>
#include <string>
#include <sstream>

std::string separated_line(const std::string &left, const std::string &right);

std::string to_string_with_line_numbers(const std::string &code);

std::string to_string_single_line(const std::string &code, const size_t lineNumber);

std::string to_string_line_and_highlight(const std::string &code, const size_t lineNumber, const size_t columnNumber, const size_t highlightWidth = 1);

//class Printer {
//public:
//    Printer(std::ostream& ostr = std::cout)
//    : _ostr(ostr) {}
//
//    void print(const std::string &message) const;
//
//private:
//    std::ostream& _ostr;
//};

#endif //GAMEBOY_DISASSEMBLE_PRINT_CODE_H
