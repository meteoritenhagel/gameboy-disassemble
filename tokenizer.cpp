#include "tokenizer.h"

bool issign(const char character) {
    return (character == '+' || character == '-') ? true : false;
}

Tokenizer::Tokenizer(const std::string code, const size_t currentPosition)
        : _code(code), _currentPosition(currentPosition)
{}

bool Tokenizer::is_out_of_range() const {
    return (_currentPosition >= _code.size());
}

Token Tokenizer::get_next_token() {
    Token currentToken;
    ignore_whitespace();

    if (read_current() == CHAR_EOF)
    {
        throw std::out_of_range("Lexical error: End of file reached.");
    }

    if (read_current() == ';') // comment
    {
        ignore_until_end_of_line();
    }

    if (read_current() == '(')
    {
        if (isalpha(read_next()))
        {
            currentToken = tokenize_identifier();
        }
        else if (isdigit(read_next()))
        {
            currentToken = tokenize_address();
        }
    }
    else if (read_current() == ',')
    {
        increment_position();
        currentToken = Token(get_line(), get_column(), TokenType::COMMA, ",");
    }
    else if (isdigit(read_current()) || issign(read_current()))
    {
        currentToken = tokenize_number();
    }
    else if (isalpha(read_current()))
    {
        currentToken = tokenize_identifier();
    }
    else
    {
        char currentChar = read_current();
        increment_position();
        throw std::logic_error(std::string("Lexical error: Unknown character '") + currentChar + "' at " + get_position_string());
    }
    return currentToken;
}

Token Tokenizer::tokenize_identifier() {
    std::string str{};
    ignore_whitespace();
    size_t columnPosition = get_column();

    bool hasParentheses = false;

    // get token. Identifiers may start directly or with parenthesis

    if (read_current() == '(')
    {
        str += fetch();
        hasParentheses = true;
    }

    while (isalpha(read_current()))
    {
        str += fetch();
    }

    if (hasParentheses)
    {
        // may have + or - before closing parenthesis
        if (issign(read_current()))
        {
            str += fetch();
        }
        str += fetch_and_expect(')');
    }

    return Token(get_line(), columnPosition, TokenType::IDENTIFIER, str);
}

Token Tokenizer::tokenize_number() {
    std::string str{};
    ignore_whitespace();
    size_t columnPosition = get_column();

    // possible sign
    if (issign(read_current()))
    {
        str += fetch();
    }

    // hexadecimal number
    if (read_current() == '0' && (read_next() == 'x' || read_next() == 'X'))
    {
        str += fetch();
        str += fetch();

        while (isxdigit(read_current()))
        {
            str += fetch();
        }
    }
    else
    {
        while (isdigit(read_current()))
        {
            str += fetch();
        }
    }

    return Token(get_line(), columnPosition, TokenType::NUMBER, str);
}

Token Tokenizer::tokenize_address() {
    std::string str{};
    ignore_whitespace();
    size_t columnPosition = get_column();

    // address must start with '('
    str += fetch_and_expect('(');

    while (isalpha(read_current()))
    {
        str += fetch();
    }

    // address must end with ')'
    str += fetch_and_expect(')');


    return Token(get_line(), columnPosition, TokenType::ADDRESS, str);
}

void Tokenizer::increment_position() {
    if (read_current() == '\n')
    {
        increment_linecount();
        _linePosition = _currentPosition+1;
    }

    if (!is_out_of_range())
    {
        ++_currentPosition;
    }
}

void Tokenizer::increment_linecount() {
    ++_lineCount;
}

char Tokenizer::read_current() const {
    return (is_out_of_range()) ? CHAR_EOF : _code.at(_currentPosition);
}

char Tokenizer::read_next() const {
    return (is_out_of_range()) ? CHAR_EOF : _code.at(_currentPosition+1);
}

char Tokenizer::fetch() {
    char currentChar = read_current();
    increment_position();
    return currentChar;
}

char Tokenizer::fetch_and_expect(const char character) {
    const char currentCharacter = fetch();
    if (currentCharacter != character)
    {
        throw std::logic_error(std::string("Lexical error: Found '") + currentCharacter + "'. Expected '" + character + " at " + get_position_string());
    }
    return character;
}

void Tokenizer::ignore_whitespace() {
    while(isspace(read_current()))
    {
        increment_position();
    }
}

void Tokenizer::ignore_until_end_of_line() {
    while(read_current() != '\n')
    {
        fetch();
    }
    increment_position();
}

size_t Tokenizer::get_line() const {
    // add 1 since the uppermost line has index 1
    return _lineCount + 1;
}

size_t Tokenizer::get_column() const {
    // add 1 since the leftmost character has index 1
    return _currentPosition - _linePosition+1;
}

std::string Tokenizer::get_position_string() {
    return std::to_string(get_line()) + ":" + std::to_string(get_column());
}
