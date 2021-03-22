#ifndef GAMEBOY_DISASSEMBLE_TOKENIZER_H
#define GAMEBOY_DISASSEMBLE_TOKENIZER_H

#include "token.h"

#include <iostream>
#include <string>
#include <vector>

const char CHAR_EOF = 0x04;

bool issign(const char character);

class Tokenizer
{
public:
    Tokenizer(const std::string code, const size_t currentPosition = 0);

    bool is_out_of_range() const;

    Token get_next_token();

private:

    Token tokenize_identifier();

    Token tokenize_number();

    Token tokenize_address();


    void increment_position();

    void increment_linecount();

    char read_current() const;

    char read_next() const;

    char fetch();

    char fetch_and_expect(const char character);

    void ignore_whitespace();

    void ignore_until_end_of_line();

    size_t get_line() const;

    size_t get_column() const;

    std::string get_position_string();

    std::string _code;
    size_t _currentPosition{0};
    size_t _lineCount{0};
    size_t _linePosition{0};
};

#endif //GAMEBOY_DISASSEMBLE_TOKENIZER_H
