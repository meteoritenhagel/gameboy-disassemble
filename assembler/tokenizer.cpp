#include "tokenizer.h"
#include "print_code.h"

bool issign(const char character) {
    return (character == '+' || character == '-') ? true : false;
}

Tokenizer::Tokenizer(const std::string& code, const size_t currentPosition)
        : _code(code),
          _currentPosition(currentPosition)
{}

bool Tokenizer::is_finished() const {
    return _isFinished;
}

Token Tokenizer::get_next_token() {
    Token currentToken;
    ignore_whitespace();

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
        currentToken = Token(get_line(), get_column(), TokenType::COMMA, ",");
        increment_position();
    }
    else if (isdigit(read_current()) || issign(read_current()))
    {
        currentToken = tokenize_number();
    }
    else if (isalpha(read_current()))
    {
        currentToken = tokenize_identifier();
    }
    else if (read_current() == '\n')
    {
        currentToken = tokenize_end_of_line();
    }
    else if (read_current() == CHAR_EOF)
    {
        _isFinished = true;
        currentToken = Token(get_line(), get_column(), TokenType::END_OF_FILE, "[EOF]");
    }
    else
    {
        char currentChar = read_current();
        const std::string errorMessage = std::string("Lexical error: Unknown character '") + currentChar + "' at " + get_position_string();
        const size_t oldLineNumber = get_line();
        const size_t oldColumnNumber = get_column();
        increment_position();

        throw_logic_error_and_highlight(oldLineNumber, oldColumnNumber, errorMessage);
    }
    return currentToken;
}

const std::string& Tokenizer::get_code() const
{
    return _code;
}

bool Tokenizer::is_out_of_range() const {
    return (_currentPosition >= get_code().size());
}

Token Tokenizer::tokenize_identifier() {
    std::string str{};
    ignore_whitespace();
    const size_t columnPosition = get_column();

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
    const size_t columnPosition = get_column();

    // possible sign
    if (issign(read_current())) {
        str += fetch();
    }

    // hexadecimal number
    if (read_current() == '0' && (read_next() == 'x' || read_next() == 'X')) {
        str += fetch();
        str += fetch();

        while (isxdigit(read_current())) {
            str += fetch();
        }
    } else {
        while (isdigit(read_current())) {
            str += fetch();
        }
    }

    return try_to_create_token(get_line(), columnPosition, TokenType::NUMBER, str);
}

Token Tokenizer::tokenize_address() {
    std::string str{};
    ignore_whitespace();
    const size_t columnPosition = get_column();

    // address must start with '('
    str += fetch_and_expect('(');

    while (isalpha(read_current()))
    {
        str += fetch();
    }

    // address must end with ')'
    str += fetch_and_expect(')');

    return try_to_create_token(get_line(), columnPosition, TokenType::ADDRESS, str);
}

Token Tokenizer::tokenize_end_of_line() {

    const size_t initialLinePosition = get_line();
    const size_t initialColumnPosition = get_column();

    // remove all whitespace including '\n'
    while(read_current() == '\n')
    {
        increment_position();
        ignore_whitespace();
    }

    if (read_current() == CHAR_EOF) {
        _isFinished = true;
        return Token(initialLinePosition, initialColumnPosition, TokenType::END_OF_FILE, "[EOF]");
    } else {
        return Token(initialLinePosition, initialColumnPosition, TokenType::END_OF_LINE, "\\n");
    }

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
    return (is_out_of_range()) ? CHAR_EOF : get_code().at(_currentPosition);
}

char Tokenizer::read_next() const {
    return (is_out_of_range()) ? CHAR_EOF : get_code().at(_currentPosition+1);
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
        throw_logic_error_and_highlight(get_line(), get_column(), "Lexical error: Found '" + std::to_string(currentCharacter) + "', but expected '" + character);
    }
    return character;
}

void Tokenizer::ignore_whitespace() {
    while(isspace(read_current()) && (read_current() != '\n'))
    {
        increment_position();
    }
}

void Tokenizer::ignore_until_end_of_line() {
    while(read_current() != '\n')
    {
        fetch();
    }
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
    return ::get_position_string(get_line(), get_column());
}

void Tokenizer::throw_logic_error_and_highlight(const size_t lineNumber, const size_t columnNumber, const std::string &errorMessage) {
    ::throw_logic_error_and_highlight(get_code(), lineNumber, columnNumber, errorMessage);
}

Token Tokenizer::try_to_create_token(const size_t lineNumber, const size_t columnNumber, const TokenType tokenType, const std::string &tokenString) {
    try{
        return Token(lineNumber, columnNumber, tokenType, tokenString);
    } catch (...) {
        throw_logic_error_and_highlight(lineNumber, columnNumber, "Lexical error: Cannot convert expression \"" + tokenString + "\" to " + to_string(tokenType));
    }
}
