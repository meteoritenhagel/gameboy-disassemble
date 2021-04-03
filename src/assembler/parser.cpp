#include "parser.h"

#include <algorithm>

bool Parser::is_finished() const noexcept {
    return (_currentPosition >= _tokenVector.size());
}

size_t Parser::get_current_position() const noexcept {
    return _currentPosition;
}

void Parser::increment_position() {
    if (!is_finished())
    {
        ++_currentPosition;
    }
}

void Parser::reset() noexcept {
    _currentPosition = 0;
}

Token Parser::read_current() const {
    if (get_current_position() < _tokenVector.size()) {
        return _tokenVector.at(get_current_position());
    } else {
        return _tokenVector.at(_tokenVector.size() - 1);
    }
}

Token Parser::read_next() const {
    if (get_current_position() < _tokenVector.size() - 1) {
        return _tokenVector.at(get_current_position() + 1);
    } else {
        return _tokenVector.at(_tokenVector.size() - 1);
    }
}

Token Parser::fetch() {
    const Token currentToken = read_current();
    increment_position();
    return currentToken;
}

template<typename T>
Token Parser::fetch_and_expect(const T expectedTypes) {
    const Token tkn = fetch();
    expect_type(tkn, expectedTypes);
    return tkn;
}

Token Parser::fetch_and_expect(const std::vector<TokenType> expectedTypes) {
    const Token tkn = fetch();
    expect_type(tkn, expectedTypes);
    return tkn;
}

const std::string &Parser::get_code() const noexcept {
    return _code;
}

void Parser::throw_logic_error_and_highlight(const Token &token, const std::string &errorMessage) const {
    ::throw_exception_and_highlight(get_code(), token.get_line(), token.get_column(), errorMessage,
                                    token.get_string().size());
}

void Parser::throw_invalid_argument_and_highlight(const Token &token, const std::string &errorMessage) const {
    ::throw_exception_and_highlight<std::invalid_argument>(get_code(), token.get_line(), token.get_column(), errorMessage,
                                                           token.get_string().size());
}

long Parser::to_number(const Token &numToken) const {
    try {
        if (numToken.has_numeric_value()) {
            return numToken.get_numeric();
        } else {
            return _symbolicTable.at(numToken.get_string());
        }
    } catch (...) {
        throw_invalid_argument_and_highlight(numToken,
                                             "Parse error: Symbol " + numToken.get_string() +
                                             " could not be resolved");
    }
}

byte Parser::to_number_8_bit(const Token &numToken) const {
    const long num = to_number(numToken);
    if (!is_8_bit(num)) {
        throw_logic_error_and_highlight(numToken,
                                        "Parse error: Number " + std::to_string(num) + " is expected to be 8-bit");
    }
    return static_cast<byte>(num);
}

byte Parser::to_unsigned_number_8_bit(const Token &numToken) const {
    const long num = to_number(numToken);
    if (!is_unsigned_8_bit(num)) {
        throw_logic_error_and_highlight(numToken, "Parse error: Number " + std::to_string(num) +
                                                  " is expected to be unsigned 8-bit");
    }
    return static_cast<byte>(num);
}

byte Parser::to_signed_number_8_bit(const Token &numToken) const {
    const long num = to_number(numToken);
    if (!is_signed_8_bit(num)) {
        throw_logic_error_and_highlight(numToken, "Parse error: Number " + std::to_string(num) +
                                                  " is expected to be signed 8-bit");
    }
    return static_cast<byte>(num);
}

long Parser::to_number_16_bit(const Token &numToken) const {
    const long num = to_number(numToken);
    if (!((-32768 <= num && num <= 32767) || (0 <= num && num <= 65535))) {
        throw_logic_error_and_highlight(numToken,
                                        "Parse error: Number " + std::to_string(num) + " is expected to be 16-bit");
    }
    return num;
}

long Parser::to_unsigned_number_16_bit(const Token &numToken) const {
    const long num = to_number(numToken);
    if (!(is_signed_16_bit(num) || is_unsigned_16_bit(num))) {
        throw_logic_error_and_highlight(numToken,
                                        "Parse error: Number " + std::to_string(num) + " is expected to be 16-bit");
    }
    return num;
}

byte Parser::to_index(const Token &indexToken) const {
    const long num = to_number(indexToken);
    if (!is_index(num)) {
        throw_logic_error_and_highlight(indexToken, "Parse error: Found expression \"" + indexToken.get_string() +
                                                    "\" but expected index (0, ..., 7)");
    }
    return num;
}

FlagCondition Parser::to_flag_condition(const Token &conditionToken) const {
    FlagCondition flagCondition;
    const std::string str = conditionToken.get_string();

    try {
        flagCondition = ::to_flag_condition(str);
    } catch (...) {
        throw_logic_error_and_highlight(conditionToken, "Parse error: Found expression \"" + str +
                                        "\" but expected condition flag, i.e. Z, NZ, C, or NC");
    }
    return flagCondition;
}

Register Parser::to_register(const Token &token) const {
    const std::string str = token.get_string();
    if (!is_register(token)) {
        throw_logic_error_and_highlight(token, "Parse error: Found expression \"" + str +
                                               "\" but expected register");
    }
    return ::to_register(str);
}

Register8Bit Parser::to_register_8_bit(const Token &token) const {
    const std::string str = token.get_string();
    if (!is_register_8_bit(token)) {
        throw_logic_error_and_highlight(token,
                                        "Parse error: Found expression \"" + str + "\" but expected 8-bit register");
    }
    return ::to_register_8_bit(::to_register(str));
}

Register16Bit Parser::to_register_16_bit(const Token &token) const {
    const std::string str = token.get_string();
    if (!is_register_16_bit(token)) {
        throw_logic_error_and_highlight(token,
                                        "Parse error: Found expression \"" + str + "\" but expected 16-bit register");
    }
    return ::to_register_16_bit(::to_register(str));
}

Register Parser::to_register_expect(const Token &token, const Register &reg) const {
    const Register tokenRegister = to_register(token);

    if (tokenRegister != reg) {
        throw_logic_error_and_highlight(token, "Parse error: Found expression \"" + token.get_string() +
                                               "\" but expected register \"" + to_string(reg) + "\"");
    }
    return tokenRegister;
}

void Parser::expect_type(const Token &token, const TokenType expectedType) const {
    const TokenType currentType = token.get_token_type();
    if (currentType != expectedType) {
        throw_logic_error_and_highlight(token, "Parse error: Found \"" + to_string(currentType) +
                                               "\" but expected \"" + to_string(expectedType) + "\"");
    }
}

void Parser::expect_type(const Token &token, const std::vector<TokenType> expectedTypes) const {
    const TokenType currentType = token.get_token_type();
    if (std::find(expectedTypes.cbegin(), expectedTypes.cend(), currentType) == expectedTypes.cend()) // expected type not found
    {
        throw_logic_error_and_highlight(token, "Parse error: Found \"" + to_string(currentType) +
                                               "\" but expected \"" + to_string(expectedTypes) + "\"");
    }
}

void Parser::expect_string(const Token& token, const std::string &expectedString) const {
    const std::string currentString = token.get_string();
    if (currentString != expectedString) {
        throw_logic_error_and_highlight(token, "Parse error: Found \"" + currentString +
                                               "\" but expected \"" + to_string(expectedString) + "\"");
    }
}

void Parser::expect_string(const Token& token, const std::vector<std::string> &expectedStrings) const {
    const std::string currentString = token.get_string();
    if (std::find(expectedStrings.cbegin(), expectedStrings.cend(), currentString) == expectedStrings.cend()) // expected type not found
    {
        throw_logic_error_and_highlight(token, "Parse error: Found \"" + to_string(currentString) +
                                               "\" but expected \"" + to_string(expectedStrings) + "\"");
    }
}

void Parser::expect_end_of_context(const Token &token) const {
    const TokenType currentType = token.get_token_type();
    if (currentType != TokenType::END_OF_LINE && currentType != TokenType::END_OF_FILE) {
        throw_logic_error_and_highlight(token, "Parse error: Found \"" + to_string(currentType) +
                                               "\" but expected newline or end of file");
    }
}