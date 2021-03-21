#ifndef GAMEBOY_DISASSEMBLE_ASSEMBLER_H
#define GAMEBOY_DISASSEMBLE_ASSEMBLER_H

#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

bool issign(const char character)
{
    return (character == '+' || character == '-') ? true : false;
}

enum class TokenType {
    INVALID,
    IDENTIFIER,
    COMMA,
    NUMBER,
    ADDRESS
};

std::string to_string(const TokenType tokenType)
{
    switch(tokenType)
    {
        case TokenType::IDENTIFIER: return "IDENTIFIER";
        case TokenType::COMMA: return "COMMA";
        case TokenType::NUMBER: return "NUMBER";
        case TokenType::ADDRESS: return "ADDRESS";
        default: return "INVALID";
    }
}

//
//enum class TokenizerState {
//    DETERMINE_STATE,
//
//};

class Token;

using VectorOfTokens = std::vector<Token>;

class Token{
public:

    Token() = default;

    Token(const size_t lineNumber, const size_t columnNumber, const TokenType tokenType, const std::string &tokenString)
    : _lineNumber(lineNumber),
      _columnNumber(columnNumber),
      _tokenType(tokenType),
      _tokenString(tokenString)
    {
        if (_tokenType == TokenType::ADDRESS || _tokenType == TokenType::NUMBER)
        {
            // convert string (either octal, decimal or hex to the right long number)
            _numericValue = (stol(_tokenString, nullptr, 0));
            check_range(_numericValue.value());
        }
    }

    size_t get_line() const
    {
        return _lineNumber;
    }

    size_t get_column() const
    {
        return _columnNumber;
    }

    TokenType get_token_type() const
    {
        return _tokenType;
    }

    void set_token_type(const TokenType tokenType)
    {
        _tokenType = tokenType;
    }

    std::string get_string() const
    {
        return _tokenString;
    }

    void append_to_string(const std::string &str)
    {
        _tokenString += str;
    }

    // if no numeric value is contained, std::bad_optional_access is thrown.
    long get_numeric() const
    {
        return _numericValue.value();
    }

    void print() const
    {
        std::cout << to_string(get_token_type()) << " " << get_line() << ":" << get_column() << " " << get_string();
        if (_numericValue.has_value())
        {
            std::cout << " " << get_numeric();
        }
        std::cout << '\n';
    }

private:
    std::string get_position_string()
    {
        return "line: " + std::to_string(get_line()) + " / column: " + std::to_string(get_column());
    }

    void check_range(const long num)
    {
        if (!((-32768 <= num && num <= 32767) || (0 <= num && num <= 65535)))
        {
            throw std::range_error("ERROR: Number " + std::to_string(num) + " is out of range: " + get_position_string());
        }
    }

    size_t _lineNumber{0};
    size_t _columnNumber{0};
    TokenType _tokenType{TokenType::INVALID};
    std::string _tokenString{};
    std::optional<long> _numericValue{};
};

class Tokenizer
{
public:
    Tokenizer(const std::string code, const size_t currentPosition = 0)
    : _code(code), _currentPosition(currentPosition)
    {}

    bool is_out_of_range() const
    {
        return (_currentPosition >= _code.size());
    }

    Token get_next_token()
    {
        Token currentToken;
        ignore_whitespace();

        if (read_current_char() == ';') // comment
        {
            ignore_until_end_of_line();
        }

        if (read_current_char() == '(')
        {
            if (isalpha(read_next_char()))
            {
                currentToken = tokenize_identifier();
            }
            else if (isdigit(read_next_char()))
            {
                currentToken = tokenize_address();
            }
        }
        else if (read_current_char() == ',')
        {
            increment_position();
            currentToken = Token(get_line(), get_column(), TokenType::COMMA, ",");
        }
        else if (isdigit(read_current_char()) || issign(read_current_char()))
        {
            currentToken = tokenize_number();
        }
        else if (isalpha(read_current_char()))
        {
            currentToken = tokenize_identifier();
        }
        else
        {
            throw std::logic_error(std::string("ERROR: Unknown character '") + read_current_char() + "' at " + get_position_string());
        }
        return currentToken;
    }

private:

    Token tokenize_identifier()
    {
        std::string str{};
        ignore_whitespace();
        size_t columnPosition = get_column();

        bool hasParentheses = false;

        // get token. Identifiers may start directly or with parenthesis

        if (read_current_char() == '(')
        {
            str += fetch_current_char();
            hasParentheses = true;
        }

        while (isalpha(read_current_char()))
        {
            str += fetch_current_char();
        }

        if (hasParentheses)
        {
            str += fetch_and_expect_character(')');
        }

        return Token(get_line(), columnPosition, TokenType::IDENTIFIER, str);
    }

    Token tokenize_number()
    {
        std::string str{};
        ignore_whitespace();
        size_t columnPosition = get_column();

        // possible sign
        if (issign(read_current_char()))
        {
            str += fetch_current_char();
        }

        // hexadecimal number
        if (read_current_char() == '0' && (read_next_char() == 'x' || read_next_char() == 'X'))
        {
            str += fetch_current_char();
            str += fetch_current_char();

            while (isxdigit(read_current_char()))
            {
                str += fetch_current_char();
            }
        }
        else
        {
            while (isdigit(read_current_char()))
            {
                str += fetch_current_char();
            }
        }

        return Token(get_line(), columnPosition, TokenType::NUMBER, str);
    }

    Token tokenize_address()
    {
        std::string str{};
        ignore_whitespace();
        size_t columnPosition = get_column();

        // address must start with '('
        str += fetch_and_expect_character('(');

        while (isalpha(read_current_char()))
        {
            str += fetch_current_char();
        }

        // address must end with ')'
        str += fetch_and_expect_character(')');


        return Token(get_line(), columnPosition, TokenType::ADDRESS, str);
    }


    void increment_position()
    {
        if (read_current_char() == '\n')
        {
            increment_linecount();
            ++_currentPosition;
            _linePosition = _currentPosition;
        }
        else
        {
            ++_currentPosition;
        }
    }

    void increment_linecount()
    {
        ++_lineCount;
    }

    char read_current_char() const
    {
        return _code.at(_currentPosition);
    }

    char read_next_char() const
    {
        return _code.at(_currentPosition+1);
    }

    char fetch_current_char()
    {
        char currentChar = read_current_char();
        increment_position();
        return currentChar;
    }

    char fetch_and_expect_character(const char character)
    {
        if (!(fetch_current_char() == character))
        {
            throw std::logic_error(std::string("ERROR: ") + character + " expected at " + get_position_string());
        }
        return character;
    }

    void ignore_whitespace()
    {
        while(isspace(read_current_char()))
        {
            increment_position();
        }
    }

    void ignore_until_end_of_line()
    {
        while(read_current_char() != '\n')
        {
            fetch_current_char();
        }
        increment_position();
    }

    size_t get_line() const
    {
        // add 1 since the uppermost line has index 1
        return _lineCount + 1;
    }

    size_t get_column() const
    {
        // add 1 since the leftmost character has index 1
        return _currentPosition - _linePosition+1;
    }

    std::string get_position_string()
    {
        return "line: " + std::to_string(get_line()) + " / column: " + std::to_string(get_column());
    }

    std::string _code;
    size_t _currentPosition{0};
    size_t _lineCount{0};
    size_t _linePosition{0};
};

#endif //GAMEBOY_DISASSEMBLE_ASSEMBLER_H
