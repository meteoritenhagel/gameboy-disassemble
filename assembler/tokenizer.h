#ifndef GAMEBOY_DISASSEMBLE_TOKENIZER_H
#define GAMEBOY_DISASSEMBLE_TOKENIZER_H

#include "print_code.h"
#include "token.h"

#include <iostream>
#include <string>
#include <vector>

const char CHAR_EOF = 0x04;

bool issign(const char character);

class Tokenizer
{
public:
    Tokenizer(const std::string &code, const size_t currentPosition = 0);

    bool is_finished() const;

    Token get_next_token();

    const std::string& get_code() const;

private:

    bool is_out_of_range() const;

    Token tokenize_identifier();

    Token tokenize_number();

    Token tokenize_address();

    Token tokenize_end_of_line();

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

    void throw_logic_error_and_highlight(const size_t lineNumber, const size_t columnNumber, const std::string& errorMessage);

    Token try_to_create_token(const size_t lineNumber, const size_t columnNumber, const TokenType tokenType, const std::string &tokenString);

    const std::string& _code{};
    size_t _currentPosition{0};
    size_t _lineCount{0};
    size_t _linePosition{0};
    bool _isFinished{false};
};

#endif //GAMEBOY_DISASSEMBLE_TOKENIZER_H
