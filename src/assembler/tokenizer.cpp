#include "tokenizer.h"
#include "pretty_format.h"

Tokenizer::Tokenizer(const std::string& code, const size_t startingPosition)
        : _code(code),
          _currentPosition(startingPosition)
{}

TokenVector Tokenizer::tokenize() {
    TokenVector tokenVector{};
    Token currentToken{};

    do
    {
        currentToken = get_next_token();
        tokenVector.push_back(currentToken);
    }
    while (currentToken.get_token_type() != TokenType::END_OF_FILE);

    return tokenVector;
}

const std::string& Tokenizer::get_code() const noexcept{
    return _code;
}

Token Tokenizer::get_next_token() {
    Token currentToken;
    ignore_whitespace();

    if (read_current() == ';') // comment
    {
        ignore_until_end_of_line();
    }

    if (read_current() == '(' || read_current() == '[')
    {
        if (isalpha(read_next()))
        {
            currentToken = tokenize_identifier_or_global_label();
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
    else if (isdigit(read_current()) || is_sign(read_current()))
    {
        currentToken = tokenize_number();
    }
    else if (isalpha(read_current()))
    {
        currentToken = tokenize_identifier_or_global_label();
    }
    else if (read_current() == '.')
    {
        currentToken = tokenize_local_label();
    }
    else if (read_current() == '\n')
    {
        currentToken = tokenize_end_of_line();
    }
    else if (read_current() == CHAR_EOF)
    {
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

bool Tokenizer::is_out_of_range() const noexcept {
    return (_currentPosition >= get_code().size());
}

Token Tokenizer::tokenize_identifier_or_global_label() {
    std::string str{};
    Token currentToken;
    const size_t columnPosition = get_column();

    bool hasParentheses = false;
    bool hasBrackets = false;

    // get token. Identifiers may start directly or with parenthesis / bracket

    if (read_current() == '(') {
        str += fetch();
        hasParentheses = true;
    } else if (read_current() == '[') {
        hasBrackets = true;
    }

    while (isalnum(read_current())) {
        str += fetch();
    }

    // assert that the correct closing brace is present
    if (hasParentheses) {
        // may have + or - before closing parenthesis
        if (is_sign(read_current())) {
            str += fetch();
        }
        str += fetch_and_expect(')');
    } else if (hasBrackets) {
        // may have + or - before closing parenthesis
        if (is_sign(read_current())) {
            str += fetch();
        }
        str += fetch_and_expect(']');
    }

    if (read_current() == ':') { // is GLOBAL_LABEL
        str += ':';
        currentToken = Token(get_line(), columnPosition, TokenType::GLOBAL_LABEL, str);
        increment_position();
    } else { // is IDENTIFIER
        currentToken = Token(get_line(), columnPosition, TokenType::IDENTIFIER, str);
    }

    return currentToken;
}

Token Tokenizer::tokenize_number() {
    std::string str{};
    const size_t columnPosition = get_column();

    // possible sign
    if (is_sign(read_current())) {
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
    const size_t columnPosition = get_column();

    // address must start with '('
    str += fetch_and_expect('(');

    while (isalnum(read_current()))
    {
        str += fetch();
    }

    // address must end with ')'
    str += fetch_and_expect(')');

    return try_to_create_token(get_line(), columnPosition, TokenType::ADDRESS, str);
}

Token Tokenizer::tokenize_local_label() {
    std::string str{};
    const size_t columnPosition = get_column();

    // local label must start with '.'
    str += fetch_and_expect('.');

    while (isalnum(read_current()))
    {
        str += fetch();
    }

    return Token(get_line(), columnPosition, TokenType::LOCAL_LABEL, str);
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
        return Token(initialLinePosition, initialColumnPosition, TokenType::END_OF_FILE, "[EOF]");
    } else {
        return Token(initialLinePosition, initialColumnPosition, TokenType::END_OF_LINE, "\\n");
    }

}

void Tokenizer::increment_position() noexcept {
    if (read_current() == '\n')
    {
        increment_linecount();
        _currentLineStart = _currentPosition+1;
    }

    if (!is_out_of_range())
    {
        ++_currentPosition;
    }
}

void Tokenizer::increment_linecount() noexcept {
    ++_lineCount;
}

char Tokenizer::read_current() const noexcept {
    return (is_out_of_range()) ? CHAR_EOF : get_code().at(_currentPosition);
}

char Tokenizer::read_next() const noexcept {
    return (is_out_of_range()) ? CHAR_EOF : get_code().at(_currentPosition+1);
}

char Tokenizer::fetch() noexcept {
    char currentChar = read_current();
    increment_position();
    return currentChar;
}

char Tokenizer::fetch_and_expect(const char expectedCharacter) {
    const char currentCharacter = fetch();
    if (currentCharacter != expectedCharacter)
    {
        throw_logic_error_and_highlight(get_line(), get_column(), "Lexical error: Found '" + std::to_string(currentCharacter) + "', but expected '" + expectedCharacter);
    }
    return expectedCharacter;
}

void Tokenizer::ignore_whitespace() noexcept {
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
    return _currentPosition - _currentLineStart+1;
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
